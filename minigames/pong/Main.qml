import QtQuick
import QtQuick.Controls
import MiniGames

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Pong")

    Item {
        id: mainMenu
        anchors.centerIn: parent
        width: 200
        height: menuContainerColumn.implicitHeight

        Column {
            id: menuContainerColumn
            width: 180
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: "Pong MiniGame"
                font.pointSize: 12
                font.bold: true
            }
            Item {
                width: parent.width
                height: startGameButton.height

                Button {
                    id: startGameButton
                    anchors.centerIn: parent
                    width: 80
                    text: "Start Game"
                    onPressed: {
                        mainMenu.visible = false;
                        pongMiniGame.visible = true;
                        pongMiniGame.resetGame();
                    }
                }
            }

            Item {
                width: parent.width
                height: gameModeComboBox.height

                ComboBox {
                    id: gameModeComboBox
                    anchors.centerIn: parent
                    width: 120
                    model: ["Classic", "Difference 10", "Difference 20", "30 and 30"]
                    onCurrentIndexChanged: {
                        pongMiniGame.gameMode = gameModeComboBox.currentIndex;
                    }
                }
            }

            Item {
                width: parent.width
                height: gameControlComboBox.height

                ComboBox {
                    id: gameControlComboBox
                    anchors.centerIn: parent
                    width: 120
                    model: ["Player vs Player", "Player vs CPU", "CPU vs Player", "Ball"]
                    onCurrentIndexChanged: {
                        pongMiniGame.gameControlMode = gameControlComboBox.currentIndex;
                    }
                }
            }

            Item {
                width: parent.width
                height: gameBonusComboBox.height

                ComboBox {
                    id: gameBonusComboBox
                    anchors.centerIn: parent
                    width: 120
                    model: ["No bonus", "Only buffs", "Only debuffs", "Buffs and debuffs"]
                    onCurrentIndexChanged: {
                        pongMiniGame.bonusMode = gameBonusComboBox.currentIndex;
                    }
                }
            }

            Item {
                width: parent.width
                height: exitGameButton.height

                Button {
                    id: exitGameButton
                    anchors.centerIn: parent
                    width: 80
                    text: "Exit Game"
                    onPressed: {
                        root.close();
                    }
                }
            }
        }
    }

    Item {
        id: winnerScreen
        visible: false
        anchors.centerIn: parent
        width: 200
        height: menuContainerColumn.implicitHeight

        property bool winnerLeft: false
        property int winnerLeftScore: 0
        property int winnerRightScore: 0

        Column {
            id: winnerScreenColumn
            width: 180
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: "Game is over"
                font.pointSize: 12
            }
            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 11
                text: "Winner is " + (winnerScreen.winnerLeft ? "left player" : "right player") + "!!!"
            }
            Text {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 11
                text: "Final score is " + winnerScreen.winnerLeftScore + " - " + winnerScreen.winnerRightScore
            }
            Item {
                width: parent.width
                height: backToMainMenuButton.height

                Button {
                    id: backToMainMenuButton
                    anchors.centerIn: parent
                    width: 120
                    text: "Back to Main Menu"
                    onPressed: {
                        winnerScreen.visible = false;
                        mainMenu.visible = true;
                    }
                }
            }
        }
    }

    PongMiniGame {
        id: pongMiniGame
        active: false
        visible: false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        inputHandler: InputHandler {
        }

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

        onWeHaveWinner: function (leftWinner, leftScore, rightScore){
            pongMiniGame.active = false;
            pongMiniGame.visible = false;
            winnerScreen.visible = true;
            winnerScreen.winnerLeft = leftWinner;
            winnerScreen.winnerLeftScore = leftScore;
            winnerScreen.winnerRightScore = rightScore;
        }
    }
}
