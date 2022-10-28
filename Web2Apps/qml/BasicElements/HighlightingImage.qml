import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id : thistext
    property alias content:content
    property alias fillMode: content.fillMode
    property alias source: content.source

    property alias tooltip:tooltipid.text
    property string action
    property var args
    property int forgetretval:0
    property color selectedcolor:skin.selectcolor
    property real selectopacity:0.2
    property color overlayColor: "#000000"
    property color overlayColorOnHover: "#000000"
    property bool enableHelp: false
    property alias imageSize: content.sourceSize.width
    property color helpBoxBackgroundColor: "transparent"
//    signal signalId(int id)

    Image {
        id: content
        visible: false
        anchors.centerIn: parent
        sourceSize.width: s.icon
        fillMode: Image.PreserveAspectFit
    }

    ColorOverlay {
        id: contentOverlay
        source: content
        anchors.fill: content
        color: overlayColor
        z: 1
        Behavior on color {
            ColorAnimation{duration: 400}
        }
    }

    Timer {
        id:click
        interval: 800; running: false; repeat: false
        onTriggered: {
                thistext.state='Default'
        }
    }
    Rectangle {
        id: backgroundtext
        anchors.fill: parent
        opacity: 0
        radius: skin.radius
        color: selectedcolor
        Behavior on opacity {
            NumberAnimation{duration: 200}
        }
         Behavior on color {
             ColorAnimation{duration: 200}
         }
    }
    signal clicked()
    onClicked: {
        if(action!=""){
            var popup = connector.perform(action, args);
            if (forgetretval == 1) args["existingRetVal"] = 0;
            else args["existingRetVal"] = popup;
            //if (args["popupVar"] != "") {
            //    // popup variable only used for calendar popup for now
            //    popup.selectedDate = args["popupVar"];
            //}
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

    MouseArea {
        id: mousearea1
        hoverEnabled : true
        anchors.fill: parent
        onEntered: {
            tutorialTimer.start()
            if(thistext.state!='Clicked'){
                thistext.state='MouseOver'
            }
            if(tooltip!=""){tooltiptimer.running=true}
        }
        onExited: {
            tutorialTimer.stop()
            if(thistext.state!='Clicked'){
                thistext.state='Default'
            }
            tooltiptimer.running=false
            tooltiptimer.interval=500
            tooltipid.opacity=0
        }
        onClicked: {
            thistext.state='Clicked'
            click.interval=800
            click.restart()
            startAction()
        }
    }

    Timer {
        id:tooltiptimer
        interval: 500; running: false; repeat: false
        onTriggered: {
            interval=500
            tooltipid.opacity=1
            tooltipid.parent = connector.getMainScreen()
            tooltipid.x = thistext.mapToItem(connector.getMainScreen(),0,0).x+thistext.width+3
            tooltipid.y = thistext.mapToItem(connector.getMainScreen(),0,0).y-15
            tooltipid.z=10000
        }
    }
    Tooltip{
        id:tooltipid
        opacity:0
        z:999
    }

    states: [
        State {
            name: "MouseOver"
            PropertyChanges {
                target: backgroundtext
                opacity: selectopacity
            }
            PropertyChanges {
                target: contentOverlay
                color: overlayColorOnHover
            }
        },
        State {
            name: "Clicked"
            PropertyChanges {
                target: backgroundtext
                color: skin.selectcolor
            }
            PropertyChanges {
                target: backgroundtext
                opacity: selectopacity
            }
        },
        State {
            name: "Default"
            PropertyChanges {
                target: backgroundtext
                color: selectedcolor
            }
            PropertyChanges {
                target: backgroundtext
                opacity: 0
            }
            PropertyChanges {
                target: contentOverlay
                color: overlayColor
            }
        }
    ]
}
