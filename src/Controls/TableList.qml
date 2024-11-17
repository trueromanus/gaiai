import QtQuick
import gaiai

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
                    sourceComponent: simpleText

                    property int columnWidth: modelData.columnWidth
                    property string columnValue: listRow.rowModel[modelData.field]
                }
            }
        }
    }

    Component {
        id: simpleText

        PlainText {
            verticalAlignment: Text.AlignVCenter
            leftPadding: 2
            width: columnWidth
            height: 20
            text: columnValue
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
            maximumLineCount: 1
        }
    }
}
