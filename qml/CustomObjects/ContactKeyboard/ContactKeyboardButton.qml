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
        target: contact_manager

        onAllCapKeySignal:
        {
            if (keyId === 3)
            {
                if (value && keyValue === "Shift")
                {
                    keyValue = "SHIFT"
                }
                else if (!value && keyValue === "SHIFT")
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
                contact_manager.addKeySignal(keyValue)
            }
            else if (keyId === 1)
            {
                contact_manager.deleteKeySignal()
            }
            else if (keyId === 2)
            {
                contact_manager.enterKeySignal()
            }
            else if (keyId === 3)
            {
                contact_manager.shiftKeySignal(keyboardState)
            }
            else if (keyId === 4)
            {
                contact_manager.switchKeySignal(keyboardState)
            }
            else if (keyId === 5)
            {
                contact_manager.cancelKeySignal()
            }
            else if (keyId === 6)
            {
                contact_manager.doneKeySignal()
            }
        }
    }

}
