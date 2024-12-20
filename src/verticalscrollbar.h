#ifndef VERTICALSCROLLBAR_H
#define VERTICALSCROLLBAR_H

#include <QQuickItem>

class VerticalScrollBar : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scrollAreaHeight READ scrollAreaHeight WRITE setScrollAreaHeight NOTIFY scrollAreaHeightChanged FINAL)
    Q_PROPERTY(qreal scrollAreaContentHeight READ scrollAreaContentHeight WRITE setScrollAreaContentHeight NOTIFY scrollAreaContentHeightChanged FINAL)
    Q_PROPERTY(qreal thumb READ thumb NOTIFY thumbChanged FINAL)
    Q_PROPERTY(qreal thumbPosition READ thumbPosition WRITE setThumbPosition NOTIFY thumbPositionChanged FINAL)
    Q_PROPERTY(bool moving READ moving WRITE setMoving NOTIFY movingChanged FINAL)
    Q_PROPERTY(bool isNeedScroll READ isNeedScroll NOTIFY isNeedScrollChanged FINAL)
    QML_ELEMENT

private:
    qreal m_scrollAreaHeight { 0 };
    qreal m_scrollAreaContentHeight { 0 };
    qreal m_percent { 0 };
    qreal m_thumb { 0 };
    qreal m_thumbPosition { 0 };
    qreal m_originY { -1 };
    bool m_moving { false };
    bool m_isNeedScroll { false };

public:
    VerticalScrollBar();

    qreal scrollAreaHeight() const noexcept { return m_scrollAreaHeight; }
    void setScrollAreaHeight(qreal scrollAreaHeight) noexcept;

    qreal scrollAreaContentHeight() const noexcept { return m_scrollAreaContentHeight; }
    void setScrollAreaContentHeight(qreal scrollAreaContentHeight) noexcept;

    qreal thumb() const noexcept { return m_thumb; }

    qreal thumbPosition() const noexcept { return m_thumbPosition; }
    void setThumbPosition(qreal thumbPosition) noexcept;

    bool moving() const noexcept { return m_moving; }
    void setMoving(bool moving) noexcept;

    bool isNeedScroll() const noexcept { return m_isNeedScroll; }

    Q_INVOKABLE void setOriginY(qreal value);
    Q_INVOKABLE void clearOriginY();
    Q_INVOKABLE void changeAfterChangePosition(qreal mousePosition);
    Q_INVOKABLE void changeAfterChangeSource(qreal contentY);
    Q_INVOKABLE void scrollUp();
    Q_INVOKABLE void scrollDown();

private:
    void refreshPercent();
    void refreshThumbHeight();
    void checkIfItRequireScroll();

signals:
    void scrollAreaHeightChanged();
    void scrollAreaContentHeightChanged();
    void thumbChanged();
    void thumbPositionChanged();
    void requiredChangeScrollPosition(qreal newValue);
    void movingChanged();
    void isNeedScrollChanged();

};


#endif // VERTICALSCROLLBAR_H
