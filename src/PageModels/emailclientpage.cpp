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
    readedColumn->setTitle("Readed");
    readedColumn->setField("title");
    readedColumn->setSelectable(true);
    readedColumn->setColumnWidth(199);
    m_emailColumns.append(readedColumn);

    auto hasAttachmentColumn = new GameTableColumn(this);
    hasAttachmentColumn->setTitle("Has Attachment");
    hasAttachmentColumn->setField("title");
    hasAttachmentColumn->setSelectable(true);
    hasAttachmentColumn->setColumnWidth(199);
    m_emailColumns.append(hasAttachmentColumn);

    auto fromColumn = new GameTableColumn(this);
    fromColumn->setTitle("From");
    fromColumn->setField("title");
    fromColumn->setSelectable(true);
    fromColumn->setColumnWidth(199);
    m_emailColumns.append(fromColumn);

    auto toColumn = new GameTableColumn(this);
    toColumn->setTitle("To");
    toColumn->setField("title");
    toColumn->setSelectable(true);
    toColumn->setColumnWidth(199);
    m_emailColumns.append(toColumn);

    auto subjectColumn = new GameTableColumn(this);
    subjectColumn->setTitle("Subject");
    subjectColumn->setField("title");
    subjectColumn->setSelectable(true);
    subjectColumn->setColumnWidth(199);
    m_emailColumns.append(subjectColumn);
}

void EmailClientPage::fillObjectSections()
{
    m_sectionObjects.clear();

    foreach (auto section, m_sections) {
        m_sectionObjects.append(qobject_cast<QObject*>(section));
    }
}
