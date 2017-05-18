import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    property alias startButton: startButton
    anchors.fill: parent
    ColumnLayout {
        id: mainPage
        anchors.fill: parent
        Label {
            text: qsTr("Game Engine")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: false
        }

        Label {
            text: qsTr("Скрипты кораблей")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.italic: true
        }

        Label {
            text: "Красные"
            color: "red"
            font.pointSize: 16
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
        TableView {
            focus: true
            id: redTeam
            model: redModel
            Layout.preferredWidth: parent.width * 0.8
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            TableViewColumn {
                role: "number"
                title: "Корабль"
                width: redTeam.width * 0.25
            }
            TableViewColumn {
                role: "scriptPath"
                title: "Скрипт"
                width: redTeam.width * 0.25
            }
            TableViewColumn {
                role: "constructionPath"
                title: "ТТХ"
                width: redTeam.width * 0.25
            }
            TableViewColumn {
                role: "comander"
                title: "Командир"
                width: redTeam.width * 0.24
            }
        }

        ListModel {
            id: redModel
            ListElement {
                number: 1
                scriptPath: "bin/resurses/Ship1.lua"
                constructionPath: "bin/Ship1.desc"
                comander: "Illya Komaniec"
            }
            ListElement {
                number: 2
                scriptPath: "bin/resurses/Ship1.lua"
                constructionPath: "bin/Ship1.desc"
                comander: "Illya Komaniec"
            }
            ListElement {
                number: 3
                scriptPath: "bin/resurses/Ship1.lua"
                constructionPath: "bin/Ship1.desc"
                comander: "Illya Komaniec"
            }
        }

        ListModel {
            id: greenModel
            ListElement {
                number: 1
                scriptPath: "bin/resurses/Ship2.lua"
                constructionPath: "bin/Ship2.desc"
                comander: "Artem Mikhalev"
            }
            ListElement {
                number: 2
                scriptPath: "bin/resurses/Ship2.lua"
                constructionPath: "bin/Ship2.desc"
                comander: "Artem Mikhalev"
            }
            ListElement {
                number: 3
                scriptPath: "bin/resurses/Ship3.lua"
                constructionPath: "bin/Ship3.desc"
                comander: "Artem Mikhalev"
            }
        }

        Label {
            text: "Зелёные"
            color: "green"
            font.pointSize: 16
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
        TableView {
            focus: true
            id: greenTeam
            model: greenModel

            Layout.preferredWidth: parent.width * 0.8
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            TableViewColumn {
                role: "number"
                title: "Корабль"
                width: greenTeam.width * 0.25
            }
            TableViewColumn {
                role: "scriptPath"
                title: "Скрипт"
                width: greenTeam.width * 0.25
            }
            TableViewColumn {
                role: "constructionPath"
                title: "ТТХ"
                width: greenTeam.width * 0.25
            }
            TableViewColumn {
                role: "comander"
                title: "Командир"
                width: greenTeam.width * 0.24
            }
        }
        Button {
            id: startButton
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: "Запустить"
        }
    }
}
