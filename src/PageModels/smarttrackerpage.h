#ifndef SMARTTRACKERPAGE_H
#define SMARTTRACKERPAGE_H

#include <QObject>
#include "../Models/gametablecolumn.h"

class SmartTrackerPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)

private:
    QList<GameTableColumn*> m_columns { QList<GameTableColumn*>() };

public:
    explicit SmartTrackerPage(QObject *parent = nullptr);

    QList<GameTableColumn*> columns() const noexcept { return m_columns; }
    void setColumns(const QList<GameTableColumn*> columns) noexcept;

signals:
    void columnsChanged();

};

#endif // SMARTTRACKERPAGE_H
