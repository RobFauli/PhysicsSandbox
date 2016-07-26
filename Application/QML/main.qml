import Enums 1.0
import QtQuick 2.7
import QtQuick.Window 2.2

//mngr.addForce(ForceEnum.GRAVITY)
//mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, 0);
//mngr.addObject("moon", 1.0, 0, 0.3, 0, 2.0, 0);
//mngr.startLiveRendering();

Window {
    id: window
    visible: true
    width: 360
    height: 360
    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "Hello World \n"
                  + Screen.name
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mngr.addForce(ForceEnum.GRAVITY)
                mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, 0);
                mngr.addObject("moon", 1.0, 0, 0.3, 0, 2.0, 0);
                mngr.startLiveRendering(Screen.name);
                //Qt.quit();
            }
        }
    }
}
