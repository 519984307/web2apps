import QtQuick 2.4
import QtGraphicalEffects 1.0
import ".."

Rectangle {
    id: button

    property string temporaryError
    property int forcedWidth
    property int forcedHeight
    property string action
    property var args
    property int forgetretval:0
    property color iconColor: skin.standaloneiconcolor
    property color iconHoverColor: skin.standaloneiconcolorhighlight
    property alias iconSource: icon.source
    property alias iconwidth: icon.sourceSize.width
    property bool checked:false

    property string text: button.text /* TODO : Not used for now ! */

    width: forcedWidth > 0
           ? forcedWidth
           : s.r25
    height: forcedHeight > 0
            ? forcedHeight
            : s.r20
    radius: skin.radius
    color:"transparent"

    Keys.onReturnPressed:
    {
        startAction()
    }
    Keys.onEnterPressed:
    {
        startAction()
    }

    state:temporaryError != ""?"error":(
                                    (checked||mousearea1.containsPress)?"clicked":(
                   mousearea1.containsMouse?"hovered":"normal"))
    states:[
        State{
            name:"normal"
            PropertyChanges {
                target: iconColorOverlay
                color: iconColor
            }
        },
        State{
            name:"clicked"
            PropertyChanges {
                target: iconColorOverlay
                color: iconHoverColor
            }
        },
        State{
            name:"hovered"
            PropertyChanges {
                target: iconColorOverlay
                color: iconHoverColor
            }
        }
        ,
        State{
            name:"error"
            PropertyChanges {
                target: iconColorOverlay
                color: skin.warningcolor
            }
        }
    ]



    /*onFocusChanged: {
        if (focus)
            button.state="hovered"
        else
            button.state="normal"
    }*/

    onTemporaryErrorChanged: {
        if (temporaryError != ""){
            errorTimer.running=true
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
            temporaryError= ""
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


    Image {
        id: icon
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        source: ""
        sourceSize.width: s.r20
        visible: false
    }

    ColorOverlay {
        id: iconColorOverlay
        anchors.fill: icon
        source: icon
        color: "#000000"
    }

    MouseArea {
        id: mousearea1
        anchors.fill: parent
        hoverEnabled: true
        onClicked: startAction()

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
