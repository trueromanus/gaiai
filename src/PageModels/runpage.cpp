#include "runpage.h"

RunPage::RunPage(QObject *parent)
    : QObject{parent}
{}

void RunPage::runCommand(const QString &command)
{
    m_usedCommands.append(command);

    emit commandRunned(command);
}


