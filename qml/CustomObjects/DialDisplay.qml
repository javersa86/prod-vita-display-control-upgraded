import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id: root
    property int value
    property string unit
    property int diameter
    height: diameter + .1 * diameter
    width: diameter + .1 * diameter
    signal clicked()

    MouseArea
    {
        anchors.fill:parent
        onClicked:
        {
            root.clicked()
        }
    }


    RadialGradient {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.4; color: Style.general_set_display }
            GradientStop { position: .5; color: Style.primary_dark }
        }
    }


    Rectangle{
        id: mainDisplay

        height: root.diameter
        width: root.diameter
        radius: .5 * root.diameter
        border.width: width / 50
        border.color: Style.general_set_display
        color: Style.primary_dark
        anchors.centerIn:  root

        Text {
            id: valueDisplay
            text: value
            font: Style.measuredFont
            color: Style.general_set_display
            anchors.centerIn: mainDisplay
        }

        Text {
            id: unitDisplay
            text: qsTr(unit)
            font: Style.numberButtonFont
            color: Style.general_set_display
            anchors.horizontalCenter: mainDisplay.horizontalCenter
            y: mainDisplay.height * .72
        }
    }
}
