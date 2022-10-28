import QtQuick 2.0

import QtQuick.Dialogs 1.2

Rectangle{


    width:150
    color:"#4d4d4d"
    /* Text{
        id:toolsText
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.top:parent.top
        anchors.topMargin: 20
        text:"Tools"
        font.bold: true
        font.pointSize: 10
    }*/
    Column{
        id:thiscol
        anchors.left:parent.left
        anchors.top: parent.top //toolsText.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.topMargin: 10

        ButtonW2A{
            text: "Add new"
            color:"#333333"
            iconSource:"qrc:/images/Icons/Edit Add.svg"

        }

        ButtonW2A{
            text:"Button/Link"
            iconSource: "qrc:/images/Icons/Edit Button.svg"
            onClicked: {
                domParser.addItem("button","Click me!");
            }

        }
        ButtonW2A{
            text:"Image"
            iconSource:"qrc:/images/Icons/Edit Image.svg"
            onClicked: {
                domParser.addItem("image","qrc:/images/html-images/image.svg");
            }
        }
        ButtonW2A{
            text:"Text"
            iconSource:"qrc:/images/Icons/Edit TXT.svg"
            onClicked: {
                domParser.addItem("html", "");
            }

        }

        ButtonW2A {
            text: "Current page"

            color:"#333333"
            iconSource:"qrc:/images/Iconpack Minimal View 2.svg"
        }
        /*
        TextFieldW2A{

            placeholderText: "Element url"
            //iconSource:"qrc:/images/Icons/Select search url.svg"
            text:""//domParser.content[domParser.currentPage][currentPhoneScreen.lastSelected]["content"]["linkToUrl"]
        }*/
/*
        ButtonW2A{
            id: textSmaller

            iconSource:"qrc:/images/Icons/Select decrease.svg"
            text: "Decrease size"
            onClicked: {
                var updatedItems=0;
                for(var i=0;i<currentPhoneScreen.items.length;i++){
                    if(currentPhoneScreen.items[i].item != undefined){
                        if(currentPhoneScreen.items[i].item.selected){
                            updatedItems++;
                            domParser.updateElementParam(i,
                                                         "textSizeOffset",
                                                         currentPhoneScreen.items[i].item.textsizeoffset-1)
                            currentPhoneScreen.items[i].item.textsizeoffset=currentPhoneScreen.items[i].item.textsizeoffset-1;

                        }
                    }
                }
               // if(updatedItems==0){
               //     textsize--;
               // }
            }
        }
        ButtonW2A {
            id: textBigger
            text: "Increase size"
            iconSource:"qrc:/images/Icons/Select increase.svg"

            onClicked: {
                var updatedItems=0;
                for(var i=0;i<currentPhoneScreen.items.length;i++){
                    if(currentPhoneScreen.items[i].item != undefined){
                        if(currentPhoneScreen.items[i].item.selected){
                            updatedItems++;
                            domParser.updateElementParam(i,
                                                         "textSizeOffset",
                                                         currentPhoneScreen.items[i].item.textsizeoffset+1)
                            currentPhoneScreen.items[i].item.textsizeoffset=currentPhoneScreen.items[i].item.textsizeoffset+1;
                        }
                    }
                }
                //if(updatedItems==0){
                //    textsize++;
                //}
            }
        }*/
        ButtonW2A {
            id: backGround
            text: "Background"
            iconSource:"qrc:/images/Icons/Global background.svg"

            onClicked: {
                fileDialog.open()
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                // folder: shortcuts.home
                onAccepted: {
                    //phoneBackground.source=fileDialog.fileUrl
                    //domParser.uploadFile(fileDialog.fileUrl,"bg.jpg");


                    //console.log(backgrounds)
                    domParser.updatePageConfig(domParser.currentContainer,
                                "background",
                                          fileDialog.fileUrl)
                    //console.log("You chose: " + fileDialog.fileUrls)
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
        }
        ButtonW2A {
            id: links
            text: "Link properties"
            iconSource:"qrc:/images/Icons/Select.svg"

            onClicked: {
                pageSettings.expand=!pageSettings.expand
            }
        }

        ButtonW2A {
            id: colors
            text: "Change color"
            iconSource:"qrc:/images/Icons/Select color.svg"

            onClicked: {
                colorpick.expand=!colorpick.expand
            }
        }

        ButtonW2A {
            text: "Global design"
            color:"#333333"
            iconSource:"qrc:/images/Icons/Global.svg"
        }


        ButtonW2A {
            id: arrangement
            text: "Structure"
            iconSource:"qrc:/images/Icons/Global structure.svg"


            onClicked: {
                structure.expand=!structure.expand
            }
        }
        ButtonW2A {
            id: skinButtonW2A
            text: "Skin"
            iconSource:"qrc:/images/Icons/Global color.svg"

            onClicked: {
                templates.expand=!templates.expand
            }
        }
        ButtonW2A {
            text: "Project"
            color:"#333333"
            iconSource:"qrc:/images/Icons/Project.svg"
        }
        ButtonW2A{
            id:exportButtonW2A
            height: 50

            text: "Generate App!"
            iconSource:"qrc:/images/Icons/Project Generate.svg"
            color:"#ec2a48"
            onClicked: {
                domParser.storeConfig()
            }
        }
        ButtonW2A{
            id:newButtonW2A

            text: "Reset project"
            iconSource:"qrc:/images/Icons/Project Reset.svg"

            onClicked: {
                domParser.resetProject()
            }
        }
        ButtonW2A{
            id:previewButton

            text: "Preview mobile"
            color:"#333333"
            iconSource:"qrc:/images/Icons/Select search url.svg"

            onClicked: {
                domParser.resetProject()
            }
        }
        Row{
            ButtonW2A {
                iconSource:  "qrc:/images/Icons/Apple.svg"
                width: 50
            }
            ButtonW2A {
                iconSource:"qrc:/images/Icons/Windows.svg"
                width: 50

            }
            ButtonW2A {
                iconSource:"qrc:/images/Icons/Android.svg"
                width: 50

            }
        }

    }
    Image {
        id: logoImage
        fillMode: Image.PreserveAspectFit
        anchors.margins: 20

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom:parent.bottom

        source: "qrc:///logo.png"
    }
}
