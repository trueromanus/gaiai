cmake_minimum_required(VERSION 3.16)

project(gaiai VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.7)

qt_add_executable(appgaiai
    main.cpp
)

qt_add_qml_module(appgaiai
    URI gaiai
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES ingamewindow.h ingamewindow.cpp
        SOURCES ingamewindowdefaultheader.h ingamewindowdefaultheader.cpp
        SOURCES ingametaskbar.h ingametaskbar.cpp
        SOURCES ingamebutton.h ingamebutton.cpp
        SOURCES ingamestartmenu.h ingamestartmenu.cpp
        SOURCES systemsettings.h systemsettings.cpp
        QML_FILES Controls/DefaultHeaderWindow.qml
        QML_FILES Controls/IconButton.qml
        QML_FILES Controls/DefaultWindow.qml
        QML_FILES Controls/Panel.qml
        QML_FILES Controls/TaskBar.qml
        QML_FILES Controls/ButtonPanel.qml
        QML_FILES Controls/DefaultButton.qml
        RESOURCES Icons/WindowToolbarIcons/close.svg        
        RESOURCES Images/disablesound.png Images/enablesound.png
        QML_FILES Controls/PlainText.qml Controls/ContentButton.qml Controls/ToggleButton.qml Controls/StartMenuPopup.qml Controls/MenuPanel.qml
        QML_FILES Pages/ShutDownPage.qml
        RESOURCES Images/keys.png
        RESOURCES Images/menuhelp.png Images/menusettings.png Images/menushutdown.png        
        RESOURCES Images/menudocuments.png Images/menuprograms.png Images/menurun.png        
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
