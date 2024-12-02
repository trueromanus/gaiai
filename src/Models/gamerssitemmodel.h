#ifndef GAMERSSITEMMODEL_H
#define GAMERSSITEMMODEL_H

#include <QObject>

class GameRssItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged FINAL)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged FINAL)
    Q_PROPERTY(QString topic READ topic WRITE setTopic NOTIFY topicChanged FINAL)
    Q_PROPERTY(int day READ day WRITE setDay NOTIFY dayChanged FINAL)

private:
    QString m_icon { "" };
    QString m_header { "" };
    QString m_content { "" };
    QString m_topic { "" };
    int m_day { 0 };

public:
    explicit GameRssItemModel(QObject *parent = nullptr);

    QString icon() const noexcept { return m_icon; }
    void setIcon(const QString& icon) noexcept;

    QString header() const noexcept { return m_header; }
    void setHeader(const QString& header) noexcept;

    QString content() const noexcept { return m_content; }
    void setContent(const QString& content) noexcept;

    QString topic() const noexcept { return m_topic; }
    void setTopic(const QString& topic) noexcept;

    int day() const noexcept { return m_day; }
    void setDay(int day) noexcept;

signals:
    void iconChanged();
    void headerChanged();
    void contentChanged();
    void topicChanged();
    void dayChanged();

};

#endif // GAMERSSITEMMODEL_H
