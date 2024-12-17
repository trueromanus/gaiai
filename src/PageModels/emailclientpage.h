#ifndef EMAILCLIENTPAGE_H
#define EMAILCLIENTPAGE_H

#include <QObject>
#include "../Models/gametablecolumn.h"
#include "../Models/gameemailsectionmodel.h"
#include "../Models/gameemailmodel.h"

class EmailClientPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTableColumn*> foldersColumns READ foldersColumns NOTIFY foldersColumnsChanged FINAL)
    Q_PROPERTY(QList<GameTableColumn*> emailColumns READ emailColumns NOTIFY emailColumnsChanged FINAL)
    Q_PROPERTY(QList<QObject*> sections READ sections NOTIFY sectionsChanged FINAL)
    Q_PROPERTY(QList<QObject*> emails READ emails NOTIFY emailsChanged FINAL)
    Q_PROPERTY(QString selectedGroup READ selectedGroup WRITE setSelectedGroup NOTIFY selectedGroupChanged FINAL)

private:
    const QString InboxGroup { "inbox" };
    const QString OutboxGroup { "outbox" };
    const QString SentGroup { "sent" };
    const QString TrashGroup { "trash" };

    QList<GameTableColumn*> m_foldersColumns { QList<GameTableColumn*>() };
    QList<GameTableColumn*> m_emailColumns { QList<GameTableColumn*>() };
    QList<GameEmailSectionModel*> m_sections { QList<GameEmailSectionModel*>() };
    QList<QObject*> m_sectionObjects { QList<QObject*>() };
    GameEmailSectionModel* m_accountSection { nullptr };
    GameEmailSectionModel* m_inBoxSection { nullptr };
    GameEmailSectionModel* m_outBoxSection { nullptr };
    GameEmailSectionModel* m_sentSection { nullptr };
    GameEmailSectionModel* m_trashSection { nullptr };
    QList<GameEmailModel*> m_emails { QList<GameEmailModel*>() };
    QList<QObject*> m_emailObjects { QList<QObject*>() };
    QString m_selectedGroup { "" };

public:
    explicit EmailClientPage(QObject *parent = nullptr);
    QList<GameTableColumn*> foldersColumns() const noexcept { return m_foldersColumns; }

    QList<GameTableColumn*> emailColumns() const noexcept { return m_emailColumns; }

    QList<QObject*> sections() const noexcept { return m_sectionObjects; }

    QList<QObject*> emails() const noexcept { return m_emailObjects; }

    QString selectedGroup() const noexcept { return m_selectedGroup; }
    void setSelectedGroup(const QString& selectedGroup) noexcept;

    void fillForDay(int day) noexcept;

    Q_INVOKABLE void refreshDisplayEmails() noexcept;

private:
    void createObjectSections();
    void fillObjectSections();
    void createSectionColumns();
    void createEmailColumns();

signals:
    void foldersColumnsChanged();
    void emailColumnsChanged();
    void sectionsChanged();
    void emailsChanged();
    void selectedGroupChanged();

};

#endif // EMAILCLIENTPAGE_H
