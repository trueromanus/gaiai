#include "smarttrackerpage.h"

SmartTrackerPage::SmartTrackerPage(QObject *parent)
    : QObject{parent}
{
    auto titleColumn = new GameTableColumn(this);
    titleColumn->setTitle("Title");
    titleColumn->setField("title");
    titleColumn->setColumnWidth(190);
    m_columns.append(titleColumn);

    auto completedColumn = new GameTableColumn(this);
    completedColumn->setTitle("Completed");
    completedColumn->setField("completed");
    completedColumn->setColumnWidth(80);
    m_columns.append(completedColumn);
}

void SmartTrackerPage::setColumns(const QList<GameTableColumn *> columns) noexcept
{
    if (m_columns == columns) return;

    m_columns = columns;
    emit columnsChanged();
}
