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
    color: "darkgrey"
    Rectangle {
        width: 120
        height: 120
        color: "steelblue"
        border.color: Qt.lighter(color)
        border.width: 3
        radius: 16
        Text {
            anchors.centerIn: parent
            text: "Start simulation"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mngr.addForce(ForceEnum.GRAVITY)
                mngr.addObject("sol", 1e5, 0, 0.5, 0, 0, 0);
                mngr.addObject("moon", 1.0, 0, 0.3, 0, 1.0, 0);
                mngr.setObjectVelocity("moon", 0.003, 0, 0);
                mngr.setLightPosition(10, 0, 0);
                mngr.startLiveRendering(Screen.name);
                //Qt.quit();
            }
        }

    }
}
