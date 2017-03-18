import QtQuick 2.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    id: taskEditor
    anchors.fill: parent
    ColumnLayout {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        Label {
            id: taskName
            text: qsTr("Задание 1: Hello, my Capitan!")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.bold: true
            font.pointSize: 18
        }

        TextArea {
            id: taskDescription
            width: parent.width * 0.8
            text: qsTr("Приветствую, мой капитан! \
Я - твой персональный электронный ассистент, и сейчас я помогу разобраться с техникой.\
 Давай освоим основы управления воздушным судном.\
 Напиши хеллоуворд. Аррр, на абордаж!")
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pointSize: 13
            readOnly: true
        }

        RowLayout {
            Layout.leftMargin: parent.width * 0.15
            Layout.rightMargin: parent.width * 0.15
            ColumnLayout {
                id: numbersForCode

                Rectangle {
                    width: 25
                    height: 6
                }

                Repeater {
                    id: numbersList
                    delegate:
                        Rectangle {
                        width: 25
                        height: 25
                        Text {
                            text: index
                            anchors.verticalCenter: parent.verticalCenter
                            font.bold: true
                        }
                    }
                    model: codeArea.lineCount + 1
                }
            }
            TextArea {
                id: codeArea
                anchors.top: parent.top
                text: qsTr("int main() {\n\tprint(\"Hello\");\n}")
                font.pointSize: 17
                wrapMode: Text.NoWrap
                Layout.fillWidth: true
            }
        }

        Button {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: qsTr("К бою!")
        }
    }
}
