import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle
{
    id:root
    property Item valueHolder
    color: Style.transparent
    property alias value: dial.value
    property StackView stack

    Component.onCompleted:
    {
        valueHolder.value = root.value
    }

    DialDisplay
    {
        id: dial
        diameter: parent.width / 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        unit: valueHolder.unit
        property int max: valueHolder.max
        property int min: valueHolder.min
        value: root.value

        onClicked:
        {
            stack.openKeyboard()
        }

        Connections
        {
            target: knob
            onEncoderIncrement:
            {
                var currStep = Math.round(dial.value / valueHolder.step) * valueHolder.step

                if (currStep + encoderVal * valueHolder.step <= dial.max && currStep + encoderVal * valueHolder.step >= dial.min)
                {
                    dial.value = currStep + encoderVal * valueHolder.step
                    valueHolder.value = dial.value
                }
            }

            onButtonPush:
            {
                stack.settingConfirmed()
            }
        }

        onValueChanged:
        {
            root.value = dial.value
        }
    }



    VerticalIndicator
    {
        id: scale
        height: 305
        width: 61
        min: valueHolder.min
        max: valueHolder.max
        x: dial.x + dial.width + 112
        y: 91
        value: root.value
    }
}
