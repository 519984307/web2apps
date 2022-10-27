import QtQuick 2.0
import ".."
import "../BasicElements"

Rectangle {
    id: elementSetting

    width: expand?s.r320:0
    height: parent.height
    property bool expand:domParser.currentItem>-1
    clip: true
    color: "transparent"
    Column{
        y:0
        x:0
        width: s.r320
        ButtonW2A {
            text: "Link to URL"
            color:"#333333"
            width: s.r320
            iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
        }
        TextFieldW2A{
            placeholderText: "Link to URL"
            width: s.r320

            text:{
                if(domParser.currentItem==-1){
                    return "";
                } else {
                    return domParser.content["container"][domParser.currentContainer]["content"][domParser.currentItem]["content"]["linkToUrl"]

                }
            }
            onAccepted: {
                domParser.updateElementContent(domParser.currentItem,"linkToUrl",text)
            }

        }
        ButtonW2A {
            text: "Link to Page"
            color:"#333333"
            width: s.r320
            iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
        }
        TextFieldW2A{
            placeholderText: "Link to Page"
            width: s.r320

            text:{
                if(domParser.currentItem==-1){
                    return "";
                } else {
                    return domParser.content["container"][domParser.currentContainer]["content"][domParser.currentItem]["content"]["linkToPage"]
                }
            }
            onAccepted: {
                domParser.updateElementContent(domParser.currentItem,"linkToPage",text)
            }

        }
        ButtonW2A {
            text: "Content"
            color:"#333333"
            width: s.r320
            iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
        }
        TextFieldW2A{
            placeholderText: "Content"
            width: s.r320

            text:{
                if(domParser.currentItem==-1){
                    return "";
                } else {
                    var element = domParser.content["container"][domParser.currentContainer]["content"][domParser.currentItem]
                    return element["content"]["html"]
                }
            }
            onAccepted: {
                domParser.updateElementContent(domParser.currentItem,"html",text)
            }

        }
        Item
        {
            height: 30
            width: 30
        }
        ButtonW2A {
            text: "Store and close"
            color:"#333333"
            width: s.r320
            //iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
            onClicked: {
                domParser.currentItem=-1
            }
        }
    }
}
