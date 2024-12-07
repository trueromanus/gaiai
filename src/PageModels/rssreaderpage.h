#ifndef RSSREADERPAGE_H
#define RSSREADERPAGE_H

#include <QObject>
#include "../Models/gametreesectionmodel.h"
#include "../Models/gamerssitemmodel.h"

class RssReaderPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTreeSectionModel*> tree READ tree NOTIFY treeChanged FINAL)
    Q_PROPERTY(QList<GameRssItemModel*> filteredRssItems READ filteredRssItems NOTIFY filteredRssItemsChanged FINAL)
    Q_PROPERTY(QObject* selectedSection READ selectedSection WRITE setSelectedSection NOTIFY selectedSectionChanged FINAL)

private:
    QList<GameTreeSectionModel*> m_tree { QList<GameTreeSectionModel*>() };
    QList<GameRssItemModel*> m_dayRssItems { QList<GameRssItemModel*>() };
    QList<GameRssItemModel*> m_filteredRssItems { QList<GameRssItemModel*>() };
    QList<GameRssItemModel*> m_rssItems { QList<GameRssItemModel*>() };
    QObject* m_selectedSection { nullptr };

public:
    explicit RssReaderPage(QObject *parent = nullptr);

    QList<GameTreeSectionModel*> tree() const noexcept { return m_tree; }

    QList<GameRssItemModel*> filteredRssItems() const noexcept { return m_filteredRssItems; }

    QObject* selectedSection() const noexcept { return m_selectedSection; }
    void setSelectedSection(QObject* selectedSection) noexcept;

    void fillForDay(int day, const QSet<QString>& completedTasks);

private:
    void fillForFirst();
    void loadRssItems(const QString& language);
    void filterItems(QSet<QString> items);

signals:
    void treeChanged();
    void filteredRssItemsChanged();
    void selectedSectionChanged();

};

#endif // RSSREADERPAGE_H
