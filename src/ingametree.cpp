#include "ingametree.h"

InGameTree::InGameTree() {}

void InGameTree::setAllExpandedOnStart(bool allExpandedOnStart) noexcept
{
    if (m_allExpandedOnStart == allExpandedOnStart) return;

    m_allExpandedOnStart = allExpandedOnStart;
    emit allExpandedOnStartChanged();
}

void InGameTree::selectNode(QObject *node)
{
    if (m_selectedNode == node) return;

    m_selectedNode = node;
    emit selectedNodeChanged();
}
