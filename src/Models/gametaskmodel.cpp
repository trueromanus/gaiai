#include "gametaskmodel.h"

GameTaskModel::GameTaskModel(bool isMandatory, const QString& title, const QString& parentId, int day, QObject *parent)
    : QObject{parent}, m_isMandatory{isMandatory}, m_title{title}, m_parentId{parentId}
{

}

void GameTaskModel::setCompleted(bool completed) noexcept
{
    if (m_completed == completed) return;

    m_completed = completed;
    emit completedChanged();
}
