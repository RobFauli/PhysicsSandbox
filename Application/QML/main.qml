import Enums 1.0
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

//mngr.addForce(ForceEnum.GRAVITY)
//mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, 0);
//mngr.startLiveRendering();

Rectangle {
    id: root
    width: 800
    height: 600
    color: "transparent"
    Timer {
        id: timer
        interval: 100
        repeat: true
        running: true
        property real secs: 0
        onTriggered: {
            secs += 0.001*interval
        }
    }
    ToolBar {
        id: toolbar
        anchors.bottom: parent.bottom
        Button {
            anchors.verticalCenter: parent.verticalCenter
            text: "Add object"
            onClicked: {
            }
        }
        Text {
            id: clock
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            text: timer.secs
        }
    }
    ToolBar {
        anchors.bottom: toolbar.top
        anchors.horizontalCenter: toolbar.horizontalCenter
        width: toolbar.width/1.2
        z: -1
        RowLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.fill: parent
        Input {
            id: nameInput
            KeyNavigation.tab: massInput
            Layout.minimumWidth: 100
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "Name"
        }
        Input {
            id: massInput
            KeyNavigation.tab: chargeInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "m"
        }
        Input {
            id: chargeInput
            KeyNavigation.tab: radiusInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "q"
        }
        Input {
            id: radiusInput
            KeyNavigation.tab: xInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "r"
        }
        Input {
            id: xInput
            KeyNavigation.tab: yInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "x"
        }
        Input {
            id: yInput
            KeyNavigation.tab: zInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "y"
        }
        Input {
            id: zInput
            KeyNavigation.tab: vxInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "z"
        }
        Input {
            id: vxInput
            KeyNavigation.tab: vyInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "vx"
        }
        Input {
            id: vyInput
            KeyNavigation.tab: vzInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "vy"
        }
        Input {
            id: vzInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "vz"
        }
        Button {
            anchors.verticalCenter: parent.verticalCenter
            text: "Preview"
            onClicked: {
                // Add to visualization temporarily.
            }
        }
        Button {
            anchors.verticalCenter: parent.verticalCenter
            text: "Add"
            onClicked: {
                mngr.addObject(nameInput.text, massInput.text, chargeInput.text, radiusInput.text,
                xInput.text, yInput.text, zInput.text);
            }
        }
        }
    }

}
