#include <cmath>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "ingametaskbar.h"
#include "ingamewindowpage.h"

InGameTaskBar::InGameTaskBar() {
    loadWindows("en");
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

void InGameTaskBar::componentComplete()
{
    QQuickItem::componentComplete();
}

void InGameTaskBar::refreshVisibleItems()
{
    fillVisibleItems();
}

void InGameTaskBar::createDefaultWindow(const QString& command, int position, const QString& arguments)
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
    if (!arguments.isEmpty()) window->setArguments(arguments);
    if (m_notShowOnTaskBar.contains(command)) window->setNotShowOnTaskBar(true);

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

    m_windowCounter += 1;
    window->setOrder(m_windowCounter);

    connect(window, &InGameWindow::windowClosed, this, &InGameTaskBar::removeWindow);

    // create page (page it is content of window) inside window
    if (m_commandToPageMapping.contains(command)) createPageInsideWindow(m_commandToPageMapping.value(command), window, context, engine);

    m_windows.insert(window, component);

    activateWindow(window);

    fillVisibleItems();
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
    auto containerChildren = childrens.value(childrens.size() - 2);

    page->setParent(containerChildren);
    page->setParentItem(containerChildren);

    connect(page, &InGameWindowPage::closeContainerWindow, window, &InGameWindow::closeWindow);

    return page;
}

void InGameTaskBar::fillVisibleItems()
{
    m_visibleItems.clear();

    auto windows = m_windows.keys();
    foreach (auto window, windows) {
        if (window->notShowOnTaskBar()) continue;

        m_visibleItems.append(window);
    }
    auto taskBarWidth = static_cast<double>(width() - 72);  // 72 width of smart button, TODO replace on bindable property
    auto count = static_cast<double>(m_visibleItems.size());
    if (count < 5) count = 5;
    m_widthVisibleItem = std::ceil(taskBarWidth / count);

    std::sort(
        m_visibleItems.begin(),
        m_visibleItems.end(),
        [](InGameWindow* left, InGameWindow* right) {
            return left->order() < right->order();
        }
    );

    emit widthVisibleItemChanged();
    emit visibleItemsChanged();
}

void InGameTaskBar::loadWindows(const QString& language)
{
    m_defaultNamesOfWindows.clear();
    m_windowSizes.clear();
    m_uniqueWindows.clear();
    m_commandToPageMapping.clear();
    m_notShowOnTaskBar.clear();

    QFile file(":/qt/qml/gaiai/TextContents/windows." + language + ".json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    auto content = file.readAll();
    file.close();

    auto document = QJsonDocument::fromJson(content);
    auto array = document.array();

    foreach (auto item, array) {
        auto object = item.toObject();

        auto command = object.value("command").toString();
        auto component = object.value("component").toString();
        m_commandToPageMapping.insert(command, component);

        auto isUnique = object.value("isUnique").toBool();
        if (isUnique) m_uniqueWindows.insert(command);

        auto width = object.value("width").toInt();
        auto height = object.value("height").toInt();

        m_windowSizes.insert(command, std::make_tuple(width, height));

        auto defaultTitle = object.value("defaultTitle").toString();
        m_defaultNamesOfWindows.insert(command, defaultTitle);

        auto notShowOnTaskBar = object.value("notShowOnTaskBar").toBool();
        if (notShowOnTaskBar) m_notShowOnTaskBar.insert(command);
    }
}

void InGameTaskBar::removeWindow(InGameWindow *window)
{
    if (!m_windows.contains(window)) return;

    auto component = m_windows.value(window);
    component->deleteLater();
    m_windows.remove(window);

    window->setParentItem(nullptr);
    window->deleteLater();

    fillVisibleItems();
}
