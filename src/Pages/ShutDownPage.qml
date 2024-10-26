import QtQuick
import "../Controls"

Item {
    id: root

    Image {
        id: iconShutDown
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: 40
        height: 40
        source: assetsLocation.imagedPath + "Images/menushutdown.png"
    }

    PlainText {
        anchors.left: iconShutDown.right
        anchors.leftMargin: 10
        text: "Are you sure you want to:"
    }

    DefaultButton {
        id: noButton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: 100
        height: 80
        title: "No"
    }

    DefaultButton {
        anchors.right: noButton.left
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: 100
        height: 80
        title: "Yes"
    }
}
