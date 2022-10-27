import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
AutoElement{
    Column{
        y:thisae.wantedMargin
        id:textinput
        spacing: 5
        property string link:otherValue["action"]
        property string postOrGet:otherValue["method"]!="POST"?"GET":"POST"

        function submitRequest(){
            var goalUrl
            if(link.indexOf("http")<0){
                var wantedUrl=""
                wantedUrl=phoneScreen.url
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
            console.log("sending method" + postOrGet)
            if(postOrGet=="GET"){
                goalUrl=goalUrl+"?"
                for(var i=0;i<valueOfItem.length;i++){
                    goalUrl=goalUrl+valueOfItem[i]["name"]+"="+textinput.data[i].text
                    if((i+1)<(valueOfItem.length)){
                        goalUrl=goalUrl+"&"
                    }
                }
            }
            console.log("Opening for form" + goalUrl)
            phoneScreen.url=goalUrl

        }

        Repeater{
            id:formrepeater
            model:valueOfItem.length


            delegate: Item {
                height: submitButton.visible||inputfield.visible?20:0
                property string text:valueOfItem[index]["type"]==="submit"?submitButton.text:inputfield.text
                width: 10
                Button{
                    id:submitButton
                    visible: valueOfItem[index]["type"]==="submit" && valueOfItem[index]["content"]!==""
                    text:valueOfItem[index]["content"]
                    onClicked: {
                        console.log("Sending " + formrepeater.postOrGet +" "+formrepeater.link);
                        textinput.submitRequest()

                    }
                }
                TextField{
                    id:inputfield
                    visible: valueOfItem[index]["type"]=="text"
                    text: valueOfItem[index]["content"]
                    onAccepted:                  {
                        console.log("Sending " + formrepeater.postOrGet +" "+formrepeater.link);
                        textinput.submitRequest()
                    }
                }
                /*TextField{

                style: TextFieldStyle {
                    textColor: "red"
                }
                visible: (!inputfield.visible && !submitButton.visible)&&
                         (valueOfItem[index]["content"]!=="") &&
                         (valueOfItem[index]["type"]!=="hidden")
                text: valueOfItem[index]["type"] + ":"+ valueOfItem[index]["name"]
                      + " "+ valueOfItem[index]["content"]

            }*/
            }
        }
    }
}
