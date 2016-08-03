// Input.qml

import QtQuick 2.7

FocusScope {
    Rectangle {
        anchors.fill: parent
        color: "white"
        border.color: "green"
        TextInput {
            id: input
            anchors.margins: 4
            anchors.centerIn: parent
            focus: true
        }
    }

    property alias text: input.text
    property alias input: input

}