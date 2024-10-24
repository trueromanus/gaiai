#include "ingamestartmenu.h"
#include <QQmlPropertyMap>

InGameStartMenu::InGameStartMenu() {
    QVariantMap programsMap;
    programsMap["title"] = "Programs";
    programsMap["image"] = "menuprograms.png";
    programsMap["topLine"] = false;
    m_menu.append(programsMap);

    QVariantMap documentsMap;
    documentsMap["title"] = "Documents";
    documentsMap["image"] = "menudocuments.png";
    documentsMap["topLine"] = false;
    m_menu.append(documentsMap);

    QVariantMap settingsMap;
    settingsMap["title"] = "Settings";
    settingsMap["image"] = "menusettings.png";
    settingsMap["topLine"] = false;
    m_menu.append(settingsMap);

    QVariantMap helpMap;
    helpMap["title"] = "Help";
    helpMap["image"] = "menuhelp.png";
    helpMap["topLine"] = false;
    m_menu.append(helpMap);

    QVariantMap runMap;
    runMap["title"] = "Run";
    runMap["image"] = "menurun.png";
    runMap["topLine"] = false;
    m_menu.append(runMap);

    QVariantMap shutDownMap;
    shutDownMap["title"] = "Shut Down...";
    shutDownMap["image"] = "menushutdown.png";
    shutDownMap["topLine"] = true;
    m_menu.append(shutDownMap);
}
