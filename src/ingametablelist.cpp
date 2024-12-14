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

void InGameTableList::setItems(const QList<QObject*> items) noexcept
{
    if (m_items == items) return;

    m_items = items;
    emit itemsChanged();
}

void InGameTableList::setSelectedItem(const QObject *selectedItem) noexcept
{
    if (m_selectedItem == selectedItem) return;

    m_selectedItem = const_cast<QObject *>(selectedItem);
    emit selectedItemChanged();
}

void InGameTableList::setSelectedStyle(int selectedStyle) noexcept
{
    if (m_selectedStyle == selectedStyle) return;

    m_selectedStyle = selectedStyle;
    emit selectedStyleChanged();
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
