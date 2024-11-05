#include "ingamestartmenu.h"
#include <QQmlPropertyMap>

InGameStartMenu::InGameStartMenu() {
    QVariantMap programsMap;
    programsMap["title"] = "Programs";
    programsMap["image"] = "menuprograms.png";
    programsMap["command"] = "";
    programsMap["topLine"] = false;
    m_menu.append(programsMap);

    QVariantMap documentsMap;
    documentsMap["title"] = "Documents";
    documentsMap["image"] = "menudocuments.png";
    documentsMap["command"] = "";
    documentsMap["topLine"] = false;
    m_menu.append(documentsMap);

    QVariantMap settingsMap;
    settingsMap["title"] = "Settings";
    settingsMap["image"] = "menusettings.png";
    settingsMap["command"] = "";
    settingsMap["topLine"] = false;
    m_menu.append(settingsMap);

    QVariantMap helpMap;
    helpMap["title"] = "Help";
    helpMap["image"] = "menuhelp.png";
    //TODO: restore help command!
    helpMap["command"] = "smarttracker";
    helpMap["topLine"] = false;
    m_menu.append(helpMap);

    QVariantMap runMap;
    runMap["title"] = "Run";
    runMap["image"] = "menurun.png";
    runMap["command"] = "run";
    runMap["topLine"] = false;
    m_menu.append(runMap);

    QVariantMap shutDownMap;
    shutDownMap["title"] = "Shut Down...";
    shutDownMap["image"] = "menushutdown.png";
    shutDownMap["command"] = "shutdown";
    shutDownMap["topLine"] = true;
    m_menu.append(shutDownMap);
}
