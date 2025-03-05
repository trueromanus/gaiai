#include "runpage.h"

RunPage::RunPage(QObject *parent)
    : QObject{parent}
{}

void RunPage::runCommand(const QString &command)
{
    emit runCommanded(command);

    m_usedCommands.append(command);
}


