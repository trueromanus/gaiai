import QtQuick
import gaiai
import "../Controls"
import "../Controls/Panels"

InGameWindowPage {
    id: root
    anchors.fill: parent

    Item {
        id: mainMenuItem
        anchors.left: parent.left
        anchors.right: parent.right
        height: 0
    }

    Panel {
        id: treeHeader
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: mainMenuItem.bottom
        anchors.topMargin: 2
        width: 200
        height: 22

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 4
            text: "All tasks"
        }
    }

    Panel {
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: treeHeader.bottom
        anchors.topMargin: 2
        anchors.right: treeHeader.right
        anchors.bottom: parent.bottom

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        Tree {
            id: tasksTree
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.topMargin: 4
            model: gameBackend.tasks
        }
    }


    Panel {
        id: contentsHeader
        anchors.left: treeHeader.right
        anchors.leftMargin: 4
        anchors.top: mainMenuItem.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        height: 22

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 4
            text: "Contents of"
        }
    }

    Panel {
        visible: (tasksTree.selectedNode && tasksTree.selectedNode.hasChildrens)
        anchors.left: contentsHeader.left
        anchors.top: contentsHeader.bottom
        anchors.topMargin: 2
        anchors.right: contentsHeader.right
        anchors.bottom: parent.bottom

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        TableList {
            anchors.fill: parent
            columns: gameBackend.smartTrackerPage.columns
        }
    }

    Panel {
        visible: (tasksTree.selectedNode && !tasksTree.selectedNode.hasChildrens)
        anchors.left: contentsHeader.left
        anchors.top: contentsHeader.bottom
        anchors.topMargin: 2
        anchors.right: contentsHeader.right
        anchors.bottom: parent.bottom

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        Text {
            text: "item presentation"
        }
    }
}
