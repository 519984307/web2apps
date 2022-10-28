import QtQuick 2.0

Item{
    Behavior on opacity {
        NumberAnimation{
            duration:400
        }
    }
    Row{
        layoutDirection:Qt.RightToLeft
        anchors.right: parent.right
        anchors.top: parent.top
        width: 20
        spacing: 5
        z:100


        IconHolderButton {
            iconwidth: 20
            iconSource: "qrc:/images/Iconpack Minimal Up.svg"

            id:myrectbefore
            visible: index!=0
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    domParser.updatePosition(index,-1)
                }
            }

        }
        IconHolderButton {
            iconwidth: 20
            iconSource: "qrc:/images/Iconpack Minimal down.svg"
            visible: index!=(repeaterList.count-1)

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    domParser.updatePosition(index,1)
                }
            }
        }
        IconHolderButton {
            iconwidth: 20
            iconSource: "qrc:/images/Iconpack Minimal Discard.svg"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    domParser.updatePosition(index,0)
                }
            }
        }
        IconHolderButton {
            iconwidth: 20
            iconSource: "qrc:/images/Iconpack Minimal Edit 2.svg"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    domParser.currentItem=index
                    //elementsSetting.expand=true
                    //domParser.updatePosition(index,0)
                }
            }
        }
    }
}
