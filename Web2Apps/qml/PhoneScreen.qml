import QtQuick 2.0

Item{
    id:phoneScreen
    property alias loadUrl:repeaterList.loadUrl

    property string struct:domParser.content["structure"]?domParser.content["structure"]:"Normal"
    property int structWidth:domParser.content["structureWidth"]?domParser.content["structureWidth"]:100
    property string pageToLoad:domParser.currentPage
    onPageToLoadChanged: {
        if(repeaterList.x==leftMenu.width){
            if(pageToLoad==repeaterList.wantedPage){
                return;
            }

            repeaterList2.wantedPage=domParser.currentPage
        } else {
            if(pageToLoad==repeaterList2.wantedPage){
                return;
            }
            repeaterList.wantedPage=domParser.currentPage
        }
        asyncMove.restart()
    }

    Timer{
       id:asyncMove
       running: false
       interval: 50
       onTriggered: {
           if(repeaterList.x==leftMenu.width){
               repeaterList.x=repeaterList.x-repeaterList.width/*-200*/
           } else {
               repeaterList.x=leftMenu.width
           }
       }
    }


    PhoneScreenZone{
        id:repeaterList
        //wantedContainer:
        Component.onCompleted: {
            wantedPage=domParser.currentPage
        }
        anchors.top: parent.top
        anchors.bottom: bottomMenu.top

        x:leftMenu.width
        width: parent.width-leftMenu.width
        Behavior on x{
            NumberAnimation{
                duration:400
            }
        }
    }
    PhoneScreenZone{
        id:repeaterList2
        anchors.top: parent.top
        anchors.bottom: bottomMenu.top
        x:repeaterList.x+repeaterList.width/*+200*/
        width: parent.width-leftMenu.width
    }





    Rectangle{
        id:leftMenu
        anchors.left:parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        border.width: 1

        color:skin.tabbedmenuboxcolor
        PhoneScreenZone{
            anchors.fill: leftMenu
            spacing: 5
            bgColor: skin.menuboxcolor
            wantedContainer:"Left"
        }
        width: phoneScreen.struct==="Left Menu"?structWidth:0
        /*Behavior on width {
            NumberAnimation{
                duration: 400
            }
        }*/
    }
    Rectangle{
        id:bottomMenu
        anchors.left:parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color:skin.tabbedmenuboxcolor
        border.width: 1

        PhoneScreenZone{
            anchors.fill: parent
            wantedContainer:"Bottom"
        }

        height: phoneScreen.struct==="Bottom Menu"?structWidth:0
       /* Behavior on height {
            NumberAnimation{
                duration: 400
            }
        }*/
    }



}



