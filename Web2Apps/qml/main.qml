import QtQuick 2.3
import QtQuick.Window 2.2
import QtMultimedia 5.4
import "SettingsElements"

Window {
    visible: true
    id:mywindow
    property int textsize:12
    property color textcolor:"black"
    //property int pageAmount:domParser.pageAmount
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    color:"#fafafa"
    width: 1300
    height: 750

    PageList {
        id:pagesContainer
        anchors.top:parent.top
        anchors.right: toolsMenu.left
        anchors.bottom: parent.bottom
    }

    FullPhone{
        id:phonePanel
        color:"#4d4d4d"
        clip: true

        anchors.right: pagesContainer.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        PhoneScreen{
            clip:true
            id:currentPhoneScreen
            anchors.right: parent.right
            anchors.rightMargin:phonePanel.screenTopX
            anchors.top:parent.top
            anchors.topMargin: phonePanel.screenTopY
            height: phonePanel.screenHeigth
            width: phonePanel.screenWidth
            onLoadUrlChanged: {
                if(loadUrl!=""){
                    leftBrowser.url=loadUrl
                }
            }
        }

    }
    MenuTools{
        id: toolsColumn
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Rectangle{
        color:"#4d4d4d"
        id:toolsMenu
        anchors.right: toolsColumn.left
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        width: childrenRect.width
        clip:true
        Behavior on width {
            NumberAnimation  { duration: 400 }
        }

        ColorPicker{
            id:colorpick
            color:"#4d4d4d"
            anchors.centerIn: parent
            onCurrentColorChanged:{
                var updatedItems=0;
                for(var i=0;i<currentPhoneScreen.items.length;i++){
                    if(currentPhoneScreen.items[i].item != undefined){
                        if(currentPhoneScreen.items[i].item.selected){
                            updatedItems++;
                            domParser.updateElementParam(i,
                                                         "textColor",
                                                         currentColor)
                            currentPhoneScreen.items[i].item.textcolor=currentColor;
                        }
                    }
                }
            }
        }
        StructureChooser{
            id:structure
            anchors.centerIn: parent
            color:"#4d4d4d"
        }
        Template{
            id:templates
            anchors.centerIn: parent
            color:"#4d4d4d"
        }
        ElementSetting{
            id:elementsSettings
            anchors.centerIn: parent
            color:"#4d4d4d"
        }
        PageSettings{
            id:pageSettings
            anchors.centerIn: parent
            color:"#4d4d4d"
        }
    }


    WebBrowserPanel{
        id:browserPanel
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.right: phonePanel.left
    }

    WebBrowser{
        id:leftBrowser
        url:"http://www.heilbronn-marketing.de/"
        border.color: "black"
        border.width: 1
        anchors.top:browserPanel.bottom
        anchors.left: parent.left
        anchors.right: phonePanel.left
        anchors.bottom: parent.bottom
        storeToApp: browserPanel.storeToApp

        onUrlChanged: {
            //if(leftBrowser.url!=leftBrowser.url){
            //    leftBrowser.url=leftBrowser.url;
            // }
        }
    }
}
