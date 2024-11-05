import QtQuick

Item {
    id: root

    property alias model: items.model


    Column {
        anchors.fill: parent

        Repeater {
            id: items
            delegate: TreeItem {
                width: root.width
                title: modelData.title
                hasChildren: modelData.hasChildrens
            }
        }
    }
}
