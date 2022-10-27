import QtQuick 2.0
import ".."

Rectangle {
    id: pageSetting

    width: expand?s.r320:0
    height: parent.height
    property bool expand:false
    clip: true
    color: "transparent"
    Column{
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
        Repeater{
            model:domParser.content["pages"][domParser.currentPage]["config"]["urls"]

            delegate: Column{
                width: s.r320
                ButtonW2A {
                    text: "Link to Page"
                    color:"#333333"
                    width: s.r300
                    iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
                }
                TextFieldW2A{
                    width: s.r300
                    text:modelData
                    onAccepted: {
                        var urlList=domParser.content["pages"][domParser.currentPage]["config"]["urls"]
                        urlList[index]=text
                        domParser.updatePageConfig(domParser.currentPage,"urls",urlList)
                    }
                }
            }
        }
    }
}
