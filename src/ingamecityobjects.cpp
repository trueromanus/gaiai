#include "ingamecityobjects.h"

InGameCityObjects::InGameCityObjects(QObject *parent) {}

void InGameCityObjects::setGameBackend(const GameBackend* backend) noexcept
{
    m_gameBackend = const_cast<GameBackend *>(backend);
}

void InGameCityObjects::handleTimerForCitizens(int time) noexcept
{
    foreach (auto citizen, m_gameCitizens) {
        citizen->handleTimer(time, *m_gameBackend);
    }
}
