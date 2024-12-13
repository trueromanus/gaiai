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
            delegate: DefaultButton {
                title: modelData.title
                width: modelData.columnWidth
                leftAligned: true
                height: 20
            }
        }
    }

    ListView {
        anchors.top: columnHeaders.bottom
        anchors.bottom: parent.bottom
        width: root.fullWidth
        model: root.items
        delegate: Row {
            id: listRow
            width: root.fullWidth
            height: 20

            property var rowModel: modelData

            Repeater {
                model: root.columns
                delegate: Loader {
                    sourceComponent: switch(modelData.formatter) {
                        case "checkbox": return checkBoxComponent;
                        default: return simpleText;
                    }

                    property int columnWidth: modelData.columnWidth
                    property string columnValue: listRow.rowModel[modelData.field]
                    property bool selectable: modelData.selectable
                    property bool selectedItem: root.selectedItem === listRow.rowModel

                    signal selectItem()
                    onSelectItem: {
                        root.selectedItem = listRow.rowModel;
                    }
                }
            }
        }
    }

    Component {
        id: simpleText

        Item {
            width: columnWidth
            height: 20

            Rectangle {
                visible: selectable && selectedItem
                width: valueText.contentWidth + 4
                height: parent.height
                color: "#00007F"

                DashRectangle {
                    anchors.fill: parent
                    anchors.leftMargin: 1
                    dashColor: "#C6C642"
                }
            }

            PlainText {
                id: valueText
                verticalAlignment: Text.AlignVCenter
                leftPadding: 2
                width: parent.width
                height: parent.height
                text: columnValue
                color: selectable && selectedItem ? "white" : "black"
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
}
