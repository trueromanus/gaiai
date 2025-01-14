import QtQuick
import gaiai
import "../Panels"

InGameButton {
    id: root
    default property alias content: contentContainer.children

    property bool notShowGridPanel: false

    ButtonPanel {
        anchors.fill: parent
        pressed: root.pressed

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 2
            anchors.topMargin: 2
            visible: root.pressed && !root.notShowGridPanel
            color: "white"
        }

        GridCanvasPanel {
            anchors.fill: parent
            anchors.leftMargin: 2
            anchors.topMargin: 2
            visible: root.pressed && !root.notShowGridPanel
        }

        Item {
            id: contentContainer
            anchors.fill: parent
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            if (root.disabled) return;

            if (root.pressed) {
                root.release();
            } else {
                root.press();
            }
        }
    }
}
