#ifndef EMAILCLIENTPAGE_H
#define EMAILCLIENTPAGE_H

#include <QObject>
#include "../Models/gametablecolumn.h"
#include "../Models/gameemailsectionmodel.h"

class EmailClientPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> foldersColumns READ foldersColumns NOTIFY foldersColumnsChanged FINAL)
    Q_PROPERTY(QList<GameTableColumn*> emailColumns READ emailColumns NOTIFY emailColumnsChanged FINAL)
    Q_PROPERTY(QList<QObject*> sections READ sections NOTIFY sectionsChanged FINAL)

private:

    QList<GameTableColumn*> m_foldersColumns { QList<GameTableColumn*>() };
    QList<GameTableColumn*> m_emailColumns { QList<GameTableColumn*>() };
    QList<GameEmailSectionModel*> m_sections { QList<GameEmailSectionModel*>() };
    QList<QObject*> m_sectionObjects { QList<QObject*>() };

public:
    explicit EmailClientPage(QObject *parent = nullptr);
    QList<GameTableColumn*> foldersColumns() const noexcept { return m_foldersColumns; }

    QList<GameTableColumn*> emailColumns() const noexcept { return m_emailColumns; }

    QList<QObject*> sections() const noexcept { return m_sectionObjects; }

private:
    void fillObjectSections();

signals:
    void foldersColumnsChanged();
    void emailColumnsChanged();
    void sectionsChanged();

};

#endif // EMAILCLIENTPAGE_H
