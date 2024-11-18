#include "ingamecheckbox.h"

InGameCheckBox::InGameCheckBox() {}

void InGameCheckBox::setChecked(bool checked) noexcept
{
    if (m_checked == checked) return;

    m_checked = checked;
    emit checkedChanged();
}
