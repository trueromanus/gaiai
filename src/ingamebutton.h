#ifndef INGAMEBUTTON_H
#define INGAMEBUTTON_H

#include <QQuickItem>

class InGameButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ pressed NOTIFY pressedChanged FINAL)
    Q_PROPERTY(bool toggled READ toggled WRITE setToggled NOTIFY toggledChanged FINAL)
    Q_PROPERTY(bool disabled READ disabled WRITE setdisabled NOTIFY disabledChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE settitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool leftAligned READ leftAligned WRITE setLeftAligned NOTIFY leftAlignedChanged FINAL)
    QML_ELEMENT    
private:
    bool m_pressed { false };
    bool m_disabled { false };
    QString m_title { "" };
    bool m_leftAligned { false };

public:
    InGameButton();

    bool pressed() const noexcept { return m_pressed; }

    bool toggled() const noexcept { return m_pressed; }
    void setToggled(bool toggled) noexcept;

    bool disabled() const noexcept { return m_disabled; }
    void setdisabled(bool disabled) noexcept;

    QString title() const noexcept { return m_title; }
    void settitle(const QString& title) noexcept;

    bool leftAligned() const noexcept { return m_leftAligned; }
    void setLeftAligned(bool leftAligned) noexcept;

    Q_INVOKABLE void press() noexcept;
    Q_INVOKABLE void release() noexcept;

signals:
    void pressedChanged();
    void disabledChanged();
    void titleChanged();
    void clicked();
    void leftAlignedChanged();
    void toggledChanged();

};

#endif // INGAMEBUTTON_H
