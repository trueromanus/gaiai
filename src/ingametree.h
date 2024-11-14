#ifndef INGAMETREE_H
#define INGAMETREE_H

#include <QQuickItem>

class InGameTree : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QObject* selectedNode READ selectedNode NOTIFY selectedNodeChanged FINAL)
    QML_ELEMENT

private:
    QObject* m_selectedNode { nullptr };

public:
    InGameTree();

    QObject* selectedNode() const noexcept { return m_selectedNode; }

    Q_INVOKABLE void selectNode(QObject* node);

signals:
    void selectedNodeChanged();

};

#endif // INGAMETREE_H
