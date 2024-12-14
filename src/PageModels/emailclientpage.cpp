#include "emailclientpage.h"

EmailClientPage::EmailClientPage(QObject *parent)
    : QObject{parent}
{
    // folders columns

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

    // email columns

    auto readedColumn = new GameTableColumn(this);
    readedColumn->setTitle("R");
    readedColumn->setField("title");
    readedColumn->setSelectable(true);
    readedColumn->setColumnWidth(34);
    m_emailColumns.append(readedColumn);

    auto hasAttachmentColumn = new GameTableColumn(this);
    hasAttachmentColumn->setTitle("A");
    hasAttachmentColumn->setField("title");
    hasAttachmentColumn->setSelectable(true);
    hasAttachmentColumn->setColumnWidth(30);
    m_emailColumns.append(hasAttachmentColumn);

    auto fromColumn = new GameTableColumn(this);
    fromColumn->setTitle("From");
    fromColumn->setField("title");
    fromColumn->setSelectable(true);
    fromColumn->setColumnWidth(90);
    m_emailColumns.append(fromColumn);

    auto toColumn = new GameTableColumn(this);
    toColumn->setTitle("To");
    toColumn->setField("title");
    toColumn->setSelectable(true);
    toColumn->setColumnWidth(90);
    m_emailColumns.append(toColumn);

    auto subjectColumn = new GameTableColumn(this);
    subjectColumn->setTitle("Subject");
    subjectColumn->setField("title");
    subjectColumn->setSelectable(true);
    subjectColumn->setColumnWidth(90);
    m_emailColumns.append(subjectColumn);

    createObjectSections();
    fillObjectSections();
}

void EmailClientPage::createObjectSections()
{
    m_accountSection = new GameEmailSectionModel(this);
    //Eve Trent
    m_accountSection->setTitle("et.t-h@goverment");

    m_inBoxSection = new GameEmailSectionModel(this);
    m_inBoxSection->setTitle("Inbox");

    m_outBoxSection = new GameEmailSectionModel(this);
    m_outBoxSection->setTitle("Outbox");

    m_sentSection = new GameEmailSectionModel(this);
    m_sentSection->setTitle("Sent");

    m_trashSection = new GameEmailSectionModel(this);
    m_trashSection->setTitle("Trash");

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
