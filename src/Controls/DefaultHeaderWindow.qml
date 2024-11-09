import QtQuick
import gaiai

InGameWindowDefaultHeader {
    id: root

    Rectangle {
        anchors.fill: parent
        anchors.leftMargin: 3
        anchors.rightMargin: 3.5
        anchors.topMargin: 3
        anchors.bottomMargin: 2
        color: root.activated ? "#00007F" : "#7F787F"
        width: root.width
        height: root.height

    }

    Text {
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        width: root.width - 28
        font.pixelSize: 12
        font.family: "Arial"
        maximumLineCount: 1
        wrapMode: Text.Wrap
        elide: Text.ElideRight
        color: "white"
        font.bold: true
        text: root.title
    }

    MouseArea {
        id: mouseArea
        property real originX: -1
        property real originY: -1
        property bool moving: false

        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        onPressed: {
            moving = true;
        }
        onReleased: {
            moving = false;
            originX = -1;
            originY = -1;
        }
        onPositionChanged: function (mouse) {
            if (mouseArea.moving) {
                if (originX === -1) originX = mouse.x;
                if (originY === -1) originY = mouse.y;

                const deltaX = originX - mouse.x;
                const deltaY = originY - mouse.y;

                let newXValue = root.parent.x - deltaX;
                if (newXValue < 0) newXValue = 0;
                if (newXValue + root.width > desktop.width) newXValue = desktop.width - root.width;
                root.parent.x = newXValue;

                let newYValue = root.parent.y - deltaY;
                if (newYValue < 0) newYValue = 0;
                root.parent.y = newYValue;
            }
        }
    }

    IconButton {
        anchors.top: root.top
        anchors.topMargin: 5
        anchors.right: root.right
        anchors.rightMargin: 6
        width: 16
        height: 16
        iconWidth: 10
        iconHeight: 8
        iconX: 3
        iconY: 3
        iconSource: assetsLocation.imagedPath + "closewindowicon.png"
        onPressed: {
            root.needCloseWindow();
        }
    }
}
