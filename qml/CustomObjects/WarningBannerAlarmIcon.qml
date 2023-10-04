import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id: root
    width: 75
    height: 65
    radius: 5
    color: Style.transparent

    signal clicked()

    Item {
        id: alertImage
        width: root.width
        height: root.height
        anchors.centerIn: parent

        Image {
            id: alarm_icon
            source: "../iconography/icon_40_alarm.svg"
            sourceSize.width: width
            sourceSize.height: height
            width: parent.width
            height: parent.height
            smooth: true
        }

        ColorOverlay {
            id: alertOverlay
            anchors.fill: alarm_icon
            source: alarm_icon
            color: Style.primary_light
        }
    }

    MouseArea
    {
        id: numActiveWarningsFlagMouseArea
        anchors.fill: parent
        pressAndHoldInterval: 225
        onPressAndHold:
        {
            root.color = Style.primary_light_disabled
            root.delay(200)
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
            root.clicked()
            root.color = Style.transparent
            timer.stop()
        }
    }
}
