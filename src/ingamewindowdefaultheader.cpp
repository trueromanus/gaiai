#include "ingamewindowdefaultheader.h"

InGameWindowDefaultHeader::InGameWindowDefaultHeader() {
    setProperty("elementMode", "windowheader");
}

void InGameWindowDefaultHeader::setTitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void InGameWindowDefaultHeader::setActivated(bool activated) noexcept
{
    if (m_activated == activated) return;

    m_activated = activated;
    emit activatedChanged();
}

void InGameWindowDefaultHeader::componentComplete()
{
    QQuickItem::componentComplete();
}
