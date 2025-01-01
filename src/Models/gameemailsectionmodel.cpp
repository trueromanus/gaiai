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

void GameEmailSectionModel::addToCount(bool isNew)
{
    if (isNew) m_newCount += 1;
    m_totalCount += 1;
}

void GameEmailSectionModel::refreshCounts()
{
    emit newCountChanged();
    emit totalCountChanged();
}

void GameEmailSectionModel::resetCounts()
{
    m_newCount = 0;
    m_totalCount = 0;

    emit newCountChanged();
    emit totalCountChanged();
}
