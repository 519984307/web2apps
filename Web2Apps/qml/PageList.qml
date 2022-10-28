import QtQuick 2.0
import "BasicElements"

Item{

    id:pagesContainer
    width: 120

    Rectangle {

        anchors.top:parent.top
        anchors.right: parent.right
        anchors.left:parent.left
        anchors.bottom: parent.bottom
        color:"#f2f2f2"
        border.color: "#9f9f9f"
        border.width: 2
        ListView{
            id:pageList

            model:domParser.pageList
            anchors.fill:parent
            anchors.margins: 10
            spacing: 10
            delegate: Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80
                height: 120
                property bool selected:domParser.currentPage==index
                //checkable: true
                color:"white"
                border.color: selected?"red":"#9f9f9f"
                border.width: selected?2:1
                DText{
                    x:10
                    y:10
                    text:modelData
                }
                Image {
                    source: "qrc:/images/Icons/Code.svg"
                    anchors.top:parent.top
                    anchors.right: parent.right
                    width: 35
                    fillMode: Image.PreserveAspectFit
                }
                Image {
                    source: "qrc:/images/Icons/Delete.svg"
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right

                    width: 35
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        domParser.currentPage=modelData
                    }
                }
            }
        }
    }

    Image {
        source:  "qrc:/images/Icons/Add.svg"
        anchors.right: parent.right
        anchors.margins: -10
        //unpressedColor:"#4d4d4d"
        //anchors.left: parent.left
        anchors.bottom: parent.bottom
        //text:"Add page"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                domParser.pageAmount++
            }
        }
    }
}
