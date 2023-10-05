import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import SettingIndex 1.0
import IDs 1.0

Button {
    id: control
    property alias measuredValueText: measuredValue.text

    property alias title: title.text
    property alias unit: unit.text
    property string borderColor: Style.primary_light

    property int step
    property bool locked: false
    property int setting_id
    property int minOn
    property string helpText

    property var scalingY


    enabled: !locked
    onMeasuredValueTextChanged:
    {
        scalingY = (1 - (Number.parseInt(measuredValue.text) - Number.parseInt(control.min)) / (Number.parseInt(control.max) - Number.parseInt(control.min)))
        if(scalingY < 0)
        {
            scalingY = 0
        }
        if(scalingY > 1)
        {
            scalingY = 1
        }
    }

    Component.onCompleted:
    {
        scalingY = (1 - (Number.parseInt(measuredValue.text) - Number.parseInt(control.min)) / (Number.parseInt(control.max) - Number.parseInt(control.min)))
        if(scalingY < 0)
        {
            scalingY = 0
        }
        if(scalingY > 1)
        {
            scalingY = 1
        }
    }

    signal clicked();

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6
    horizontalPadding: padding + 2
    spacing: 6

    icon.width: 24
    icon.height: 24
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
        id: pneumatic_button
        implicitWidth: 100
        implicitHeight: 40
        visible: !control.flat || control.down || control.checked || control.highlighted

        radius: 8
        width: 290; height: 158
        color: Style.transparent
        border.color: control.borderColor
        border.width: 4

        Timer {
            id: timer
            repeat: false
            onTriggered:
            {
                control.clicked()
                pneumatic_button.color = Style.transparent
                timer.stop()
            }
        }

        function delay(delayTime)
        {
            timer.interval = delayTime;
            timer.start();
        }

        MouseArea {
            id: mouseArea
            anchors.fill:parent
            pressAndHoldInterval: 225
            onPressAndHold:{
                pneumatic_button.color = Style.primary_light_selected
                pneumatic_button.delay(50)
            }
        }

        Rectangle{
            id: measuredUnitTitleBox
            height: 150
            width: 194
            color: Style.transparent
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: measuredValue
                font: Style.measuredFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
                y: 0
            }

            Text{
                id: title
                font: Style.titleFont
                y: 99
                anchors.horizontalCenter: parent.horizontalCenter
                color: Style.primary_light
            }

            Text{
                id: unit
                font: Style.unitFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: title.bottom
                topPadding: 5
                textFormat: Text.RichText
                color: Style.unit
            }
        }

        Item {
            id: lockImage
            width: 40
            height: 40
            anchors.left: parent.left
            anchors.bottom:parent.bottom
            visible: control.locked
            Image {
                id: alarm_icon
                source: "../iconography/lock_element.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
            }

            ColorOverlay {
                anchors.fill: alarm_icon
                source: alarm_icon
                color: control.borderColor
            }
        }
    }
}
