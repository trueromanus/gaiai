#ifndef GAMETASKMODEL_H
#define GAMETASKMODEL_H

#include <QObject>

class GameTaskModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString parentId READ parentId NOTIFY parentIdChanged FINAL)
    Q_PROPERTY(bool completed READ completed WRITE setCompleted NOTIFY completedChanged FINAL)
    Q_PROPERTY(bool isMandatory READ isMandatory NOTIFY isMandatoryChanged FINAL)
    Q_PROPERTY(int day READ day NOTIFY dayChanged FINAL)
    Q_PROPERTY(bool hasChildrens READ hasChildrens NOTIFY hasChildrensChanged FINAL)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged FINAL)

private:
    QString m_title { "" };
    QString m_parentId { "" };
    bool m_completed { false };
    bool m_isMandatory { false };
    int m_day { 0 };
    std::function<bool()> m_action { nullptr };
    QString m_description { "" };

public:
    explicit GameTaskModel(bool isMandatory, const QString& title, const QString& parentId, int day, std::function<bool()> action, QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }

    QString parentId() const noexcept { return m_parentId; }

    bool completed() const noexcept { return m_completed; }
    void setCompleted(bool completed) noexcept;

    bool isMandatory() const noexcept { return m_isMandatory; }

    int day() const noexcept { return m_day; }

    void checkCompleted() noexcept;

    bool hasChildrens() const noexcept { return false; }

    QString description() const noexcept { return m_description; }
    void setDescription(const QString& description) noexcept;

signals:
    void titleChanged();
    void parentIdChanged();
    void completedChanged();
    void isMandatoryChanged();
    void dayChanged();
    void hasChildrensChanged();
    void descriptionChanged();

};

#endif // GAMETASKMODEL_H
