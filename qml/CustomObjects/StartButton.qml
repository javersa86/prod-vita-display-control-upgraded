import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: startButtonBox

    height: 43
    width: 105
    color:Style.transparent

    signal clicked();
    property bool enabled

    Rectangle
    {
        id: startButton
        color:Style.affirmative
        anchors.fill: parent
        anchors.centerIn: startButtonBox
        radius: 24
        opacity: startButtonBox.enabled ? 1 : .5
        border.width: 2
        border.color: Style.affirmative

        Text {
            text: "START"
            color:Style.primary_dark
            font:Style.buttonFont
            anchors.centerIn: parent
        }
    }

    MouseArea
    {
        anchors.fill:parent
        id: continueMouseArea
        enabled:startButtonBox.enabled
        pressAndHoldInterval: 225

        onPressAndHold:
        {
            startButton.color = Style.affirmative_transluscent
            timer.start()
        }
    }

    Timer {
        id: timer
        interval: 50
        repeat: false
        onTriggered:
        {
            startButtonBox.clicked()
            startButton.color = Style.affirmative
            timer.stop()
        }
    }
}
