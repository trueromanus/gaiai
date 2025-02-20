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

void GameHouse::setXvalue(int xvalue) noexcept
{
    if (m_xvalue == xvalue) return;

    m_xvalue = xvalue;
    emit xvalueChanged();
}

void GameHouse::setYvalue(int yvalue) noexcept
{
    if (m_yvalue == yvalue) return;

    m_yvalue = yvalue;
    emit yvalueChanged();
}

void GameHouse::setRotation(int rotation) noexcept
{
    if (m_rotation == rotation) return;

    m_rotation = rotation;
    emit rotationChanged();
}
