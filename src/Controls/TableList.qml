import QtQuick
import gaiai
import "Buttons"

InGameTableList {
    id: root

    Rectangle {
        width: parent.width
        height: 20
        color: "#BFB8BF"
    }

    Row {
        id: columnHeaders
        width: root.fullWidth
        height: 20

        Repeater {
            model: root.columns
            delegate: ContentButton {
                width: modelData.columnWidth
                leftAligned: true
                height: 20

                Loader {
                    anchors.fill: parent
                    property var itemData: modelData
                    sourceComponent: switch(modelData.columnHeaderFormatter) {
                        case "image": return columnHeaderImageComponent;
                        default: return columnHeaderTextComponent;
                    }
                }
            }
        }
    }

    Component {
        id: columnHeaderTextComponent

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.right: parent.right
            anchors.rightMargin: 4
            horizontalAlignment: itemData.columnHeaderAlign === 1 ? Text.AlignHCenter : (itemData.columnHeaderAlign === 2 ? Text.AlignRight : Text.AlignLeft)
            text: itemData.title
        }
    }

    Component {
        id: columnHeaderImageComponent

        Item {
            anchors.fill: parent

            Image {
                anchors.centerIn: parent
                width: itemData.columnHeaderWidth
                height: itemData.columnHeaderHeight
                source: assetsLocation.imagedPath + itemData.title + ".png"
            }
        }
    }

    ListView {
        id: flickableArea
        anchors.top: columnHeaders.bottom
        anchors.bottom: parent.bottom
        width: root.fullWidth
        model: root.items
        clip: true
        delegate: Row {
            id: listRow
            width: root.fullWidth
            height: 20

            property var rowModel: modelData
            property int rowIteratorIndex: index

            Repeater {
                model: root.columns
                delegate: Loader {
                    sourceComponent: switch(modelData.formatter) {
                        case "checkbox": return checkBoxComponent;
                        case "image": return imageComponent;
                        case "emailpage": return emailPage;
                        default: return simpleText;
                    }

                    property int columnWidth: modelData.columnWidth
                    property string columnValue: listRow.rowModel[modelData.field]
                    property bool selectable: modelData.selectable
                    property bool selectedItem: root.selectedItem === listRow.rowModel
                    property bool highlightLine: listRow.rowModel["highlight"] ? listRow.rowModel["highlight"] : false
                    property int currentRowIndex: listRow.rowIteratorIndex
                    property bool isLastIndex: listRow.rowIteratorIndex  === root.items.length - 1

                    signal selectItem()
                    onSelectItem: {
                        root.selectedItem = listRow.rowModel;
                    }
                }
            }
        }
    }

    Item {
        id: fullVerticalScrollBar
        width: verticalScrollBar.isNeedScroll ? 16 : 0
        visible: verticalScrollBar.isNeedScroll
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        ContentButton {
            id: upButton
            width: fullVerticalScrollBar.width
            height: 16
            anchors.top: parent.top
            anchors.right: parent.right
            disabled: verticalScrollBar.thumb === 0

            RightTriangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                shapeColor: verticalScrollBar.thumb === 0 ? "#818181" :"black"
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

            width: fullVerticalScrollBar.width

            GridCanvasPanel {
                anchors.fill: parent
            }

            ButtonPanel {
                id: scrollRoot
                anchors.right: parent.right
                y: verticalScrollBar.thumbPosition
                width: 16
                height: verticalScrollBar.thumb

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
            width: fullVerticalScrollBar.width
            height: 16
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            disabled: verticalScrollBar.thumb === 0

            RightTriangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                shapeColor: verticalScrollBar.thumb === 0 ? "#818181" : "black"
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

    Component {
        id: simpleText

        Item {
            width: columnWidth
            height: 20

            Rectangle {
                visible: selectable && selectedItem && root.selectedStyle === 0
                width: valueText.contentWidth + 4
                height: parent.height
                color: "#00007F"

                DashRectangle {
                    anchors.fill: parent
                    anchors.leftMargin: 1
                    dashColor: "#C6C642"
                }
            }

            Rectangle {
                visible: selectable && selectedItem && root.selectedStyle === 1
                anchors.fill: parent
                color: "#BFB8BF"
            }

            PlainText {
                id: valueText
                verticalAlignment: Text.AlignVCenter
                leftPadding: 2
                width: parent.width
                height: parent.height
                text: columnValue
                color: selectable && selectedItem && root.selectedStyle === 0 ? "white" : "black"
                font.bold: highlightLine
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                maximumLineCount: 1
            }

            MouseArea {
                anchors.fill: parent
                enabled: selectable
                onPressed: {
                    selectItem();
                }
                onDoubleClicked: {
                    root.openItem();
                }
            }
        }
    }

    Component {
        id: emailPage

        Item {
            width: columnWidth
            height: 20

            Rectangle {
                visible: selectable && selectedItem
                anchors.fill: parent
                color: "#BFB8BF"
            }

            VerticalDashLine {
                id: verticalDashLine
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: isLastIndex ? 11 : 0
                anchors.left: parent.left
                anchors.leftMargin: currentRowIndex > 0 ? 20 : 0
                dashColor: currentRowIndex > 0 ? "black" : "transparent"
            }

            HorizontalDashLine {
                id: dashLine
                anchors.left: verticalDashLine.right
                anchors.verticalCenter: parent.verticalCenter
                width: 10
                dashColor: "black"
            }

            Image {
                id: emailSectionIcon
                anchors.left: dashLine.right
                anchors.leftMargin: 1
                anchors.verticalCenter: parent.verticalCenter
                width: 16
                height: 16
                source: assetsLocation.imagedPath + (columnValue.split(":")[1]) + ".png"
            }

            PlainText {
                id: valueText
                anchors.left: emailSectionIcon.right
                anchors.leftMargin: 1
                anchors.right: parent.right
                verticalAlignment: Text.AlignVCenter
                leftPadding: 2
                height: parent.height
                text: columnValue.split(":")[0]
                color: "black"
                font.bold: highlightLine
                wrapMode: Text.NoWrap
                elide: Text.ElideRight
                maximumLineCount: 1
            }

            MouseArea {
                anchors.fill: parent
                enabled: selectable
                onPressed: {
                    selectItem();
                }
                onDoubleClicked: {
                    root.openItem();
                }
            }
        }
    }

    Component {
        id: checkBoxComponent

        Item {
            width: columnWidth
            height: 20

            CheckBoxPanel {
                anchors.centerIn: parent
                width: 14
                height: 14
            }
        }
    }

    Component {
        id: imageComponent

        Item {
            width: columnWidth
            height: 20

            Rectangle {
                visible: selectable && selectedItem && root.selectedStyle === 1
                anchors.fill: parent
                color: "#BFB8BF"
            }

            Image {
                anchors.centerIn: parent
                width: 20
                height: 20
                source: columnValue ? assetsLocation.imagedPath + columnValue + ".png" : ""
            }
        }
    }
}
