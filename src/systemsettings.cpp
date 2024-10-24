#include <QGuiApplication>
#include <QScreen>
#include "systemsettings.h"

SystemSettings::SystemSettings(QObject *parent)
    : QObject{parent}
{
    auto screen = QGuiApplication::primaryScreen();
    if (screen != nullptr) m_textMultiplier = screen->devicePixelRatio();
}
