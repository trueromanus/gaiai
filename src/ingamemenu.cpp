#include "ingamemenu.h"

InGameMenu::InGameMenu() {}

void InGameMenu::setItems(const QList<GameMenuModel *> &items) noexcept
{
    if (m_items == items) return;

    m_items = items;
    emit itemsChanged();
}
