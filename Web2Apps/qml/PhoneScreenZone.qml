import QtQuick 2.4


ListView{
    id:myZone
    property string wantedContainer:domParser.content["pages"][wantedPage]["container"]
    property string wantedPage:"p1"
    property string loadUrl:""
    property color bgColor:"#00000000"
    property bool currentlySelectedForAdd:(wantedContainer===domParser.currentContainer)

    property var pageModel:domParser.content["container"][wantedContainer];

    spacing: 15

    model:pageModel?pageModel["content"]:0

    header : Rectangle{
        height: 5
        color:"red"
    }

    Image {
        id: phoneBackground
        source: {
            if(pageModel){
                if(typeof pageModel["config"] !== 'undefined'){
                    if(typeof pageModel["config"]["background"]  !== 'undefined'){
                        return "image://ip/"+pageModel["config"]["background"];
                    }
                }
            }

            if (bgColor=="#00000000"){
                return skin.background;
            }
            return "";
        }
        visible: source!=""
        //cache:false
        anchors.fill:parent
        fillMode: Image.PreserveAspectCrop
        z:-1
    }
    Rectangle{
        anchors.fill: parent
        color:bgColor
        z:-2
    }

    onCurrentlySelectedForAddChanged: {
        if(currentlySelectedForAdd){
            currentContainerHighlight.opacity=1
            hideCurrentWindow.restart()

        } else {
            currentContainerHighlight.opacity=0
        }
    }

    Timer{
        id:hideCurrentWindow
        running: false
        interval: 400
        onTriggered: {
            currentContainerHighlight.opacity=0
        }
    }

    function getPageFromUrl(_url){
        console.log("Somebody asked PhoneScreen.qml to load " + _url)
        domParser.getPageFromUrl(_url);
    }

    Rectangle{
        id:currentContainerHighlight
        visible:domParser.fullEditor
        anchors.fill: parent
        border.color: "red"
        border.width: 2
        color:"transparent"
        opacity: 0
        Behavior on opacity {
            NumberAnimation{
                duration:400
            }
        }
    }


    //headerPositioning: ListView.OverlayHeader
    /* MouseArea{
            propagateComposedEvents: true
            property string loadUrl:""
            height: myZone.height
            width: myZone.width
            z:1

            onClicked: {
                domParser.currentContainer=wantedPage
                mouse.accepted = false
            }
        }*/

    delegate: Loader {
        id:container
        z:2
        width: myZone.width-4
        x:2
        source:{
            //return "qrc:///qml/AutoHtmlEditor.qml";
            var contentType=containeritem["content"]["type"];
            if(contentType==="header"){
                return "qrc:///qml/AutoFormHeader.qml";
            } else if(contentType==="form"){
                return "qrc:///qml/AutoFormItem.qml";
            } else if(contentType==="block"){
                return "qrc:///qml/AutoBlockItem.qml";
            } else if(contentType==="button"){
                return "qrc:///qml/AutoButton.qml";
            }else if(contentType==="image"){
                return "qrc:///qml/AutoImageItem.qml";
            }else if(contentType==="html"){
                if(domParser.fullEditor && (wantedPage==domParser.currentContainer)){
                    return "qrc:///qml/AutoHtmlEditor.qml";
                } else {
                    return "qrc:///qml/AutoBlockItem.qml";
                }
            }
        }
        property var containeritem:modelData //domParser.getElement(index)
        property var valueOfItem:containeritem["content"]
        property var paramsOfItem:containeritem["param"]
        property var otherValue:containeritem["ov"]
        property string container:wantedContainer
        property var phoneScreen:repeaterList
    }
}
