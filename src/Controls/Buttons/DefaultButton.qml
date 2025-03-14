import QtQuick
import gaiai
import "../Panels"

InGameButton {
    id: root
    height: 30

    ButtonPanel {
        anchors.fill: parent
        pressed: root.pressed

        PlainText {
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: !root.leftAligned ? Text.AlignHCenter : Text.AlignLeft
            color: root.disabled ? "#818181" : "black"
            text: root.title
            maximumLineCount: 1
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
        }
    }

    MouseArea {
        id: mouseArea
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
