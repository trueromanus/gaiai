#include "ingameshifttimer.h"

InGameShiftTimer::InGameShiftTimer() {}

void InGameShiftTimer::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    m_time += 1;
    emit displayTimeChanged();
    emit timeChanged(m_time);
}

void InGameShiftTimer::setBackend(const GameBackend *backend) noexcept
{
    if (m_backend == backend) return;

    m_backend = const_cast<GameBackend *>(backend);
    emit backendChanged();
}

QString InGameShiftTimer::displayTime() const noexcept
{
    auto isNextDay = m_time > 10700;
    auto processedTime = m_time > 10700 ? m_time - 10700 : m_time;
    auto time = QTime::fromMSecsSinceStartOfDay((isNextDay ? 0 : 75600000) + processedTime * 1000);
    return time.toString(m_format);
}

void InGameShiftTimer::setFormat(const QString &format) noexcept
{
    if (m_format == format) return;

    m_format = format;
    emit formatChanged();
}

void InGameShiftTimer::restartShift()
{
    stopShiftTimer();

    m_time = 0;

    startShiftTimer();
}

void InGameShiftTimer::pauseTimer()
{
    stopShiftTimer();
}

void InGameShiftTimer::startShiftTimer()
{
    m_shiftTimer = startTimer(1000 / 10, Qt::CoarseTimer);
}

void InGameShiftTimer::stopShiftTimer()
{
    if (m_shiftTimer == -1) return;

    killTimer(m_shiftTimer);
    m_shiftTimer = -1;
}
