import QtQuick 2.4
import ".."

Rectangle {
    property alias text: content.text
    property int forcedWidth
    property int forcedHeight
    id: tooltip
    width: forcedWidth>0?forcedWidth:200
    height: forcedHeight>0?forcedHeight:50
    radius: skin.radius
    color:skin.tooltipcolor


    DText {
        id: content
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
    }
}
