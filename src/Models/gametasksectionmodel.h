#ifndef GAMETASKSECTIONMODEL_H
#define GAMETASKSECTIONMODEL_H

#include <QObject>
#include "gametaskmodel.h"

class GameTaskSectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool hasChildrens READ hasChildrens NOTIFY hasChildrensChanged FINAL)
    Q_PROPERTY(QList<GameTaskModel*> childrens READ childrens NOTIFY childrensChanged FINAL)

private:
    QString m_title { "" };
    QList<GameTaskModel*> m_innerTasks { QList<GameTaskModel*>() };

public:
    explicit GameTaskSectionModel(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    bool hasChildrens() const noexcept { return !m_innerTasks.isEmpty(); }

    QList<GameTaskModel*> childrens() const noexcept { return m_innerTasks; }

    void reassignInnerTasks(const QList<GameTaskModel*> tasks) noexcept;

    void clearInnerTasks() noexcept;

    void addInnerTask(GameTaskModel* task) noexcept;

signals:
    void titleChanged();
    void hasChildrensChanged();
    void isEndItemChanged();
    void childrensChanged();

};

#endif // GAMETASKSECTIONMODEL_H
