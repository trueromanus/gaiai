import QtQuick
import gaiai
import "Controls"

Window {
    id: desktop
    width: 1280
    height: 720
    visible: true
    title: qsTr("gaiai")

    Rectangle {
        anchors.fill: parent
        color: "#00787F"
    }

    Item {
        id: desktopWindows
        anchors.fill: parent
    }

    Item {
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            enabled: startMenuPopup.visible
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed: {
                if (startMenuPopup.visible) taskBar.toggleStartMenuButton();
            }
        }
    }

    TaskBar {
        id: taskBar
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    StartMenuPopup {
        id: startMenuPopup
        visible: taskBar.startMenuOpened
        y: taskBar.y - (height - 5)
    }

    SystemSettings {
        id: systemSettings
    }

    Item {
        id: assetsLocation
        property string iconsPath: Qt.resolvedUrl("Icons/")
        property string imagedPath: Qt.resolvedUrl("Images/")
    }
}
