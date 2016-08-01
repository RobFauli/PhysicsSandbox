import Enums 1.0
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4

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
        Input {
            id: nameInput
            width: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            text: "Name"
        }
        Button {
            anchors.right: parent.right
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
