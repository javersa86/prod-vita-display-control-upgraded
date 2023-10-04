import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Styles"

Rectangle {
    id: control
    property int value
    width: 80
    height: 80
    color: mouseArea.pressed ? Style.primary_light_selected : Style.transparent
    border.color: Style.primary_light
    border.width: 4
    radius: width*0.5

    signal clicked();

    Text {
        id: value_text
        text: value
        font: Style.numberButtonFont
        color: Style.primary_light
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill:parent
        
        onClicked:{
            control.clicked()
        }
    }
}
