// Input.qml

import QtQuick 2.7

FocusScope {
    height: parent.height*0.9
    Rectangle {
        anchors.fill: parent
        color: "white"
        border.color: "green"
    }

    property alias text: input.text
    property alias input: input

    TextInput {
        id: input
        anchors.margins: 4
        anchors.centerIn: parent
        focus: true
    }
}