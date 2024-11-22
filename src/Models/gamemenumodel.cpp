#include "gamemenumodel.h"

GameMenuModel::GameMenuModel(QObject *parent)
    : QObject{parent}
{}

void GameMenuModel::setTitle(const QString &title)
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void GameMenuModel::setIcon(const QString& icon) noexcept
{
    if (m_icon == icon) return;

    m_icon = icon;
    emit iconChanged();
}

void GameMenuModel::setBottomLine(bool bottomLine) noexcept
{
    if (m_bottomLine == bottomLine) return;

    m_bottomLine = bottomLine;
    emit bottomLineChanged();
}

void GameMenuModel::setUpperLine(bool upperLine) noexcept
{
    if (m_upperLine == upperLine) return;

    m_upperLine = upperLine;
    emit upperLineChanged();
}

void GameMenuModel::addChildren(GameMenuModel *children) noexcept
{
    m_childrens.append(children);

    emit hasChildrensChanged();
}

void GameMenuModel::addChildrenWithoutEmit(GameMenuModel *children) noexcept
{
    m_childrens.append(children);
}

