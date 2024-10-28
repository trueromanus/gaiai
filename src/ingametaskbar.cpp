#include "ingametaskbar.h"

InGameTaskBar::InGameTaskBar() {
    m_defaultNamesOfWindows.insert("shutdown", "Shut Down SmartCityOS");
    m_windowSizes.insert("shutdown", std::make_tuple(400, 210));
    m_uniqueWindows.insert("shutdown");

    m_commandToPageMapping.insert("shutdown", "Pages/ShutDownPage.qml");
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
        activateWindowByCommand(command);
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
    if (m_windowSizes.contains(command)) {
        auto sizeTuple = m_windowSizes.value(command);
        window->setWindowWidth(std::get<0>(sizeTuple));
        window->setWindowHeight(std::get<1>(sizeTuple));
    } else {
        window->setWindowWidth(100);
        window->setWindowHeight(100);
    }
    window->setX(100);
    window->setY(100);
    window->setParentItem(m_windowsContainer);
    if (m_uniqueWindows.contains(command)) window->setUniqueId(command);

    // create page (page it is content of window) inside window
    if (m_commandToPageMapping.contains(command)) createPageInsideWindow(m_commandToPageMapping.value(command), window, context, engine);

    m_windows.append(window);
}

void InGameTaskBar::activateWindow(InGameWindow *window)
{
    if (m_activeWindow == window) return;

    if (m_activeWindow != nullptr) m_activeWindow->setActivated(false);

    window->setActivated(true);
    m_activeWindow = window;
}

void InGameTaskBar::activateWindowByCommand(const QString &command)
{
    auto window = getWindowByUnique(command);
    if (window == nullptr) return;

    activateWindow(window);
}

bool InGameTaskBar::alreadyOpenedUniqueWindow(const QString &command)
{
    auto iterator = std::find_if(m_windows.cbegin(), m_windows.cend(), [command](InGameWindow* item){
        return item->uniqueId() == command;
    });
    return iterator != m_windows.cend();
}

InGameWindow *InGameTaskBar::getWindowByUnique(const QString &command)
{
    auto iterator = std::find_if(m_windows.cbegin(), m_windows.cend(), [command](InGameWindow* item){
        return item->uniqueId() == command;
    });
    if (iterator != m_windows.cend()) return nullptr;

    return *iterator;
}

QQuickItem* InGameTaskBar::createPageInsideWindow(const QString &path, InGameWindow *window, QQmlContext *context, QQmlEngine *engine)
{
    QUrl relativeUrl(path);
    auto fullUrl = context->resolvedUrl(relativeUrl);

    QQmlComponent component(engine, fullUrl, this);
    auto object = component.create(context);
    auto page = qobject_cast<QQuickItem*>(object);

    auto childrens = window->childItems();
    auto containerChildren = childrens.last();

    page->setParentItem(containerChildren);

    return page;
}
