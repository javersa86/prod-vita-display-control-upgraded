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


    Connections
    {
        target: knob
        onButtonPush:
        {
            if((keyboard.workingValue == root.min || keyboard.workingValue >=humidity_1.minimumOn) && keyboard.workingValue <= root.max)
            {
                stack.confirmSettings()
            }
        }
    }

    Text {
        id: jetStr
        text: qsTr("Jet and Aux")
        color: Style.mode_label
        font: Style.titleFont
        x: keyboard.x + (keyboard.width - width) * .5
        anchors.bottom: keyboard.top
        bottomPadding: 15
    }

    AdjustmentKeypad {
        id: keyboard
        anchors.centerIn: parent
        min: humidity_1.min
        max: humidity_1.max
        width: .163 * parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        minOn: humidity_1.minimumOn
        initialValue: state_manager.getSettingValue(humidity_1.id)

        adjustableKnob: root.adjustableKnob
        step: humidity_1.step
        settingID: humidity_1.id

        onKeyboardValueChanged:
        {
            stack.setHum1(workingValue)
            stack.setHumAux(workingValue)
        }
    }

    Text {
        id: dispay_unit
        x: 785
        y: 80
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
            stack.replace("HumidityUnifiedDial.qml", {"stack": stack})
        }
    }
}
