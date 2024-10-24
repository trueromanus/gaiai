import QtQuick

Item {
    id: root
    property alias iconWidth: iconImage.width
    property alias iconHeight: iconImage.height
    property alias iconSource: iconImage.source

    signal pressed()

    Rectangle {
        color: "#BFB8BF"
        anchors.fill: parent
    }

    Rectangle {
        color: "#FFF8FF"
        anchors.left: parent.left
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "#FFF8FF"
        anchors.top: parent.top
        width: parent.width
        height: 1
    }

    Rectangle {
        color: "black"
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "#7B7B7B"
        anchors.right: parent.right
        anchors.rightMargin: 1
        width: 1
        height: parent.height
    }

    Rectangle {
        color: "black"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    Rectangle {
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

    Image {
        id: iconImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onPressed: function (mouse){
            mouse.accepted = true;
            root.pressed();
        }
    }
}
