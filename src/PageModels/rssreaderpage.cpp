#include "rssreaderpage.h"

RssReaderPage::RssReaderPage(QObject *parent)
    : QObject{parent}
{
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
    medicineSection->addSubSection(medicineLocalNewsSection);

    m_tree.append(medicineSection);
}

void RssReaderPage::setSelectedSection(QObject *selectedSection) noexcept
{
    if (m_selectedSection == selectedSection) return;

    m_selectedSection = selectedSection;
    emit selectedSectionChanged();
}

void RssReaderPage::fillForDay(int day, const QSet<QString>& completedTasks)
{
    m_rssItems.clear();

    switch (day) {
        case 1:
            fillForFirst();
            break;
    }
}

void RssReaderPage::fillForFirst()
{
    auto rssItem = new GameRssItemModel();
    rssItem->setHeader("");
    rssItem->setContent("");
    rssItem->setIcon("");
    m_rssItems.append(rssItem);
}

void RssReaderPage::filterItems()
{
    m_filteredRssItems.clear();


}
