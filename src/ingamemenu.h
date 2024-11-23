#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include <QQuickItem>
#include "Models/gamemenumodel.h"

class InGameMenu : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QList<GameMenuModel*> items READ items WRITE setItems NOTIFY itemsChanged FINAL)
    Q_PROPERTY(QList<GameMenuModel*> subLevels READ subLevels NOTIFY subLevelsChanged FINAL)
    QML_ELEMENT

private:
    QList<GameMenuModel*> m_items { QList<GameMenuModel*>() };
    QList<GameMenuModel*> m_subLevels { QList<GameMenuModel*>() };

public:
    InGameMenu();

    QList<GameMenuModel*> items() const noexcept { return m_items; }
    void setItems(const QList<GameMenuModel*>& items) noexcept;

    QList<GameMenuModel*> subLevels() const noexcept { return m_subLevels; }

signals:
    void itemsChanged();
    void subLevelsChanged();
    void commandPerformed(const QString& command);

};

#endif // INGAMEMENU_H
