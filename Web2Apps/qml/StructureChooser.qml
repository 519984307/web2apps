import QtQuick 2.0
import "components"
import ColorComponents 1.0

import QtQuick.Controls 1.4

Rectangle {
    id: colorPicker

    property int verticalArrangement:0
    clip: true
    height: 650
    width: expand?190:0
    property bool expand:false

    Column{
        anchors.centerIn: parent
        Button{
            text:"Normal"
            onClicked:{
                structure.expand=false
                domParser.updateParam("structure",
                                      "Normal")
            }
        }
        Button{
            text:"Left Menu"
            onClicked:{
                structure.expand=false
                domParser.updateParam("structure",
                                      "Left Menu")
            }
        }
        Button{
            text:"Bottom Menu"
            onClicked:{
                structure.expand=false
                domParser.updateParam("structure",
                                      "Bottom Menu")
            }
        }
        TextFieldW2A{
              placeholderText: "Enter width"
              onAccepted:
                  domParser.updateParam("structureWidth",
                                        parseInt(text))
        }


    }
}
