import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id: keyboard_root
    width: 288
    height: 600
    color: Style.transparent

    property int min
    property int max
    property int value
    property int minOn
    property alias initialValue: keyboard.initialValue
    property alias adjusted: keyboard.adjusted
    property int workingValue: adjusted ? keyboard.value : keyboard.initialValue

    property bool adjustableKnob
    property int step
    property int settingID

    signal keyboardValueChanged();

    Keyboard
    {
        id:keyboard
        anchors.horizontalCenter: parent.horizontalCenter
        value: keyboard_root.value
        initialValue: 0

        adjustableKnob: keyboard_root.adjustableKnob
        min: keyboard_root.min
        max: keyboard_root.max
        minOn: keyboard_root.minOn
        step: keyboard_root.step
        settingID: keyboard_root.settingID

        onValueChange:
        {
            keyboard_root.value = value
            keyboard_root.keyboardValueChanged();

        }
    }

    Text {
        id: outsideRangeIndicator
        text: qsTr("Outside accepted range")
        color: Style.primary_light
        font: Style.minMaxFont
        visible: keyboard_root.workingValue > keyboard_root.max || keyboard_root.workingValue < keyboard_root.min || keyboard_root.workingValue > keyboard_root.min && keyboard_root.workingValue < keyboard_root.minOn

        anchors.top: keyboard.bottom
        topPadding: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: knobText
        text: qsTr("Knob")
        color: adjustableKnob ? Style.mode_label : Style.mode_inactive
        font: Style.titleFont
        visible: humidity_1.id === settingID || humidity_aux.id === settingID
        anchors.bottom: scale.top
        anchors.right: scale.right
    }

    VerticalIndicator
    {
        id: scale
        height: 305
        width: 61
        x: keyboard_root.width + keyboard_root.width * .695
        y: keyboard.height / 2 - height / 2
        min: keyboard_root.min
        max: keyboard_root.max
        value: keyboard_root.workingValue
        minOn: keyboard_root.minOn
    }
}
