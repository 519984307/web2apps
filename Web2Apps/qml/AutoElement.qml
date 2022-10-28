import QtQuick 2.0
MouseArea{

    id:mousea
    height: childrenRect.height


    property bool selected:false
    property int wantedMargin:activeHover?25:0
    property int activeHover:domParser.fullEditor&&
                             container==domParser.currentContainer&&
                             mousea.containsMouse

    Rectangle {
        id:highlightrectangle
        color:mousea.activeHover?"#55ffffff":"#00ffffff"
        anchors.fill: parent
        radius:5
        border.color: selected?"green":"transparent"
        border.width: 2
        Behavior on color{
            ColorAnimation {
                duration: 400
            }
        }
    }
    Behavior on wantedMargin {
        NumberAnimation {
            duration: 400
        }
    }


    z:1
    propagateComposedEvents: true
    acceptedButtons: Qt.NoButton
    hoverEnabled: true
    Loader{
        active:mousea.activeHover
        source:"AutoElementMenu.qml"
        height: wantedMargin
        width: parent.width
        x:0
        y:0
    }
}
