import QtQuick
import gaiai

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

        Rectangle {
            id: upButton
            width: 10
            height: 10
            anchors.top: parent.top
            anchors.right: parent.right
            color: "green"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    verticalScrollBar.scrollUp();
                }
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

            width: 10

            Rectangle {
                anchors.fill: parent
                color: "yellow"
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

        Rectangle {
            id: downButton
            width: 10
            height: 10
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            color: "green"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    verticalScrollBar.scrollDown();
                }
            }
        }
    }

    //TODO: horizontalScrollBar
}
