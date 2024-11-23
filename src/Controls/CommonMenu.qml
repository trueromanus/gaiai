import QtQuick
import gaiai

InGameMenu {
    id: root

    property int menuWidth: 200

    CommonMenuList {
        width: root.menuWidth
        listModel: root.items
        onCommandPerformed: function (command) {
            root.commandPerformed(command);
        }
    }
}
