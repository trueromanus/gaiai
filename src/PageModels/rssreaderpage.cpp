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

    auto peopleSection = new GameTreeSectionModel(this);
    peopleSection->setTitle("People");

    auto cityCitizenSection = new GameTreeSectionModel(this);
    cityCitizenSection->setTitle("City citizens");
    peopleSection->addSubSection(cityCitizenSection);

    auto localNewsSection = new GameTreeSectionModel(this);
    localNewsSection->setTitle("Local news");
    peopleSection->addSubSection(localNewsSection);

    m_tree.append(peopleSection);

    auto lettersSection = new GameTreeSectionModel(this);
    lettersSection->setTitle("Letters");

    auto funSection = new GameTreeSectionModel(this);
    funSection->setTitle("Fun");
    lettersSection->addSubSection(funSection);

    auto praiseSection = new GameTreeSectionModel(this);
    praiseSection->setTitle("Praise");
    lettersSection->addSubSection(praiseSection);

    auto criticismSection = new GameTreeSectionModel(this);
    criticismSection->setTitle("Criticism");
    lettersSection->addSubSection(criticismSection);

    m_tree.append(lettersSection);

    auto lawSection = new GameTreeSectionModel(this);
    lawSection->setTitle("Law");

    auto incidentsSection = new GameTreeSectionModel(this);
    incidentsSection->setTitle("Incidents in the city");
    lawSection->addSubSection(incidentsSection);

    auto criminalsSection = new GameTreeSectionModel(this);
    criminalsSection->setTitle("Criminals");
    lawSection->addSubSection(criminalsSection);

    m_tree.append(lawSection);

    auto medicineSection = new GameTreeSectionModel(this);
    medicineSection->setTitle("Medicine");

    auto medicineLocalNewsSection = new GameTreeSectionModel(this);
    medicineLocalNewsSection->setTitle("Local news");
    medicineLocalNewsSection->setCommand("medicinelocalnews");
    medicineSection->addSubSection(medicineLocalNewsSection);

    m_tree.append(medicineSection);
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
