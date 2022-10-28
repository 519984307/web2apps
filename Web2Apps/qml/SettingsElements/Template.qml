import QtQuick 2.4
import "../Boxes"
import "../Skins/skins.js" as MyJavascriptSkins


Rectangle {
    property var skinlist: MyJavascriptSkins
    id: templateSetting

    width: expand?s.r320:0
    height: parent.height
    property bool expand:false

    color: "transparent"
    GridView{
        id: column1
        anchors{
            top: parent.top
            topMargin: 20
            bottom: parent.bottom
            bottomMargin: s.m15
            right: parent.right
            rightMargin: 10
            left: parent.left
            leftMargin: 10

        }
        clip: true
        cellHeight:s.r140+s.r10
        cellWidth:s.r280+s.r10
        width: s.r280+s.r5

        model: ListModel {
            // Here is the list where the skins will be added
            id:thismodel

        }
        Component.onCompleted: {
          skinlist.addSkins(thismodel);
        }
        delegate:
            SkinPreview {
            name:m_name
            width: s.r280
            height: s.r140
            onSkinSelected: {
                skinlist.loadSkin(m_name);
               // settings.setSetting("Skin",m_name)
                expand = 0
            }

            Rectangle{
                id: nameBar
                anchors.bottom: parent.bottom
                width: parent.width
                height: s.r25
                color: skin.skinpreviewnamebarcolor
                opacity: skin.skinpreviewnamebaropacity

                Text{
                    id: nameBarText
                    font.pixelSize: skin.titlefontsize
                    color: skin.skinpreviewnamebarfontcolor
                    text: m_name
                    anchors.centerIn: parent
                }
            }
        }
    }

}

