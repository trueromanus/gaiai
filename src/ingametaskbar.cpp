#include "ingametaskbar.h"
#include "ingamewindowpage.h"

InGameTaskBar::InGameTaskBar() {
    adjustShutDownPage();
    adjustOnboardingPage();
    adjustSmartTrackerPage();
    adjustRssReaderPage();
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

void InGameTaskBar::createDefaultWindow(const QString& command, int position)
{
    if (alreadyOpenedUniqueWindow(command)) {
        activateWindowByCommand(command);
        return;
    }

    auto context = qmlContext(this);
    auto engine = qmlEngine(this);
    QUrl relativeUrl("Controls/DefaultWindow.qml");
    auto fullUrl = context->resolvedUrl(relativeUrl);

    QQmlComponent* component = new QQmlComponent(engine, fullUrl, this);
    auto object = component->create(context);
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
    if (position == 0) {
        window->setX(0);
        window->setY(0);
    }
    if (position == 1) {
        auto parentItem = qobject_cast<QQuickItem*>(parent());
        auto parentWidth = parentItem->width() / 2;
        auto parentHeight = parentItem->height() / 2;
        window->setX(parentWidth - (window->width() / 2));
        window->setY(parentHeight - (window->height() / 2));
    }
    window->setParent(m_windowsContainer);
    window->setParentItem(m_windowsContainer);
    if (m_uniqueWindows.contains(command)) window->setUniqueId(command);

    connect(window, &InGameWindow::windowClosed, this, &InGameTaskBar::removeWindow);

    // create page (page it is content of window) inside window
    if (m_commandToPageMapping.contains(command)) createPageInsideWindow(m_commandToPageMapping.value(command), window, context, engine);

    m_windows.insert(window, component);

    activateWindow(window);
}

void InGameTaskBar::activateWindow(InGameWindow *window)
{
    if (m_activeWindow == window) return;

    auto windows = m_windows.keys();
    foreach (auto windowKey, windows) {
        if (windowKey == window) continue;

        windowKey->setActivated(false);
    }

    window->setActivated(true);
    m_activeWindow = window;

    auto childrens = m_windowsContainer->childItems();
    if (childrens.size() == 1) return;

    //move element on top of all items
    auto lastElement = childrens.last();
    if (lastElement == window) return;

    window->stackAfter(lastElement);
}

void InGameTaskBar::activateWindowByCommand(const QString &command)
{
    auto window = getWindowByUnique(command);
    if (window == nullptr) return;

    activateWindow(window);
}

bool InGameTaskBar::alreadyOpenedUniqueWindow(const QString &command)
{
    auto keys = m_windows.keys();
    auto iterator = std::find_if(keys.cbegin(), keys.cend(), [command](InGameWindow* item){
        return item->uniqueId() == command;
    });
    return iterator != keys.cend();
}

InGameWindow *InGameTaskBar::getWindowByUnique(const QString &command)
{
    auto keys = m_windows.keys();
    auto iterator = std::find_if(keys.cbegin(), keys.cend(), [command](InGameWindow* item){
        return item->uniqueId() == command;
    });
    if (iterator != keys.cend()) return nullptr;

    return *iterator;
}

QQuickItem* InGameTaskBar::createPageInsideWindow(const QString &path, InGameWindow *window, QQmlContext *context, QQmlEngine *engine)
{
    QUrl relativeUrl(path);
    auto fullUrl = context->resolvedUrl(relativeUrl);

    QQmlComponent component(engine, fullUrl, this);
    auto object = component.create(context);
    auto page = qobject_cast<InGameWindowPage*>(object);

    auto childrens = window->childItems();
    auto containerChildren = childrens.last();

    page->setParent(containerChildren);
    page->setParentItem(containerChildren);

    connect(page, &InGameWindowPage::closeContainerWindow, window, &InGameWindow::closeWindow);

    return page;
}

void InGameTaskBar::refreshVisibleWindows()
{

}

void InGameTaskBar::adjustShutDownPage()
{
    m_defaultNamesOfWindows.insert(m_shutDownPage, "Shut Down SmartCityOS");
    m_windowSizes.insert(m_shutDownPage, std::make_tuple(400, 195));
    m_uniqueWindows.insert(m_shutDownPage);
    m_commandToPageMapping.insert(m_shutDownPage, "Pages/ShutDownPage.qml");
}

void InGameTaskBar::adjustOnboardingPage()
{
    m_defaultNamesOfWindows.insert(m_onboardingPage, "Welcome");
    m_windowSizes.insert(m_onboardingPage, std::make_tuple(488, 355));
    m_uniqueWindows.insert(m_onboardingPage);
    m_commandToPageMapping.insert(m_onboardingPage, "Pages/OnboardingPage.qml");
}

void InGameTaskBar::adjustSmartTrackerPage()
{
    m_defaultNamesOfWindows.insert(m_smartTrackerPage, "SmartTracker");
    m_windowSizes.insert(m_smartTrackerPage, std::make_tuple(558, 355));
    m_uniqueWindows.insert(m_smartTrackerPage);
    m_commandToPageMapping.insert(m_smartTrackerPage, "Pages/SmartTrackerPage.qml");
}

void InGameTaskBar::adjustRssReaderPage()
{
    m_defaultNamesOfWindows.insert(m_rssReaderPage, "RSS Reader");
    m_windowSizes.insert(m_rssReaderPage, std::make_tuple(650, 355));
    m_uniqueWindows.insert(m_rssReaderPage);
    m_commandToPageMapping.insert(m_rssReaderPage, "Pages/RssReaderPage.qml");
}

void InGameTaskBar::removeWindow(InGameWindow *window)
{
    if (!m_windows.contains(window)) return;

    auto component = m_windows.value(window);
    component->deleteLater();
    m_windows.remove(window);

    window->setParentItem(nullptr);
    window->deleteLater();

    refreshVisibleWindows();
}
