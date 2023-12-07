import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import SettingIndex 1.0
import IDs 1.0

Button {
    id: control

    property alias setValueText: setValue.text
    property alias setColor: setValue.color
    property alias measuredDisplayColor: scaleValueDisplay.color
    property alias measuredValueText: measuredValue.text
    property alias measuredColor: measuredValue.color
    property alias scaleHeight: scaleRectangleBox.height
    property alias measuredValueDisplay: scaleValueDisplay.y

    property alias gradientBelowVisible: gradientBelow.visible

    property alias title: title.text
    property alias unit: unit.text

    property alias min: min.text
    property alias max: max.text
    property string borderColor: Style.primary_light

    property int step
    property bool locked: false
    property int setting_id
    property int minOn
    property string helpText

    property var scalingY

    property color warningDisplayed: Style.primary_light
    property int presetState: 0

    property int adjustmentState: 0
    property int adjustmentCount: 0
    property int resetCount: 0

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

    Connections
    {
        target: state_manager

        onOxygenAdjustmentSignal:
        {
            if (setting_id === Index.O2)
            {
                if (id === 0)
                {
                    if (!resetTimer.running && adjustmentState)
                    {
                        resetTimer.start()
                    }
                    adjustmentTimer.stop()
                    adjustmentCount = 0
                }

                else if (id === 1)
                {

                    if (resetTimer.running)
                    {
                        resetTimer.stop()
                        resetCount = 0
                    }

                    if (!adjustmentTimer.running && !adjustmentState)
                    {
                        adjustmentTimer.start()
                    }
                }
            }
        }

        onLimitedO2State:
        {
            if (setting_id === Index.O2 && state_manager.limited_o2_success < 2)
            {
                var temp;
                if (state_manager.limited_o2_success > 0)
                {
                    temp = state_manager.laserO2Limit;
                }
                else
                {
                    temp = oxygen.max;
                }

                scalingY = (1 - (Number.parseInt(measuredValue.text) - Number.parseInt(control.min)) / (Number.parseInt(temp) - Number.parseInt(control.min)))
                if(scalingY < 0)
                {
                    scalingY = 0
                }
                if(scalingY > 1)
                {
                    scalingY = 1
                }
                console.log("Limited O2 State: " + state_manager.limited_o2_success)
            }
        }
    }

    Timer
    {
        id: adjustmentTimer
        repeat: true
        interval: 1000
        running: false
        onTriggered:
        {
            adjustmentCount = adjustmentCount + 1
            if (adjustmentCount >= 5)
            {
                adjustmentState = 1
                adjustmentTimer.stop()
                adjustmentCount = 0
            }
        }
    }

    Timer
    {
        id: resetTimer
        repeat: true
        interval: 1000
        running: false
        onTriggered:
        {
            resetCount = resetCount + 1
            if (resetCount >= 2)
            {
                adjustmentState = 0
                resetTimer.stop()
                resetCount = 0
            }
        }
    }

    signal clicked();

    //property alias settingID: settingID.identifier

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
            id: setValueBox
            color: Style.transparent
            width: 74.8
            height: 38
            x: 187
            y:48
            Text {
                id: setValue
                font: Style.setFont
                anchors.right:parent.right
                color: Style.primary_light
            }
        }

        Rectangle{
            id: valueDisplay
            height: 141
            width: 93
            x: 187
            y: 8
            color: Style.transparent

            Rectangle{
                id: scaleRectangleBox
                height: 140
                width: 11
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                color: Style.transparent

                Rectangle {
                    id: scaleRectangle
                    radius: 2
                    width: scaleRectangleBox.width
                    height: scaleRectangleBox.height

                    color: Style.primary_dark
                    border.color: Style.scale_rectangle_border
                    border.width: 2
                }

                Rectangle
                {
                    id: artificicalBorder
                    height: parent.height - parent.border.width* 2
                    width: parent.width
                    anchors.centerIn: parent
                    color: Style.transparent

                    Rectangle {
                        id: scaleValueDisplay
                        width: parent.width
                        height: 2
                        color: Style.general_set_display
                        radius: 2
                        y: parent.height *  control.scalingY - height / 2
                    }

                    Rectangle {
                        id: gradientBelow
                        visible:false
                        anchors.top: scaleValueDisplay.bottom
                        anchors.bottom: parent.bottom
                        width: parent.width - 4
                        anchors.horizontalCenter: parent.horizontalCenter
                        gradient: Gradient {
                            GradientStop { position: 1.0; color: "transparent"}
                            GradientStop { position: 0.0; color: control.measuredDisplayColor}
                        }
                    }
                }
            }

            Text {
                id: min
                font: Style.minMaxFont
                color: Style.minMax
                anchors.bottom: parent.bottom
                anchors.right: scaleRectangleBox.left
                rightPadding: 5
            }

            Text {
                id: max
                font: Style.minMaxFont
                color: Style.minMax
                anchors.top: parent.top
                anchors.right: scaleRectangleBox.left
                rightPadding: 5
            }
        }

        Rectangle{
            id: measuredUnitTitleBox
            height: 150
            width: 194
            color: Style.transparent

            property bool oxygen_state: setting_id === Index.O2 &&
                                        (state_manager.ventilating || state_manager.aux > 0) &&
                                        !adjustmentState &&
                                        presetState === 0

            Text {
                id: measuredValue
                font: measuredUnitTitleBox.oxygen_state ? Style.setFont : Style.measuredFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
                y: measuredUnitTitleBox.oxygen_state ? 30 : 0
            }

            ProgressDisplayMeasureValue
            {
                id: measuredSpinner
                anchors.horizontalCenter: parent.horizontalCenter
                y: 10
                visible: measuredUnitTitleBox.oxygen_state
                colorState: warningDisplayed

                onPressAndHold:
                {
                    pneumatic_button.color = Style.primary_light_selected
                    pneumatic_button.delay(50)
                }
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
