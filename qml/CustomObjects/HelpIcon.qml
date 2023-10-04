import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Item {
    id: hint_button
    objectName: "hint_button"
    height: 70 //35
    width: 70 //35

    signal clicked()

    property int state: 0
    property color pressColor: Style.help_icon_selected
    property color releaseColor: Style.general_set_display

    Image {
        id: hint_icon
        source: "../iconography/icon_40_help.svg"
        sourceSize.width: width
        sourceSize.height: height
        width: parent.width
        height: parent.height
        smooth: true
    }
    ColorOverlay {
        id: hint_overlay
        anchors.fill: hint_icon
        source: hint_icon
        color: hint_button.state ? pressColor : releaseColor
    }

    MouseArea {
        id: hint_mouse_area
        anchors.fill:parent
        pressAndHoldInterval: 225
        onPressAndHold:
        {
            onPressed: hint_overlay.color = pressColor
            hint_button.delay(50)
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
            hint_button.clicked()
            hint_overlay.color = releaseColor
            timer.stop()
        }
    }
}
