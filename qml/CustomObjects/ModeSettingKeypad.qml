import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle
{
    id: root
    property Item valueHolder;
    property alias value: keypad.value;
    color: Style.transparent

    property bool adjustableKnob: true

    property StackView stack

    Component.onCompleted:
    {
        valueHolder.value = root.value
    }

    AdjustmentKeypad
    {
        id: keypad
        anchors.horizontalCenter: parent.horizontalCenter
        onKeyboardValueChanged:
        {
            valueHolder.value = keypad.workingValue
        }
        min: valueHolder.min
        max: valueHolder.max
        initialValue: state_manager.getSettingValue(valueHolder.settingId)


        settingID: valueHolder.settingId
        step: valueHolder.step
        adjustableKnob: root.adjustableKnob
    }

    Connections
    {
        target: knob

        onButtonPush:
        {
            stack.settingConfirmed()
        }
    }
}
