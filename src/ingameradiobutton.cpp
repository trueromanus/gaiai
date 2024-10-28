#include "ingameradiobutton.h"

InGameRadioButton::InGameRadioButton() {}

void InGameRadioButton::setActualValue(int actualValue) noexcept
{
    if (m_actualValue == actualValue) return;


    m_actualValue = actualValue;
    emit actualValueChanged();
}

void InGameRadioButton::setRadioValue(int radioValue) noexcept
{
    if (m_radioValue == radioValue) return;

    m_radioValue = radioValue;
    emit radioValueChanged();
}

void InGameRadioButton::setTitle(QString title) noexcept
{
    if (m_title == title) return;

    m_title = title;
    emit titleChanged();
}
