#include "ingamebutton.h"

InGameButton::InGameButton() {}

void InGameButton::setdisabled(bool disabled) noexcept
{
    if (m_disabled == disabled) return;

    m_disabled = disabled;
    emit disabledChanged();

    m_pressed = false;
    emit pressedChanged();
}

void InGameButton::settitle(const QString &title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}

void InGameButton::setLeftAligned(bool leftAligned) noexcept
{
    if (m_leftAligned == leftAligned) return;

    m_leftAligned = leftAligned;
    emit leftAlignedChanged();
}

void InGameButton::press() noexcept
{
    m_pressed = true;
    emit pressedChanged();
}

void InGameButton::release() noexcept
{
    m_pressed = false;
    emit pressedChanged();
}
