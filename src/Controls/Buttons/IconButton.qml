import QtQuick
import gaiai

InGameButton {
    id: root
    default property alias content: contentContainer.children

    Rectangle {
        color: "#BFB8BF"
        anchors.fill: parent
    }

    Rectangle {
        visible: mouseArea.containsMouse
        color: root.pressed ? "black" : "#FFF8FF"
        anchors.left: parent.left
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: mouseArea.containsMouse
        color: root.pressed ? "black" : "#FFF8FF"
        anchors.top: parent.top
        width: parent.width
        height: 1
    }

    Rectangle {
        visible: mouseArea.containsMouse
        color: root.pressed ? "#FFF8FF" : "black"
        anchors.right: parent.right
        width: 1
        height: parent.height
    }

    Rectangle {
        visible: mouseArea.containsMouse
        color: root.pressed ? "#FFF8FF" : "black"
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
    }

    Item {
        id: contentContainer
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            if (root.disabled) return;

            root.press();
        }
        onReleased: {
            root.release();

            if (!root.disabled && mouseArea.containsMouse) root.clicked();
        }
    }
}
