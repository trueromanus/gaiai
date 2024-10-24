import QtQuick

Item {
    id: root
    default property alias content: contentContainer.children
    property bool pressed

    Rectangle {
        color: "#BFB8BF"
        anchors.fill: parent
    }

    Rectangle {
        color: "#C6DDDC"
        anchors.top: parent.top
        width: parent.width - 2
        height: 1
    }

    Rectangle {
        color: "white"
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        width: parent.width - 4
        height: 1
    }

    Rectangle {
        color: "#C6DDDC"
        anchors.left: parent.left
        width: 1
        height: parent.height - 2
    }

    Rectangle {
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        width: 1
        height: parent.height - 4
    }

    Rectangle {
        color: "#7B7B7B"
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        width: parent.width - 4
        height: 1
    }

    Rectangle {
        color: "black"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 2
    }

    Rectangle {
        color: "#7B7B7B"
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 2
        width: 1
        height: parent.height - 4
    }

    Rectangle {
        color: "black"
        anchors.right: parent.right
        width: 2
        height: parent.height
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        anchors.margins: 2
    }
}
