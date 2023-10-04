/**
  Update by Joseph Aversa

  Mini Generic Dial to change O2 Setting from O2 Calibration page and High DPR Calibration value.
*/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root
    property real value
    property string unit
    property string title
    property int settingID
    property int min
    property int max
    property int minOn
    property StackView stack
    property StackView popupStack
    property real step

    signal settingConfirmed();
    signal dialSignal();

    color: Style.primary_dark

    Component.onCompleted:
    {
        if(root.value > root.max)
        {
            root.value = root.max
        }
        if(root.value < root.min)
        {
            root.value = root.min
        }

        if (!minOn)
        {
            minOn = min
        }
    }

    Connections
    {
        target: knob
        onEncoderIncrement:
        {
            var currStep = Math.round(root.value / step) * step
            if (root.value < root.minOn && encoderVal > 0)
            {
                root.value = root.minOn;
            }
            else if(root.value <= minOn && encoderVal < 0)
            {
                root.value = root.min;
            }

            else if (currStep + encoderVal * root.step <= root.max && currStep + encoderVal * root.step >= root.minOn)
            {
                root.value = currStep + encoderVal * root.step;
            }
            root.dialSignal();
        }
        onButtonPush:
        {
            root.settingConfirmed()
        }
    }

    DialDisplayMini
    {
        id: dialDisplay
        value: root.value
        unit: root.unit
        diameter: 120
    }
}
