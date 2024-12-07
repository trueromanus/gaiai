#ifndef EMAILCLIENTPAGE_H
#define EMAILCLIENTPAGE_H

#include <QObject>
#include "../Models/gametablecolumn.h"

class EmailClientPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> foldersColumns READ foldersColumns NOTIFY foldersColumnsChanged FINAL)
    Q_PROPERTY(QList<GameTableColumn*> emailColumns READ emailColumns NOTIFY emailColumnsChanged FINAL)

private:
    QList<GameTableColumn*> m_foldersColumns { QList<GameTableColumn*>() };
    QList<GameTableColumn*> m_emailColumns { QList<GameTableColumn*>() };

public:
    explicit EmailClientPage(QObject *parent = nullptr);

    QList<GameTableColumn*> foldersColumns() const noexcept { return m_foldersColumns; }

    QList<GameTableColumn*> emailColumns() const noexcept { return m_emailColumns; }

signals:
    void foldersColumnsChanged();
    void emailColumnsChanged();

};

#endif // EMAILCLIENTPAGE_H
