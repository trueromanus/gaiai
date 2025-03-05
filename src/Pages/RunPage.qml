import QtQuick
import QtQuick.Controls
import gaiai
import "../Controls"
import "../Controls/Panels"
import "../Controls/Buttons"

InGameWindowPage {
    id: root
    anchors.fill: parent

    property int selectedOption: 1

    Image {
        id: iconShutDown
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 15
        width: 40
        height: 40
        source: assetsLocation.imagedPath + "menurun.png"
    }

    PlainText {
        id: headerText
        anchors.left: iconShutDown.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "Type the name of a program, or document, and\nSmartCity will open it for you."
    }

    Item {
        anchors.top: iconShutDown.bottom
        anchors.topMargin: 4
        width: parent.width
        height: 30

        PlainText {
            id: openText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "Open:"
        }

        ButtonPanel {
            pressed: true
            anchors.left: openText.right
            anchors.leftMargin: 16
            anchors.right: parent.right
            anchors.rightMargin: 18
            anchors.verticalCenter: parent.verticalCenter
            height: 22

            TextField {
                id: openTextField
                anchors.fill: parent
                anchors.rightMargin: 1
                anchors.bottomMargin: 1
            }
        }
    }


    DefaultButton {
        id: helpButton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        width: 90
        height: 28
        title: "Browse..."
        onClicked: {
            root.closeContainerWindow();
        }
    }

    DefaultButton {
        id: noButton
        anchors.right: helpButton.left
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        width: 90
        height: 28
        title: "Cancel"
        onClicked: {
            root.closeContainerWindow();
        }
    }

    DefaultButton {
        id: yesButton
        anchors.right: noButton.left
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        width: 90
        height: 28
        title: "OK"
        onClicked: {

            root.closeContainerWindow();
        }
    }
}
