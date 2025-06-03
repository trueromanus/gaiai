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

    Item {
        anchors.top: parent.top
        anchors.topMargin: 4
        width: parent.width
        height: 30

        PlainText {
            id: openText
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "Change day:"
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

        DefaultButton {
            id: changeDayButton
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            width: 90
            height: 28
            title: "Change"
            onClicked: {
                gameBackend.fillDay(parseInt(openTextField.text));
                root.closeContainerWindow();
            }
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
