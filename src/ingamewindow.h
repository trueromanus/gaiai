#ifndef INGAMEWINDOW_H
#define INGAMEWINDOW_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>

class InGameWindow : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setWindowWidth NOTIFY windowWidthChanged FINAL)
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged FINAL)
    Q_PROPERTY(bool activated READ activated NOTIFY activatedChanged FINAL)
    QML_ELEMENT
private:
    QString m_title { "" };
    int m_windowWidth { 0 };
    int m_windowHeight { 0 };
    QQuickItem* m_header { nullptr };
    bool m_activated { true };

public:
    explicit InGameWindow();

    QString title() const noexcept { return m_title; }
    void setTitle(const QString& title) noexcept;

    int windowWidth() const noexcept { return m_windowWidth; }
    void setWindowWidth(int windowWidth) noexcept;

    int windowHeight() const noexcept { return m_windowHeight; }
    void setWindowHeight(int windowHeight) noexcept;

    bool activated() const noexcept { return m_activated; }

protected:
    void componentComplete() override;

private:
    void refreshWindowHeight();

signals:
    void titleChanged();
    void windowWidthChanged();
    void windowHeightChanged();
    void activatedChanged();

};

#endif // INGAMEWINDOW_H
