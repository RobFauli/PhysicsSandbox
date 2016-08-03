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
            Layout.minimumWidth: 100
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "Name"
        }
        Input {
            id: massInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "m"
        }
        Input {
            id: chargeInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "q"
        }
        Input {
            id: xInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "x"
        }
        Input {
            id: yInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "y"
        }
        Input {
            id: zInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "z"
        }
        Input {
            id: vxInput
            Layout.minimumWidth: 20
            Layout.fillHeight: true
            anchors.verticalCenter: parent.verticalCenter
            text: "vx"
        }
        Input {
            id: vyInput
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
            text: "Add"
            onClicked: {
                mngr.addForce(ForceEnum.GRAVITY);
                mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, -6);
                mngr.addObject("moon", 1.0, 0, 0.3, 0, 2.0, -6);
            }
        }
        }
    }
}
