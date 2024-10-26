#include <QQmlContext>
#include "ingametaskbar.h"

InGameTaskBar::InGameTaskBar() {
    m_defaultNamesOfWindows.insert("shutdown", "Shut Down SmartCityOS");
    m_uniqueWindows.insert("shutdown");
}

void InGameTaskBar::setActiveWindow(int activeWindow) noexcept
{
    if (m_activeWindow == activeWindow) return;

    m_activeWindow = activeWindow;
    emit activeWindowChanged();
}

void InGameTaskBar::setStartMenuOpened(bool startMenuOpened) noexcept
{
    if (m_startMenuOpened == startMenuOpened) return;

    m_startMenuOpened = startMenuOpened;
    emit startMenuOpenedChanged();
}

void InGameTaskBar::setWindowsContainer(const QQuickItem* windowsContainer) noexcept
{
    if (m_windowsContainer == windowsContainer) return;

    m_windowsContainer = const_cast<QQuickItem*>(windowsContainer);
    emit windowsContainerChanged();
}

void InGameTaskBar::showPreviousVisibleItems()
{

}

void InGameTaskBar::showNextVisibleItems()
{

}

void InGameTaskBar::refreshVisibleItems()
{

}

void InGameTaskBar::createDefaultWindow(const QString& command)
{
    if (alreadyOpenedUniqueWindow(command)) {
        //TODO:activate opened window
        return;
    }

    auto context = qmlContext(this);
    auto engine = qmlEngine(this);
    QUrl relativeUrl("Controls/DefaultWindow.qml");
    auto fullUrl = context->resolvedUrl(relativeUrl);

    QQmlComponent component(engine, fullUrl, this);
    auto object = component.create(context);
    auto window = qobject_cast<InGameWindow*>(object);

    window->setTitle(m_defaultNamesOfWindows.value(command));
    window->setWindowWidth(200);
    window->setWindowHeight(100);
    window->setX(100);
    window->setY(100);
    window->setParentItem(m_windowsContainer);
    if (m_uniqueWindows.contains(command)) window->setUniqueId(command);

    m_windows.append(window);
}

bool InGameTaskBar::alreadyOpenedUniqueWindow(const QString &command)
{
    auto iterator = std::find_if(m_windows.cbegin(), m_windows.cend(), [command](InGameWindow* item){
        return item->uniqueId() == command;
    });
    return iterator != m_windows.cend();
}
