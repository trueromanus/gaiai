#ifndef INGAMEWINDOWDEFAULTHEADER_H
#define INGAMEWINDOWDEFAULTHEADER_H

#include <QQuickItem>

class InGameWindowDefaultHeader : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(bool activated READ activated WRITE setActivated NOTIFY activatedChanged FINAL)
    QML_ELEMENT

private:
    QString m_title { "" };
    bool m_activated { false };

public:
    InGameWindowDefaultHeader();

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    bool activated() const noexcept { return m_activated; }
    void setActivated(bool activated) noexcept;

protected:
    void componentComplete() override;

signals:
    void titleChanged();
    void activatedChanged();

};

#endif // INGAMEWINDOWDEFAULTHEADER_H
