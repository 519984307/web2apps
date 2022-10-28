import QtQuick 2.4
import "../BasicElements"
import ".."
Rectangle {
    property string name

    signal skinSelected();
    id: rectangle6
    border.color: skin.bordercolor
    border.width: skin.bordersize
    clip:true


    Image {
        id: fakebackground
        anchors.fill: parent
        anchors.margins: skin.bordersize
        fillMode: Image.PreserveAspectCrop
        source: "qrc:///qml/Skins/"+name+"/SynNext.jpg"

    }

    Rectangle{
        id: backgroundSelectionMark
        anchors.fill: parent
        color: "transparent"
        border.width: skin.skinpreviewbackgroundselectionmarkwidth//skin background selection Mark width
        border.color: "transparent"
        z: 50000
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            rectangle6.skinSelected();
        }        
        onHoveredChanged: {
            if(containsMouse == true){
                backgroundSelectionMark.border.color = skin.skinpreviewbackgroundselectionmarkcolor //skin background selection Mark color
            } else {
                backgroundSelectionMark.border.color = "transparent"
            }
        }
    }
}
