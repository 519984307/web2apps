import QtQuick 2.6
FocusScope {

  //  property var text
    property alias text: text_input1.text
    property alias placeholdertext:labelElement.text
    property alias cursorVisible:text_input1.cursorVisible
    property bool showBig:!text_input1.cursorVisible && text_input1.text==""
    property bool editable:true
    property bool invertColors:false
    property alias selectionStart: text_input1.selectionStart
    property alias selectionEnd: text_input1.selectionEnd
    property alias cursorPosition: text_input1.cursorPosition

    property bool sendChangesWhileTyping:false
    property bool sendChangesOnFocusLoss:true
    property bool dataChanged:true

   // property int sqlid:0

    property string textloaded
    onTextloadedChanged:
    {
        if(myloader.item){
            myloader.item.mydoc.loadText(textloaded);
        } else {
            text=textloaded;
        }
    }

    signal accepted()
    function plainText(){
        if(myloader.item){
            var thistext=myloader.item.mydoc.plainText()
          //  console.log("found text!" + thistext);
            return thistext;
        }
        //console.log("no documenthandler :-(")
        //Warning: QML getText function is buggy and replaces \n with ?
        // Still, when no documenthandler is present, this means that
        //we are not curretnyl editing the text: Should be sufficient.
        return text_input1.getText(0,text_input1.length)
    }
    width: parent.width
    height: (text_input1.implicitHeight>0?
                 text_input1.implicitHeight+s.r15:
                 s.r30)+menubar.height

    Rectangle {
        id:inputbox
        color:!editable?skin.lockedinputcolor:(invertColors?skin.tabbedmenuboxcolor:skin.inputboxbackground)
        anchors.fill: parent
        radius: skin.radius
        opacity:text==""?0.5:0
        border.width: skin.bordersize
        border.color: text_input1.activeFocus?skin.selectcolor:skin.bordercolor
        Behavior on opacity {
            NumberAnimation{
                duration:400
            }
        }
    }

    Item{
        id:menubar
        height: myloader.source!=""?s.r30:0
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: s.r5
        clip: true
        Loader{
            id:myloader
            source: text_input1.cursorVisible&&editable?"HtmlEditorBar.qml":""
            anchors.fill: parent
            property var textEditor:text_input1
        }
        Behavior on height {
            NumberAnimation{
                duration: 300
            }
        }
    }
    Timer {
        id: dataAcceptedTimer;
        interval: 1;
        running: false;
        repeat: false;
        onTriggered: {
            dataAcceptedBigTimer.stop()
            dataAcceptedBigTimer.interval=600
            //console.log("dataAcceptedTimer!")
            accepted()
        }
    }
    Timer {
        id: dataAcceptedBigTimer;
        interval: 600;
        running: false;
        repeat: false;
        onTriggered: {

            //console.log("dataAcceptedBigTimer!")
            accepted()
        }
    }

    TextEdit {
        id: text_input1
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: menubar.bottom

        anchors.margins: s.r5
        //font.family:skin.usedfont
        //font.pixelSize: skin.textfontsize
        readOnly: !editable
        selectByMouse: true
        selectionColor: skin.selectcolor
        wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
        focus:true
        textFormat: TextEdit.AutoText
        width:s.r85
        onTextChanged: {
            //console.log("onTextChanged!")
            if(cursorVisible){
                if(textloaded != text){
                    if(sendChangesWhileTyping){
                        dataAcceptedBigTimer.interval=600
                        dataAcceptedBigTimer.restart();
                    } else {
                        dataChanged=true
                    }
                }
            }
        }

        Component.onDestruction: {
            //console.log("onDestruction");
            if((cursorVisible==1)&&(sendChangesOnFocusLoss)){
                dataAcceptedTimer.restart();
            }
        }
        onCursorVisibleChanged:
        {
            //console.log("onCursorVisibleChanged" + cursorVisible);
            if((!cursorVisible)&&(sendChangesOnFocusLoss)){
                console.log("cursorVisible");
                dataAcceptedTimer.running=true;
            }
        }
    }
    function cut() {
        text_input1.cut();
    }
    function copy() {
        text_input1.copy();
    }
    function paste() {
        text_input1.paste();
    }
    DropArea {
        id: dropArea;
        anchors.fill: parent;
        onEntered: {
            inputbox.color = "green";
            drag.accept (Qt.CopyAction);
            // console.log("onEntered");
        }
        onDropped: {
            inputbox.color = "grey";
            parent.text = drag.source.text
            // console.log ("onDropped" + drag.source.text);
        }
        onExited: {
            inputbox.color = "white";
            //  console.log ("onExited");
        }
    }
    DText {
        id: labelElement
        anchors {
            left: inputbox.left
            verticalCenter: inputbox.verticalCenter
            margins: 3
        }
        visible:showBig
        color: skin.inputboxtextcolor
    }
    DText{
        id: labelElement2

        visible:!showBig
        anchors.right: inputbox.right
        anchors.top: inputbox.bottom
        text:labelElement.text
        horizontalAlignment: Text.AlignRight
        font.pixelSize: skin.textfontsize-3
        color: skin.inputboxsmalltextcolor
    }
}
