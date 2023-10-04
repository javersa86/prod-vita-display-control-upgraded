import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Styles"

Switch {
    id: control

    width: 184
    height: 42

    checked: state_manager.sp_line_state

    indicator: Rectangle {
        id: control_area

        width: parent.width
        height: parent.height
        color: Style.primary_dark
        border.color: control.checked ? Style.mode_active_warning : Style.primary_light
        border.width: 2
        radius: 20

        Rectangle {
            x: control.checked ? parent.width - width - 4 : 0 + 4
            anchors.verticalCenter: parent.verticalCenter
            width: 88
            height: 32
            radius: 16
            color: control.checked ? Style.mode_active_warning : Style.primary_light
        }

        Rectangle {
            anchors.left: parent.left
            width: parent.width / 2
            height: parent.height
            color: Style.transparent

            Text {
                id: uncheckedText
                text: "Show"
                color: control.checked ? Style.mode_inactive : Style.mode_active
                font: Style.titleFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            anchors.right: parent.right
            width: parent.width / 2
            height: parent.height
            color: Style.transparent

            Text {
                id: checkedText
                text: "Hide"
                color: control.checked ? Style.mode_active : Style.mode_inactive
                font: Style.titleFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            pressAndHoldInterval: 225

            onPressAndHold: control_area.delay(50)
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
                if (state_manager.sp_line_state === 0)
                {
                    state_manager.setSPLineState(1)
                }
                else if (state_manager.sp_line_state === 1)
                {
                    state_manager.setSPLineState(0)
                }

                timer.stop()
            }
        }
    }
}
