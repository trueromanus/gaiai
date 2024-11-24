import QtQuick
import gaiai
import "Panels"

Item {
    anchors.fill: parent

    default property alias content: flickableArea.children

    Flickable {
        id: flickableArea
        anchors.right: fullVerticalScrollBar.left
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom // replace on horizontal scrollbar
        clip: true
    }

    Item {
        id: fullVerticalScrollBar
        width: 16
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        ContentButton {
            id: upButton
            width: 16
            height: 16
            anchors.top: parent.top
            anchors.right: parent.right

            RightTriangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                shapeColor: "black"
                transform: [
                    Scale {
                        origin.x: 5;
                        origin.y: 10;
                        xScale: 0.43
                        yScale: 0.43
                    },
                    Rotation {
                        origin.x: 5;
                        origin.y: 10;
                        angle: -90
                    }
                ]
            }

            onClicked: {
                verticalScrollBar.scrollUp();
            }
        }

        VerticalScrollBar {
            id: verticalScrollBar
            anchors.top: upButton.bottom
            anchors.right: parent.right
            anchors.bottom: downButton.top

            scrollAreaHeight: flickableArea.height
            scrollAreaContentHeight: flickableArea.contentHeight
            moving: mouseRoot.pressed

            onRequiredChangeScrollPosition: function (newValue) {
                flickableArea.contentY = newValue;
            }

            width: 16

            GridCanvasPanel {
                anchors.fill: parent
            }


            Rectangle {
                id: scrollRoot
                anchors.right: parent.right
                y: verticalScrollBar.thumbPosition
                width: 10
                height: verticalScrollBar.thumb
                color: "red"

                MouseArea {
                    id: mouseRoot
                    anchors.fill: parent

                    onPressed: function (mouse) {
                        verticalScrollBar.setOriginY(mouse.y);
                    }
                    onReleased: {
                        verticalScrollBar.clearOriginY();
                    }

                    onPositionChanged: function (mouse) {
                        if (!pressed) return;

                        verticalScrollBar.changeAfterChangePosition(mouse.y);
                    }
                }
            }
        }

        ContentButton {
            id: downButton
            width: 16
            height: 16
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            RightTriangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                shapeColor: "black"
                transform: [
                    Scale {
                        origin.x: 5;
                        origin.y: 10;
                        xScale: 0.43
                        yScale: 0.43
                    },
                    Rotation {
                        origin.x: 5;
                        origin.y: 10;
                        angle: 90
                    }
                ]
            }

            onClicked: {
                verticalScrollBar.scrollDown();
            }
        }
    }

    //TODO: horizontalScrollBar
}
