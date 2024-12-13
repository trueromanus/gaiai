import QtQuick

Item {
    id: root
    default property alias content: contentContainer.children

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
        color: "#7F787F"
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "#7F787F"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        anchors.margins: 1
    }
}
