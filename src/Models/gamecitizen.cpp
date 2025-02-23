#include "gamecitizen.h"

GameCitizen::GameCitizen(QObject *parent)
    : QObject{parent}
{}

void GameCitizen::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameCitizen::setStressLevel(int stressLevel) noexcept
{
    if (m_stressLevel == stressLevel) return;

    m_stressLevel = stressLevel;
    emit stressLevelChanged();
    emit isMadChanged();
}

void GameCitizen::setLocation(const QString &location) noexcept
{
    if (m_location == location) return;

    m_location = location;
    emit locationChanged();
}

void GameCitizen::setOriginalLocation(const QString &originalLocation) noexcept
{
    if (m_originalLocation == originalLocation) return;

    m_originalLocation = originalLocation;
    emit originalLocationChanged();
}

void GameCitizen::setEnableSchedule(bool enableSchedule) noexcept
{
    if (m_enableSchedule == enableSchedule) return;

    m_enableSchedule = enableSchedule;
    emit enableScheduleChanged();
}

bool GameCitizen::handleTimer(int time)
{
    if (!m_isAlive) return false;
    if (!m_enableSchedule) return false;

    if (m_schedule.contains(time)) {
        setLocation(m_schedule.value(time));
        return true;
    }

    return false;
}

void GameCitizen::addSchedule(int time, const QString &location) noexcept
{
    m_schedule.insert(time, location);
}

bool GameCitizen::isInHomeLocation()
{
    return m_location == m_originalLocation;
}

void GameCitizen::setIsNotAlive()
{
    m_isAlive = false;
    emit isAliveChanged();
}

void GameCitizen::setStressLevel()
{
    if (m_stressLevel == 10) {
        setIsNotAlive();
        return;
    }

    m_stressLevel += 1;
    emit stressLevelChanged();
}
