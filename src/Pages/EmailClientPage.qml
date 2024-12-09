import QtQuick
import gaiai
import "Controls"

InGameWindowPage {
    id: root
    anchors.fill: parent


    TableList {
        anchors.fill: parent
        columns: gameBackend.emailClientPage.foldersColumns
        //items: tasksTree.selectedNode.objectChildrens
        /*onSelectedItemChanged: {
            gameBackend.smartTrackerPage.selectedTaskInList = selectedItem;
        }
        onOpenItem: {
            tasksTree.selectNode(gameBackend.smartTrackerPage.selectedTaskInList);
        }*/
    }
}
