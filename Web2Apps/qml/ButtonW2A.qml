import QtQuick 2.0
import "BasicElements"
Rectangle {
    id:thisbutton
    property alias textEl:mytext
    property alias text:mytext.text
    property alias iconSource:myicon.source
    property int specialOffset
    height: 35
    width: 150
    property color unpressedColor:"#00000000"
    color:myMa.pressed?"red":myMa.containsMouse?"#808080":unpressedColor
    signal clicked()
    Image {
        id: myicon
        source: ""
        property int zoomOffset:myMa.containsMouse?10:0
        height: 35+zoomOffset*2
        anchors.left: parent.left
        fillMode: Image.PreserveAspectFit
        anchors.leftMargin: 10-zoomOffset+specialOffset
        anchors.verticalCenter: parent.verticalCenter
        Behavior on zoomOffset {
            NumberAnimation{duration: 200}
        }
    }
    DText{
        id:mytext
        anchors.left: myicon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        color: "white"
    }
    MouseArea{
        id:myMa

        anchors.fill: parent
        hoverEnabled: thisbutton.color!="#333333"
        onClicked: {

            thisbutton.clicked()
        }
    }
}
