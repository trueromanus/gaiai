#ifndef INGAMESHIFTTIMER_H
#define INGAMESHIFTTIMER_H

#include <QQuickItem>
#include <QDateTime>
#include "gamebackend.h"

class InGameShiftTimer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(GameBackend* backend READ backend WRITE setBackend NOTIFY backendChanged FINAL)
    Q_PROPERTY(QString displayTime READ displayTime NOTIFY displayTimeChanged FINAL)
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged FINAL)
    QML_ELEMENT

private:
    int m_time { 0 };
    int m_shiftTimer { -1 };
    GameBackend* m_backend { nullptr };
    QString m_format { "HH:mm" };

public:
    InGameShiftTimer();

    void timerEvent(QTimerEvent *event) override;

    GameBackend* backend() const noexcept { return m_backend; }
    void setBackend(const GameBackend* backend) noexcept;

    QString displayTime() const noexcept;

    QString format() const noexcept { return m_format; }
    void setFormat(const QString& format) noexcept;

    Q_INVOKABLE void restartShift();

private:
    void startShiftTimer();
    void stopShiftTimer();
    void handleTimerForPeople();

signals:
    void backendChanged();
    void displayTimeChanged();
    void formatChanged();

};

#endif // INGAMESHIFTTIMER_H
