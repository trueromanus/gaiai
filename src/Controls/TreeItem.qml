import QtQuick
import QtQuick.Shapes
import "Lines"

Item {
    id: root
    height: 20

    property alias title: textTitle.text
    property bool hasChildren: false
    property bool isEndItem: false
    property bool expanded: false
    property bool isSelected: false
    default property alias content: contentContainer.children

    signal itemPressed()

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
        anchors.right: itemTitle.left
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

    Item {
        id: itemTitle
        anchors.left: iconContainer.right
        anchors.leftMargin: 10
        width: textTitle.width + 6
        height: 20

        Rectangle {
            visible: root.isSelected
            anchors.fill: parent
            color: "#00007F"

            DashRectangle {
                anchors.fill: parent
                anchors.leftMargin: 1
                dashColor: "#C6C642"
            }
        }

        Text {
            id: textTitle
            color: root.isSelected ? "white" : "black"
            font.weight: root.isSelected ? Font.Medium : Font.Normal
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    root.itemPressed();
                }
            }
        }
    }

    Item {
        id: contentContainer
        anchors.left: itemTitle.left
        anchors.top: iconContainer.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
