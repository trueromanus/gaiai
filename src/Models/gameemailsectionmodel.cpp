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

void GameEmailSectionModel::setFilter(const QString &filter) noexcept
{
    if (m_filter == filter) return;

    m_filter = filter;
    emit filterChanged();
}
