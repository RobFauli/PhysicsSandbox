//AddObjectToolBar

import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ToolBar {
    id: addObjectToolBar
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
            Keys.onReturnPressed: {
                clicked()
                event.accepted = true
            }
            onClicked: {
                mngr.addObject(nameInput.text, massInput.text, chargeInput.text, radiusInput.text,
                xInput.text, yInput.text, zInput.text);
                mngr.setObjectVelocity(nameInput.text, vxInput.text, vyInput.text, vzInput.text);
            }
        }
    }
}