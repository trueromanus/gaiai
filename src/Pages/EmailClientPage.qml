import QtQuick
import gaiai
import "../Controls"
import "../Controls/Lines"

InGameWindowPage {
    id: root
    anchors.fill: parent

    TableList {
        id: sectionsTableList
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 290
        height: 80
        columns: gameBackend.emailClientPage.foldersColumns
        items: gameBackend.emailClientPage.sections
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

        VerticalLine {
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 20
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
