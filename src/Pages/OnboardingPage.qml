import QtQuick
import gaiai
import "../Controls"
import "../Controls/Panels"
import "../Controls/Lines"
import "../Controls/Buttons"

InGameWindowPage {
    id: root
    anchors.fill: parent

    FramePaginator {
        id: framePaginator
        startPage: 0
        countPages: 2
        onCurrentPageChanged: {
            switch (currentPage) {
                case 0: return frameLoader.sourceComponent = firstPage;
                case 1: return frameLoader.sourceComponent = secondPage;
            }
        }
    }

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
            id: frameLoader
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
        disabled: !framePaginator.hasNextPage
        onClicked: {
            framePaginator.nextPage();
        }
    }

    DefaultButton {
        id: previousPageButton
        anchors.top: nextPageButton.bottom
        anchors.topMargin: 8
        anchors.left: informationPanel.right
        anchors.leftMargin: 14
        width: 150
        title: "Previous Page"
        disabled: !framePaginator.hasPreviousPage
        onClicked: {
            framePaginator.previousPage();
        }
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
                text: "Hello newcomer and welcome to Temple-House City Government family!<br><br>
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
                id: headerSmartTrackerText
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                textFormat: Text.StyledText
                wrapMode: Text.WordWrap
                fontSize: 12
                text: "Your shift will start at 21:00 in the evening and end at 09:00 in the morning of the next day.
Immediately after accepting the shift, you need to check your tasks in the <b>SmartTracker</b> program.<br><br>
To open the program, you need to click on <b>Smart</b> button in the lower left corner and select <b>SmartTracker</b> option in <b>Programs</b> section."
            }
            Image {
                id: iconSmartTracker
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: headerSmartTrackerText.bottom
                anchors.topMargin: 15
                width: 40
                height: 40
                source: assetsLocation.imagedPath + "smarttracker.png"
            }
            PlainText {
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.top: iconSmartTracker.bottom
                anchors.topMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                textFormat: Text.StyledText
                wrapMode: Text.WordWrap
                fontSize: 12
                text: "All mandatory tasks must be completed before the end of the shift!"
            }
        }
    }
}
