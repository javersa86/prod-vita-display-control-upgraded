import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent
    property StackView popupStack

    property bool lowState: false
    property bool highState: false

    property real value: 45.000000
    property string unit: ""
    property string title: ""
    property int settingID: driving_pressure_1.id
    property int min: 5.000000
    property int max: 50.000000
    property real step: 0.200000
    property int warningThreshold: driving_pressure_1.warningThreshold

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
    }

    Connections
    {
        target: backend

        onLowDPRFinished:
        {
            lowState = false
        }
    }

    SlidingBox
    {
        id: confirmBox

        height: 491
        width: 696

        color: Style.primary_dark
        border.color: Style.general_set_display
        border.width: 2

        Rectangle
        {
            id: textBox
            width: 98
            height: 57
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.left: parent.left
            anchors.leftMargin: 60
            color: Style.transparent

            Text {
                id: title
                text: "Calibration"
                font: Style.titleFont
                color: Style.general_set_display
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Text {
                id: subtitle
                text: "Driving Pressure"
                font: Style.pageTitle
                color: Style.primary_light
                anchors.top: title.bottom
                anchors.topMargin: 4
                anchors.left: parent.left
            }

            HelpIcon
            {
                id: help_button
                anchors.left: subtitle.right
                anchors.leftMargin: 20
                anchors.verticalCenter: subtitle.verticalCenter

                onClicked:
                {
                    helpBox.state = "moveIn"
                }
            }
        }

        GenericDialMini
        {
            id: dial

            value: root.value
            unit: root.unit
            title: root.title
            settingID: root.settingID
            min: root.min
            max: root.max
            step: root.step

            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 160

            onDialSignal:
            {
                backend.highDPRConfirmation(1, dial.value)
            }

            onSettingConfirmed:
            {
                backend.highDPRConfirmation(2,0)
            }
        }

        Rectangle
        {
            id: lowBox
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.left: parent.left
            anchors.leftMargin: 60
            color: Style.transparent

            Text {
                id: lowTitle
                text: "Low"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Text {
                id: lowValue
                text: "1"
                font: Style.buttonFont
                color: Style.primary_light
                anchors.verticalCenter: lowTitle.verticalCenter
                anchors.left: lowTitle.right
                anchors.leftMargin: 30
            }

            Rectangle
            {
                id: actualLowBox
                width: 80
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2
                anchors.top: lowTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                Text {
                    id: actualLowValue
                    text: state_manager.currentDPR
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: actualLowText
                text: "Actual"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: actualLowBox.bottom
                anchors.horizontalCenter: actualLowBox.horizontalCenter
            }

            Rectangle
            {
                id: lastLowBox
                width: 80
                height: 60
                color: Style.transparent
                anchors.top: lowTitle.bottom
                anchors.topMargin: 16
                anchors.right: parent.right

                Text {
                    id: lastLowValue
                    text: dprManager.DPRCalVal
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: lastLowText
                text: "Last"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: lastLowBox.bottom
                anchors.horizontalCenter: lastLowBox.horizontalCenter
            }

            VerifyButton
            {
                id: lowButton
                anchors.top: actualLowText.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                confirmState: true
                enabled: !lowState

                onClicked:
                {
                    lowState = true
                    //backend.updateDPRConfirmation(1)
                    backend.updateDPRStates(0);
                }
            }

            CancelButton
            {
                id: lowCancel
                anchors.top: lowButton.bottom
                anchors.topMargin: 12
                anchors.left: lowButton.left
                enabled: lowState
                visible: lowState

                onClicked:
                {
                    lowState = false
                    backend.lowDPRConfirmation(0)
                }
            }
        }

        Rectangle
        {
            id: highBox
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.right: parent.right
            anchors.rightMargin: 60
            color: Style.transparent

            Text {
                id: highTitle
                text: "High"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Text {
                id: highValue
                text: "100 - 105"
                font: Style.buttonFont
                color: Style.primary_light
                anchors.verticalCenter: highTitle.verticalCenter
                anchors.left: highTitle.right
                anchors.leftMargin: 30
            }

            Rectangle
            {
                id: actualHighBox
                width: 80
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2
                anchors.top: highTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                Text {
                    id: actualHighValue
                    text: state_manager.currentDPR
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: actualHighText
                text: "Actual"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: actualHighBox.bottom
                anchors.horizontalCenter: actualHighBox.horizontalCenter
            }

            Rectangle
            {
                id: lastHighBox
                width: 80
                height: 60
                color: Style.transparent
                anchors.top: highTitle.bottom
                anchors.topMargin: 16
                anchors.right: parent.right

                Text {
                    id: lastHighValue
                    text: dprManager.DPRCalVal
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: lastHighText
                text: "Last"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: lastHighBox.bottom
                anchors.horizontalCenter: lastHighBox.horizontalCenter
            }

            VerifyButton
            {
                id: highButton
                anchors.top: actualHighText.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: !highState

                onClicked:
                {
                    highState = true
                    backend.updateDPRStates(1);
                }
            }

            VerifyButton
            {
                id: saveButton
                anchors.top: highButton.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                confirmState: true
                enabled: highState
                visible: highState

                onClicked:
                {
                    highState = false
                    backend.highDPRConfirmation(2,0)
                }
            }

            CancelButton
            {
                id: highCancel
                anchors.top: saveButton.bottom
                anchors.topMargin: 12
                anchors.left: highButton.left
                enabled: highState
                visible: highState

                onClicked:
                {
                    highState = false
                    backend.highDPRConfirmation(0,0)
                }
            }
        }

        Rectangle
        {
            id: no_button

            height: 43
            width: 105
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16

            signal clicked()

            onClicked:
            {
                backend.endDPRCalibration();
                popupStack.clear()
            }

            Text
            {
                id: noStr
                text: qsTr("CLOSE")
                color: Style.primary_light
                anchors.verticalCenter: no_button.verticalCenter
                anchors.horizontalCenter: no_button.horizontalCenter
                leftPadding: .2 * no_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                pressAndHoldInterval: 225
                onPressAndHold: {
                    no_button.color = Style.primary_light_disabled
                    no_button.delay(50)
                }
                anchors.fill: no_button
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
                    no_button.clicked()
                    no_button.color = Style.primary_light_selected
                    timer.stop()
                }
            }

            Rectangle
            {
                id: closeIconBackground
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                radius: .5 * height
                color: Style.primary_light

            }

            Item {
                id: closeIcon
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                Image {
                    id: xicon
                    source: "../../iconography/icon_40_close.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: xicon
                    source: xicon
                    color: Style.primary_light_selected
                }
            }

        }
    }

    property string dpText: "The service technician will have the option to conduct Low and High Driving Pressure Regulator Calibration.<br><br>" +
                            "Conduct the following steps to calibrate the Driving Pressure Regulator at its lowest possible setting:<br><br>" +
                            "1. Connect air and oxygen gas supply to the NVENT VITA.<br>" +
                            "2. Connect the Jet 1 tube to the Jet 1 Port of the NVENT VITA.<br>" +
                            "3. Ensure that the Jet 1 tube is exposed to open atmosphere.<br>" +
                            "4. Press the Confirm button to set the pneumatic setting for Driving Pressure to 0 and close the DPR valve.<br>" +
                            "5. If the DPR Calibration Measurement is 1, then calibration was a success.<br><br>" +
                            "Conduct the following steps to calibrate the Driving Pressure Regulator at its highest possible setting:<br><br>" +
                            "1. Connect air and oxygen gass supply to the NVENT VITA.<br>" +
                            "2. Connect the Jet 1 tube to the Jet 1 Port of the NVENT VITA.<br>" +
                            "3. Connect the Jet 1 tube to the external pressure measuring device.<br>" +
                            "4. Press the Confirm button to set the pneumatic setting for Driving Pressure to 45, open the DPR valve, and enable the encoder knob to further adjust Driving Pressure at precise intervals.<br>" +
                            "5. The DPR Calibration Measurement should be between 100 and 105.<br>" +
                            "6. Verify that the pressure output is 45 PSI by using the external pressure measuring device.<br>" +
                            "7. Further adjust the pressure by using the knob on the front panel of the NVENT VITA until the measured value is exactly 45 PSI.<br>" +
                            "8. Press the Verify Button to confirm the success of the calibration procedure."

    CalibrationHelpBox
    {
        id: helpBox
        titleText: "Calibration"
        helpText: dpText
    }
}
