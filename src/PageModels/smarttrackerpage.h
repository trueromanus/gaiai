#ifndef SMARTTRACKERPAGE_H
#define SMARTTRACKERPAGE_H

#include <QObject>
#include "../Models/gametablecolumn.h"
#include "../Models/gametaskmodel.h"

class SmartTrackerPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
    Q_PROPERTY(GameTaskModel* selectedTaskInList READ selectedTaskInList WRITE setSelectedTaskInList NOTIFY selectedTaskInListChanged FINAL)

private:
    QList<GameTableColumn*> m_columns { QList<GameTableColumn*>() };
    GameTaskModel* m_selectedTaskInList { nullptr };

public:
    explicit SmartTrackerPage(QObject *parent = nullptr);

    QList<GameTableColumn*> columns() const noexcept { return m_columns; }
    void setColumns(const QList<GameTableColumn*> columns) noexcept;

    GameTaskModel* selectedTaskInList() const noexcept { return m_selectedTaskInList; }
    void setSelectedTaskInList(const GameTaskModel* selectedTaskInList);

signals:
    void columnsChanged();
    void selectedTaskInListChanged();

};

#endif // SMARTTRACKERPAGE_H
