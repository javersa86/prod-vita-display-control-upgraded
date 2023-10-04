import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: keyboard_root
    width: 288
    height: 487
    color: Style.transparent

    property alias value: value_display.value
    property alias initialValue: value_display.initialValue
    property int maxDigits: 6
    property alias adjusted: value_display.adjusted

    property bool adjustableKnob
    property int min
    property int max
    property int minOn
    property int step
    property int settingID
    property int updateStep: 0

    signal valueChange()

    Connections
    {
        target: knob

        onEncoderIncrement:
        {
            if (keyboard_root.adjustableKnob)
            {
                if (keyboard_root.updateStep)
                {
                    if (encoderVal > 0)
                    {
                        keyboard_root.step = 5;
                    }
                    else if (encoderVal < 0)
                    {
                        keyboard_root.step = 1;
                    }
                    keyboard_root.updateStep = 0;
                }

                if (value_display.adjusted)
                {
                    value_display.initialValue = value_display.value
                }

                if (encoderVal > 0 && value_display.initialValue < keyboard_root.min)
                {
                    value_display.initialValue = keyboard_root.min
                }
                else if (encoderVal < 0 && value_display.initialValue > keyboard_root.max)
                {
                    value_display.initialValue = keyboard_root.max
                }

                else if (encoderVal > 0 && value_display.initialValue < keyboard_root.max)
                {
                    if ((settingID === aux_flow.id) && value_display.initialValue < aux_flow.minimumOn)
                    {
                        value_display.initialValue = aux_flow.minimumOn
                    }
                    else
                    {
                        value_display.initialValue = value_display.initialValue + keyboard_root.step
                    }
                }
                else if(encoderVal < 0 && value_display.initialValue > keyboard_root.min)
                {
                    if ((settingID === aux_flow.id) && keyboard_root.min < value_display.initialValue && value_display.initialValue <= aux_flow.minimumOn)
                    {
                        value_display.initialValue = keyboard_root.min
                    }
                    else
                    {
                        value_display.initialValue = value_display.initialValue - keyboard_root.step
                    }
                }
                value_display.adjusted = false
                keyboard_root.valueChange()

                if (value_display.initialValue == 30 && settingID === rate_1.id)
                {
                    updateStep = 1;
                }
            }
        }
    }

    Component.onCompleted:
    {
        if (keyboard_root.adjustableKnob)
        {
            keyboard_root.maxDigits = getMaxDigits()

            if (keyboard_root.settingID === rate_1.id)
            {
                if (keyboard_root.initialValue < 30)
                {
                    keyboard_root.step = 1;
                }
                else if (keyboard_root.initialValue > 30)
                {
                    keyboard_root.step = 5;
                }
                else
                {
                    keyboard_root.updateStep = 1;
                }
            }
        }
    }

    function getMaxDigits()
    {
        switch(keyboard_root.settingID) {
            case driving_pressure_1.id: return 2
            case rate_1.id: return 3
            case inspiratory_time_1.id: return 2
            case stacking_pressure_1.id: return 3
            case oxygen.id: return 3
            case pip.id: return 3
            case aux_flow.id: return 2
            case humidity_1.id: return 3
            case humidity_aux.id: return 3
            case etco2_rate.id: return 3
            case etco2_inpiratory_time.id: return 2
            case etco2_num_breaths.id: return 2
            case laser_o2.id: return 2
            case etco2_driving_pressure.id: return 2
        }
    }

    Rectangle {
        id: value_display
        width: parent.width
        height: 57
        color: Style.transparent
        border.color: Style.general_set_display
        border.width: 2
        radius: 4
        x: 0
        y:0
        property int value: 0
        property int initialValue:0
        property bool adjusted: false
        Text {
            text: parent.adjusted ? parent.value : parent.initialValue
            color: Style.general_set_display
            anchors.centerIn:parent
            font: Style.numericUiDisplayFont
        }

        function add(val){
            if ((typeof value === "number")&&(typeof val == "number")){
                if (!adjusted)
                {
                    value = 0;
                }

                if (Math.floor(Math.log10(value)) + 2 <= maxDigits)
                {
                    value = value * 10 + val
                    adjusted = true
                    keyboard_root.valueChange()

                    if (value_display.value < 30 && settingID === rate_1.id)
                    {
                        keyboard_root.step = 1
                    }
                    else if (value_display.value >= 30 && settingID === rate_1.id)
                    {
                        keyboard_root.step = 5
                    }
                }
            } 
        }

        function backspace(){
            if (typeof value == "number"){
                if (!adjusted)
                {
                    value = 0;
                }

                value = value / 10
                adjusted = true
                keyboard_root.valueChange()

                if (value_display.value < 30 && settingID === rate_1.id)
                {
                    keyboard_root.step = 1
                }
                else if (value_display.value >= 30 && settingID === rate_1.id)
                {
                    keyboard_root.step = 5
                }
            }
        }
    }

    Rectangle {
        id: numberButtonBox
        height: 392
        width: parent.width
        y: 95
        color: Style.transparent

        NumberButton {
            value: 1
            anchors.left: parent.left
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 2
            anchors.horizontalCenter: parent.horizontalCenter
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 3
            anchors.right: parent.right
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 4
            anchors.left: parent.left
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 5
            anchors.horizontalCenter: parent.horizontalCenter
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 6
            anchors.right: parent.right
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 7
            anchors.left: parent.left
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 8
            anchors.horizontalCenter: parent.horizontalCenter
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 9
            anchors.right: parent.right
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 0
            anchors.horizontalCenter: parent.horizontalCenter
            y: 312
            onClicked: {
                value_display.add(value)
            }
        }

        Item {
            width: 45
            height: 45
            x: 225
            y: 329

            signal clicked();

            onClicked: {
                value_display.backspace()
            }
            Image {
                id: lock_icon
                source: "../iconography/keyboard-delete.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
            }

            ColorOverlay {
                anchors.fill: lock_icon
                source: lock_icon
                color: Style.primary_light
            }

            MouseArea {
                id: mouseArea
                anchors.fill:parent
        
                onClicked:{
                    value_display.backspace()
                }
            }
        }
    }
}
