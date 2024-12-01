#ifndef INGAMETREE_H
#define INGAMETREE_H

#include <QQuickItem>

class InGameTree : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QObject* selectedNode READ selectedNode NOTIFY selectedNodeChanged FINAL)
    Q_PROPERTY(bool allExpandedOnStart READ allExpandedOnStart WRITE setAllExpandedOnStart NOTIFY allExpandedOnStartChanged FINAL)
    QML_ELEMENT

private:
    QObject* m_selectedNode { nullptr };
    bool m_allExpandedOnStart { false };

public:
    InGameTree();

    QObject* selectedNode() const noexcept { return m_selectedNode; }

    bool allExpandedOnStart() const noexcept { return m_allExpandedOnStart; }
    void setAllExpandedOnStart(bool allExpandedOn) noexcept;

    Q_INVOKABLE void selectNode(QObject* node);

signals:
    void selectedNodeChanged();
    void allExpandedOnStartChanged();

};

#endif // INGAMETREE_H
