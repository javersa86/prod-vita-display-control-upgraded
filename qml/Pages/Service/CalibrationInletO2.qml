import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent
    property StackView popupStack

    property bool zeroState: true
    property bool verifyState: false

    property int result: -1

    property real tmpValue: -1

    property real verifyValue: (state_manager.service_notification_vector[7] - state_manager.inletO2) > 0 ?
                               (state_manager.service_notification_vector[7] - state_manager.inletO2) :
                               0.0

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
    }

    function setZeroPass()
    {
        passfailText.visible = true
        passfailText.text = "Zero Passed"
        passfailText.color = Style.affirmative
        passfail.visible = true
        passfailIcon.source = "../../iconography/thumbs-up.svg"
        colorOverlay.color = Style.affirmative
    }

    function setZeroFail()
    {
        passfailText.visible = true
        passfailText.text = "Actual Value for Zeroing (" + tmpValue + ") is not less than 3"
        passfailText.color = Style.dissident
        passfail.visible = true
        passfailIcon.source = "../../iconography/thumbs-down.svg"
        colorOverlay.color = Style.dissident
    }

    function setZeroFail()
    {
        passfailText.visible = true
        passfailText.text = "Calibration Fail"
        passfailText.color = Style.dissident
        passfail.visible = true
        passfailIcon.source = "../../iconography/thumbs-down.svg"
        colorOverlay.color = Style.dissident
    }

    function resetPassFail()
    {
        passfailText.visible = false
        passfailText.text = ""
        passfailText.color = Style.primary_dark
        passfail.visible = false
        passfailIcon.source = ""
        colorOverlay.color = Style.primary_dark
    }

    Connections
    {
        target: backend

        onZeroFinished:
        {
            result = value
            if (result == 0)
            {
                setVerifyFail()
                zeroState = false
                verifyState = true
            }
            else
            {
                actualZeroValue.visible = false
                setVerifyPass()
                zeroState = true
                verifyState = false
            }
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
                text: "Inlet O<sub>2</sub>"
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

        Rectangle
        {
            id:passfail
            y: 86
            anchors.right: parent.right
            anchors.rightMargin: 60

            width: 35.1
            height: 35.1

            visible: false
            color: Style.transparent

            Image {
                id: passfailIcon
                source: ""
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                smooth: true
            }

            ColorOverlay {
                id: colorOverlay
                anchors.fill: passfailIcon
                source: passfailIcon
            }
        }

        Text {
            id: passfailText
            text: ""
            anchors.verticalCenter: passfail.verticalCenter
            anchors.right: passfail.right
            anchors.rightMargin: 60
            font: Style.buttonFont
        }

        Rectangle
        {
            id: zeroBox
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.left: parent.left
            anchors.leftMargin: 60
            color: Style.transparent

            Text {
                id: zeroTitle
                text: "Zero"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: actualZeroBox
                width: 80
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2
                anchors.top: zeroTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                Text {
                    id: actualZeroValue
                    text: zeroState ? state_manager.service_notification_vector[6].toFixed(1) : state_manager.inletO2.toFixed(1)
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: actualZeroText
                text: "Actual"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: actualZeroBox.bottom
                anchors.horizontalCenter: actualZeroBox.horizontalCenter
            }

            Rectangle
            {
                id: lastZeroBox
                width: 80
                height: 60
                color: Style.transparent
                anchors.top: zeroTitle.bottom
                anchors.topMargin: 16
                anchors.right: parent.right

                Text {
                    id: lastZeroValue
                    text: zero_manager.inletO2.toFixed(1)
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: lastZeroText
                text: "Last"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: lastZeroBox.bottom
                anchors.horizontalCenter: lastZeroBox.horizontalCenter
            }

            VerifyButton
            {
                id: zeroButton
                anchors.top: actualZeroText.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                confirmState: true
                enabled: zeroState

                onClicked:
                {
                    tmpValue = state_manager.service_notification_vector[6]
                    if (0 < tmpValue && tmpValue < 5)
                    {
                        state_manager.setZeroInletO2(tmpValue)
                        setZeroPass()
                        zeroState = false
                        verifyState = true
                    }
                    else
                    {
                        setZeroFail()
                    }
                }
            }

            CancelButton
            {
                id: zeroCancel
                anchors.top: zeroButton.bottom
                anchors.topMargin: 12
                anchors.left: zeroButton.left
                enabled: verifyState && !zeroState
                visible: verifyState && !zeroState

                onClicked:
                {
                    resetPassFail()
                    zeroState = true
                    verifyState = false
                }
            }
        }

        Rectangle
        {
            id: verifyBox
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.right: parent.right
            anchors.rightMargin: 60
            color: Style.transparent

            Text {
                id: verifyTitle
                text: "Verify"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: actualVerifyBox
                width: 80
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2
                anchors.top: verifyTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                Text {
                    id: actualVerifyValue
                    text: verifyValue.toFixed(1)
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                    visible: verifyState
                }
            }

            Text {
                id: actualVerifyText
                text: "Actual"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: actualVerifyBox.bottom
                anchors.horizontalCenter: actualVerifyBox.horizontalCenter
            }

            Rectangle
            {
                id: lastVerifyBox
                width: 80
                height: 60
                color: Style.transparent
                anchors.top: verifyTitle.bottom
                anchors.topMargin: 16
                anchors.right: parent.right

                Text {
                    id: lastVerifyValue
                    text: zero_manager.verifiedInletO2.toFixed(1)
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: lastVerifyText
                text: "Last"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: lastVerifyBox.bottom
                anchors.horizontalCenter: lastVerifyBox.horizontalCenter
            }

            VerifyButton
            {
                id: verifyButton
                anchors.top: actualVerifyText.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: verifyState

                onClicked:
                {
                    verifyState = false
                    zeroState = true
                    backend.initZeroSensor(4, verifyValue)
                }
            }

            CancelButton
            {
                id: verifyCancel
                anchors.top: verifyButton.bottom
                anchors.topMargin: 12
                anchors.left: verifyButton.left
                enabled: verifyState && !zeroState
                visible: verifyState && !zeroState

                onClicked:
                {
                    verifyState = false
                    zeroState = true
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

    property string airText: "If the Inlet O<sub>2</sub> Sensor is reading measurements while O<sub>2</sub> is not connected, the service technician will be required to conduct a " +
                             "thorough calibration procedure and verify that the data is accurate.<br><br>" +

                             "To zero the Inlet O<sub>2</sub> Sensor, push down on the Confirm button on the Zero Section. " +
                             "A thumbs up or down icon will be displayed on the top right of the window to indicate that the zero procedure succeeds or fails. " +
                             "After Sensor Calibration is accomplished, the low verification procedure will be available.<br><br>" +

                             "NOTE: Remove the O<sub>2</sub> gas supply line from the rear of the NVENT VITA and ensure no pressure is in the system. <br><br>" +

                             "To verify the Inlet O<sub>2</sub> Measurement is accurate, the following steps need to be conducted:<br><br>" +
                             "1. Apply 30 PSI or below to the O<sub>2</sub> gas supply line on the rear panel of the NVENT VITA. <br>" +
                             "2. Push down on the left Verify button on the Verification Section.<br>" +
                             "3. The down arrow will change to green to indicate that the measurement has been reached and high verification procedure will be available.<br>" +
                             "4. Apply 31 PSI or above to the O<sub>2</sub> gas supply line on the rear panel of the NVENT VITA. <br>" +
                             "5. Push down on the right Verify button on the Verification Section.<br>" +
                             "6. The up arrow will change to green to indicate that the measurement has been reached. <br><br>" +

                             "The thumbs up or down icon will be displayed again to indicate that calibration succeeded or failed, " +
                             "and actual values on the Zero and Verify section are saved."

    CalibrationHelpBox
    {
        id: helpBox
        titleText: "Calibration"
        helpText: airText
    }
}
