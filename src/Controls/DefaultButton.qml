import QtQuick
import gaiai

InGameButton {
    id: root

    ButtonPanel {
        anchors.fill: parent
        pressed: root.pressed

        PlainText {
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            text: root.title
            maximumLineCount: 1
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
        }
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            root.press();
        }
        onReleased: {
            root.release();

            if (!root.disabled && mouseArea.containsMouse) root.clicked();
        }
        onContainsMouseChanged: {
            if (!mouseArea.containsMouse) root.release();
            if (mouseArea.containsMouse) root.press();
        }
    }
}
