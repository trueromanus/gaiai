import QtQuick
import gaiai

InGameStartMenu {
    id: root
    width: 290
    height: 336

    MenuPanel {
        anchors.fill: parent

        Rectangle {
            id: mainMenuTitle
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            width: 35
            color: "#86878C"

            PlainText {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -8
                anchors.left: parent.left
                anchors.leftMargin: 17
                fontSize: 28
                font.bold: true
                color: "#BFC0C5"
                text: "SmartCity<font color='#FAFBFF'>OS</font>"
                rotation: -90
                transformOrigin: Item.Left
            }
        }

        Column {
            id: itemsColumn
            anchors.left: mainMenuTitle.right
            width: root.width - 42

            Repeater {
                width: parent.width
                model: root.menu
                delegate: Item {
                    width: itemsColumn.width
                    height: 55

                    Rectangle {
                        id: topLine
                        visible: modelData.topLine
                        anchors.top: parent.top
                        height: 1
                        width: parent.width
                        color: "#85858D"
                    }

                    Rectangle {
                        visible: modelData.topLine
                        anchors.top: topLine.bottom
                        height: 1
                        width: parent.width
                        color: "#FAF9FF"
                    }

                    Rectangle {
                        id: selectedRectangle
                        visible: false
                        anchors.fill: parent
                        color: "#00007F"
                    }

                    Image {
                        id: icon
                        anchors.left: parent.left
                        anchors.leftMargin: 17
                        anchors.verticalCenter: parent.verticalCenter
                        source: assetsLocation.imagedPath + modelData.image
                        width: 40
                        height: 40
                    }

                    PlainText {
                        anchors.left: icon.right
                        anchors.leftMargin: 18
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.title
                        color: selectedRectangle.visible ? "white" : "black"
                        fontSize: 15
                    }

                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.NoButton
                        hoverEnabled: true
                        onEntered: {
                            selectedRectangle.visible = true;
                        }
                        onExited: {
                            selectedRectangle.visible = false;
                        }
                    }
                }
            }
        }
    }

}
