import QtQuick
import gaiai
import "Controls"

Window {
    id: desktop
    width: 1280
    minimumWidth: 1280
    height: 720
    minimumHeight: 720
    visible: true
    title: qsTr("gaiai")

    Item {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "#00787F"
        }

        Item {
            id: desktopWindows
            anchors.fill: parent
        }

        Item {
            anchors.fill: parent

            MouseArea {
                anchors.fill: parent
                enabled: startMenuPopup.visible
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onPressed: {
                    if (startMenuPopup.visible) taskBar.toggleStartMenuButton();
                }
            }
        }

        TaskBar {
            id: taskBar
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            windowsContainer: desktopWindows
        }

        StartMenuPopup {
            id: startMenuPopup
            visible: taskBar.startMenuOpened
            y: taskBar.y - (height - 5)
            onCommandRunned: function (command){
                if (command === "") return;

                taskBar.toggleStartMenuButton();

                taskBar.createDefaultWindow(command, 1);
            }
        }

        SystemSettings {
            id: systemSettings
        }
    }

    GameBackend {
        id: gameBackend
    }

    Item {
        id: assetsLocation
        property string iconsPath: Qt.resolvedUrl("Icons/")
        property string imagedPath: Qt.resolvedUrl("Images/")
    }
}

/*
Subject: Warm Welcome and Congratulations on Your New Position as System Operator
Dear [Newcomer's Name],
I am delighted to extend a warm welcome to you as you embark on your journey with our team as a System Operator. Congratulations on your new position! Your expertise and skills will undoubtedly make a valuable contribution to our team, and we are thrilled to have you on board.
As you settle into your new role, please know that myself and the entire team are here to support you every step of the way. Should you have any questions or need assistance, do not hesitate to reach out. We believe that with your experience and dedication, you will excel in this role and be an integral part of our organization.
I look forward to seeing your contributions and witnessing your growth within our company. Once again, congratulations on your new position as a System Operator. Welcome to the team!
Warm regards,
Mr. Norton
[Your Position]
[Company Name]
*/
