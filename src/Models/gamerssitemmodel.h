#ifndef GAMERSSITEMMODEL_H
#define GAMERSSITEMMODEL_H

#include <QObject>

class GameRssItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged FINAL)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged FINAL)

private:
    QString m_icon { "" };
    QString m_header { "" };
    QString m_content { "" };

public:
    explicit GameRssItemModel(QObject *parent = nullptr);

    QString icon() const noexcept { return m_icon; }
    void setIcon(const QString& icon) noexcept;

    QString header() const noexcept { return m_header; }
    void setHeader(const QString& header) noexcept;

    QString content() const noexcept { return m_content; }
    void setContent(const QString& content) noexcept;

signals:
    void iconChanged();
    void headerChanged();
    void contentChanged();

};

#endif // GAMERSSITEMMODEL_H
