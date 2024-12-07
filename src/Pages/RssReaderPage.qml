import QtQuick
import gaiai
import "../Controls"
import "../Controls/Panels"
import "../Controls/Lines"

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

        Loader {
            id: treeLoader
            sourceComponent: root.visible ? treeComponent : null
        }
    }

    Panel {
        id: contentsPanel
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

        ListView {
            id: topicsListView
            anchors.fill: parent
            clip: true
            model: gameBackend.rssReaderPage.filteredRssItems
            delegate: Item {
                required property string icon
                required property string header
                required property string content
                required property string topic
                required property int day
                required property int index

                width: topicsListView.width
                height: headerText.height + contentText.height + 8

                Image {
                    id: topicPoster
                    width: 100
                    height: 70
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    mipmap: true
                    source: assetsLocation.imagedPath + icon
                }

                PlainText {
                    id: headerText
                    anchors.left: topicPoster.right
                    anchors.leftMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    width: parent.width - 100
                    text: header
                    font.bold: true
                    fontSize: 13
                }
                PlainText {
                    id: contentText
                    anchors.left: topicPoster.right
                    anchors.leftMargin: 2
                    anchors.top: headerText.bottom
                    anchors.topMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    text: content
                    wrapMode: Text.WordWrap
                }

                HorizontalLine {
                    visible: index !== topicsListView.model.length - 1
                    width: parent.width -2
                    anchors.left: parent.left
                    anchors.leftMargin: 1
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 1
                }
            }
        }
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

    Component {
        id: treeComponent

        Tree {
            id: tasksTree
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.topMargin: 4
            allExpandedOnStart: true
            model: gameBackend.rssReaderPage.tree
            Component.onCompleted: {
                tasksTree.selectNode(gameBackend.rssReaderPage.tree[0]);
            }
            onSelectedNodeChanged: {
                gameBackend.rssReaderPage.selectedSection = tasksTree.selectedNode;
            }
        }
    }
}
