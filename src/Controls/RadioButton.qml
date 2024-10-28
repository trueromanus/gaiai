import QtQuick
import gaiai

InGameRadioButton {
    id: root
    width: parent.width
    height: 24

    Image {
        id: checkboxIcon
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        source: assetsLocation.imagedPath + "disabledradio.png"
    }

    Text {
        anchors.left: checkboxIcon.right
        anchors.leftMargin: 4
        anchors.verticalCenter: parent.verticalCenter
        text: root.title
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {

        }
    }
}
