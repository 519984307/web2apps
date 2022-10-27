import QtQuick 2.0
import QtGraphicalEffects 1.0

AutoElement{
    id:thisae

    Image {
        y:thisae.wantedMargin
        id:imageitem
        source:{

            var address=valueOfItem["html"].toString();
            if(address.indexOf("qrc:/")==0){
                return address;

            }
            var endsWithGif = /gif$/;

            if(!endsWithGif.test(address)){
                return "image://ip/"+address
            }
            return "";
        }
        sourceSize.width: thisae.width
        asynchronous:true
        fillMode: Image.PreserveAspectFit
    }
    AnimatedImage {
        y:thisae.wantedMargin
        id:imageitemdif
        source:{
            var endsWithGif = /gif$/;
            var address=valueOfItem["html"].toString();
            if(endsWithGif.test(address)){
                return address
            }
            return "";
        }
        width: 100//thisae.width
        anchors.centerIn: parent
        asynchronous:true
        fillMode: Image.PreserveAspectFit
    }
    ColorOverlay {
        id: contentOverlay
        source: imageitem
        anchors.fill: imageitem
        color: "#80800000"
        opacity:ma.pressed?1:0
        z: 1
        Behavior on color {
            ColorAnimation{duration: 400}
        }
        Behavior on opacity{
            NumberAnimation{
                duration:100
            }
        }

    }


    MouseArea{
        id:ma
        anchors.fill: imageitem
        enabled: {
            if((typeof valueOfItem["linkToPage"] !== 'undefined')||
                    (typeof valueOfItem["linkToUrl"] !== 'undefined')||
                    (imageitem.source=="qrc:/images/html-images/image.svg")){
                return true;
            }
            return false;
        }
        onClicked: {
            console.log("image click")

            var link=valueOfItem["linkToUrl"]

            if(valueOfItem["linkToPage"]){
                domParser.currentPage=valueOfItem["linkToPage"];
            } else if(valueOfItem["linkToUrl"]){

                var goalUrl
                if(link.indexOf("http")<0){
                    var wantedUrl=""
                    wantedUrl=valueOfItem["baseUrl"]
                    wantedUrl=wantedUrl.toString()

                    if(link.indexOf("/")==0){
                        var pos=wantedUrl.indexOf("/",9);
                        console.log("POSitionnnn in" + wantedUrl + " " + pos)
                        goalUrl=wantedUrl.substring(0, pos)+link
                    } else {
                        var pos=wantedUrl.lastIndexOf("/");
                        console.log("POSitionnnn in" + wantedUrl + " " + pos)
                        goalUrl=wantedUrl.substring(0, pos)+"/"+link
                    }
                } else {
                    goalUrl=link
                }
                domParser.currentPage=domParser.getPageFromUrl(goalUrl)
                phoneScreen.loadUrl=goalUrl

            } else if (imageitem.source=="qrc:/images/html-images/image.svg"){
                myloader.active=true
                console.log("actoivate Popup!")
            }
        }
    }
    Loader{
        id:myloader
        active: false
        source: "FilePopup.qml"
        anchors.fill: parent
        property var indexOffset:index
    }
}

