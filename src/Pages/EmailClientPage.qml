import QtQuick
import gaiai
import "../Controls"
import "../Controls/Lines"
import "../Controls/Buttons"
import "../Controls/Panels"

InGameWindowPage {
    id: root
    anchors.fill: parent

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 2
        width: 290
        height: 240
    }

    TableList {
        id: sectionsTableList
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        width: 290
        height: 240
        columns: gameBackend.emailClientPage.foldersColumns
        items: gameBackend.emailClientPage.sections
        selectedStyle: 1
        /*onSelectedItemChanged: {
           gameBackend.smartTrackerPage.selectedTaskInList = selectedItem;
        }
        onOpenItem: {
           tasksTree.selectNode(gameBackend.smartTrackerPage.selectedTaskInList);
        }*/
    }

    Item {
        id: actionsToolbar
        anchors.left: sectionsTableList.right
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 2
        height: 34

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            color: "white"
            height: 1
        }

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            width: 1
            color: "white"
            height: parent.height
        }

        RevertedPanel {
            id: splitterLine1
            width: 3
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
        }

        RevertedPanel {
            id: splitterLine2
            width: 3
            anchors.left: splitterLine1.right
            anchors.leftMargin: 1
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
        }

        IconButton {
            id: pullNewEmailsButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: splitterLine2.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 28
                height: 28
                source: assetsLocation.imagedPath + "pullnewemails.png"
            }

            onClicked: {

            }
        }

        IconButton {
            id: sendWaitingEmailsButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: pullNewEmailsButton.right

            Image {
                anchors.centerIn: parent
                width: 28
                height: 28
                source: assetsLocation.imagedPath + "sendwaitingemails.png"
            }

            onClicked: {

            }
        }

        VerticalLine {
            id: firstSectionLine
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.left: sendWaitingEmailsButton.right
            anchors.leftMargin: 2
        }

        IconButton {
            id: createnewEmailButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: firstSectionLine.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 28
                height: 28
                source: assetsLocation.imagedPath + "createnewemail.png"
            }

            onClicked: {

            }
        }
    }

    TableList {
        id: emailsTableList
        anchors.left: sectionsTableList.right
        anchors.leftMargin: 4
        anchors.top: actionsToolbar.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        columns: gameBackend.emailClientPage.emailColumns
        //items: gameBackend.emailClientPage.sections
    }
}
