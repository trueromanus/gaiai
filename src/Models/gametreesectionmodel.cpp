#include "gametreesectionmodel.h"

GameTreeSectionModel::GameTreeSectionModel(QObject *parent)
    : QObject{parent}
{}

void GameTreeSectionModel::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameTreeSectionModel::setCommand(const QString &command) noexcept
{
    if (m_command == command) return;

    m_command = command;
    emit commandChanged();
}

void GameTreeSectionModel::addSubSection(GameTreeSectionModel *subsection) noexcept
{
    m_childrens.append(subsection);
    emit hasChildrensChanged();
    emit childrensChanged();
}
