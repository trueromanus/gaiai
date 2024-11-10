#include "gametaskmodel.h"

GameTaskModel::GameTaskModel(bool isMandatory, const QString& title, const QString& parentId, int day, std::function<bool()> action, QObject *parent)
    : QObject{parent}, m_isMandatory{isMandatory}, m_title{title}, m_parentId{parentId}, m_day{day}, m_action{action}
{

}

void GameTaskModel::setCompleted(bool completed) noexcept
{
    if (m_completed == completed) return;

    m_completed = completed;
    emit completedChanged();
}

void GameTaskModel::checkCompleted() noexcept
{
    if (m_completed) return;
    if (m_action == nullptr) return;

    m_completed = m_action();
    if (m_completed) emit completedChanged();
}
