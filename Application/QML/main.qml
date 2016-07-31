import Enums 1.0
import QtQuick 2.7
import QtQuick.Controls 1.5

//mngr.addForce(ForceEnum.GRAVITY)
//mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, 0);
//mngr.addObject("moon", 1.0, 0, 0.3, 0, 2.0, 0);
//mngr.startLiveRendering();

Rectangle {
    id: root
    width: 800
    height: 600
    color: "transparent"
    ToolBar {
        anchors.bottom: parent.bottom
        Button {
            anchors.verticalCenter: parent.verticalCenter
            Text {
                anchors.centerIn: parent
                text: "Add body"
            }
            onClicked: {
            }
        }
    }
}
