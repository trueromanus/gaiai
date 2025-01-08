#include "gameentity.h"

GameEntity::GameEntity() {}

void GameEntity::setIdentifier(const QString &identifier) noexcept
{
    if (m_identifier == identifier) return;

    m_identifier = identifier;
    emit identifierChanged();
}
