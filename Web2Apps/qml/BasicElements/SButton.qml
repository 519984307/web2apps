import QtQuick 2.4
import ".."

Rectangle {
    id: button

    property string text
    property string temporaryError
    property string displayText:text


    property int forcedWidth:0
    property int forcedHeight:0
    property alias font:content.font
    property alias fontcolor:content.color
    property string action
    property var args
    property int forgetretval:0

    property alias buttonImageSource : buttonImage.source
    property alias overlayColor : buttonImage.overlayColor
    property alias overlayColorOnHover : buttonImage.overlayColorOnHover
    property color clickedcolor1: skin.clickbuttongradient1
    property color clickedcolor2: skin.clickbuttongradient2

    //set different colors (e.g. for exit-, confirm buttons)
    property color buttongradient1 : skin.buttongradient1
    property color buttongradient2 : skin.buttongradient2
    property color clickbuttongradient1 : skin.clickbuttongradient1
    property color clickbuttongradient2 : skin.clickbuttongradient2
    property color buttonhovergradient1 : skin.buttonhovergradient1
    property color buttonhovergradient2 : skin.buttonhovergradient2
    property color warningcolor : skin.warningcolor

    width: forcedWidth > 0
           ? forcedWidth
           : content.paintedWidth + s.r25 + buttonImage.content.width
    height: forcedHeight > 0
            ? forcedHeight
            :(width<30?width:content.paintedHeight + s.r20)

    radius: skin.radius

    clip: true


    Keys.onReturnPressed:
    {
        startAction()
    }
    Keys.onEnterPressed:
    {
        startAction()
    }

    state:"normal"
    states:[
        State{
            name:"normal"
            PropertyChanges {
                target: gradientstop1
                color: buttongradient1
            }
            PropertyChanges {
                target: gradientstop2
                color: buttongradient2
            }
            PropertyChanges {
                target: button
                displayText: text
            }
        },
        State{
            name:"clicked"
            PropertyChanges {
                target: gradientstop1
                color: clickbuttongradient1
            }
            PropertyChanges {
                target: gradientstop2
                color: clickbuttongradient2
            }
        },
        State{
            name:"hovered"
            PropertyChanges {
                target: gradientstop1
                color: buttonhovergradient1
            }
            PropertyChanges {
                target:gradientstop2
                color: buttonhovergradient2
            }
        }
        ,
        State{
            name:"error"
            PropertyChanges {
                target: gradientstop1
                color: skin.warningcolor
            }
            PropertyChanges {
                target: gradientstop2
                color: skin.warningcolor
            }
            PropertyChanges {
                target: button
                displayText: temporaryError
            }
        }
    ]



    onFocusChanged: {
        if (focus)
            button.state="hovered"
        else
            button.state="normal"
    }

    onTemporaryErrorChanged: {
        if (temporaryError != ""){
            button.state="error"
            errorTimer.restart();
        }
    }
    Timer {
        id: startActionTimer;
        interval: 10;
        running: false;
        repeat: false;
        onTriggered: {
            clicked()
        }
    }
    function startAction(){
        startActionTimer.running=true
    }

    Timer {
        id: errorTimer;
        interval: 3000;
        running: false;
        repeat: false;
        onTriggered: {
            button.state="normal"
            temporaryError = ""
            stop();
        }
    }
    signal clicked()
    onClicked: {

        if(action!=""){
            args["existingRetVal"]=connector.perform(action,args);
            if(forgetretval==1){
                args["existingRetVal"]=0
            }
        }
    }

    gradient: Gradient {
        GradientStop {
            id: gradientstop1
            position: 0
            Behavior on color {
                ColorAnimation  { duration: 500 }
            }
        }

        GradientStop {
            id: gradientstop2
            position: 1
            Behavior on color {
                ColorAnimation  { duration: 500 }
            }
        }
    }

    HighlightingImage{
        id: buttonImage
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        source:""
    }

    Text {
        id: content
        width: forcedWidth>0? forcedWidth-20:s.r85
        height: forcedHeight>0? forcedHeight-30:35
        wrapMode: Text.Wrap
        text: displayText
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: buttonImage.content.source != ""? undefined: parent.horizontalCenter
            left: buttonImage.content.source != ""? buttonImage.left : undefined
            leftMargin: s.r15
        }
        verticalAlignment:  Text.AlignVCenter
        horizontalAlignment: buttonImage.content.source != ""? undefined: Text.AlignHCenter
        color: skin.buttontextcolor
    }
    MouseArea {
        id: mousearea1
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            if (button.state != "error")
                button.state="hovered"
        }
        onExited: {
            if (button.state != "error")
                button.state="normal"
        }
        onPressed: {
            if (button.state != "error")
                button.state="clicked"
        }
        onReleased: {
            if (button.state != "error")
                button.state="normal"
        }
        onClicked: {
            if (button.state != "error")
                startAction()
        }

    }

    transitions: [
        Transition {
            ColorAnimation {
                duration: 100
            }
        }
    ]

    Behavior on width {
        NumberAnimation{
            duration: 100
        }
    }

    Behavior on height {
        NumberAnimation{
            duration: 100
        }
    }
}
