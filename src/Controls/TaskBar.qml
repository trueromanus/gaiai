import QtQuick
import gaiai
import "Panels"
import "Buttons"

InGameTaskBar {
    id: root
    width: desktop.width
    height: 32
    startMenuOpened: smartButton.pressed

    signal toggleStartMenuButton()
    onToggleStartMenuButton: {
        if (root.startMenuOpened) {
            smartButton.release();
        } else {
            smartButton.press();
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#BFB8BF"
    }

    Rectangle {
        anchors.top: parent.top
        height: 2
        width: parent.width
        color: "#fff8ff"
    }

    ToggleButton {
        id: smartButton
        width: 72
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 2
        notShowGridPanel: true

        Image {
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 20
            height: 20
            mipmap: true
            sourceSize.width: 500
            sourceSize.height: 500
            source: assetsLocation.imagedPath + "keys.png"
        }

        PlainText {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 6
            text: "Smart"
            font.bold: true
        }
    }

    Item {
        anchors.left: smartButton.right
        anchors.right: timeAndVolumePanel.left
        anchors.rightMargin: 2
        height: 26

        Row {
            id: rowTaskbarWindows
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            spacing: 3
            height: parent.height

            Repeater {
                model: root.visibleItems
                delegate: ToggleButton {
                    id: taskBarWindow
                    width: root.widthVisibleItem
                    height: rowTaskbarWindows.height
                    toggled: modelData.activated

                    PlainText {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        text: modelData.title
                        font.bold: taskBarWindow.pressed
                    }

                    onPressedChanged: {
                        if (!taskBarWindow.pressed && modelData.activated) taskBarWindow.press();
                        if (taskBarWindow.pressed && !modelData.activated) root.activateWindow(modelData);
                    }
                }
            }
        }
    }

    Panel {
        id: timeAndVolumePanel
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 4
        width: 75
        height: 26

        Image {
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 20
            height: 20
            source: assetsLocation.imagedPath + "enablesound.png"
        }

        Text {
            text: shiftTimer.displayTime
            font.pixelSize: 12
            font.family: "Arial"
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
