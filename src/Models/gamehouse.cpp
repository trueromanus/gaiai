#include "gamehouse.h"

GameHouse::GameHouse(QObject *parent)
    : QObject{parent}
{
}

void GameHouse::setName(const QString &name) noexcept
{
    if (m_name == name) return;

    m_name = name;
    emit nameChanged();
}

void GameHouse::setDistrict(const QString &district) noexcept
{
    if (m_district == district) return;

    m_district = district;
    emit districtChanged();
}

void GameHouse::setShape(const QString &shape) noexcept
{
    if (m_shape == shape) return;

    m_shape = shape;
    emit shapeChanged();
}
