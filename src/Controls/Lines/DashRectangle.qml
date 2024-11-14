import QtQuick

Item {
    id: root
    property color dashColor: "transparent"

    HorizontalDashLine {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        dashColor: root.dashColor
    }

    HorizontalDashLine {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        dashColor: root.dashColor
    }

    VerticalDashLine {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        dashColor: root.dashColor
    }

    VerticalDashLine {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: -1
        dashColor: root.dashColor
    }
}
