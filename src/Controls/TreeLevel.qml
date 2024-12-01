import QtQuick

Column {
    id: root
    anchors.fill: parent

    height: 20 + fullHeight

    property var nestedChildrens
    property var treeRoot
    property Component childComponent
    property int fullHeight: 0
    property bool allExpandedOnStart: false

    Repeater {
        id: items
        model: root.nestedChildrens
        delegate: TreeItem {
            id: treeItem
            width: root.treeRoot.width
            title: modelData.title
            hasChildren: modelData.hasChildrens
            isEndItem: index === items.model.length - 1
            isSelected: treeRoot.selectedNode === modelData
            height: 20 + (expanded ? nestedHeight : 0)
            property int nestedHeight: 0

            Loader {
                id: loader
                anchors.fill: parent
                property var levelChildrens: modelData.childrens
                sourceComponent: treeItem.expanded && modelData.hasChildrens ? root.childComponent : null
                onLoaded: {
                    recalculateNestedHeight();
                }
            }

            onItemPressed: {
                treeRoot.selectNode(modelData);
            }

            onExpandedChanged: {
                recalculateNestedHeight();
            }

            Component.onCompleted: {
                if (root.allExpandedOnStart) treeItem.expanded = true;
            }

            function recalculateNestedHeight() {
                if (loader.status !== Loader.Ready) return;

                let fullHeight = 0;
                for (const element of loader.item.children) {
                    fullHeight += element.height;
                }

                const changed = treeItem.nestedHeight !== fullHeight;
                treeItem.nestedHeight = fullHeight;

                if (changed) recalculateFullHeight();
            }
        }
    }

    function recalculateFullHeight() {
        let fullHeight = 0;
        for (const element of items.children) {
            fullHeight += element.nestedHeight;
        }
        root.fullHeight = fullHeight;
    }
}
