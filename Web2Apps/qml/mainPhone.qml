import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtMultimedia 5.4

Window {
    visible: true
    width: 480
    height: 640
    id:mywindow
    property int textsize:12
    property color textcolor:"black"
    property var dataToDisplay:domParser.content
    onDataToDisplayChanged: {
        console.log("Received model changed from qml")
    }

    PhoneScreen{
        id:phoneScreen
        anchors.fill: parent
    }
}

