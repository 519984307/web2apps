import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


Row {
    spacing: 10
    visible:domParser.content["structure"]!="Normal"

    property int mainScreenChecked:domParser.currentContainer!="Left"
    onMainScreenCheckedChanged: {
        if(mainScreenChecked){
            mainScreen.checked=true
        }
    }

    RadioButton {
        text: "Menu"
        exclusiveGroup: tabPositionGroup
        onCheckedChanged: {
            if(checked){
                domParser.currentContainer="Left"
            }
        }
    }

    ExclusiveGroup { id: tabPositionGroup }
    RadioButton {
        id:mainScreen
        text: "Main Screen"
        exclusiveGroup: tabPositionGroup
        checked: true
        onCheckedChanged: {
            if(checked){
                domParser.currentContainer=domParser.currentPage
            }
        }
    }
}
