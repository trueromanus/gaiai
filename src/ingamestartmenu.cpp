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

    addStartMenuItem("Run", "menurun.png", "run", false, false);

    addStartMenuItem("Shut Down...", "menushutdown.png", "shutdown", true, false);

    fillProgramsMenu();
}

void InGameStartMenu::fillProgramsMenu()
{
    auto smartTracker = new GameMenuModel(this);
    smartTracker->setTitle("SmartTracker");
    smartTracker->setIcon("smarttracker.png");
    smartTracker->setCommand("smarttracker");
    m_programs.append(smartTracker);

    auto rssReader = new GameMenuModel(this);
    rssReader->setTitle("RSS Reader");
    rssReader->setIcon("rssreader.png");
    rssReader->setCommand("rssreader");
    m_programs.append(rssReader);

    auto emailClient = new GameMenuModel(this);
    emailClient->setTitle("I'm The Bat_an!");
    emailClient->setIcon("emailclient.png");
    emailClient->setCommand("emailclient");
    m_programs.append(emailClient);
}

void InGameStartMenu::addStartMenuItem(const QString &title, const QString &image, const QString &command, bool topLine, bool subMenu)
{
    QVariantMap map;
    map["title"] = title;
    map["image"] = image;
    map["command"] = command;
    map["topLine"] = topLine;
    map["submenu"] = subMenu;
    m_menu.append(map);
}
