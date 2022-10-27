import QtQuick 2.0
AutoElement{
    Text {
        y:thisae.wantedMargin
        id:block
        linkColor:"white"
        textFormat: Text.RichText
        wrapMode :Text.WordWrap
        width:repeaterList.width
        text: valueOfItem["html"]
        baseUrl: valueOfItem["baseUrl"]
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
