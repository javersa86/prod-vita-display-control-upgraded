import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import IDs 1.0
import "../Styles"
import "../CustomObjects"

InteractiveKnobPage {
    id: numeric_root
    objectName: "numeric_ui"
    color: Style.primary_dark

    property StackView homeStack
    property StackView popupStack
    property string title
    property string unit
    property int setting_id
    property int min
    property int max
    property int step
    property string helpText
    property int warningThreshold

    property bool adjustableKnob: true

    Component.onCompleted:
    {
        var tmp = true
        if (setting_id === aux_flow.id)
        {
            if (keyboard.initialValue > numeric_root.min && keyboard.initialValue < aux_flow.minimumOn)
            {
                tmp = false
            }
        }

        saveButton.maEnabled = keyboard.initialValue >= numeric_root.min && keyboard.initialValue <= numeric_root.max && tmp
    }

    Connections
    {
        target: knob
        onButtonPush:
        {
            if(saveButton.maEnabled)
            {
                if(keyboard.workingValue < numeric_root.warningThreshold)
                {
                    confirmSetting(setting_id, keyboard.workingValue)
                }

                else
                {
                    popupStack.push("HighSettingConfirmation.qml", {"settingPage": numeric_root, "value": keyboard.workingValue, "settingID": numeric_root.setting_id, "settingTitle": title})
                }
            }
        }
    }

    Text {
        id: setting_title
        text: title + " (" + unit + ")"
        textFormat: Text.RichText
        color: Style.primary_light
        font: Style.numericUiDisplayFont
        x: 25
        y: 80
    }

    HelpIcon {
        id: hint_button
        anchors.left: setting_title.right
        anchors.verticalCenter: setting_title.verticalCenter

        onClicked:
        {
            popupStack.pushHelpBox(title,helpText)
            backend.setMode(ID.LISTENING_KNOB,0)
        }
    }

    AdjustmentKeypad {
        id: keyboard
        x: 484
        y: 165
        min: numeric_root.min
        max: numeric_root.max
        initialValue: state_manager.getSettingValue(numeric_root.setting_id)

        adjustableKnob: numeric_root.adjustableKnob
        step: numeric_root.step
        settingID: numeric_root.setting_id

        onKeyboardValueChanged:
        {
            var tmp = true
            if (setting_id === aux_flow.id)
            {
                if (keyboard.workingValue > numeric_root.min && keyboard.workingValue < aux_flow.minimumOn)
                {
                    tmp = false
                }
            }

            saveButton.maEnabled = keyboard.workingValue >= numeric_root.min && keyboard.workingValue <= numeric_root.max && tmp
        }
    }

    Text {
        id: dispay_unit
        x: 785
        y: 173
        text: unit
        font: Style.numericUiDisplayFont
        color: Style.numeric_ui_unit
    }

    Rectangle
    {
        width: cancel_button.width + saveButton.width + 50
        height: cancel_button.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: .96 * parent.height - height
        color: Style.transparent

        CancelButton
        {
            id: cancel_button
            onClicked:
            {
                if(homeStack) homeStack.pop()
            }
            anchors.left: parent.left
        }

        SaveButton
        {
            id: saveButton
            onClicked: {

                if(keyboard.workingValue < numeric_root.warningThreshold)
                {
                    confirmSetting(setting_id, keyboard.workingValue)
                }

                else
                {
                    popupStack.push("HighSettingConfirmation.qml", {"settingPage": numeric_root, "value": keyboard.workingValue, "settingId": numeric_root.setting_id, "settingTitle": title})
                }
            }
            anchors.right: parent.right
            anchors.verticalCenter: cancel_button.verticalCenter
        }
    }

    Rectangle {
        id: dial_button
        objectName: "dial_button"
        x: 1141
        y: 729
        width: 121
        height: 44
        color: Style.primary_dark

        Rectangle {
            id: dial_button_area
            width: parent.width
            height: parent.height
            color: Style.transparent
            radius: 24
            border.width: 2
            border.color: Style.primary_light

            Text {
                font: Style.buttonFont
                color: Style.primary_light
                x: 59
                anchors.verticalCenter: parent.verticalCenter
                text: "DIAL"
            }
            Image {
                id: keypad_icon
                source: "../iconography/numpad_icon.svg"
                sourceSize.width: width
                sourceSize.height: height
                x: 15
                anchors.verticalCenter: parent.verticalCenter
                width: 33
                height: 35
                smooth: true
            }

            ColorOverlay {
                anchors.fill: keypad_icon
                source: keypad_icon
                color: Style.primary_light
            }
        }

        MouseArea {
            id: keypad_mouse_area
            anchors.fill:parent

            onPressed: dial_button_area.color = Style.primary_light_selected
            onReleased: dial_button_area.color = Style.transparent
            onClicked: {
                numeric_root.homeStack.openSettingDial(numeric_root.title, numeric_root.unit, numeric_root.setting_id, numeric_root.min, numeric_root.max, numeric_root.step, numeric_root.helpText, numeric_root.warningThreshold)
            }
        }
    }

    Rectangle
    {
        id: pipDisconnectionButton
        height: 42
        width: 300
        color: pipDisconnectionMA.pressed ? Style.primary_light_selected : Style.primary_dark
        border.color: Style.primary_light
        border.width: 2
        radius: 20
        anchors.left: setting_title.left
        y: setting_title.y + setting_title.height + 15
        visible: setting_id === 9 && state_manager.pip_monitoring_mode === 1 && !state_manager.preset_create_active

        MouseArea
        {
            id: pipDisconnectionMA
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                pipDisconnectionButton.color = Style.primary_light_selected
                pipDisconnectionButton.delay(50)
            }
        }

        function delay(delayTime)
        {
            timer.interval = delayTime;
            timer.start();
        }

        Timer {
            id: timer
            repeat: false
            onTriggered:
            {
                backend.setMode(5,0);
                pipDisconnectionButton.color = Style.primary_dark
                timer.stop()
            }
        }

        Text {
            id: pipDisconnectionText
            text: qsTr("Disable PIP Disconnection")
            anchors.centerIn: parent
            color: Style.primary_light
            font: Style.titleFont
        }
    }

    Text
    {
        id: pipDisconnectionInstruction
        text: qsTr("PIP Disconnection is \"ON\". Press button to disable.")
        visible: pipDisconnectionButton.visible
        color: Style.mode_label
        font: Style.titleFont
        anchors.top: pipDisconnectionButton.bottom
        anchors.left: pipDisconnectionButton.left
        wrapMode: "WordWrap"
        topPadding: 15
        width: 230
    }

    function confirmSetting(settingID, value)
    {
        backend.receiveSettingsUpdate(settingID, value)
        popupStack.clear()
        homeStack.pop()
    }

    function cancelSetting()
    {
        popupStack.clear()
        backend.setMode(ID.LISTENING_KNOB,1)
    }
}
