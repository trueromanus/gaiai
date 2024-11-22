#ifndef INGAMETABLELIST_H
#define INGAMETABLELIST_H

#include <QQuickItem>
#include "Models/gametablecolumn.h"

class InGameTableList : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> columns READ columns WRITE setColumns NOTIFY columnsChanged FINAL)
    Q_PROPERTY(QList<QObject*> items READ items WRITE setItems NOTIFY itemsChanged FINAL)
    Q_PROPERTY(QObject* selectedItem READ selectedItem WRITE setSelectedItem NOTIFY selectedItemChanged FINAL)
    Q_PROPERTY(int fullWidth READ fullWidth NOTIFY fullWidthChanged FINAL)
    QML_ELEMENT

private:
    QList<GameTableColumn*> m_columns { QList<GameTableColumn*>() };
    QList<QObject*> m_items { QList<QObject*>() };
    int m_fullWidth { 0 };
    QObject* m_selectedItem { nullptr };

public:
    InGameTableList();

    QList<GameTableColumn*> columns() const noexcept { return m_columns; }
    void setColumns(const QList<GameTableColumn*> columns) noexcept;

    QList<QObject*> items() const noexcept { return m_items; }
    void setItems(const QList<QObject*> items) noexcept;

    int fullWidth() const noexcept { return m_fullWidth; }

    QObject* selectedItem() const noexcept { return m_selectedItem; }
    void setSelectedItem(const QObject* selectedItem) noexcept;

private:
    void recalculateFullWidth();

signals:
    void columnsChanged();
    void fullWidthChanged();
    void itemsChanged();
    void selectedItemChanged();
    void openItem();

};

#endif // INGAMETABLELIST_H
