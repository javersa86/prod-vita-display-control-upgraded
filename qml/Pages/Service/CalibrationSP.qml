import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
import NotificationIndex 1.0

Rectangle {
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent
    property StackView popupStack
    property StackView newStack

    property bool zeroState: true
    property bool verifyState: false

    property int result: -1

    property real tmpValue: -1

    property real verifyValue: (state_manager.service_notification_vector[1] - state_manager.zeroSP) > 0 ?
                               (state_manager.service_notification_vector[1] - state_manager.zeroSP) : 0.0

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

    function setVerifyPass()
    {
        passfailText.visible = true
        passfailText.text = "Calibration Success (" + zero_manager.zeroSP.toFixed(1) + ") (" + zero_manager.verifiedZeroSP.toFixed(1) + ")"
        passfailText.color = Style.affirmative
        passfail.visible = true
        passfailIcon.source = "../../iconography/thumbs-up.svg"
        colorOverlay.color = Style.affirmative
    }

    function setVerifyFail()
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
                text: "SP"
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

//            Text {
//                id: zeroValue
//                text: "Target: 0 - 3"
//                font: Style.buttonFont
//                color: Style.primary_light
//                anchors.verticalCenter: zeroTitle.verticalCenter
//                anchors.left: zeroTitle.right
//                anchors.leftMargin: 30
//            }

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
                    text: zeroState ? state_manager.service_notification_vector[0].toFixed(1) : state_manager.zeroSP.toFixed(1)
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
                    text: zero_manager.zeroSP.toFixed(1)
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
                    tmpValue = state_manager.service_notification_vector[0]
                    if (0 < tmpValue && tmpValue < 5)
                    {
                        state_manager.setZeroSP(tmpValue)
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

//            Text {
//                id: verifyValue
//                text: "Raw"
//                font: Style.buttonFont
//                color: Style.primary_light
//                anchors.verticalCenter: verifyTitle.verticalCenter
//                anchors.left: verifyTitle.right
//                anchors.leftMargin: 30
//            }

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
                    text: zero_manager.verifiedZeroSP.toFixed(1)
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
                    backend.initZeroSensor([1, verifyValue])
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

    property string spText: "If the SP Sensor is reading measurements while ventilation is inactive, the service technician " +
                            "will be required to conduct a thorough calibration procedure.<br><br>" +

                            "To begin calibration, we need zero the SP Sensor by ensuring that the actual value, averaged data, " +
                            "is reaching the target value between 0 and 5. " +
                            "Once the value is reached, press the Confirm button on the Zero Section to continue with verification.<br><br>" +

                            "The thumbs up or down icon will be displayed on the top right of the window to indicate that the average data is zeroed. " +
                            "The actual value will display the saved average data.<br><br>" +

                            "To complete calibration, the user will need to verify that the actual value, " +
                            "the raw data subtracted from the saved average, is also accurate.<br><br>" +

                            "NOTE: Verify that the Jet tube is connected to the front of the NVENT VITA and that it is open to the atmosphere.<br><br>" +

                            "To verify the Stacking Pressure Measurement is accurate, the following steps need to be conducted:<br><br>" +
                            "1. Connect the Jet tube to an external pressure measuring device. <br>" +
                            "2. Apply 100 cmH<sub>2</sub>O to the Jet tube. <br>" +
                            "3. Verify that the onboard sensor and the external pressure measuring device match. <br>" +
                            "4. Push down on the Verify button on the Verify Section to complete the procedure. <br><br>" +

                            "The thumbs up or down icon will be displayed again to indicate that calibration succeeded or failed, " +
                            "and actual values on the Zero and Verify sections are saved."


    CalibrationHelpBox
    {
        id: helpBox
        titleText: "Calibration"
        helpText: spText
    }

}
