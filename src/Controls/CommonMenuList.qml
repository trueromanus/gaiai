import QtQuick
import "Panels"
import "Lines"

MenuPanel {
    id: root
    height: itemsColumn.height + 4

    property alias listModel: items.model


    Column {
        id: itemsColumn
        anchors.left: parent.left
        anchors.right: parent.right

        Repeater {
            id: items
            delegate: Item {
                width: itemsColumn.width
                height: 28

                HorizontalLine {
                    visible: modelData.upperLine
                    width: parent.width
                }

                Rectangle {
                    visible: menuMouseArea.isHovered
                    anchors.fill: parent
                    anchors.topMargin: 1
                    anchors.bottomMargin: 2
                    anchors.rightMargin: 1
                    color: "#00007F"
                }

                PlainText {
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    anchors.right: parent.right
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    color: menuMouseArea.isHovered ? "white" : "black"
                    text: modelData.title
                    fontSize: 13
                }

                HorizontalLine {
                    visible: modelData.bottomLine
                    width: parent.width
                    anchors.bottom: parent.bottom
                }

                MouseArea {
                    id: menuMouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton
                    hoverEnabled: true

                    property bool isHovered: false

                    onEntered: {
                        isHovered = true;
                    }
                    onExited: {
                        isHovered = false;
                    }
                    onPressed: function (mouse) {
                        mouse.accepted = true;
                        if (modelData.hasChildrens) return; // for submenu don't need to make any action

                        //if (modelData.command) root.commandRunned(modelData.command)
                    }
                }
            }
        }
    }

}
