#ifndef INGAMECHECKBOX_H
#define INGAMECHECKBOX_H

#include <QQuickItem>

class InGameCheckBox : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged FINAL)
    QML_ELEMENT

private:
    bool m_checked { false };

public:
    InGameCheckBox();

    bool checked() const noexcept { return m_checked; }
    void setChecked(bool checked) noexcept;

signals:
    void checkedChanged();

};

#endif // INGAMECHECKBOX_H
