import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../CustomObjects"
import "../../Styles"

Rectangle {
    id: root
    width: 96
    height: 96
    radius: 16
    color: backgroundColor
    border.color: outlineColor
    border.width: 2

    property var keyValue
    property var keyId

    property var backgroundColor: Style.primary_dark
    property var outlineColor: Style.primary_light

    property StackView popupStack
    property string previous_name

    property var keyboardState

    Text {
        id: key
        text: root.keyValue
        anchors.centerIn: parent
        color: outlineColor
        font: Style.numberButtonFont
    }

    Connections
    {
        target: preset_manager

        onPresetAllCapChanged:
        {
            if (keyId === 3)
            {
                if (preset_manager.allCapState && keyValue === "Shift")
                {
                    keyValue = "SHIFT"
                }
                else if (!preset_manager.allCapState && keyValue === "SHIFT")
                {
                    keyValue = "Shift"
                }
            }
        }
    }

    MouseArea
    {
        id: keyArea

        anchors.fill: parent

        onPressed: parent.color = Style.primary_light_selected
        onReleased: parent.color = backgroundColor

        onClicked:
        {
            if (keyId === 0)
            {
                preset_manager.addPresetName(keyValue)
            }
            else if (keyId === 1)
            {
                preset_manager.backspacePresetName();
            }
            else if (keyId === 2)
            {
                //preset_manager.enterPresetName();
                preset_manager.resetKeyboard();
                popupStack.clear()
            }
            else if (keyId === 3)
            {
                preset_manager.updateKeyboardState(keyboardState)
            }
            else if (keyId === 4)
            {
                preset_manager.setPresetName(previous_name)
                preset_manager.resetKeyboard();
                popupStack.clear()
            }
        }
    }
}
