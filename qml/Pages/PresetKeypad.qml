import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"
import IDs 1.0

InteractiveKnobPage{
    id: root
    property int value
    property string unit
    property string title
    property int settingID
    property int min
    property int max
    property StackView stack
    property StackView popupStack
    property int minOn
    property int step
    property string helpText
    property int initialValue


    signal settingConfirmed();
    signal openPresetDial(var parameters);

    Component.onCompleted:
    {
        initialValue = value
        saveButton.maEnabled = initialValue >= root.min && initialValue <= root.max
    }


    color: Style.primary_dark

    Connections
    {
        target: knob

        onButtonPush:
        {
            if(keyboard.workingValue >= root.min && keyboard.workingValue <= root.max)
            {
                root.value = keyboard.workingValue
                root.settingConfirmed()
            }
        }
    }

    Text {
        id: setting_title
        text: title + " (" + unit + ")"
        color: Style.primary_light
        font: Style.numericUiDisplayFont
        textFormat: Text.RichText
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
        }
    }

    AdjustmentKeypad {
        id: keyboard
        x: 484
        y: 165
//        y: 121
        min: root.min
        max:root.max
        minOn:root.minOn
        initialValue: root.value

        adjustableKnob: true
        step: root.step
        settingID: root.settingID

        onKeyboardValueChanged:
        {

            saveButton.maEnabled = keyboard.workingValue >= root.min && keyboard.workingValue <= root.max
        }
    }

    Text {
        id: dispay_unit
        x: 785
        y: 132
        text: unit
        font: Style.numericUiDisplayFont
        color: Style.numeric_ui_unit
    }

    Rectangle
    {
        width: cancelButton.width + saveButton.width + 50
        height: cancelButton.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: .96 * parent.height - height
        color: Style.transparent

        CancelButton
        {
            id: cancelButton
            anchors.left: parent.left
            onClicked:
            {
                if(stack) stack.pop()
            }
        }

        SaveButton
        {
            id: saveButton
            anchors.right: parent.right
            anchors.verticalCenter: cancelButton.verticalCenter
            onClicked: {
                root.value = keyboard.workingValue
                root.settingConfirmed()
            }
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
                root.openPresetDial({"value" : initialValue,
                                        "unit" : unit,
                                        "title" : title,
                                        "settingID" : settingID,
                                        "min" : min,
                                        "max" : max,
                                        "stack" : stack,
                                        "minOn" : minOn,
                                        "step" : step,
                                        "helpText" : helpText,
                                        "popupStack" : popupStack})
            }
        }
    }
}
