#include "ingamestartmenu.h"
#include <QQmlPropertyMap>

InGameStartMenu::InGameStartMenu() {
    QVariantMap programsMap;
    programsMap["title"] = "Programs";
    programsMap["image"] = "menuprograms.png";
    programsMap["command"] = "";
    programsMap["topLine"] = false;
    programsMap["submenu"] = true;
    m_menu.append(programsMap);

    QVariantMap documentsMap;
    documentsMap["title"] = "Documents";
    documentsMap["image"] = "menudocuments.png";
    documentsMap["command"] = "";
    documentsMap["topLine"] = false;
    documentsMap["submenu"] = false;
    m_menu.append(documentsMap);

    QVariantMap settingsMap;
    settingsMap["title"] = "Settings";
    settingsMap["image"] = "menusettings.png";
    settingsMap["command"] = "";
    settingsMap["topLine"] = false;
    settingsMap["submenu"] = false;
    m_menu.append(settingsMap);

    QVariantMap helpMap;
    helpMap["title"] = "Help";
    helpMap["image"] = "menuhelp.png";
    //TODO: restore help command!
    helpMap["command"] = "smarttracker";
    helpMap["topLine"] = false;
    helpMap["submenu"] = false;
    m_menu.append(helpMap);

    QVariantMap runMap;
    runMap["title"] = "Run";
    runMap["image"] = "menurun.png";
    runMap["command"] = "run";
    runMap["topLine"] = false;
    runMap["submenu"] = false;
    m_menu.append(runMap);

    QVariantMap shutDownMap;
    shutDownMap["title"] = "Shut Down...";
    shutDownMap["image"] = "menushutdown.png";
    shutDownMap["command"] = "shutdown";
    shutDownMap["topLine"] = true;
    shutDownMap["submenu"] = false;
    m_menu.append(shutDownMap);

    fillProgramsMenu();
}

void InGameStartMenu::fillProgramsMenu()
{
    auto smartTracker = new GameMenuModel(this);
    smartTracker->setTitle("SmartTracker");
    smartTracker->setIcon("smarttracker.png");
    m_programs.append(smartTracker);

    //fot test purposes
    m_programs.append(smartTracker);
    m_programs.append(smartTracker);
}
