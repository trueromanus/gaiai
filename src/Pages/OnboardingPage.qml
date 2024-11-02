import QtQuick
import gaiai
import "../Controls"

InGameWindowPage {
    id: root
    anchors.fill: parent

    PlainText {
        id: headerText
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 12
        text: "Welcome to <b>SmartCity</b><font color=\"white\">OS</font>"
        fontSize: 22
    }

    InformationPanel {
        id: informationPanel
        anchors.left: parent.left
        anchors.leftMargin: 13
        anchors.top: headerText.bottom
        anchors.topMargin: 8
        width: 290
        height: 290

        //background points color #E9E7C8

        Loader {
            anchors.fill: parent
            sourceComponent: firstPage
        }
    }

    DefaultButton {
        id: nextPageButton
        anchors.top: informationPanel.top
        anchors.left: informationPanel.right
        anchors.leftMargin: 14
        width: 150
        title: "Next Page"
    }

    DefaultButton {
        id: previousPageButton
        anchors.top: nextPageButton.bottom
        anchors.topMargin: 8
        anchors.left: informationPanel.right
        anchors.leftMargin: 14
        width: 150
        title: "Previous Page"
    }

    HorizontalLine {
        id: horizontalLine
        anchors.top: previousPageButton.bottom
        anchors.topMargin: 60
        anchors.left: informationPanel.right
        anchors.leftMargin: 14
        anchors.right: parent.right
        anchors.rightMargin: 15
    }

    DefaultButton {
        anchors.top: horizontalLine.bottom
        anchors.topMargin: 20
        anchors.left: informationPanel.right
        anchors.leftMargin: 14
        width: 150
        title: "Close"
        onClicked: {
            root.closeContainerWindow();
        }
    }

    Component {
        id: firstPage

        Item {
            anchors.fill: parent

            PlainText {
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: parent.width
                height: parent.height
                textFormat: Text.StyledText
                wrapMode: Text.WordWrap
                fontSize: 12
                text: "Hello newcomer and welcome to your new Temple-House City Government family!<br><br>
Our city is not very big, but by becoming a part of our city and city government, you will become part of a warm and cozy family!<br><br>
You are our new system operator, congratulations! But first of all, what does it mean to be a systems operator?<br><br>
You take on great power (of course, with great responsibility) and become the watchmen of the city of Temple-House. You like a superhero, but without a cape, and if something breaks, you just fix it and make everyone in our city happy.
"
            }
        }
    }

    Component {
        id: secondPage

        Item {
            anchors.fill: parent

            PlainText {
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: parent.width
                height: parent.height
                textFormat: Text.StyledText
                wrapMode: Text.WordWrap
                fontSize: 12
                text: "Your shift will start at 21:00 in the evening and end at 09:00 in the morning of the next day.
Immediately after accepting the shift, you need to check your tasks in the SmartCityTracker application.
All mandatory tasks must be completed before the end of the shift!"
            }
        }
    }
}
