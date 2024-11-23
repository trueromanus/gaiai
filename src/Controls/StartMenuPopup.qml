import QtQuick
import gaiai
import "Panels"
import "Lines"

InGameStartMenu {
    id: root
    width: 290
    height: 336

    MenuPanel {
        id: mainMenuPanel
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
                    id: itemRoot
                    width: itemsColumn.width
                    height: 55

                    property bool highlightItem: menuMouseArea.isHovered ||
                        (modelData.title === "Programs" && programsMenu.visible)

                    HorizontalLine {
                        anchors.top: parent.top
                        visible: modelData.topLine
                        width: parent.width
                    }

                    Rectangle {
                        id: selectedRectangle
                        visible: itemRoot.highlightItem
                        anchors.fill: parent
                        color: "#00007F"
                    }

                    Image {
                        id: icon
                        anchors.left: parent.left
                        anchors.leftMargin: 17
                        anchors.verticalCenter: parent.verticalCenter
                        width: 40
                        height: 40
                        source: assetsLocation.imagedPath + modelData.image
                    }

                    PlainText {
                        anchors.left: icon.right
                        anchors.leftMargin: 18
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.title
                        color: itemRoot.highlightItem ? "white" : "black"
                        fontSize: 15
                    }

                    RightTriangle {
                        visible: modelData.submenu
                        anchors.right: parent.right
                        anchors.rightMargin: 4
                        anchors.verticalCenter: parent.verticalCenter
                        shapeColor: itemRoot.highlightItem ? "white" : "black"
                        transform: Scale {
                            origin.x: 5;
                            origin.y: 10;
                            xScale: 0.5
                            yScale: 0.5
                        }
                    }

                    MouseArea {
                        id: menuMouseArea
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        hoverEnabled: true

                        property bool isHovered: false

                        onEntered: {
                            menuMouseArea.isHovered = true;
                            programsMenu.visible = modelData.submenu && modelData.title === "Programs";
                        }
                        onExited: {
                            menuMouseArea.isHovered = false;
                        }
                        onPressed: function (mouse) {
                            mouse.accepted = true;
                            if (modelData.submenu) return;
                            if (modelData.command) root.commandRunned(modelData.command);
                        }
                    }
                }
            }
        }
    }

    CommonMenu {
        id: programsMenu
        anchors.left: mainMenuPanel.right
        anchors.leftMargin: -6
        anchors.top: mainMenuPanel.top
        visible: false
        items: root.programs
        menuWidth: 170
        onCommandPerformed: function (command){
            root.commandRunned(command);
        }
    }

    onVisibleChanged: {
        programsMenu.visible = false;
    }
}
