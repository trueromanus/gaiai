import QtQuick
import gaiai
import "../Controls"
import "../Controls/Lines"
import "../Controls/Buttons"
import "../Controls/Panels"

InGameWindowPage {
    id: root
    anchors.fill: parent

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 2
        width: 290
        height: 280
    }

    TableList {
        id: sectionsTableList
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.top: parent.top
        width: 290
        height: 280
        columns: gameBackend.emailClientPage.foldersColumns
        items: gameBackend.emailClientPage.sections
        selectedStyle: 1
        onSelectedItemChanged: {
           gameBackend.emailClientPage.selectedGroup = selectedItem.group;
        }
    }

    Item {
        id: actionsToolbar
        anchors.left: sectionsTableList.right
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 2
        height: 34

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            color: "white"
            height: 1
        }

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            width: 1
            color: "white"
            height: parent.height
        }

        RevertedPanel {
            id: splitterLine1
            width: 3
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
        }

        RevertedPanel {
            id: splitterLine2
            width: 3
            anchors.left: splitterLine1.right
            anchors.leftMargin: 1
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
        }

        IconButton {
            id: pullNewEmailsButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: splitterLine2.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 30
                height: 30
                source: assetsLocation.imagedPath + "pullnewemails.png"
            }

            onClicked: {

            }
        }

        IconButton {
            id: sendWaitingEmailsButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: pullNewEmailsButton.right

            Image {
                anchors.centerIn: parent
                width: 30
                height: 30
                source: assetsLocation.imagedPath + "sendwaitingemails.png"
            }

            onClicked: {

            }
        }

        VerticalLine {
            id: firstSectionLine
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.left: sendWaitingEmailsButton.right
            anchors.leftMargin: 2
        }

        IconButton {
            id: createnewEmailButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: firstSectionLine.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 30
                height: 30
                source: assetsLocation.imagedPath + "createnewemail.png"
            }

            onClicked: {

            }
        }
        IconButton {
            id: resendEmailButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: createnewEmailButton.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 30
                height: 30
                source: assetsLocation.imagedPath + "resendemail.png"
            }

            onClicked: {

            }
        }
        IconButton {
            id: forwardEmailButton
            width: 40
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 1
            anchors.left: resendEmailButton.right
            anchors.leftMargin: 2

            Image {
                anchors.centerIn: parent
                width: 30
                height: 30
                source: assetsLocation.imagedPath + "forwardemail.png"
            }

            onClicked: {

            }
        }
    }

    Rectangle {
        anchors.left: sectionsTableList.right
        anchors.leftMargin: 4
        anchors.top: actionsToolbar.bottom
        anchors.right: parent.right
        width: 290
        height: 248
    }

    TableList {
        id: emailsTableList
        anchors.left: sectionsTableList.right
        anchors.leftMargin: 4
        anchors.top: actionsToolbar.bottom
        anchors.right: parent.right
        height: 248
        columns: gameBackend.emailClientPage.emailColumns
        items: gameBackend.emailClientPage.emails
        selectedStyle: 1
        onSelectedItemChanged: {
            gameBackend.emailClientPage.selectedEmail = selectedItem;
        }
    }

    ButtonPanel {
        id: basicInfoAboutEmail
        pressed: true
        anchors.top: sectionsTableList.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 6
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        height: 50

        Item {
            id: separator
            anchors.left: parent.left
            anchors.leftMargin: 60
            width: 2
            height: parent.height
        }

        PlainText {
            id: fromText
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.right: separator.left
            text: "From"
            font.bold: true
        }

        PlainText {
            id: toText
            anchors.right: separator.left
            anchors.top: fromText.bottom
            text: "To"
            font.bold: true
        }

        PlainText {
            id: subjectText
            anchors.right: separator.left
            anchors.top: toText.bottom
            text: "Subject"
            font.bold: true
        }

        PlainText {
            id: fromValueText
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: separator.right
            anchors.leftMargin: 6
            text: (gameBackend.emailClientPage.selectedEmail ? gameBackend.emailClientPage.selectedEmail["from"] : "")
        }

        PlainText {
            id: toValueText
            anchors.left: separator.right
            anchors.leftMargin: 6
            anchors.top: fromText.bottom
            text: (gameBackend.emailClientPage.selectedEmail ? gameBackend.emailClientPage.selectedEmail["to"] : "")
        }

        PlainText {
            id: subjectValueText
            anchors.left: separator.right
            anchors.leftMargin: 6
            anchors.top: toText.bottom
            text: (gameBackend.emailClientPage.selectedEmail ? gameBackend.emailClientPage.selectedEmail["subject"] : "")
        }
    }

    Panel {
        id: emailContentPanel
        anchors.top: basicInfoAboutEmail.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 1
        anchors.leftMargin: 2
        anchors.rightMargin: 3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2

        Rectangle {
            anchors.fill: parent
            color: "#EFE8EF"
        }

        FlickableArea {
            id: contentFlickableArea
            anchors.fill: parent
            contentHeight: emailTextContent.height

            PlainText {
                id: emailTextContent
                anchors.left: parent.left
                anchors.leftMargin: 8
                color: "#00007F"
                width: contentFlickableArea.width - 30
                wrapMode: Text.WordWrap
                text: (gameBackend.emailClientPage.selectedEmail ? gameBackend.emailClientPage.selectedEmail["content"] : "")
            }
        }

    }
}
