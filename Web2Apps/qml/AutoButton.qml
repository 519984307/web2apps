import QtQuick 2.0
//import QtQuick.Controls 1.4
import "BasicElements"

AutoElement{
    id:thisae
    SButton{
        y:thisae.wantedMargin
        anchors.horizontalCenter: parent.horizontalCenter
        forcedWidth: thisae.width
        text:valueOfItem["html"]
        onClicked: {
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
            }
        }
    }

}
