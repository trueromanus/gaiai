cmake_minimum_required(VERSION 3.16)

project(gaiai VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.7)

qt_add_executable(appgaiai
    Models/gametaskmodel.h Models/gametaskmodel.cpp
    Models/gametrafficlightmodel.h Models/gametrafficlightmodel.cpp
    main.cpp
)

qt_add_qml_module(appgaiai
    URI gaiai
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES Controls/DefaultHeaderWindow.qml
    QML_FILES Controls/IconButton.qml
    QML_FILES Controls/DefaultWindow.qml
    QML_FILES Controls/Panel.qml
    QML_FILES Controls/TaskBar.qml
    QML_FILES Controls/ButtonPanel.qml Controls/InformationPanel.qml
    QML_FILES Controls/DefaultButton.qml
    QML_FILES Controls/PlainText.qml Controls/ContentButton.qml Controls/ToggleButton.qml Controls/StartMenuPopup.qml Controls/MenuPanel.qml
    QML_FILES Pages/ShutDownPage.qml Pages/OnboardingPage.qml Pages/SmartTrackerPage.qml
    QML_FILES Controls/WindowPanel.qml Controls/RadioButton.qml Controls/HorizontalLine.qml
    QML_FILES Controls/Tree.qml Controls/TreeItem.qml
    QML_FILES Controls/VerticalDashLine.qml Controls/HorizontalDashLine.qml

    SOURCES ingamewindow.h ingamewindow.cpp
    SOURCES ingamewindowdefaultheader.h ingamewindowdefaultheader.cpp
    SOURCES ingametaskbar.h ingametaskbar.cpp
    SOURCES ingamebutton.h ingamebutton.cpp
    SOURCES ingamestartmenu.h ingamestartmenu.cpp
    SOURCES systemsettings.h systemsettings.cpp
    SOURCES ingameradiobutton.h ingameradiobutton.cpp
    SOURCES ingamewindowpage.h ingamewindowpage.cpp
    SOURCES ingamedesktop.h ingamedesktop.cpp
    SOURCES framepaginator.cpp framepaginator.h
    SOURCES gamebackend.h gamebackend.cpp

    RESOURCES Images/disablesound.png Images/enablesound.png
    RESOURCES Images/keys.png
    RESOURCES Images/menuhelp.png Images/menusettings.png Images/menushutdown.png
    RESOURCES Images/menudocuments.png Images/menuprograms.png Images/menurun.png
    RESOURCES Images/disabledradio.png Images/smarttracker.png Images/closewindowicon.png
)

set_target_properties(appgaiai PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.emptyflow.games.gaiai
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgaiai
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appgaiai
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#add_subdirectory(LogicHelpers)
#target_link_libraries(appgaiai
#    PRIVATE Qt6::Quick
#    logichelpersplugin
#)
#install(TARGETS appgaiai
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
