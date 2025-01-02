#ifndef GAMEEMAILSECTIONMODEL_H
#define GAMEEMAILSECTIONMODEL_H

#include <QObject>

class GameEmailSectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(int newCount READ newCount NOTIFY newCountChanged FINAL)
    Q_PROPERTY(int totalCount READ totalCount NOTIFY totalCountChanged FINAL)
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged FINAL)
    Q_PROPERTY(bool highlight READ highlight NOTIFY highlightChanged FINAL)

private:
    QString m_title { "" };
    int m_newCount { 0 };
    int m_totalCount { 0 };
    QString m_group { "" };

public:
    explicit GameEmailSectionModel(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    int newCount() const noexcept { return m_newCount; }
    int totalCount() const noexcept { return m_totalCount; }

    QString group() const noexcept { return m_group; }
    void setGroup(const QString& group) noexcept;

    bool highlight() const noexcept { return m_newCount > 0; }

    void addToCount(bool isNew);
    void refreshCounts();
    void resetCounts();

signals:
    void titleChanged();
    void newCountChanged();
    void totalCountChanged();
    void groupChanged();
    void highlightChanged();

};

#endif // GAMEEMAILSECTIONMODEL_H
