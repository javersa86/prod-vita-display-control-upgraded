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

    property int numWarnings

    signal clicked()

    Item {
        id: alertImage

        width: root.width
        height: root.height
        anchors.centerIn: parent

        Image {
            id: alarm_icon
            source: "../iconography/icon_40_alarm_2.svg"
            sourceSize.width: width
            sourceSize.height: height
            width: parent.width
            height: parent.height
            //fillMode: Image.PreserveAspectFit
            smooth: true
        }

        ColorOverlay {
            id: alertOverlay
            anchors.fill: alarm_icon
            source: alarm_icon
            color: Style.primary_light
        }
    }

    Rectangle {
        id: numFlag
        visible: numWarnings !== 1
        x: 38.918
        y: 6.018
        height: 35.765
        width: height
        radius: width*0.5
        color: Style.transparent

        Text{
            id: numActiveWarningsFlagText
            color: Style.primary_light
            font: numWarnings > 9 ? Style.warningFlagMini : Style.warningFlag
            text: numWarnings
            anchors.centerIn: parent
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
