import QtQuick

Item {
    id: root
    default property alias content: contentContainer.children
    property bool pressed

    Rectangle {
        color: "#FCFFE0"
        anchors.fill: parent
    }

    Rectangle {
        color: "white"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 1
    }

    Rectangle {
        color: "white"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
    }

    Rectangle {
        color: "black"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        width: 1
    }

    Rectangle {
        color: "black"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 1
        height: 1
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        anchors.margins: 1
    }
}
