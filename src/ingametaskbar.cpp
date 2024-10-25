#include <QQmlContext>
#include "ingametaskbar.h"

InGameTaskBar::InGameTaskBar() {}

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

void InGameTaskBar::showPreviousVisibleItems()
{

}

void InGameTaskBar::showNextVisibleItems()
{

}

void InGameTaskBar::refreshVisibleItems()
{

}

void InGameTaskBar::createDefaultWindow(const QString &title, int mode, QQuickItem* parent)
{
    auto context = qmlContext(this);
    auto engine = qmlEngine(this);
    QUrl relativeUrl("Controls/DefaultWindow.qml");
    auto fullUrl = context->resolvedUrl(relativeUrl);

    QQmlComponent component(engine, fullUrl, this);
    auto object = component.create(context);
    auto window = qobject_cast<InGameWindow*>(object);
    window->setTitle(title);
    window->setWindowWidth(200);
    window->setWindowHeight(100);
    window->setX(100);
    window->setY(100);
    window->setParentItem(parent);

    m_windows.append(window);
}
