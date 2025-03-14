#ifndef PONGMINIGAME_H
#define PONGMINIGAME_H

#include <QQuickItem>
#include <QMap>
#include <QRandomGenerator>
#include "gameentity.h"
#include "inputhandler.h"

class PongMiniGame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint ballPosition READ ballPosition NOTIFY ballPositionChanged FINAL)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged FINAL)
    Q_PROPERTY(InputHandler* inputHandler READ inputHandler WRITE setInputHandler NOTIFY inputHandlerChanged FINAL)
    Q_PROPERTY(int leftScore READ leftScore NOTIFY leftScoreChanged FINAL)
    Q_PROPERTY(int rightScore READ rightScore NOTIFY rightScoreChanged FINAL)
    Q_PROPERTY(QString ballColor READ ballColor NOTIFY ballColorChanged FINAL)
    Q_PROPERTY(QString leftPaddleColor READ leftPaddleColor NOTIFY leftPaddleColorChanged FINAL)
    Q_PROPERTY(QString rightPaddleColor READ rightPaddleColor NOTIFY rightPaddleColorChanged FINAL)
    Q_PROPERTY(int gameMode READ gameMode WRITE setGameMode NOTIFY gameModeChanged FINAL)
    Q_PROPERTY(int gameControlMode READ gameControlMode WRITE setGameControlMode NOTIFY gameControlModeChanged FINAL)
    Q_PROPERTY(int bonusMode READ bonusMode WRITE setBonusMode NOTIFY bonusModeChanged FINAL)
    QML_ELEMENT

private:
    QPoint m_ballPosition { QPoint(0, 0) };
    QPoint m_ballDirection { QPoint(3, 2) };
    bool m_active { false };
    int m_activeTimer { -1 };
    int m_moveStep { 6 };
    int m_dodgeMoveStep { 20 };
    int m_defaultPaddleLength { 40 };
    int m_longPaddleLength { 68 };
    bool m_pausePressed { false };
    QMap<QString, GameEntity*> m_childrens { QMap<QString, GameEntity*>() };
    GameEntity* m_ball { nullptr };
    GameEntity* m_leftPaddle { nullptr };
    GameEntity* m_rightPaddle { nullptr };
    GameEntity* m_leftWall { nullptr };
    GameEntity* m_topWall { nullptr };
    GameEntity* m_rightWall { nullptr };
    GameEntity* m_bottomWall { nullptr };
    InputHandler* m_inputHandler { nullptr };
    int m_leftScore { 0 };
    int m_rightScore { 0 };
    int m_ballMode { 0 };
    int m_ballTimer { 0 };
    int m_leftPaddleDownTimer { 0 };
    int m_rightPaddleDownTimer { 0 };
    bool m_ballModeIterator { false };
    int m_leftPaddleFreezed { 0 };
    int m_rightPaddleFreezed { 0 };
    int m_collideTimer { 0 };
    int m_gameMode { 0 };
    int m_gameControlMode { 0 };
    int m_bonusMode { 0 };

public:
    PongMiniGame();

    QPoint ballPosition() const noexcept { return m_ballPosition; }

    bool active() const noexcept { return m_active; }
    void setActive(bool active) noexcept;

    InputHandler* inputHandler() const noexcept { return m_inputHandler; }
    void setInputHandler(const InputHandler* inputHandler) noexcept;

    int leftScore() const noexcept { return m_leftScore; }
    int rightScore() const noexcept { return m_rightScore; }

    QString ballColor() const noexcept;
    QString leftPaddleColor() const noexcept;
    QString rightPaddleColor() const noexcept;

    int gameMode() const noexcept { return m_gameMode; }
    void setGameMode(int gameMode) noexcept;

    int gameControlMode() const noexcept { return m_gameControlMode; }
    void setGameControlMode(int gameControlMode) noexcept;

    int bonusMode() const noexcept { return m_bonusMode; }
    void setBonusMode(int bonusMode) noexcept;

    Q_INVOKABLE void moveBallToCenter();
    Q_INVOKABLE void leftPaddleMove(int direction, bool dodge);
    Q_INVOKABLE void rightPaddleMove(int direction, bool dodge);
    Q_INVOKABLE void resetGame();

private:
    int moveUp(int currentY, int limit, bool dodge);
    int moveDown(int currentY, int currentYDown, int limit, bool dodge);
    void timerEvent(QTimerEvent *event) override;
    void componentComplete() override;
    bool ballIsCollidingWalls();
    bool ballIsCollidingPaddles();
    bool IsPaddleCollision(const GameEntity* paddle, bool isLeft);
    void handleLeftWallCollision();
    void handleRightWallCollision();
    void handlePaddleCollision(bool isLeft);
    void handleWinner();
    void incrementLeftScore();
    void decrementLeftScore();
    void incrementRightScore();
    void decrementRightScore();
    int randomBallEnabled();
    void handlePaddleHeight(GameEntity* paddle, bool isLeft);
    void handleInput();

signals:
    void ballPositionChanged();
    void activeChanged();
    void inputHandlerChanged();
    void leftScoreChanged();
    void rightScoreChanged();
    void ballColorChanged();
    void leftPaddleColorChanged();
    void rightPaddleColorChanged();
    void gameModeChanged();
    void gameControlModeChanged();
    void bonusModeChanged();
    void weHaveWinner(bool leftWinner, int leftScore, int rightScore);

};

#endif // PONGMINIGAME_H
