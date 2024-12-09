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
