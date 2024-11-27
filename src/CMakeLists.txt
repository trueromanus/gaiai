cmake_minimum_required(VERSION 3.16)

project(gaiai VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.7)

qt_add_executable(appgaiai
    Models/gametaskmodel.h Models/gametaskmodel.cpp
    Models/gametrafficlightmodel.h Models/gametrafficlightmodel.cpp
    Models/gametasksectionmodel.h Models/gametasksectionmodel.cpp
    Models/gametablecolumn.h Models/gametablecolumn.cpp
    Models/gamemenumodel.h Models/gamemenumodel.cpp
    PageModels/smarttrackerpage.h PageModels/smarttrackerpage.cpp
    main.cpp
)

qt_add_qml_module(appgaiai
    URI gaiai
    VERSION 1.0
    QML_FILES
        Main.qml
        Controls/PlainText.qml
    QML_FILES
        Controls/DefaultHeaderWindow.qml
        Controls/DefaultWindow.qml
    QML_FILES
        Controls/Panels/Panel.qml
        Controls/Panels/ButtonPanel.qml
        Controls/Panels/InformationPanel.qml
        Controls/Panels/MenuPanel.qml
        Controls/Panels/WindowPanel.qml
        Controls/Panels/CheckBoxPanel.qml
        Controls/Panels/GridCanvasPanel.qml
    QML_FILES
        Controls/Lines/VerticalDashLine.qml
        Controls/Lines/HorizontalDashLine.qml
        Controls/Lines/DashRectangle.qml
        Controls/Lines/HorizontalLine.qml
        Controls/Lines/RightTriangle.qml
    QML_FILES
        Controls/DefaultButton.qml
        Controls/IconButton.qml
        Controls/ContentButton.qml
        Controls/ToggleButton.qml
        Controls/RadioButton.qml
    QML_FILES
        Controls/TaskBar.qml
        Controls/StartMenuPopup.qml
        Controls/CommonMenu.qml
        Controls/CommonMenuList.qml
    QML_FILES
        Controls/Tree.qml
        Controls/TreeItem.qml
        Controls/TreeLevel.qml
    QML_FILES
        Controls/FlickableArea.qml
        Controls/TableList.qml
    QML_FILES
        Pages/ShutDownPage.qml
        Pages/OnboardingPage.qml
        Pages/SmartTrackerPage.qml

    SOURCES
        ingamewindow.h ingamewindow.cpp
        ingamewindowdefaultheader.h ingamewindowdefaultheader.cpp
        ingametaskbar.h ingametaskbar.cpp
        ingamebutton.h ingamebutton.cpp
        ingamestartmenu.h ingamestartmenu.cpp
        systemsettings.h systemsettings.cpp
        ingameradiobutton.h ingameradiobutton.cpp
        ingamewindowpage.h ingamewindowpage.cpp
        ingamedesktop.h ingamedesktop.cpp
        framepaginator.cpp framepaginator.h
        gamebackend.h gamebackend.cpp
        verticalscrollbar.h verticalscrollbar.cpp
        ingametree.h ingametree.cpp
        ingametablelist.h ingametablelist.cpp
        ingamecheckbox.h ingamecheckbox.cpp
        ingamemenu.h ingamemenu.cpp

    RESOURCES
        Images/disablesound.png
        Images/enablesound.png
        Images/keys.png
        Images/menuhelp.png
        Images/menusettings.png
        Images/menushutdown.png
        Images/menudocuments.png
        Images/menuprograms.png
        Images/menurun.png
        Images/disabledradio.png
        Images/smarttracker.png
        Images/closewindowicon.png
        Images/tile2x2.png

        TextContents/taskContents.en.json
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
