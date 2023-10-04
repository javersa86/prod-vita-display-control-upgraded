import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import "../Styles"
Rectangle
{
    id: cancelButtonBox

    color:Style.transparent
    height: 50
    width: 120

    signal clicked();

    Rectangle
    {
        id: cancelButton
        color:Style.transparent
        anchors.fill: parent
        anchors.centerIn: cancelButtonBox
        radius: 24
        border.width:2
        border.color: Style.cancel

        Text {
            text: qsTr("Cancel")
            color:Style.cancel
            font:Style.cancel_font
            anchors.centerIn: parent
        }
        MouseArea
        {
            id: cancelMouseArea
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                cancelButton.color = Style.primary_light_selected
                cancelButton.delay(50)
            }
        }

        function delay(delayTime)
        {
            timer.interval = delayTime;
            timer.start();
        }

        Timer {
            id: timer
            repeat: false
            onTriggered:
            {
                cancelButtonBox.clicked();
                cancelButton.color = Style.transparent
                timer.stop()
            }
        }
    }
}
