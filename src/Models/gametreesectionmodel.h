#ifndef GAMETREESECTIONMODEL_H
#define GAMETREESECTIONMODEL_H

#include <QObject>

class GameTreeSectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged FINAL)
    Q_PROPERTY(bool hasChildrens READ hasChildrens NOTIFY hasChildrensChanged FINAL)
    Q_PROPERTY(QList<GameTreeSectionModel*> childrens READ childrens NOTIFY childrensChanged FINAL)

private:
    QString m_title { "" };
    QString m_command { "" };
    QList<GameTreeSectionModel*> m_childrens { QList<GameTreeSectionModel*>() };

public:
    explicit GameTreeSectionModel(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    QString command() const noexcept { return m_command; }
    void setCommand(const QString& command) noexcept;

    bool hasChildrens() const noexcept { return !m_childrens.isEmpty(); }

    QList<GameTreeSectionModel*> childrens() const noexcept { return m_childrens; }

    void addSubSection(GameTreeSectionModel* subsection) noexcept;

signals:
    void titleChanged();
    void hasChildrensChanged();
    void childrensChanged();
    void commandChanged();

};

#endif // GAMETREESECTIONMODEL_H
