#include "gamestartscreenmodel.h"

GameStartScreenModel::GameStartScreenModel(QObject *parent)
    : QObject{parent}
{}

void GameStartScreenModel::setDay(int day) noexcept
{
    if (m_day == day) return;

    m_day = day;
    emit dayChanged();
}

void GameStartScreenModel::setNameOS(const QString &nameOS) noexcept
{
    if (m_nameOS == nameOS) return;

    m_nameOS = nameOS;
    emit nameOSChanged();
}

void GameStartScreenModel::setNameOSExtra(const QString &nameOSExtra) noexcept
{
    if (m_nameOSExtra == nameOSExtra) return;

    m_nameOSExtra = nameOSExtra;
    emit nameOSExtraChanged();
}

void GameStartScreenModel::setCompanyName(const QString &companyName) noexcept
{
    if (m_companyName == companyName) return;

    m_companyName = companyName;
    emit companyNameChanged();
}

void GameStartScreenModel::setSlogan(const QString &slogan) noexcept
{
    if (m_slogan == slogan) return;

    m_slogan = slogan;
    emit sloganChanged();
}

void GameStartScreenModel::setBackground(const QString &background) noexcept
{
    if (m_background == background) return;

    m_background = background;
    emit backgroundChanged();
}
