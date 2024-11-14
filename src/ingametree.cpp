#include "ingametree.h"

InGameTree::InGameTree() {}

void InGameTree::selectNode(QObject *node)
{
    if (m_selectedNode == node) return;

    m_selectedNode = node;
    emit selectedNodeChanged();
}
