#include "emailclientpage.h"

EmailClientPage::EmailClientPage(QObject *parent)
    : QObject{parent}
{
    createSectionColumns();
    createEmailColumns();

    createObjectSections();
    fillObjectSections();
}

void EmailClientPage::setSelectedGroup(const QString &selectedGroup) noexcept
{
    if (m_selectedGroup == selectedGroup) return;

    m_selectedGroup = selectedGroup;
    emit selectedGroupChanged();

    refreshDisplayEmails();
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
    greetingEmail->setContent(R"(I am delighted to extend a warm welcome to newcomer as you embark on your journey with our team as a System Operator.
Congratulations on your new position! Your expertise and skills will undoubtedly make a valuable contribution to our team, and we are thrilled to have you on board.
As newcomer settle into new role, please know that myself and the entire team are here to support on every step of the way.
We believe that experience and dedication, we will excel and newcomer be an integral part of our organization.
I look forward to seeing newcomer contributions and witnessing his growth within our company. Welcome to the team!

Warm regards,
Mayor of the city
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

    emit emailsChanged();
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

    m_sections.append(m_accountSection);
    m_sections.append(m_inBoxSection);
    m_sections.append(m_outBoxSection);
    m_sections.append(m_sentSection);
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
    readedColumn->setTitle("columnreadedvalueemail");
    readedColumn->setField("isReadedImage");
    readedColumn->setSelectable(true);
    readedColumn->setColumnWidth(34);
    readedColumn->setFormatter("image");
    readedColumn->setColumnHeaderFormatter("image");
    readedColumn->setColumnHeaderWidth(19);
    readedColumn->setColumnHeaderHeight(15);
    m_emailColumns.append(readedColumn);

    auto hasAttachmentColumn = new GameTableColumn(this);
    hasAttachmentColumn->setTitle("columnattachmentvaluemail");
    hasAttachmentColumn->setField("hasAttachmentImage");
    hasAttachmentColumn->setSelectable(true);
    hasAttachmentColumn->setColumnWidth(30);
    hasAttachmentColumn->setFormatter("image");
    hasAttachmentColumn->setColumnHeaderFormatter("image");
    hasAttachmentColumn->setColumnHeaderWidth(16);
    hasAttachmentColumn->setColumnHeaderHeight(16);
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
