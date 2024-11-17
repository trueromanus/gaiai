#include "gametasksectionmodel.h"

GameTaskSectionModel::GameTaskSectionModel(QObject *parent)
    : QObject{parent}
{}

void GameTaskSectionModel::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameTaskSectionModel::clearInnerTasks() noexcept
{
    m_innerTasks.clear();
    m_innerTasksAsObject.clear();
    emit hasChildrensChanged();
    emit childrensChanged();
    emit objectChildrensChanged();
}

void GameTaskSectionModel::addInnerTask(GameTaskModel *task) noexcept
{
    m_innerTasks.append(task);
    m_innerTasksAsObject.append(qobject_cast<QObject*>(task));
    emit hasChildrensChanged();
    emit childrensChanged();
    emit objectChildrensChanged();
}
