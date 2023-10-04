import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import "../Styles"

T.Button {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    spacing: 6

    signal clicked()

    icon.width: 48 //24
    icon.height: 48 //24
    icon.color: control.checked || control.highlighted ? control.palette.brightText :
                control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: control.checked || control.highlighted ? control.palette.brightText :
               control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText
    }

    background: Rectangle {
        id: hamburgerButtonArea
        implicitWidth: 200 //100
        implicitHeight: 80 //40
        visible: !control.flat || control.down || control.checked || control.highlighted
        
        radius: 13
        width: 99 //96 //48
        height: 86 //96 //48
        color: Style.transparent

        MouseArea {
            id: mouseArea
            anchors.fill:parent
            pressAndHoldInterval: 225

            onPressAndHold:
            {
                parent.color = Style.primary_light_selected
                backTouch.color = Style.transparent
                hamburgerButtonArea.delay(50)
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
                control.clicked()
                parent.color = Style.transparent
                backTouch.color = Style.primary_dark
                timer.stop()
            }
        }

        Rectangle{
            id: backTouch
            width: parent.width
            height: 40 //20
            anchors.verticalCenter:parent.verticalCenter
            color:Style.primary_dark
            Rectangle {
                width: 48 //24
                height: 8 //4
                color: Style.primary_light
                radius: 4  //2
                anchors.top:parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 48
                height: 8
                color: Style.primary_light
                radius: 4
                anchors.bottom:parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                width: 48
                height: 8
                color: Style.primary_light
                radius: 4
                anchors.verticalCenter:parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
