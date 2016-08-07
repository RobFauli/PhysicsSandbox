import Enums 1.0
import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

ToolBar {
    id: root
    // TODO Implement logic.
    RowLayout {
        id: rowLayout
        CheckBox {
            id: gravityCheck
            text: "Newtonian Gravity"
        }
        CheckBox {
            id: coulombCheck
            text: "Coulomb's Law"
        }
    }
}