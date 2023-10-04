/*
  Joseph Aversa update: HelpIcon added.
*/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"

InteractiveKnobPage{
    id: root
    color: Style.transparent
    property StackView popupStack

    property bool dialOpen: true

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.9 * parent.height
        y: .1 * parent.height
        color:Style.transparent

        StackView
        {
            id: adjustmentStack
            width: parent.width
            height: .5 * parent.height
            y: 54
            anchors.horizontalCenter: parent.horizontalCenter
            Component.onCompleted:
            {
                adjustmentStack.push("../../CustomObjects/ModeSettingDial.qml", {"valueHolder": valueHolder, "value": state_manager.laserO2Limit, "stack": adjustmentStack})
            }

            function settingConfirmed()
            {
                if(valueHolder.value <= valueHolder.max && valueHolder.value >= valueHolder.min)
                {
                    backend.receiveSettingsUpdate(valueHolder.settingId, valueHolder.value);
                    valueHolder.setValue = valueHolder.value
                }
            }

            function openDial()
            {
                adjustmentStack.clear();
                keypad_text.text = "KEYPAD"
                keypad_button.width = 135
                if(valueHolder.value < laser_o2.min) valueHolder.value = laser_o2.min
                adjustmentStack.push("../../CustomObjects/ModeSettingDial.qml", {"valueHolder": valueHolder, "value": valueHolder.setValue, "stack": adjustmentStack})
                dialOpen = true
            }

            function openKeyboard()
            {
                adjustmentStack.clear();
                keypad_text.text = "DIAL"
                keypad_button.width = 121
                if(valueHolder.value < laser_o2.min) valueHolder.value = laser_o2.min
                adjustmentStack.push("../../CustomObjects/ModeSettingKeypad.qml",{"valueHolder": valueHolder, "value": valueHolder.setValue, "stack": adjustmentStack})
                dialOpen = false
            }
        }

        SaveButton
        {
            id: confirmButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            maEnabled: state_manager.laserO2Limit !== valueHolder.value &&  valueHolder.value >= laser_o2.min && valueHolder.value <= laser_o2.max
            onClicked:
            {
                if(valueHolder.value <= laser_o2.max && valueHolder.value >= laser_o2.min)
                backend.receiveSettingsUpdate(laser_o2.id, valueHolder.value);
            }
        }


        Rectangle {
            id: keypad_button
            objectName: "dial_button"
            anchors.right: parent.right
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 16
            width: 135
            height: 44
            color: Style.primary_dark

            Rectangle {
                id: keypad_button_area
                width: parent.width
                height: parent.height
                color: Style.transparent
                radius: 24
                border.width: 2
                border.color: Style.primary_light

                Text {
                    id: keypad_text
                    font: Style.buttonFont
                    color: Style.primary_light
                    x: 59
                    anchors.verticalCenter: parent.verticalCenter
                    text: "KEYPAD"
                }
                Image {
                    id: keypad_icon
                    source: "../../iconography/numpad_icon.svg"
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

                enabled:true
                onPressed: keypad_button_area.color = Style.primary_light_selected
                onReleased: keypad_button_area.color = Style.transparent
                onClicked: {
                    if(dialOpen)
                    {
                        adjustmentStack.openKeyboard();
                    }

                    else
                    {
                        adjustmentStack.openDial();
                    }
                }
            }
        }
    }

    Item {
        id: valueHolder
        property int value: state_manager.laserO2Limit > laser_o2.max? laser_o2.max : state_manager.laserO2Limit < laser_o2.min ? laser_o2.min : state_manager.laserO2Limit
        property int min: laser_o2.min
        property int max: laser_o2.max
        property string unit: laser_o2.unit
        property int settingId: laser_o2.id
        property int step: laser_o2.step
        property int setValue:state_manager.laserO2Limit
        property string help: laser_o2.help
    }
}
