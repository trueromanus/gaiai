import QtQuick
import gaiai
import "../Controls"

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

    Rectangle {
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: treeHeader.bottom
        anchors.topMargin: 2
        anchors.right: treeHeader.right
        anchors.bottom: parent.bottom
        color: "white"
        border.width: 2
        border.color: "black"

        Tree {
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
            text: "Content of"
        }
    }
}
