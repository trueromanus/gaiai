import QtQuick

Item {
    id: root
    default property alias content: contentContainer.children

    Rectangle {
        color: "white"
        anchors.fill: parent
    }

    Rectangle {
        color: "#C3C3C3"
        anchors.top: parent.top
        width: parent.width - 1
        height: 1
    }

    Rectangle {
        color: "black"
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        width: parent.width - 2
        height: 1
    }

    Rectangle {
        color: "#C3C3C3"
        anchors.left: parent.left
        width: 1
        height: parent.height - 1
    }

    Rectangle {
        color: "black"
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
        width: 1
        height: parent.height - 2
    }

    Rectangle {
        color: "white"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    Rectangle {
        color: "white"
        anchors.top: parent.top
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "#404040"
        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 1
        width: 1
        height: parent.height - 2
    }

    Rectangle {
        color: "#404040"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 1
        width: parent.width - 1
        height: 1
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        anchors.margins: 2
    }
}
