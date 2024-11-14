import QtQuick

Item {
    id: root

    Rectangle {
        id: topLine
        anchors.top: parent.top
        height: 1
        width: parent.width
        color: "#85858D"
    }

    Rectangle {
        anchors.top: topLine.bottom
        height: 1
        width: parent.width
        color: "#FAF9FF"
    }
}
