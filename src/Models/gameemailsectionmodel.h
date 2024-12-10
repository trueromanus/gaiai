#ifndef GAMEEMAILSECTIONMODEL_H
#define GAMEEMAILSECTIONMODEL_H

#include <QObject>

class GameEmailSectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(int newCount READ newCount NOTIFY newCountChanged FINAL)
    Q_PROPERTY(int totalCount READ totalCount NOTIFY totalCountChanged FINAL)

private:
    QString m_title { "" };
    int m_newCount { 0 };
    int m_totalCount { 0 };

public:
    explicit GameEmailSectionModel(QObject *parent = nullptr);

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    int newCount() const noexcept { return m_newCount; }
    int totalCount() const noexcept { return m_totalCount; }

signals:
    void titleChanged();
    void newCountChanged();
    void totalCountChanged();

};

#endif // GAMEEMAILSECTIONMODEL_H
