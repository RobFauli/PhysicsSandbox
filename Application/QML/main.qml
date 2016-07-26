import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 360
    height: 360
    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "Hello World"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit();
            }
        }
    }
}
