#include "gametablecolumn.h"

GameTableColumn::GameTableColumn(QObject *parent)
    : QObject{parent}
{}

void GameTableColumn::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameTableColumn::setField(const QString &field) noexcept
{
    if (m_field == field) return;

    m_field = field;
    emit fieldChanged();
}

void GameTableColumn::setColumnWidth(int columnWidth) noexcept
{
    if (m_columnWidth == columnWidth) return;

    m_columnWidth = columnWidth;
    emit columnWidthChanged();
}

void GameTableColumn::setFormatter(const QString &formatter) noexcept
{
    if (m_formatter == formatter) return;

    m_formatter = formatter;
    emit formatterChanged();
}

void GameTableColumn::setSelectable(bool selectable) noexcept
{
    if (m_selectable == selectable) return;

    m_selectable = selectable;
    emit selectableChanged();
}
