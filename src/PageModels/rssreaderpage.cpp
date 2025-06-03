#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "rssreaderpage.h"
#include "../Models/gamerssitemmodel.h"

RssReaderPage::RssReaderPage(QObject *parent)
    : QObject{parent}
{
    loadRssItems("en");
}

void RssReaderPage::setSelectedSection(QObject *selectedSection) noexcept
{
    if (m_selectedSection == selectedSection) return;

    m_selectedSection = selectedSection;
    emit selectedSectionChanged();

    auto section = qobject_cast<GameTreeSectionModel*>(selectedSection);
    if (section == nullptr) return;

    QSet<QString> items;
    if (section->hasChildrens()) {
        foreach (auto children, section->childrens()) {
            auto topic = children->command();
            if (!topic.isEmpty()) items.insert(children->command());
        }
    } else {
        items.insert(section->command());
    }

    filterItems(items);
}

void RssReaderPage::fillForDay(int day, const QSet<QString>& completedTasks)
{
    switch (day) {
        case 1:
            fillForFirst();
            break;
    }
}

void RssReaderPage::fillForFirst()
{
    m_dayRssItems.clear();

    foreach (auto rssItem, m_rssItems) {
        if (rssItem->day() == 1) m_dayRssItems.append(rssItem);
    }
}

void RssReaderPage::loadRssItems(const QString& language)
{
    //load tree
    m_tree.clear();

    QFile treeFile(":/qt/qml/gaiai/TextContents/newsTree." + language + ".json");
    if (!treeFile.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto treeContent = treeFile.readAll();
    treeFile.close();

    auto treeDocument = QJsonDocument::fromJson(treeContent);
    auto treeArray = treeDocument.array();

    foreach (auto item, treeArray) {
        auto sectionObject = item.toObject();

        auto section = new GameTreeSectionModel(this);
        section->setTitle(sectionObject.value("section").toString());

        auto subSections = sectionObject.value("subsections").toArray();
        foreach (auto subSection, subSections) {
            auto subSectionObject = subSection.toObject();
            auto cityCitizenSection = new GameTreeSectionModel(this);

            cityCitizenSection->setTitle(subSectionObject.value("title").toString());

            auto command = subSectionObject.contains("id") ? subSectionObject.value("id").toString() : "";
            if (!command.isEmpty()) cityCitizenSection->setCommand(command);

            section->addSubSection(cityCitizenSection);
        }

        m_tree.append(section);
    }

    // load contents
    m_rssItems.clear();

    QFile file(":/qt/qml/gaiai/TextContents/newsContents." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto item, array) {
        GameRssItemModel* model = new GameRssItemModel(this);
        auto object = item.toObject();
        model->setTopic(object.value("topic").toString());
        model->setIcon(object.value("icon").toString() + ".png");
        model->setDay(object.value("day").toInt());
        model->setHeader(object.value("header").toString());
        model->setContent(object.value("text").toString());

        m_rssItems.append(model);
    }
}

void RssReaderPage::filterItems(QSet<QString> items)
{
    m_filteredRssItems.clear();

    foreach (auto rssItem, m_dayRssItems) {
        auto insideTopic = items.contains(rssItem->topic());
        if (insideTopic) m_filteredRssItems.append(rssItem);
    }

    emit filteredRssItemsChanged();
}
