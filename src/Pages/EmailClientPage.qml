import QtQuick
import gaiai
import "../Controls"

InGameWindowPage {
    id: root
   anchors.fill: parent

    TableList {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 200
        columns: gameBackend.emailClientPage.foldersColumns
        items: gameBackend.emailClientPage.sections
        /*onSelectedItemChanged: {
           gameBackend.smartTrackerPage.selectedTaskInList = selectedItem;
        }
        onOpenItem: {
           tasksTree.selectNode(gameBackend.smartTrackerPage.selectedTaskInList);
        }*/
    }
}
