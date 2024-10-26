#ifndef INGAMETASKBAR_H
#define INGAMETASKBAR_H

#include <QQuickItem>
#include <QQmlPropertyMap>
#include "ingamewindow.h"

class InGameTaskBar : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int activeWindow READ activeWindow WRITE setActiveWindow NOTIFY activeWindowChanged FINAL)
    Q_PROPERTY(QVariantList visibleItems READ visibleItems NOTIFY visibleItemsChanged FINAL)
    Q_PROPERTY(bool hasLeftItems READ hasLeftItems NOTIFY hasLeftItemsChanged FINAL)
    Q_PROPERTY(bool hasRightItems READ hasRightItems NOTIFY hasRightItemsChanged FINAL)
    Q_PROPERTY(bool startMenuOpened READ startMenuOpened WRITE setStartMenuOpened NOTIFY startMenuOpenedChanged FINAL)
    Q_PROPERTY(QQuickItem* windowsContainer READ windowsContainer WRITE setWindowsContainer NOTIFY windowsContainerChanged FINAL)
    QML_ELEMENT

private:
    int m_activeWindow { -1 };
    QList<InGameWindow*> m_windows { QList<InGameWindow*>() };
    QVariantList m_visibleItems { QVariantList() };
    bool m_hasLeftItems { false };
    bool m_hasRightItems { false };
    int m_startActiveWindows { -1 };
    bool m_startMenuOpened { false };
    QQuickItem* m_windowsContainer { nullptr };
    QMap<QString, QString> m_defaultNamesOfWindows { QMap<QString, QString>() };
    QSet<QString> m_uniqueWindows { QSet<QString>() };

public:
    InGameTaskBar();

    int activeWindow() const noexcept { return m_activeWindow; }
    void setActiveWindow(int activeWindow) noexcept;

    QVariantList visibleItems() const noexcept { return m_visibleItems; }
    bool hasLeftItems() const noexcept { return m_hasLeftItems; }
    bool hasRightItems() const noexcept { return m_hasRightItems; }

    bool startMenuOpened() const noexcept { return m_startMenuOpened; }
    void setStartMenuOpened(bool startMenuOpened) noexcept;

    QQuickItem* windowsContainer() const noexcept { return m_windowsContainer; }
    void setWindowsContainer(const QQuickItem* windowsContainer) noexcept;

    Q_INVOKABLE void showPreviousVisibleItems();
    Q_INVOKABLE void showNextVisibleItems();
    Q_INVOKABLE void refreshVisibleItems();
    Q_INVOKABLE void createDefaultWindow(const QString& command);

private:
    bool alreadyOpenedUniqueWindow(const QString& command);

signals:
    void activeWindowChanged();
    void visibleItemsChanged();
    void hasLeftItemsChanged();
    void hasRightItemsChanged();
    void startMenuOpenedChanged();
    void windowsContainerChanged();

};

#endif // INGAMETASKBAR_H
