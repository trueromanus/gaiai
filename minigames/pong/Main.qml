import QtQuick
import MiniGames

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    InputHandler {
        id: inputHandler
    }

    PongMiniGame {
        id: pongMiniGame
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        inputHandler: inputHandler

        Rectangle {
            anchors.fill: parent
            color: "#e6e6e6"
        }

        Text {
            anchors.centerIn: parent
            text: pongMiniGame.leftScore + " - "+ pongMiniGame.rightScore
            font.pixelSize: 50
            opacity: .9
            color: "white"
        }

        GameEntity {
            identifier: "topWall"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
        }

        GameEntity {
            identifier: "leftWall"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 1
        }

        GameEntity {
            identifier: "rightWall"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 1
        }

        GameEntity {
            identifier: "bottomWall"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1
        }

        GameEntity {
            id: leftPaddle
            identifier: "leftPaddle"
            y: 40
            width: 15
            height: 40

            Rectangle {
                anchors.fill: parent
                color: pongMiniGame.leftPaddleColor
            }
        }

        GameEntity {
            id: rightPaddle
            identifier: "rightPaddle"
            anchors.right: parent.right
            y: 40
            width: 15
            height: 40

            Rectangle {
                anchors.fill: parent
                color: pongMiniGame.rightPaddleColor
            }
        }

        GameEntity {
            identifier: "ball"
            width: 20
            height: 20
            x: pongMiniGame.ballPosition.x
            y: pongMiniGame.ballPosition.y

            Rectangle {
                anchors.fill: parent
                color: pongMiniGame.ballColor
                antialiasing: true
                radius: 10
            }
        }

        Component.onCompleted: {
            pongMiniGame.resetGame();
        }
    }
}
