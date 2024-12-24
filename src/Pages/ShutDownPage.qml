import QtQuick
import gaiai
import "../Controls"
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
        source: assetsLocation.imagedPath + "menushutdown.png"
    }

    PlainText {
        id: headerText
        anchors.left: iconShutDown.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "Are you sure you want to:"
    }

    RadioButton {
        id: shutDownRadio
        anchors.top: headerText.bottom
        anchors.topMargin: 10
        anchors.left: iconShutDown.right
        anchors.leftMargin: 20
        title: "Shut down the computer?"
        radioValue: 1
        actualValue: root.selectedOption
        onSelected: {
            root.selectedOption = radioValue;
        }
    }

    RadioButton {
        id: restartRadio
        anchors.top: shutDownRadio.bottom
        anchors.topMargin: 2
        anchors.left: iconShutDown.right
        anchors.leftMargin: 20
        title: "Restart the computer?"
        radioValue: 2
        actualValue: root.selectedOption
        onSelected: {
            root.selectedOption = radioValue;
        }
    }

    RadioButton {
        id: mssosRadio
        anchors.top: restartRadio.bottom
        anchors.topMargin: 2
        anchors.left: iconShutDown.right
        anchors.leftMargin: 20
        title: "Finish current shift?"
        radioValue: 3
        actualValue: root.selectedOption
        onSelected: {
            root.selectedOption = radioValue;
        }
    }

    DefaultButton {
        id: helpButton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        width: 100
        height: 30
        title: "Help"
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
        width: 100
        height: 30
        title: "No"
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
        width: 100
        height: 30
        title: "Yes"
        onClicked: {
            //root.closeContainerWindow();
        }
    }
}
