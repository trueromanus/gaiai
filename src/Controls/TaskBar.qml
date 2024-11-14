import QtQuick
import gaiai
import "Panels"

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

        Image {
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 2
            width: 20
            height: 20
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
        anchors.leftMargin: 2
        anchors.right: timeAndVolumePanel.left
        anchors.rightMargin: 2


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
            text: "12:24"
            font.pixelSize: 12
            font.family: "Arial"
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
