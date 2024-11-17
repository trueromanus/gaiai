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
}
