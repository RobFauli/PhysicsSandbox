import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root

    Timer {
        running: true //root.visible ? true : false
        interval: 1000
        repeat: true
        triggeredOnStart: true
        onTriggered: objectListModel.updateObjectList()
    }

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

            for (var i = 0; i<names.length; ++i) {
                var key = names[i]
                var pos = mngr.getPosition(key)
                var vel = mngr.getVelocity(key)
                var objectData = {"name": key,
                                  "mass": masses[key], "charge": charges[key],
                                  "x": pos.x, "y": pos.y, "z": pos.z,
                                  "vx": vel.x, "vy": vel.y, "vz": vel.z,
                                 }
                objectListModel.append(objectData)
            }
        }
    }

    TableView {
        anchors.fill: parent
        TableViewColumn { role: "name"; title: "Name"; width: 100}
        TableViewColumn { role: "mass"; title: "Mass"; width: 100}
        TableViewColumn { role: "charge"; title: "Charge"; width: 100}
        TableViewColumn { role: "x"; title: "x"; width: 100}
        TableViewColumn { role: "y"; title: "y"; width: 100}
        TableViewColumn { role: "z"; title: "z"; width: 100}
        model: objectListModel
    }
}