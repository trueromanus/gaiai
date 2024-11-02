#ifndef INGAMERADIOBUTTON_H
#define INGAMERADIOBUTTON_H

#include <QQuickItem>

class InGameRadioButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int actualValue READ actualValue WRITE setActualValue NOTIFY actualValueChanged FINAL)
    Q_PROPERTY(int radioValue READ radioValue WRITE setRadioValue NOTIFY radioValueChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    QML_ELEMENT

private:
    int m_actualValue { -1 };
    int m_radioValue { -1 };
    QString m_title { "" };

public:
    InGameRadioButton();

    int actualValue() const noexcept { return m_actualValue; }
    void setActualValue(int actualValue) noexcept;

    int radioValue() const noexcept { return m_radioValue; }
    void setRadioValue(int radioValue) noexcept;

    QString title() const noexcept { return m_title; }
    void setTitle(QString title) noexcept;

signals:
    void actualValueChanged();
    void radioValueChanged();
    void titleChanged();
    void selected();

};

#endif // INGAMERADIOBUTTON_H
