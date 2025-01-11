#include "ingamewindow.h"

InGameWindow::InGameWindow()
{}

void InGameWindow::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void InGameWindow::setWindowWidth(int windowWidth) noexcept
{
    if (m_windowWidth == windowWidth) return;

    m_windowWidth = windowWidth;
    emit windowWidthChanged();

    setWidth(m_windowWidth);
}

void InGameWindow::setWindowHeight(int windowHeight) noexcept
{
    if (m_windowHeight == windowHeight) return;

    m_windowHeight = windowHeight;
    emit windowHeightChanged();

    refreshWindowHeight();
}

void InGameWindow::setActivated(bool activated) noexcept
{
    if (m_activated == activated) return;

    m_activated = activated;
    emit activatedChanged();
}

void InGameWindow::setUniqueId(const QString &uniqueId) noexcept
{
    if (m_uniqueId == uniqueId) return;

    m_uniqueId = uniqueId;
    emit uniqueIdChanged();
}

void InGameWindow::setNotShowOnTaskBar(bool notShowOnTaskBar) noexcept
{
    if (m_notShowOnTaskBar == notShowOnTaskBar) return;

    m_notShowOnTaskBar = notShowOnTaskBar;
    emit notShowOnTaskBarChanged();
}

void InGameWindow::componentComplete()
{
    auto childrens = children();
    foreach (auto children, childrens) {
        auto elementMode = children->property("elementMode");
        if (elementMode.isNull()) continue;

        auto mode = elementMode.toString();
        if (mode == "windowheader") {
            m_header = qobject_cast<QQuickItem*>(children);
        }
    }

    QQuickItem::componentComplete();
    refreshWindowHeight();
}

void InGameWindow::refreshWindowHeight()
{
    auto newHeight = m_windowHeight + (m_header != nullptr ? m_header->height() : 0);
    setHeight(newHeight);
}

void InGameWindow::closeWindow()
{
    emit windowClosed(this);
}
