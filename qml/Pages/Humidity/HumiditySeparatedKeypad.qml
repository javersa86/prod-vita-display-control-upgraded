import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    id: root
    objectName: "numeric_ui"
    color: Style.transparent

    property string unit
    property int min: humidity_1.min
    property int max: humidity_1.max
    property StackView stack

    property bool adjustableKnob: true

    property int firstPage: 1


    Component.onCompleted:
    {
        stack.setHum1(state_manager.getSettingValue(humidity_1.id))
        if (firstPage)
        {
            stack.setHumAux(state_manager.getSettingValue(humidity_aux.id))
        }
        else
        {
            stack.setHumAux(0)
        }
    }

    Connections
    {
        target: knob
        onButtonPush:
        {
            root.adjustableKnob = !root.adjustableKnob
        }
    }

    Text {
        id: jetStr
        text: qsTr("Jet")
        color: Style.mode_label
        font: Style.titleFont
        x: hum1_keypad.x + (hum1_keypad.width - width) * .5
        anchors.bottom: hum1_keypad.top
        bottomPadding: 15
    }

    AdjustmentKeypad {
        id: hum1_keypad
        min: humidity_1.min
        max: humidity_1.max
        width: 150
        y: .12 * parent.height
        x: parent.width * .30 - .5* width
        minOn: humidity_1.minimumOn
        initialValue: stack.hum_1 //state_manager.getSettingValue(humidity_1.id)

        adjustableKnob: root.adjustableKnob
        step: humidity_1.step
        settingID: humidity_1.id

        onKeyboardValueChanged:
        {
            stack.setHum1(workingValue)
        }
    }

    Text {
        id: auxStr
        text: qsTr("Aux")
        color: Style.mode_label
        font: Style.titleFont
        x: hum_aux_keypad.x + (hum_aux_keypad.width - width) * .5
        anchors.bottom: hum_aux_keypad.top
        bottomPadding: 15
    }

    AdjustmentKeypad {
        id: hum_aux_keypad
        min: humidity_aux.min
        max: humidity_aux.max
        y: .12 * parent.height
        width: 150
        x: parent.width * .70 - .5* width
        minOn: humidity_aux.minimumOn
        initialValue: stack.hum_aux //state_manager.getSettingValue(humidity_aux.id)

        adjustableKnob: !root.adjustableKnob
        step: humidity_aux.step
        settingID: humidity_aux.id

        onKeyboardValueChanged:
        {
            stack.setHumAux(workingValue)
        }
    }

    Text {
        id: dispay_unit_jet
        x: hum1_keypad.x + hum1_keypad.width + 90
        y: hum1_keypad.y + 15
        text: "%"
        font: Style.numericUiDisplayFont
        color: Style.numeric_ui_unit
    }

    Text {
        id: dispay_unit_aux
        x: hum_aux_keypad.x + hum_aux_keypad.width + 90
        y: hum_aux_keypad.y + 15
        text: "%"
        font: Style.numericUiDisplayFont
        color: Style.numeric_ui_unit
    }

    DialButton
    {
        anchors.right: parent.right
        anchors.bottom:parent.bottom
        onClicked:
        {
            stack.replace("HumiditySeparatedDial.qml", {"stack": stack, "firstPage": root.firstPage})
        }
    }
}
