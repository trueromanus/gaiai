import QtQuick
import gaiai
import "Panels"

InGameWindow {
    id: root
    title: ""
    windowWidth: 100
    windowHeight: 100
    default property alias content: contentContainer.children

    WindowPanel {
        anchors.fill: parent
    }

    DefaultHeaderWindow {
        id: windowHeader
        title: root.title
        activated: root.activated
        width: parent.width
        height: 24
        anchors.top: parent.top
        onNeedCloseWindow: {
            root.closeWindow();
        }
        onNeedActivateWindow: {
            taskBar.activateWindow(root);
        }
    }

    Item {
        id: contentContainer
        anchors.top: windowHeader.bottom
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
        anchors.leftMargin: 3
        anchors.rightMargin: 3
        anchors.bottomMargin: 3
    }

}
