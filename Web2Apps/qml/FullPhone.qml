import QtQuick 2.0

Rectangle{
    id:phonePanel
    color:"#4d4d4d"
    width: iphoneLogo.width



    property int screenTopX:44/(123+1013+157)*iphoneLogo.height
    property int screenTopY:123/(123+1013+157)*iphoneLogo.height
    property int screenWidth: 570 /(123+1013+157)*iphoneLogo.height
    property int screenHeigth:1013/(123+1013+157)*iphoneLogo.height


    Image{
        anchors.right: iphoneLogo.right
        anchors.rightMargin:44/(123+1013+157)*iphoneLogo.height
        anchors.top:iphoneLogo.top
        anchors.topMargin: 123/(123+1013+157)*iphoneLogo.height
        height: 1013/(123+1013+157)*iphoneLogo.height
        width: 570 /(123+1013+157)*iphoneLogo.height
        source:"qrc:///appbackground.jpg"
        fillMode:Image.PreserveAspectCrop
        //color:"#f4f4f4"
    }
    Image {
        id: iphoneLogo
        source: "qrc:///iphone_PNG5743.png"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        //anchors.topMargin: 70
        fillMode: Image.PreserveAspectFit
    }

    ActivePageSelector{
        anchors.horizontalCenter: parent.horizontalCenter
        y:20
    }


    Image {
        id:homeButton
        source: "qrc:/images/Icons/Home Phone.svg"
        anchors.horizontalCenter: currentPhoneScreen.horizontalCenter
        anchors.top: currentPhoneScreen.bottom
        anchors.topMargin: 20
        width: 40
        fillMode: Image.PreserveAspectFit
        MouseArea{
            id:myma0
            anchors.fill: parent
            hoverEnabled: true
        }
    }
    Image {
        source: "qrc:/images/Icons/Menu Phone.svg"
        anchors.right:homeButton.left
        anchors.top: currentPhoneScreen.bottom
        anchors.topMargin: 20
        anchors.rightMargin: 50
        width: 40
        fillMode: Image.PreserveAspectFit
        MouseArea{
            id:myma1
            anchors.fill: parent
            hoverEnabled: true
        }
    }
    Image {
        source: "qrc:/images/Icons/Back Button Phone.svg"
        anchors.left:homeButton.right
        anchors.top: currentPhoneScreen.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 50
        width: 40
        fillMode: Image.PreserveAspectFit
        MouseArea{
            id:myma2
            anchors.fill: parent
            hoverEnabled: true
        }
    }
}
