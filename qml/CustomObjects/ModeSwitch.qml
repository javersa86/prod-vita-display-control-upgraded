import QtQuick 2.12
import QtQuick.Controls 2.12
import "../CustomObjects"
import "../Styles"

Switch {
    id: control

    property alias checkedText: checkedText.text
    property alias uncheckedText: uncheckedText.text
    property int modeID

    property color modeColor: Style.mode_active_warning

    property bool popupEnabled: false

    signal pressed()
    signal confirmSignal()

    width: 184
    height: 42

    indicator: Rectangle {
        id: control_area

        width: parent.width
        height: parent.height
        color: Style.primary_dark
        border.color: control.checked ? modeColor : Style.primary_light
        border.width: 2
        radius: 20

        Rectangle {
            x: control.checked ? parent.width - width - 4 : 0 + 4
            anchors.verticalCenter: parent.verticalCenter
            width: 88
            height: 32
            radius: 16
            color: control.checked ? modeColor : Style.primary_light
        }

        Rectangle {
            anchors.left: parent.left
            width: parent.width / 2
            height: parent.height
            color: Style.transparent

            Text {
                id: uncheckedText
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
                color: control.checked ? Style.mode_active : Style.mode_inactive
                font: Style.titleFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill:parent
            pressAndHoldInterval: 225

            onPressAndHold: {
                control.pressed()
                control_area.delay(50)
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

                if (popupEnabled)
                {
                    if (control.checked === false)
                    {
                        confirmSignal()
                        timer.stop()
                    }
                    else
                    {
                        control.checked = false
                        timer.stop()
                    }
                }
                else if (!popupEnabled)
                {
                    control.checked = !control.checked
                    timer.stop()
                }

            }
        }
    }

    onCheckedChanged:
     {
         var enable = 0;
         if (control.checked)
         {
             enable = 1;
         }
         backend.setMode(modeID, enable)
     }
}
