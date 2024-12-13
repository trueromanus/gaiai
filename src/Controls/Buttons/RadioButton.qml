import QtQuick
import gaiai

InGameRadioButton {
    id: root
    width: parent.width
    height: 20

    Image {
        id: checkboxIcon
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        source: assetsLocation.imagedPath + "disabledradio.png"

        Rectangle {
            visible: root.actualValue === root.radioValue
            anchors.centerIn: parent
            width: 4
            height: 4
            radius: 4
            color: "black"
        }
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
            root.selected();
        }
    }
}
