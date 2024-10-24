#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QObject>
#include <QQmlEngine>

class SystemSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal textMultiplier READ textMultiplier NOTIFY textMultiplierChanged FINAL)
    QML_ELEMENT

private:
    qreal m_textMultiplier { 0.0 };

public:
    explicit SystemSettings(QObject *parent = nullptr);

    qreal textMultiplier() const noexcept { return m_textMultiplier; }

signals:
    void textMultiplierChanged();

};

#endif // SYSTEMSETTINGS_H
