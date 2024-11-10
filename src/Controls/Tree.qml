import QtQuick

Item {
    id: root

    property alias model: items.model


    Column {
        anchors.fill: parent

        Repeater {
            id: items
            delegate: TreeItem {
                id: treeItem
                width: root.width
                title: modelData.title
                hasChildren: modelData.hasChildrens
                isEndItem: index === items.model.length - 1
                height: 20 + (expanded ? 20 * modelData.childrens.length : 0)
                Loader {
                    id: childrensLoader
                    property var nestedChildrens: modelData.childrens
                    anchors.fill: parent
                    sourceComponent: treeItem.expanded && modelData.hasChildrens ? nestedTree : null
                }
            }
        }
    }

    Component {
        id: nestedTree

        Column {
            anchors.fill: parent

            Repeater {
                id: nestedItems
                model: nestedChildrens
                delegate: TreeItem {
                    width: root.width
                    title: modelData.title
                    hasChildren: modelData.hasChildrens
                    isEndItem: index === nestedItems.model.length - 1
                }
            }
        }
    }
}
