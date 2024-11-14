import QtQuick
import gaiai

InGameTree {
    id: root

    property var model

    TreeLevel {
        id: rootLevel
        treeRoot: root
        nestedChildrens: root.model
        childComponent: childComponent
    }

    Component {
        id: childComponent

        TreeLevel {
            id: nestedLevel
            anchors.top: parent.top
            anchors.topMargin: 4
            treeRoot: root
            nestedChildrens: levelChildrens
            childComponent: rootLevel.childComponent
        }
    }
}
