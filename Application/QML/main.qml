import Enums 1.0
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//mngr.addForce(ForceEnum.GRAVITY)
//mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, 0);
//mngr.startLiveRendering();

Rectangle {
    id: root
    width: 800
    height: 600
    color: "transparent"
    state: "none"

    Timer {
        id: timer
        interval: 100
        repeat: true
        running: false
        property real secs: 0
        onTriggered: {
            secs += 0.001*interval
        }
    }
    ToolBar {
        id: toolbar
        anchors.bottom: parent.bottom
        RowLayout{
        anchors.fill: parent
            Button {
                id: addObjectButton
                anchors.verticalCenter: parent.verticalCenter
                text: "Add object"
                onClicked: {
                    root.state = "addObject"
                }
            }
            Button {
                id: forceSelectionButton
                anchors.verticalCenter: parent.verticalCenter
                text: "Forces"
                onClicked: {
                    root.state = "forceSelection"
                }
            }
            Button {
                id: objectOverviewButton
                anchors.verticalCenter: parent.verticalCenter
                text: "Objects Overview"
                onClicked: {
                    root.state = "objectOverview"
                }
            }
            Button {
                id: setupExampleButton
                anchors.verticalCenter: parent.verticalCenter
                text: "Setup Example"
                onClicked: {
                    root.state = "none"
                    //mngr.addForce(ForceEnum.GRAVITY)
                    mngr.addObject("sol", 1e5, 0, 1.0, 0, 0, -6);
                    mngr.setObjectVelocity("sol", 0, 0, 0);
                }
            }
            Button {
                id: playPauseButton
                anchors.verticalCenter: parent.verticalCenter
                text: "Play"
                onClicked: {
                    timer.running = !timer.running
                    if (timer.running) {
                        playPauseButton.text = "Pause"
                    }
                    else {
                        playPauseButton.text = "Play"
                    }
                }
            }
            Text {
                id: clock
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: (timer.secs).toFixed(2)
            }
        }

    }
    AddObjectToolBar {
        id: addObjectToolBar
        anchors.bottom: toolbar.top
        anchors.horizontalCenter: toolbar.horizontalCenter
        width: toolbar.width/1.2
        visible: false
        z: -1
    }
    ForceSelectionToolBar {
        id: forceSelectionToolBar
        anchors.bottom: toolbar.top
        anchors.horizontalCenter: toolbar.horizontalCenter
        width: toolbar.width/1.2
        visible: false
        z: -1
    }
    /* // Disabled awaiting TableView in QtQuick.Controls 2.
    ObjectOverview {
        id: objectOverview
        anchors.bottom: toolbar.top
        anchors.horizontalCenter: toolbar.horizontalCenter
        width: toolbar.width/1.2
        height: root.height/1.2
        visible: false
        z: -1
    }
    */
    states: [
        State {
            name: "addObject"
            PropertyChanges {
                target: addObjectToolBar
                visible: true
            }
            PropertyChanges {
                target: forceSelectionToolBar
                visible: false
            }
    /* // Disabled awaiting TableView in QtQuick.Controls 2.
            PropertyChanges {
                target: objectOverview
                visible: false
            }
            */
        },
        State {
            name: "forceSelection"
            PropertyChanges {
                target: addObjectToolBar
                visible: false
            }
            PropertyChanges {
                target: forceSelectionToolBar
                visible: true
            }
    /* // Disabled awaiting TableView in QtQuick.Controls 2.
            PropertyChanges {
                target: objectOverview
                visible: false
            }
            */
        },
    /* // Disabled awaiting TableView in QtQuick.Controls 2.
        State {
            name: "objectOverview"
            PropertyChanges {
                target: addObjectToolBar
                visible: false
            }
            PropertyChanges {
                target: forceSelectionToolBar
                visible: false
            }
            PropertyChanges {
                target: objectOverview
                visible: true
            }
        }, 
        */
        State {
            name: "none"
            PropertyChanges {
                target: addObjectToolBar
                visible: false
            }
            PropertyChanges {
                target: forceSelectionToolBar
                visible: false
            }
    /* // Disabled awaiting TableView in QtQuick.Controls 2.
            PropertyChanges {
                target: objectOverview
                visible: false
            }
            */
        }
    ]
}
