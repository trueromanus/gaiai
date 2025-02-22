import QtQuick
import gaiai
import "Controls"

Window {
    id: desktop
    width: 1280
    minimumWidth: 1280
    height: 720
    minimumHeight: 720
    visible: true
    title: qsTr("gaiai")

    Item {
        anchors.fill: parent

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
            windowsContainer: desktopWindows
        }

        StartMenuPopup {
            id: startMenuPopup
            visible: taskBar.startMenuOpened
            y: taskBar.y - (height - 5)
            onCommandRunned: function (command){
                if (command === "") return;

                taskBar.toggleStartMenuButton();

                taskBar.createDefaultWindow(command, 1, "");
            }
        }

        InGameFullScreen {
            id: fullScreen
            anchors.fill: parent
            visible: gameBackend.isBigScreenVisible

            Item {
                anchors.fill: parent
                visible: gameBackend.bigScreenType === "turnoff"

                Rectangle {
                    anchors.fill: parent
                    color: "black"
                }

                PlainText {
                    id: turnoffText
                    x: (parent.width / 2) - (turnoffText.width / 2)
                    y: (parent.height / 2) - turnoffText.height
                    horizontalAlignment: Text.AlignHCenter
                    color: "#FF7F00"
                    text: fullScreen.turnOffMessage
                    fontSize: 38
                    font.bold: true
                }
            }
        }
    }

    SystemSettings {
        id: systemSettings
    }

    GameBackend {
        id: gameBackend
    }

    InGameShiftTimer {
        id: shiftTimer
        backend: gameBackend
        onTimeChanged: function (time) {
            inGameCityObjects.handleTimerForObjects(time);
        }

        Component.onCompleted: {
            shiftTimer.restartShift();
        }
    }

    InGameCityObjects {
        id: inGameCityObjects
        gameBackend: gameBackend
    }

    Item {
        id: assetsLocation
        property string iconsPath: Qt.resolvedUrl("Icons/")
        property string imagedPath: Qt.resolvedUrl("Images/")
    }
}
