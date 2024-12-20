#include "verticalscrollbar.h"

VerticalScrollBar::VerticalScrollBar() {}

void VerticalScrollBar::setScrollAreaHeight(qreal scrollAreaHeight) noexcept
{
    if (m_scrollAreaHeight == scrollAreaHeight) return;

    m_scrollAreaHeight = scrollAreaHeight;
    emit scrollAreaHeightChanged();

    refreshPercent();
    refreshThumbHeight();
    checkIfItRequireScroll();
}

void VerticalScrollBar::setScrollAreaContentHeight(qreal scrollAreaContentHeight) noexcept
{
    if (m_scrollAreaContentHeight == scrollAreaContentHeight) return;

    m_scrollAreaContentHeight = scrollAreaContentHeight;
    emit scrollAreaContentHeightChanged();

    refreshPercent();
    refreshThumbHeight();
    checkIfItRequireScroll();
}

void VerticalScrollBar::setThumbPosition(qreal thumbPosition) noexcept
{
    if (m_thumbPosition == thumbPosition) return;

    m_thumbPosition = thumbPosition;
    emit thumbPositionChanged();
    auto percentInCurrent = m_thumbPosition / height();
    emit requiredChangeScrollPosition(m_scrollAreaContentHeight * percentInCurrent);
}

void VerticalScrollBar::setMoving(bool moving) noexcept
{
    if (m_moving == moving) return;

    m_moving = moving;
    emit movingChanged();
}

void VerticalScrollBar::setOriginY(qreal value)
{
    m_originY = value;
}

void VerticalScrollBar::clearOriginY()
{
    m_originY = -1;
}

void VerticalScrollBar::changeAfterChangePosition(qreal mousePosition)
{
    if (m_originY == -1) m_originY = mousePosition;

    auto deltaY = m_originY - mousePosition;

    auto newYValue = m_thumbPosition - deltaY;
    if (newYValue < 0) newYValue = 0;
    if (newYValue + m_thumb > height()) newYValue = height() - m_thumb;

    setThumbPosition(newYValue);
}

void VerticalScrollBar::changeAfterChangeSource(qreal contentY)
{
    auto position = m_scrollAreaHeight * (contentY / m_scrollAreaContentHeight);
    position -= m_thumb;
    if (position < 0) position = 0;
    m_thumbPosition = position;
    emit thumbPositionChanged();
}

void VerticalScrollBar::scrollUp()
{
    auto step = m_thumb / 3;
    auto newPosition = m_thumbPosition - step;
    if (newPosition < 0) newPosition = 0;
    setMoving(true);
    setThumbPosition(newPosition);
    setMoving(false);
}

void VerticalScrollBar::scrollDown()
{
    auto step = m_thumb / 3;
    auto newPosition = m_thumbPosition + step;
    if (newPosition + m_thumb > height()) newPosition = height() - m_thumb;
    setMoving(true);
    setThumbPosition(newPosition);
    setMoving(false);
}

void VerticalScrollBar::refreshPercent()
{
    if (m_scrollAreaHeight <= 0 || m_scrollAreaContentHeight <= 0) {
        m_percent = 0;
        return;
    }
    if (m_scrollAreaContentHeight < m_scrollAreaHeight) {
        m_percent = 0;
        return;
    }
    m_percent = m_scrollAreaHeight / m_scrollAreaContentHeight;
}

void VerticalScrollBar::refreshThumbHeight()
{
    if (m_percent <= 0) {
        m_thumb = 0;
        emit thumbChanged();
        return;
    }

    m_thumb = height() * m_percent;
    emit thumbChanged();
}

void VerticalScrollBar::checkIfItRequireScroll()
{
    m_isNeedScroll = m_percent > 0;
    emit isNeedScrollChanged();
}
