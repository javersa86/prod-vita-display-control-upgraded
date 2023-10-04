/**
  Object created to trigger message when passcode was enter incorrectly.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Text
{
    id: incorrectPassCode
    height: 20
    visible: false
    color: Style.dissident
    font: Style.buttonFont
    property int keyboardX
    property real progress: 0.0

    Timer
    {
        id: shakeTimer
        property int count: 0
        onTriggered:
        {
            if (count < 30)
            {
                if (count % 2)
                {
                    incorrectPassCode.x = keyboardX + 2
                }
                else
                {
                    incorrectPassCode.x = keyboardX - 2
                }
                count ++;
            }
            else
            {
                stop()
                incorrectPassCode.x = keyboardX
                count = 0;
            }
        }

        interval: 10
        repeat: true
    }
    function startTime()
    {
        shakeTimer.start();
    }

}
