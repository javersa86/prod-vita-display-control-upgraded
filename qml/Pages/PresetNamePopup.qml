import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"
import "../CustomObjects/Keyboard"

Rectangle{
    id: root_window
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property string previous_name

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        preset_confirm_box.state = "moveIn"
    }

    Rectangle
    {
        id: titleBox
        color: Style.primary_dark
        border.width: 2
        border.color: Style.primary_light
        radius: 15
        width: 297.6
        height: 60.800000000000004
        x: 32
        y: 85 + (.93 * 800) * .15


        TextEdit {
            id: presetTitle
            text: preset_manager.presetName
            font: Style.numberButtonFont
            color:Style.primary_light
            x: .05 * titleBox.width
            anchors.verticalCenter: parent.verticalCenter
            textFormat: TextEdit.PlainText
            cursorPosition: presetTitle.text.length
            cursorVisible: true
        }
    }

    Rectangle
    {
        id: refreshButton

        color: Style.primary_dark
        border.width: 2
        border.color: Style.primary_light
        radius: 64
        width: 96
        height: 96

        property int index: 0

        anchors.left: titleBox.right
        anchors.leftMargin: 16
        anchors.verticalCenter: titleBox.verticalCenter

        Text {
            id: refreshText
            text: "Clear"
            font: Style.numberButtonFont
            color: Style.primary_light
            anchors.centerIn: parent
        }

        MouseArea
        {
            anchors.fill: refreshButton

            onPressed: refreshButton.color = Style.primary_light_selected
            onReleased: refreshButton.color = Style.primary_dark
            onClicked: preset_manager.deletePresetName();
        }

    }

    SlidingBoxReversed
    {
        id: preset_confirm_box

        Connections
        {
            target: preset_manager

            onPresetKeyboardStateChanged:
            {
                if (preset_manager.keyboardState === 0)
                {
                    upperCase.visible = true
                    lowerCase.visible = false
                    numbersSymbols1.visible = false
                    numbersSymbols2.visible = false
                }
                else if (preset_manager.keyboardState === 1)
                {
                    upperCase.visible = false
                    lowerCase.visible = true
                    numbersSymbols1.visible = false
                    numbersSymbols2.visible = false
                }
                else if (preset_manager.keyboardState === 2)
                {
                    upperCase.visible = false
                    lowerCase.visible = false
                    numbersSymbols1.visible = true
                    numbersSymbols2.visible = false
                }
                if (preset_manager.keyboardState === 3)
                {
                    upperCase.visible = false
                    lowerCase.visible = false
                    numbersSymbols1.visible = false
                    numbersSymbols2.visible = true
                }
            }
        }

        KeyboardLayout
        {
            id: upperCase

            x: 80
            y: 32

            visible: true

            Component.onCompleted:
            {
                createFirstRow("QWERTYUIOP")
                createSecondRow("ASDFGHJKL")
                createThirdRow("ZXCVBNM")
                createSpaceBar()
                createShiftKey(1, "Shift")
                createSwitchKey(2,"123")
                createCancelKey(popupStack, previous_name)
                createBackSpaceKey()
                createReturnKey(popupStack)
            }

        }

        KeyboardLayout
        {
            id: lowerCase

            x: 80
            y: 32

            visible: false

            Component.onCompleted: {
                createFirstRow("qwertyuiop")
                createSecondRow("asdfghjkl")
                createThirdRow("zxcvbnm")
                createSpaceBar()
                createShiftKey(0, "shift")
                createSwitchKey(2,"123")
                createCancelKey(popupStack, previous_name)
                createBackSpaceKey()
                createReturnKey(popupStack)
            }
        }

        KeyboardLayout
        {
            id: numbersSymbols1

            x: 80
            y: 32

            visible: false

            Component.onCompleted: {
                createFirstRow("1234567890")
                createSecondRow("-/:;?&@")
                createThirdRow(".,!\'\"()")
                createSpaceBar()
                createShiftKey(3,"#+=")
                createSwitchKey(1,"abc")
                createCancelKey(popupStack, previous_name)
                createBackSpaceKey()
                createReturnKey(popupStack)
            }
        }

        KeyboardLayout
        {
            id: numbersSymbols2

            x: 80
            y: 32

            visible: false

            Component.onCompleted: {
                createFirstRow("[]{}#%^*+=")
                createSecondRow("$_\\|~<>`")
                createThirdRow(".,!\'\"()")
                createSpaceBar()
                createShiftKey(2,"123")
                createSwitchKey(1,"abc")
                createCancelKey(popupStack, previous_name)
                createBackSpaceKey()
                createReturnKey(popupStack)
            }
        }
    }
}
