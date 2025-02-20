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

void GameCitizen::handleTimer(int time, const GameBackend &backend)
{

}

void GameCitizen::addSchedule(int time, const QString &location) noexcept
{

}
