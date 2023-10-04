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

Rectangle
{
    id: root
    color: Style.transparent

    property int finalVolume
    property bool saveState: false

    Component.onCompleted:
    {
        finalVolume = state_manager.volume
    }

    Component.onDestruction:
    {
        if (dial.value !== finalVolume && !saveState)
        {
            backend.receiveSettingsUpdate(volume.id, finalVolume);
        }
    }

    DialDisplay
    {
        id: dial
        diameter: parent.width / 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        unit: "%"
        property int max: volume.max
        property int min: volume.min
        property int step: volume.step
        value: Math.round(finalVolume / step) * step

        Connections
        {
            target: knob
            onEncoderIncrement:
            {
                var currStep = Math.round(dial.value / dial.step) * dial.step
                if(dial.value < dial.min)
                {
                    dial.value = dial.min
                }

                else if (
                         currStep + encoderVal * dial.step <= dial.max &&
                         currStep + encoderVal * dial.step >= dial.min
                         )
                {
                    dial.value += encoderVal * dial.step
                }

                if(dial.value <= volume.max && dial.value >= volume.min)
                {
                    backend.receiveSettingsUpdate(volume.id, dial.value);
                    saveState = false
                }
            }
            onButtonPush:
            {
                if(dial.value <= volume.max && dial.value >= volume.min)
                {
                    backend.receiveSettingsUpdate(volume.id, dial.value);
                    finalVolume = dial.value
                    saveState = true
                }
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
        maEnabled: Math.round(finalVolume / volume.step) * volume.step !== dial.value &&
                   dial.value >= volume.min &&
                   dial.value <= volume.max
        onClicked:
        {
            if(dial.value <= volume.max && dial.value >= volume.min)
            {
                backend.receiveSettingsUpdate(volume.id, dial.value);
                finalVolume = dial.value
                saveState = true
            }
        }
    }
}
