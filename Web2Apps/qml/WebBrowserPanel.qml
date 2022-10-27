import QtQuick 2.0

Rectangle{

    id:browserpanel
    property alias storeToApp:addToInterface.checked
    color:"#333333"
    height: 55

    ButtonW2A{
        id:backButton
        iconSource:  "qrc:/images/Icons/Back.svg"
        anchors.left: parent.left
        anchors.verticalCenter: textinput2.verticalCenter
        width: 40
        specialOffset: -10
    }
    ButtonW2A {
        id:nextButton
        iconSource:  "qrc:/images/Icons/Forward.svg"

        anchors.verticalCenter: textinput2.verticalCenter
        anchors.left: backButton.right
        specialOffset: -10
        width: 40
    }
    TextFieldW2A{
        id:textinput2
        anchors.left: nextButton.right
        anchors.top:parent.top

        anchors.topMargin: 20
        placeholderText: "Import from website"
        anchors.right: buttonW2Ago.left
        text:leftBrowser.url
        onAccepted: {
            if(text.indexOf("http")<0){
                leftBrowser.url="http://"+text
            } else {
                leftBrowser.url=text
            }
        }
    }
    ButtonW2A{
        id:buttonW2Ago
        anchors.right: addToInterface.left
        anchors.margins: 10
        anchors.verticalCenter: textinput2.verticalCenter
        iconSource: "qrc:/images/Icons/Project Reset.svg"
        specialOffset: -10
        width: 40
    }

    ButtonW2A{
        id:addToInterface
        anchors.right: parent.right
        anchors.verticalCenter: buttonW2Ago.verticalCenter
        iconSource: checked?"qrc:/images/Icons/Add Elem2Interface4.svg":"qrc:/images/Icons/Not Add Elem2Interface4.svg"
        anchors.margins: 10
        //textEl.font.strikeout:!checked
        property bool checked:true
        text:checked?"Click adds to app":"Click navigates"

        onClicked: checked=!checked
    }
}
