import QtQuick
import gaiai

InGameWindow {
    id: root
    title: ""
    windowWidth: 100
    windowHeight: 100
    default property alias content: contentContainer.children

    Rectangle {
        color: "#BFB8BF"
        anchors.fill: parent
    }

    Rectangle {
        color: "white"
        anchors.left: parent.left
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "white"
        anchors.top: parent.top
        width: parent.width
        height: 1
    }

    Rectangle {
        color: "black"
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "black"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    DefaultHeaderWindow {
        id: windowHeader
        title: root.title
        activated: root.activated
        width: parent.width
        height: 24
        anchors.top: parent.top
    }

    Item {
        id: contentContainer
        anchors.top: windowHeader.bottom
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
        anchors.leftMargin: 3
        anchors.rightMargin: 3
        anchors.bottomMargin: 3
    }
}
