import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id: root
    width: dialDisplayBox.width + .4 * height
    height: 300
    property int diameter: height
    color: Style.transparent
    property int value
    property int min
    property int max
    property string unit
    property int minOn
    property bool selected
    property int step
    signal settingConfirmed()
    signal clicked()

    Rectangle
    {
        id: dialDisplayBox
        height: root.height * 1.1
        width: height
        color: Style.transparent


        RadialGradient {
            visible: root.selected
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.4; color: Style.general_set_display }
                GradientStop { position: .5; color: Style.transparent }
            }
        }


        Rectangle{
            id: dialDisplay

            height: root.diameter
            width: root.diameter
            radius: .5 * root.diameter
            border.width: root.selected ? width / 50 : 3
            border.color: root.selected ? Style.general_set_display : Style.primary_light
            color: Style.primary_dark
            anchors.centerIn:  parent

            Text {
                    id: valueDisplay
                text: value
                font: Style.measuredFont
                color: Style.general_set_display
                anchors.centerIn: parent
            }

            Text {
                id: unitDisplay
                text: qsTr(unit)
                font: Style.numberButtonFont
                color: Style.general_set_display
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height * .72
            }
        }

    }

    VerticalIndicator
    {
        id: indicator
        y: dialDisplay.y * .6
        height: dialDisplay.height * .76
        width: root.width / 9.8
        anchors.right: parent.right
        value: root.value
        min: root.min
        max: root.max
        minOn: root.minOn
    }

    MouseArea
    {
        anchors.fill:parent
        pressAndHoldInterval: 225

        onPressAndHold:
        {
            timer.start()
        }
    }

    Timer {
        id: timer
        repeat: false
        interval: 50

        onTriggered:
        {
            root.clicked()
            timer.stop()
        }
    }

    Connections
    {
        target: knob
        enabled: root.selected
        onEncoderIncrement:
        {
                var currStep = Math.round(root.value / root.step) * root.step
                if (root.value < root.minOn && encoderVal > 0)
                {
                    root.value = root.minOn;
                }
                else if(root.value <= minOn && encoderVal < 0)
                {
                    root.value = root.min;
                }

                else if (currStep + encoderVal * root.step <= root.max && currStep + encoderVal * root.step >= root.minOn)
                {
                    root.value = currStep + encoderVal * root.step;
                }
        }
        onButtonPush:
        {
                root.settingConfirmed()
        }
    }
}
