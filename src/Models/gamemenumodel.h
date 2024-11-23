#ifndef GAMEMENUMODEL_H
#define GAMEMENUMODEL_H

#include <QObject>
#include <QList>

class GameMenuModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool hasChildrens READ hasChildrens NOTIFY hasChildrensChanged FINAL)
    Q_PROPERTY(QList<GameMenuModel*> childrens READ childrens NOTIFY childrensChanged FINAL)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(bool bottomLine READ bottomLine WRITE setBottomLine NOTIFY bottomLineChanged FINAL)
    Q_PROPERTY(bool upperLine READ upperLine WRITE setUpperLine NOTIFY upperLineChanged FINAL)
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged FINAL)

private:
    QString m_title { "" };
    bool m_hasChildrens { false };
    QList<GameMenuModel*> m_childrens { QList<GameMenuModel*>() };
    QString m_icon { "" };
    bool m_bottomLine { false };
    bool m_upperLine { false };
    QString m_command { "" };

public:
    explicit GameMenuModel(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title);

    bool hasChildrens() const noexcept { return !m_childrens.isEmpty(); }

    QList<GameMenuModel*> childrens() const noexcept { return m_childrens; }

    QString icon() const noexcept { return m_icon; }
    void setIcon(const QString& icon) noexcept;

    bool bottomLine() const noexcept { return m_bottomLine; }
    void setBottomLine(bool bottomLine) noexcept;

    bool upperLine() const noexcept { return m_upperLine; }
    void setUpperLine(bool upperLine) noexcept;

    QString command() const noexcept { return m_command; }
    void setCommand(const QString& command) noexcept;

    void addChildren(GameMenuModel* children) noexcept;
    void addChildrenWithoutEmit(GameMenuModel* children) noexcept;

signals:
    void titleChanged();
    void hasChildrensChanged();
    void childrensChanged();
    void iconChanged();
    void bottomLineChanged();
    void upperLineChanged();
    void commandChanged();

};

#endif // GAMEMENUMODEL_H
