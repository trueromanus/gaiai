#include "pongminigame.h"

PongMiniGame::PongMiniGame() {
    auto seedValue = QRandomGenerator::system()->generate64();
    m_randomGenerator = QRandomGenerator(seedValue);
}

void PongMiniGame::setActive(bool active) noexcept
{
    if (m_active == active) return;

    m_active = active;
    emit activeChanged();

    if (m_active && m_activeTimer == -1) {
        m_activeTimer = startTimer(1000 / 80, Qt::CoarseTimer);
    }
}

void PongMiniGame::setInputHandler(const InputHandler *inputHandler) noexcept
{
    if (m_inputHandler == inputHandler) return;

    m_inputHandler = const_cast<InputHandler *>(inputHandler);
    emit inputHandlerChanged();
}

QString PongMiniGame::ballColor() const noexcept
{
    switch (m_ballMode) {
        case 1: return "#ff3333";
        case 2: return "#4d4dff";
        case 3: return "#404040";
        case 4: return "#808000";
        default: return "#00cc00";
    }
}

QString PongMiniGame::leftPaddleColor() const noexcept
{
    if (m_leftPaddleFreezed > 0) return "#4d4dff";

    return "#006600";
}

QString PongMiniGame::rightPaddleColor() const noexcept
{
    if (m_rightPaddleFreezed > 0) return "#4d4dff";

    return "#006600";
}

void PongMiniGame::setGameMode(int gameMode) noexcept
{
    if (m_gameMode == gameMode) return;

    m_gameMode = gameMode;
    emit gameModeChanged();
}

void PongMiniGame::setGameControlMode(int gameControlMode) noexcept
{
    if (m_gameControlMode == gameControlMode) return;

    m_gameControlMode = gameControlMode;
    emit gameControlModeChanged();
}

void PongMiniGame::setBonusMode(int bonusMode) noexcept
{
    if (m_bonusMode == bonusMode) return;

    m_bonusMode = bonusMode;
    emit bonusModeChanged();
}

void PongMiniGame::setOverrideBonusMode(int overrideBonusMode)
{
    if (m_overrideBonusMode == overrideBonusMode) return;

    m_overrideBonusMode = overrideBonusMode;
    emit overrideBonusModeChanged();
}

void PongMiniGame::moveBallToCenter()
{
    auto centerX = width() / 2;
    auto centerY = height() / 2;

    if (m_ball != nullptr) {
        centerX -= m_ball->width() / 2;
        centerY -= m_ball->height() / 2;
    }

    m_ballPosition.setX(centerX);
    m_ballPosition.setY(centerY);

    emit ballPositionChanged();
}

void PongMiniGame::leftPaddleMove(int direction, bool dodge)
{
    if (m_leftPaddleFreezed > 0) return;

    auto currentY = m_leftPaddle->y();
    switch (direction) {
        case 0: // up
            m_leftPaddle->setY(moveUp(currentY, m_topWall->y(), dodge));
            break;
        case 1: // down
            m_leftPaddle->setY(moveDown(currentY, m_leftPaddle->height(), m_bottomWall->y() + m_bottomWall->height(), dodge));
            break;
    }
}

void PongMiniGame::rightPaddleMove(int direction, bool dodge)
{
    if (m_rightPaddleFreezed > 0) return;

    auto currentY = m_rightPaddle->y();

    switch (direction) {
        case 0: // up
            m_rightPaddle->setY(moveUp(currentY, m_topWall->y(), dodge));
            break;
        case 1: // down
            m_rightPaddle->setY(moveDown(currentY, m_rightPaddle->height(), m_bottomWall->y() + m_bottomWall->height(), dodge));
            break;
    }
}

void PongMiniGame::resetGame()
{
    setActive(false);

    moveBallToCenter();

    auto centerHeight = (m_leftWall->height() / 2) - 20;

    m_leftPaddle->setHeight(40);
    m_leftPaddle->setY(centerHeight);

    m_rightPaddle->setHeight(40);
    m_rightPaddle->setY(centerHeight);

    m_leftScore = false;
    m_rightScore = false;

    emit leftScoreChanged();
    emit rightScoreChanged();
    setActive(true);
}

int PongMiniGame::moveUp(int currentY, int limit, bool dodge)
{
    auto step = dodge ? m_dodgeMoveStep : m_moveStep;
    auto result = currentY - step;
    return result < limit ? limit : result;
}

int PongMiniGame::moveDown(int currentY, int currentYDown, int limit, bool dodge)
{
    auto step = dodge ? m_dodgeMoveStep : m_moveStep;
    auto result = currentY + step;
    return result > (limit - currentYDown) ? limit - currentYDown : result;
}

void PongMiniGame::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (m_active == false) {
        handleInput();
        return;
    }

    if (m_collideTimer == 0) {
        bool isCollided = ballIsCollidingPaddles();
        if (!isCollided) isCollided = ballIsCollidingWalls();
        if (isCollided) m_collideTimer = 2;
    } else {
        m_collideTimer -= 1;
    }

    auto dx = m_ballDirection.x();
    auto dy = m_ballDirection.y();

    if (dx != 0) m_ballPosition.setX(m_ballPosition.x() + dx);
    if (dy != 0) m_ballPosition.setY(m_ballPosition.y() + dy);

    emit ballPositionChanged();

    handleInput();
    handleCpus();

    m_ballTimer += 1;
    if (m_ballTimer > 1600) { // 20 seconds for change mode
        m_ballTimer = 0;
        m_ballMode = randomBallEnabled();
        if (m_overrideBonusMode > 0) { // if need override bonus we force enable only required mode
            m_ballMode = m_overrideBonusMode;
        }
        emit ballColorChanged();
    }

    if (m_ballTimer > 640 && m_ballMode > 0) { // 8 seconds reset
        m_ballMode = 0;
        emit ballColorChanged();
    }

    if (m_leftPaddleFreezed > 0) {
        m_leftPaddleFreezed -= 1;
        if (m_leftPaddleFreezed == 0) emit leftPaddleColorChanged();
    }
    if (m_rightPaddleFreezed > 0) {
        m_rightPaddleFreezed -= 1;
        if (m_rightPaddleFreezed == 0) emit rightPaddleColorChanged();
    }

    handlePaddleHeight(m_leftPaddle, true);
    handlePaddleHeight(m_rightPaddle, false);
}

void PongMiniGame::componentComplete()
{
    QQuickItem::componentComplete();
    if(!isComponentComplete()) return;

    auto childrens = childItems();
    foreach (auto item, childrens) {
        auto gameEntity = qobject_cast<GameEntity*>(item);
        if (gameEntity == nullptr) continue;

        auto identifier = gameEntity->identifier();
        m_childrens.insert(identifier, gameEntity);
    }

    if (m_childrens.contains("ball")) m_ball = m_childrens.value("ball");
    if (m_childrens.contains("leftPaddle")) m_leftPaddle = m_childrens.value("leftPaddle");
    if (m_childrens.contains("rightPaddle")) m_rightPaddle = m_childrens.value("rightPaddle");

    if (m_childrens.contains("topWall")) m_topWall = m_childrens.value("topWall");
    if (m_childrens.contains("leftWall")) m_leftWall = m_childrens.value("leftWall");
    if (m_childrens.contains("rightWall")) m_rightWall = m_childrens.value("rightWall");
    if (m_childrens.contains("bottomWall")) m_bottomWall = m_childrens.value("bottomWall");

    m_leftCpuState.paddle = m_leftPaddle;
    m_leftCpuState.moveTimerGoodEnable = false;
    m_rightCpuState.paddle = m_rightPaddle;
}

bool PongMiniGame::ballIsCollidingWalls()
{
    auto ballX = m_ball->x();
    auto ballXRight = m_ball->x() + m_ball->width();
    auto ballY = m_ball->y();
    auto ballBottomY = ballY + m_ball->height();
    auto directionX = m_ballDirection.x();
    auto directionY = m_ballDirection.y();

    auto topContact = false;
    auto bottomContact = false;
    auto leftContact = false;
    auto rightContact = false;
    if (ballY <= m_topWall->y()) topContact = true;
    if (ballX <= m_leftWall->x()) leftContact = true;
    if (ballBottomY >= m_bottomWall->y()) bottomContact = true;
    if (ballXRight >= m_rightWall->x()) rightContact = true;

    if (topContact || bottomContact) m_ballDirection.setY(directionY > 0 ? -2 : 2);
    if (leftContact || rightContact) m_ballDirection.setX(directionX > 0 ? -3 : 3);
    if (leftContact) handleLeftWallCollision();
    if (rightContact) handleRightWallCollision();

    return topContact || leftContact || bottomContact || rightContact;
}

bool PongMiniGame::ballIsCollidingPaddles()
{
    if (IsPaddleCollision(m_leftPaddle, true)) {
        handlePaddleCollision(true);
        return true;
    }

    if (IsPaddleCollision(m_rightPaddle, false)) {
        handlePaddleCollision(false);
        return true;
    }

    return false;
}

bool PongMiniGame::IsPaddleCollision(const GameEntity *paddle, bool isLeft)
{
    auto ballX = isLeft ? m_ball->x() : m_ball->x() + m_ball->width();
    auto ballY = m_ball->y();
    auto ballBottomY = ballY + m_ball->height();

    auto leftX = paddle->x();
    auto leftY = paddle->y();
    auto leftXEnd = leftX + paddle->width();
    auto leftYEnd = leftY + paddle->height();

    auto leftEdgeInside = ballX >= leftX && ballX <= leftXEnd;
    auto leftTopContact = false;
    auto leftBottomContact = false;
    if (leftEdgeInside && (ballBottomY >= leftY && ballBottomY < leftYEnd)) leftTopContact = true;
    if (leftEdgeInside && (ballY >= leftY && ballY < leftYEnd)) leftBottomContact = true;

    if (leftTopContact || leftBottomContact) {
        m_ballDirection.setX(isLeft ? 3 : -3);
    }
    if (leftTopContact && (ballBottomY - leftY) < 4) m_ballDirection.setY(-2);
    if (leftBottomContact && (ballY - leftY) < 4) m_ballDirection.setY(2);

    return leftTopContact || leftBottomContact;
}

void PongMiniGame::handleLeftWallCollision()
{
    switch (m_ballMode) {
        case 0: // default
        case 4: // long paddle
            incrementLeftScore();
            break;
        case 2:  // ice
            if (m_leftPaddleFreezed > 0) incrementLeftScore();
            break;
    }
}

void PongMiniGame::handleRightWallCollision()
{
    switch (m_ballMode) {
        case 0: // default
        case 4: // long paddle
            incrementRightScore();
            break;
        case 2:  // ice
            if (m_rightPaddleFreezed > 0) incrementRightScore();
            break;
    }
}

void PongMiniGame::handlePaddleCollision(bool isLeft)
{
    if (m_ballMode == 1) { // hot
        if (isLeft) {
            incrementLeftScore();
        } else {
            incrementRightScore();
        }
    }
    if (m_ballMode == 2) { // ice
        if (isLeft) {
            m_leftPaddleFreezed = 640;
            emit leftPaddleColorChanged();
        } else {
            m_rightPaddleFreezed = 640;
            emit rightPaddleColorChanged();
        }
    }
    if (m_ballMode == 3) {
        if (isLeft) {
            decrementLeftScore();
        } else {
            decrementRightScore();
        }
    }
    if (m_ballMode == 4) { // long paddle
        if (isLeft && m_leftPaddle->height() == m_defaultPaddleLength) {
            m_leftPaddle->setHeight(m_defaultPaddleLength + 1);
        }

        if (!isLeft && m_rightPaddle->height() == m_defaultPaddleLength) {
            m_rightPaddle->setHeight(m_defaultPaddleLength + 1);
        }
    }
}

void PongMiniGame::handleWinner()
{
    switch (m_gameMode) {
        case 0: // classic
            if (m_leftScore >= 20) emit weHaveWinner(true, m_leftScore, m_rightScore);
            if (m_rightScore >= 20) emit weHaveWinner(false, m_leftScore, m_rightScore);
            break;
        case 1: // difference 10
            if (m_leftScore < m_rightScore && m_rightScore - m_leftScore >= 10) emit weHaveWinner(true, m_leftScore, m_rightScore);
            if (m_leftScore > m_rightScore && m_leftScore - m_rightScore >= 10) emit weHaveWinner(false, m_leftScore, m_rightScore);
            break;
        case 2: // difference 20
            if (m_leftScore < m_rightScore && m_rightScore - m_leftScore >= 20) emit weHaveWinner(true, m_leftScore, m_rightScore);
            if (m_leftScore > m_rightScore && m_leftScore - m_rightScore >= 20) emit weHaveWinner(false, m_leftScore, m_rightScore);
            break;
        case 3: // 30 and 30
            if (m_leftScore == 30 && m_rightScore == 30) emit weHaveWinner(true, m_leftScore, m_rightScore);
            break;
    }

}

void PongMiniGame::incrementLeftScore()
{
    m_leftScore += 1;
    emit leftScoreChanged();

    handleWinner();
}

void PongMiniGame::decrementLeftScore()
{
    m_leftScore -= 1;
    emit leftScoreChanged();

    handleWinner();
}

void PongMiniGame::incrementRightScore()
{
    m_rightScore += 1;
    emit rightScoreChanged();

    handleWinner();
}

void PongMiniGame::decrementRightScore()
{
    m_rightScore -= 1;
    emit rightScoreChanged();

    handleWinner();
}

int PongMiniGame::randomBallEnabled()
{
    auto value = m_randomGenerator.bounded(1, 5);
    int mode = 0;
    switch (value) {
        case 2:
            mode = 1;
            break;
        case 3:
            mode = 2;
            break;
    }

    if (mode == 0) return 0;

    if (m_bonusMode == 3) {
        if (m_ballModeIterator) {
            switch (mode) {
                case 1: return 3; // remove 2x score
                case 2: return 4; // long paddle
            }
        } else {
            switch (mode) {
                case 1: return 1; // hot
                case 2: return 2; // ice
            }
        }

        m_ballModeIterator = !m_ballModeIterator;
    }
    if (m_bonusMode == 1) {
        switch (mode) {
            case 1: return 3; // remove 2x score
            case 2: return 4; // long paddle
        }
    }
    if (m_bonusMode == 2) {
        switch (mode) {
            case 1: return 1; // hot
            case 2: return 2; // ice
        }
    }

    return 0;
}

void PongMiniGame::handlePaddleHeight(GameEntity* paddle, bool isLeft)
{
    auto height = static_cast<int>(paddle->height());
    if (height > m_defaultPaddleLength && height < m_longPaddleLength && m_ballMode == 4) {
        height += 1;
        paddle->setHeight(height);

        if (height == m_longPaddleLength) {
            if (isLeft) {
                m_leftPaddleDownTimer = 500;
            } else {
                m_rightPaddleDownTimer = 500;
            }
        }
        return;
    }

    if (height == m_longPaddleLength) {
        if (isLeft && m_leftPaddleDownTimer > 0) m_leftPaddleDownTimer -= 1;
        if (!isLeft && m_rightPaddleDownTimer > 0) m_rightPaddleDownTimer -= 1;
    }

    if (height > m_defaultPaddleLength && ((isLeft && m_leftPaddleDownTimer == 0) || (!isLeft && m_rightPaddleDownTimer == 0))) {
        paddle->setHeight(height - 1);
    }
}

void PongMiniGame::handleInput()
{
    if (m_active == true) {

        if (m_gameControlMode == 0 || m_gameControlMode == 1) {
            auto isLeftDodged = m_inputHandler->isKeyPressed("f");
            if (m_inputHandler->isKeyPressed("w")) leftPaddleMove(0, isLeftDodged);
            if (m_inputHandler->isKeyPressed("s")) leftPaddleMove(1, isLeftDodged);

        }
        if (m_gameControlMode == 0 || m_gameControlMode == 2) {
            auto isRightDodged = m_inputHandler->isKeyPressed("}");
            if (m_inputHandler->isKeyPressed("up")) rightPaddleMove(0, isRightDodged);
            if (m_inputHandler->isKeyPressed("down")) rightPaddleMove(1, isRightDodged);
        }
        if (m_inputHandler->isKeyPressed("r")) resetGame();
        if (m_inputHandler->isKeyPressed("b")) emit backToMainMenu();

    }

    if (m_inputHandler->isKeyPressed("p") && !m_pausePressed) {
        m_pausePressed = true;
    }
    if (!m_inputHandler->isKeyPressed("p") && m_pausePressed) {
        m_pausePressed = false;
        if (m_active) {
            setActive(false);
        } else {
            setActive(true);
        }
    }
}

void PongMiniGame::handleCpus()
{
    if (m_gameControlMode == 0) return;

    if (m_ballDirection.x() > 0 && (m_gameControlMode == 1 || m_gameControlMode == 3)) { // right paddle or ball
        handleCpuPaddle(m_rightCpuState);
    }
    if (m_ballDirection.x() < 0 && (m_gameControlMode == 2 || m_gameControlMode == 3)) { // left paddle or ball
        handleCpuPaddle(m_leftCpuState);
    }
}

void PongMiniGame::handleCpuPaddle(CpuState &state)
{
    state.moveTimer++;
    auto limit = state.moveTimerGoodEnable ? state.moveTimerGood : state.moveTimerMiddle;
    if (state.moveTimer >= limit) {
        state.moveTimer = 0;
    } else {
        return;
    }

    state.moveTimerChangedGoodMiddle++;
    if (state.moveTimerChangedGoodMiddle >= state.moveTimerChangedGoodMiddleMaximum) {
        state.moveTimerChangedGoodMiddle = 0;
        state.moveTimerGoodEnable = !state.moveTimerGoodEnable;
    }

    auto currentPosition = state.paddle->y();
    auto currentHeight = state.paddle->height();
    auto center = currentPosition + (currentHeight / 2);

    if (m_ball->y() > center) {
        state.paddle->setY(moveDown(currentPosition, currentHeight, m_bottomWall->y() + m_bottomWall->height(), false));
    }
    if (m_ball->y() < center) {
        state.paddle->setY(moveUp(currentPosition, m_topWall->y(), false));
    }
}
