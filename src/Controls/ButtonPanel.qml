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
        visible: !root.pressed
        color: "#FFF8FF"
        anchors.left: parent.left
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: !root.pressed
        color: "#FFF8FF"
        anchors.top: parent.top
        width: parent.width
        height: 1
    }

    Rectangle {
        visible: !root.pressed
        color: "black"
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: !root.pressed
        color: "#7B7B7B"
        anchors.right: parent.right
        anchors.rightMargin: 1
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: !root.pressed
        color: "black"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    Rectangle {
        visible: !root.pressed
        color: "#7B7B7B"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1
        anchors.right: parent.right
        anchors.rightMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 1
        width: parent.width
        height: 1
    }

    Rectangle {
        id: leftPressedEdge
        visible: root.pressed
        color: "black"
        anchors.left: parent.left
        width: 1
        height: parent.height
    }

    Rectangle {
        id: topPressedEdge
        visible: root.pressed
        color: "black"
        anchors.top: parent.top
        width: parent.width - 1
        height: 1
    }

    Rectangle {
        visible: root.pressed
        color: "#7f787f"
        anchors.left: leftPressedEdge.right
        width: 1
        height: parent.height - 1
    }

    Rectangle {
        visible: root.pressed
        color: "#7f787f"
        anchors.top: topPressedEdge.bottom
        width: parent.width - 1
        height: 1
    }

    Rectangle {
        visible: root.pressed
        color: "white"
        anchors.right: parent.right
        anchors.rightMargin: 1
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: root.pressed
        color: "white"
        anchors.bottom: parent.bottom
        width: parent.width - 1
        height: 1
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        anchors.margins: 1
    }
}
