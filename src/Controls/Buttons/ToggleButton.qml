import QtQuick
import gaiai
import "../Panels"

InGameButton {
    id: root
    default property alias content: contentContainer.children

    ButtonPanel {
        anchors.fill: parent
        pressed: root.pressed

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
