#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "emailclientpage.h"

EmailClientPage::EmailClientPage(QObject *parent)
    : QObject{parent}
{
    createSectionColumns();
    createEmailColumns();

    createObjectSections();
    fillObjectSections();

    loadEmails("en");
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

    if (!m_selectedEmail->isReaded()) {
        m_selectedEmail->setIsReaded(true);
        emit emailsChanged();
    }
}

void EmailClientPage::fillForDay(int day) noexcept
{
    if (day == 1) {
        auto onboardingEmail1 = m_emailTemplates.value("onboardinginbox1");
        auto onboardingEmail2 = m_emailTemplates.value("onboardinginbox2");

        m_emails.append(onboardingEmail1);
        m_emails.append(onboardingEmail2);
    }

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

void EmailClientPage::loadEmails(const QString& language)
{
    m_emailTemplates.clear();

    QFile file(":/qt/qml/gaiai/TextContents/emailContents." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto item, array) {
        GameEmailModel* model = new GameEmailModel(this);
        auto object = item.toObject();

        model->setFrom(object.value("from").toString());
        model->setTo(object.value("to").toString());
        model->setSubject(object.value("subject").toString());
        model->setGroup(object.value("group").toString());
        model->setContent(object.value("content").toString());
        model->setHasAttachments(object.value("hasAttachments").toBool());

        auto identifier = object.value("identifier").toString();

        m_emailTemplates.insert(identifier, model);
    }
}
