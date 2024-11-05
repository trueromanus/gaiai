#include "gamebackend.h"

GameBackend::GameBackend(QObject *parent)
    : QObject{parent}
{
    QVariantMap onboarding;
    onboarding["title"] = "Onboarding";
    onboarding["hasChildrens"] = true;
    onboarding["isEndItem"] = false;
    m_tasks.append(onboarding);

    QVariantMap streets;
    streets["title"] = "Streets";
    streets["hasChildrens"] = false;
    streets["isEndItem"] = true;
    m_tasks.append(streets);
}
