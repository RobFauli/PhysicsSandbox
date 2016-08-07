import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    ListModel {
        id: objectListModel

        ListElement {
            name: "exampleObject"
            mass: 3
            charge: -1
            x: -7.4; y: 0.3; z: 11.4
            vx: 0; vy: 3.2; vz: -2.2
        }

        function updateObjectList() {
            objectListModel.clear()
            var names = mngr.getObjectNames()
            var masses = mngr.getObjectMasses()
            var charges = mngr.getObjectCharges()
        }
    }

    ListView {
        anchors.fill: parent
        model: objectListModel
        delegate: Text{
            text: name
        }
    }
}