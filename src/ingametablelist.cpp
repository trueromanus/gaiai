#include "ingametablelist.h"

InGameTableList::InGameTableList() {
    recalculateFullWidth();
}

void InGameTableList::setColumns(const QList<GameTableColumn *> columns) noexcept
{
    if (m_columns == columns) return;

    m_columns = columns;
    emit columnsChanged();

    recalculateFullWidth();
}

void InGameTableList::recalculateFullWidth()
{
    auto fullWidth = 0;

    foreach (auto column, m_columns) {
        fullWidth += column->columnWidth();
    }

    m_fullWidth = fullWidth;
    emit fullWidthChanged();
}
