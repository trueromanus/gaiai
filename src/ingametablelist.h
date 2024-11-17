#ifndef INGAMETABLELIST_H
#define INGAMETABLELIST_H

#include <QQuickItem>
#include "Models/gametablecolumn.h"

class InGameTableList : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
    Q_PROPERTY(QList<QObject*> items READ items WRITE setItems NOTIFY itemsChanged FINAL)
    Q_PROPERTY(int fullWidth READ fullWidth NOTIFY fullWidthChanged FINAL)
    QML_ELEMENT

private:
    QList<GameTableColumn*> m_columns { QList<GameTableColumn*>() };
    QList<QObject*> m_items { QList<QObject*>() };
    int m_fullWidth { 0 };

public:
    InGameTableList();

    QList<GameTableColumn*> columns() const noexcept { return m_columns; }
    void setColumns(const QList<GameTableColumn*> columns) noexcept;

    QList<QObject*> items() const noexcept { return m_items; }
    void setItems(const QList<QObject*> items) noexcept;

    int fullWidth() const noexcept { return m_fullWidth; }

private:
    void recalculateFullWidth();

signals:
    void columnsChanged();
    void fullWidthChanged();
    void itemsChanged();

};

#endif // INGAMETABLELIST_H
