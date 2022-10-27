import QtQuick 2.4
import QtGraphicalEffects 1.0

ClickBoxWithTooltip {
    id : thistext
    property alias content:content
    property alias fillMode: content.fillMode
    property alias source: content.source

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
