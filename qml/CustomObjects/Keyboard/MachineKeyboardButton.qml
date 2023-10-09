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
    color: Style.primary_dark
    border.color: Style.primary_light
    border.width: 2

    property var keyValue
    property var keyId

    Text {
        id: key
        text: root.keyValue
        anchors.centerIn: parent
        color: Style.primary_light
        font: Style.numberButtonFont
    }

    Connections
    {
        target: part_manager
    }

    MouseArea
    {
        id: keyArea

        anchors.fill: parent

        onPressed: parent.color = Style.primary_light_selected
        onReleased: parent.color = Style.transparent

        onClicked:
        {
            if (keyId === 0)
            {
                part_manager.addDigit(keyValue)
            }
            else if (keyId === 1)
            {
                part_manager.removeDigit()
            }
        }
    }
}
