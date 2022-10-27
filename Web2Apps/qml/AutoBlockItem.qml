import QtQuick 2.0
AutoElement{
    id:thisae
    Text {
        y:thisae.wantedMargin
        id:block
        linkColor:"white"
        //color: paramsOfItem["textColor"]?paramsOfItem["textColor"]:mywindow.textcolor
        textFormat: Text.RichText
        wrapMode :Text.WordWrap
        width:thisae.width
        text: valueOfItem["html"]
        onLinkActivated: {
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
            console.log(goalUrl + " link activated")
        }
        baseUrl: valueOfItem["baseUrl"]
    }
}
