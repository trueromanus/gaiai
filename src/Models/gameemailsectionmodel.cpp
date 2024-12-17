#include "gameemailsectionmodel.h"

GameEmailSectionModel::GameEmailSectionModel(QObject *parent)
    : QObject{parent}
{
}

void GameEmailSectionModel::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameEmailSectionModel::setGroup(const QString &group) noexcept
{
    if (m_group == group) return;

    m_group = group;
    emit groupChanged();
}
