import QtQuick
import QtQuick.Shapes

Item {
    id: root
    height: 20

    property alias title: textTitle.text
    property bool hasChildren: false
    property bool isEndItem: false
    default property alias content: contentContainer.children

    VerticalDashLine {
        id: verticalDash
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.isEndItem ? 10 : 0
        dashColor: "#BFBFBF"
    }

    HorizontalDashLine {
        anchors.left: verticalDash.left
        anchors.right: textTitle.left
        anchors.rightMargin: 1
        anchors.verticalCenter: parent.verticalCenter
        dashColor: "#BFBFBF"
    }

    Rectangle {
        id: iconContainer
        visible: root.hasChildren
        anchors.verticalCenter: parent.verticalCenter
        width: 10
        height: 10
        color: "white"
        border.color: "black"
        border.width: 1
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
