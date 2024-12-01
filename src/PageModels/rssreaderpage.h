#ifndef RSSREADERPAGE_H
#define RSSREADERPAGE_H

#include <QObject>
#include "../Models/gametreesectionmodel.h"
#include "../Models/gamerssitemmodel.h"

class RssReaderPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<GameTreeSectionModel*> tree READ tree NOTIFY treeChanged FINAL)

private:
    QList<GameTreeSectionModel*> m_tree { QList<GameTreeSectionModel*>() };
    QList<GameRssItemModel*> m_rssItems { QList<GameRssItemModel*>() };

public:
    explicit RssReaderPage(QObject *parent = nullptr);

    QList<GameTreeSectionModel*> tree() const noexcept { return m_tree; }

    void fillForDay(int day, const QSet<QString>& completedTasks);

private:
    void fillForFirst();

signals:
    void treeChanged();

};

#endif // RSSREADERPAGE_H
