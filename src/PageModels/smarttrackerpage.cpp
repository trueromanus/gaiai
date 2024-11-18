#include "smarttrackerpage.h"

SmartTrackerPage::SmartTrackerPage(QObject *parent)
    : QObject{parent}
{
    auto titleColumn = new GameTableColumn(this);
    titleColumn->setTitle("Title");
    titleColumn->setField("title");
    titleColumn->setSelectable(true);
    titleColumn->setColumnWidth(199);
    m_columns.append(titleColumn);

    auto mandatoryColumn = new GameTableColumn(this);
    mandatoryColumn->setTitle("Mandatory");
    mandatoryColumn->setField("isMandatory");
    mandatoryColumn->setFormatter("checkbox");
    mandatoryColumn->setColumnWidth(68);
    m_columns.append(mandatoryColumn);

    auto completedColumn = new GameTableColumn(this);
    completedColumn->setTitle("Completed");
    completedColumn->setField("completed");
    completedColumn->setFormatter("checkbox");
    completedColumn->setColumnWidth(73);
    m_columns.append(completedColumn);
}

void SmartTrackerPage::setColumns(const QList<GameTableColumn *> columns) noexcept
{
    if (m_columns == columns) return;

    m_columns = columns;
    emit columnsChanged();
}

void SmartTrackerPage::setSelectedTaskInList(const GameTaskModel *selectedTaskInList)
{
    if (m_selectedTaskInList == selectedTaskInList) return;

    m_selectedTaskInList = const_cast<GameTaskModel*>(selectedTaskInList);
    emit selectedTaskInListChanged();
}
