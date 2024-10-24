#ifndef INGAMEBUTTON_H
#define INGAMEBUTTON_H

#include <QQuickItem>

class InGameButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ pressed NOTIFY pressedChanged FINAL)
    Q_PROPERTY(bool disabled READ disabled WRITE setdisabled NOTIFY disabledChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE settitle NOTIFY titleChanged FINAL)
    QML_ELEMENT    
private:
    bool m_pressed { false };
    bool m_disabled { false };
    QString m_title { "" };

public:
    InGameButton();

    bool pressed() const noexcept { return m_pressed; }

    bool disabled() const noexcept { return m_disabled; }
    void setdisabled(bool disabled) noexcept;

    QString title() const noexcept { return m_title; }
    void settitle(const QString& title) noexcept;

    Q_INVOKABLE void press() noexcept;
    Q_INVOKABLE void release() noexcept;

signals:
    void pressedChanged();
    void disabledChanged();
    void titleChanged();
    void clicked();

};

#endif // INGAMEBUTTON_H
