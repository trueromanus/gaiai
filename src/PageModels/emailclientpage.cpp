#include "emailclientpage.h"

EmailClientPage::EmailClientPage(QObject *parent)
    : QObject{parent}
{
    createSectionColumns();
    createEmailColumns();

    createObjectSections();
    fillObjectSections();

    fillForDay(1);
}

void EmailClientPage::setSelectedGroup(const QString &selectedGroup) noexcept
{
    if (m_selectedGroup == selectedGroup) return;

    m_selectedGroup = selectedGroup;
    emit selectedGroupChanged();
}

void EmailClientPage::setSelectedEmail(const GameEmailModel *selectedEmail) noexcept
{
    if (m_selectedEmail == selectedEmail) return;

    m_selectedEmail = const_cast<GameEmailModel*>(selectedEmail);
    emit selectedEmailChanged();
}

void EmailClientPage::fillForDay(int day) noexcept
{
    GameEmailModel* greetingEmail = new GameEmailModel(this);
    greetingEmail->setFrom("stuff@temple-house.gov");
    greetingEmail->setTo("Everybody");
    greetingEmail->setSubject("Warm Welcome Our New System Operator!");
    greetingEmail->setIsReaded(true);
    greetingEmail->setHasAttachments(true);
    greetingEmail->setGroup(InboxGroup);
    greetingEmail->setContent(R"(I am delighted to extend a warm welcome to you as you embark on your journey with our team as a System Operator. Congratulations on your new position! Your expertise and skills will undoubtedly make a valuable contribution to our team, and we are thrilled to have you on board.
As you settle into your new role, please know that myself and the entire team are here to support you every step of the way. Should you have any questions or need assistance, do not hesitate to reach out. We believe that with your experience and dedication, you will excel in this role and be an integral part of our organization.
I look forward to seeing your contributions and witnessing your growth within our company. Once again, congratulations on your new position as a System Operator. Welcome to the team!

Warm regards,
Mr. Norton
)");
    m_emails.append(greetingEmail);

    refreshDisplayEmails();
}

void EmailClientPage::refreshDisplayEmails() noexcept
{
    m_emailObjects.clear();

    if (m_selectedGroup.isEmpty()) {
        foreach (auto email, m_emails) m_emailObjects.append(email);
        return;
    }

    foreach (auto email, m_emails) {
        if (email->group() != m_selectedGroup) continue;

        m_emailObjects.append(email);
    }
}

void EmailClientPage::createObjectSections()
{
    m_accountSection = new GameEmailSectionModel(this);
    //Eve Trent
    m_accountSection->setTitle("et@temple-house.gov");
    m_accountSection->setGroup("");

    m_inBoxSection = new GameEmailSectionModel(this);
    m_inBoxSection->setTitle("Inbox");
    m_inBoxSection->setGroup(InboxGroup);

    m_outBoxSection = new GameEmailSectionModel(this);
    m_outBoxSection->setTitle("Outbox");
    m_outBoxSection->setGroup(OutboxGroup);

    m_sentSection = new GameEmailSectionModel(this);
    m_sentSection->setTitle("Sent");
    m_sentSection->setGroup(SentGroup);

    m_trashSection = new GameEmailSectionModel(this);
    m_trashSection->setTitle("Trash");
    m_trashSection->setGroup(TrashGroup);

    m_sections.append(m_accountSection);
    m_sections.append(m_inBoxSection);
    m_sections.append(m_outBoxSection);
    m_sections.append(m_sentSection);
    m_sections.append(m_trashSection);
}

void EmailClientPage::fillObjectSections()
{
    m_sectionObjects.clear();

    foreach (auto section, m_sections) {
        m_sectionObjects.append(qobject_cast<QObject*>(section));
    }
}

void EmailClientPage::createSectionColumns()
{
    auto folderColumn = new GameTableColumn(this);
    folderColumn->setTitle("Folder");
    folderColumn->setField("title");
    folderColumn->setSelectable(true);
    folderColumn->setColumnWidth(170);
    m_foldersColumns.append(folderColumn);

    auto newColumn = new GameTableColumn(this);
    newColumn->setTitle("New");
    newColumn->setField("newCount");
    newColumn->setSelectable(true);
    newColumn->setColumnWidth(50);
    m_foldersColumns.append(newColumn);

    auto totalColumn = new GameTableColumn(this);
    totalColumn->setTitle("Total");
    totalColumn->setField("totalCount");
    totalColumn->setSelectable(true);
    totalColumn->setColumnWidth(70);
    m_foldersColumns.append(totalColumn);
}

void EmailClientPage::createEmailColumns()
{
    auto readedColumn = new GameTableColumn(this);
    readedColumn->setTitle("R");
    readedColumn->setField("isReadedImage");
    readedColumn->setSelectable(true);
    readedColumn->setColumnWidth(34);
    readedColumn->setFormatter("image");
    m_emailColumns.append(readedColumn);

    auto hasAttachmentColumn = new GameTableColumn(this);
    hasAttachmentColumn->setTitle("A");
    hasAttachmentColumn->setField("hasAttachmentImage");
    hasAttachmentColumn->setSelectable(true);
    hasAttachmentColumn->setColumnWidth(30);
    hasAttachmentColumn->setFormatter("image");
    m_emailColumns.append(hasAttachmentColumn);

    auto fromColumn = new GameTableColumn(this);
    fromColumn->setTitle("From");
    fromColumn->setField("from");
    fromColumn->setSelectable(true);
    fromColumn->setColumnWidth(90);
    m_emailColumns.append(fromColumn);

    auto toColumn = new GameTableColumn(this);
    toColumn->setTitle("To");
    toColumn->setField("to");
    toColumn->setSelectable(true);
    toColumn->setColumnWidth(90);
    m_emailColumns.append(toColumn);

    auto subjectColumn = new GameTableColumn(this);
    subjectColumn->setTitle("Subject");
    subjectColumn->setField("subject");
    subjectColumn->setSelectable(true);
    subjectColumn->setColumnWidth(90);
    m_emailColumns.append(subjectColumn);
}
