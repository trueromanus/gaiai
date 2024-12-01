import QtQuick
import gaiai
import "../Controls"
import "../Controls/Panels"

InGameWindowPage {
    id: root
    anchors.fill: parent

    Panel {
        id: treePanel
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 26
        width: 200

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        Tree {
            id: tasksTree
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.topMargin: 4
            allExpandedOnStart: true
            model: gameBackend.rssReaderPage.tree
        }
    }

    Panel {
        id: contentsPanel
        //visible: (tasksTree.selectedNode && tasksTree.selectedNode.hasChildrens)
        anchors.left: treePanel.right
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 26

        Rectangle {
            anchors.fill: parent
            color: "white"
        }

        /*Loader {
            anchors.fill: parent
            sourceComponent: contentsPanel.visible ? tableList : null
        }*/
    }

    Panel {
        id: pageFooter
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: contentsPanel.bottom
        anchors.topMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        width: 200
        height: 22

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 4
            text: "Unreaded 0"
        }
    }
}
