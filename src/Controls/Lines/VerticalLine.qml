import QtQuick

Item {
    id: root

    Rectangle {
        id: leftLine
        anchors.top: parent.top
        height: parent.height
        width: 1
        color: "#85858D"
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: leftLine.right
        height: parent.height
        width: 1
        color: "#FAF9FF"
    }
}
