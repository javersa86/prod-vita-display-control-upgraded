import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: verifyButtonBox

    height: 50
    width: 120
    color:Style.transparent

    signal clicked();
    property bool enabled
    property bool confirmState: false

    Rectangle
    {
        id: verifyButton
        color:Style.affirmative
        anchors.fill: parent
        anchors.centerIn: verifyButtonBox
        radius: 24
        opacity: verifyButtonBox.enabled ? 1 : .5
        border.width: 2
        border.color: Style.affirmative

        Text {
            text: confirmState ? "CONFIRM" : "VERIFY"
            color:Style.primary_dark
            font:Style.buttonFont
            anchors.centerIn: parent
        }
    }

    MouseArea
    {
        anchors.fill:parent
        id: continueMouseArea
        enabled:verifyButtonBox.enabled
        pressAndHoldInterval: 225

        onPressAndHold:
        {
            verifyButton.color = Style.affirmative_transluscent
            timer.start()
        }
    }

    Timer {
        id: timer
        interval: 50
        repeat: false
        onTriggered:
        {
            verifyButtonBox.clicked()
            verifyButton.color = Style.affirmative
            timer.stop()
        }
    }
}
