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

void GameTaskSectionModel::reassignInnerTasks(const QList<GameTaskModel *> tasks) noexcept
{
    m_innerTasks.clear();

    m_innerTasks.append(tasks);

    emit hasChildrensChanged();
    emit childrensChanged();
}

void GameTaskSectionModel::clearInnerTasks() noexcept
{
    m_innerTasks.clear();
    emit hasChildrensChanged();
    emit childrensChanged();
}

void GameTaskSectionModel::addInnerTask(GameTaskModel *task) noexcept
{
    m_innerTasks.append(task);
    emit hasChildrensChanged();
    emit childrensChanged();
}
