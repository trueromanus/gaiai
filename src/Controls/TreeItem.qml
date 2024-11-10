import QtQuick
import QtQuick.Shapes

Item {
    id: root
    height: 20

    property alias title: textTitle.text
    property bool hasChildren: false
    property bool isEndItem: false
    property bool expanded: false
    default property alias content: contentContainer.children

    VerticalDashLine {
        id: verticalDash
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.isEndItem ? 11 : 0
        dashColor: "#BFBFBF"
    }

    HorizontalDashLine {
        anchors.left: verticalDash.left
        anchors.right: textTitle.left
        anchors.rightMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 10
        dashColor: "#BFBFBF"
    }

    Rectangle {
        id: iconContainer
        visible: root.hasChildren
        anchors.top: parent.top
        anchors.topMargin: 5
        width: 11
        height: 11
        color: "white"
        border.color: "black"
        border.width: 1

        Rectangle {
            x: 2
            y: 5
            width: 7
            height: 1
            color: "black"
        }

        Rectangle {
            visible: !root.expanded
            x: 5
            y: 2
            width: 1
            height: 7
            color: "black"
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                root.expanded = !root.expanded;
            }
        }
    }

    Text {
        id: textTitle
        anchors.left: iconContainer.right
        anchors.leftMargin: 10
    }

    Item {
        id: contentContainer
        anchors.left: textTitle.left
        anchors.top: iconContainer.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
