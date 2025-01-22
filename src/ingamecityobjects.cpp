#include "ingamecityobjects.h"

InGameCityObjects::InGameCityObjects(QObject *parent) {}

void InGameCityObjects::setGameBackend(const GameBackend* backend) noexcept
{
    m_gameBackend = const_cast<GameBackend *>(backend);
}

void InGameCityObjects::handleTimerForCitizens(int time) noexcept
{
    foreach (auto citizenKey, m_activeCitizens) {
        auto citizen = m_citizens.value(citizenKey);
        citizen->handleTimer(time, *m_gameBackend);
    }
}
