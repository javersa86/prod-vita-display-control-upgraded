import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    color: Style.transparent

    property int finalBrightness
    property bool saveState: false

    Component.onCompleted:
    {
        finalBrightness = Math.round(brightness_manager.getBrightness() / 10) * 10
    }

    Component.onDestruction:
    {
        if (dial.value !== finalBrightness && !saveState)
        {
            brightness_manager.changeBrightness(finalBrightness / 100);
        }
    }

    DialDisplay
    {
        id: dial
        diameter: parent.width / 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        unit: "%"
        property int max: brightness_manager.getMaxPercent()
        property int min: brightness_manager.getMinPercent()
        value: Math.round(brightness_manager.getBrightness() / 10) * 10;

        Connections
        {
            target: knob
            onEncoderIncrement:
            {
                var currStep = Math.round(dial.value / 10) * 10
                if (
                        currStep + encoderVal * 10 <= dial.max &&
                        currStep + encoderVal * 10  >= dial.min
                        )
                {
                    dial.value = currStep + encoderVal * 10
                    confirmButton.maEnabled = Math.round(brightness_manager.getBrightness() / 10) * 10 !== dial.value
                    brightness_manager.changeBrightness(dial.value / 100);
                    saveState = false
                }

            }
            onButtonPush:
            {
                brightness_manager.changeBrightness(dial.value / 100);
                finalBrightness = dial.value
                confirmButton.maEnabled = Math.round(brightness_manager.getBrightness() / 10) * 10 !== dial.value
                saveState = true
            }
        }
    }

    VerticalIndicator
    {
        id: scale
        height: 305
        width: 61
        min: dial.min
        max: dial.max
        x: dial.x + dial.width + 112
        y: 91
        value: dial.value
    }

    SaveButton
    {
        id: confirmButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 54
        maEnabled: Math.round(brightness_manager.getBrightness() / 10) * 10 !== dial.value
        onClicked:
        {
            brightness_manager.changeBrightness(dial.value / 100);
            finalBrightness = dial.value
            confirmButton.maEnabled = Math.round(brightness_manager.getBrightness() / 10) * 10 !== dial.value
            saveState = true
        }
    }
}
