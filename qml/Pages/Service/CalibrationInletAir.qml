import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent
    property StackView popupStack

    property bool zeroState: true
    property bool lowVerifyState: false
    property bool highVerifyState: false

    property int zeroResult: -1

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        backend.sensorCalibration(1,3,0)
        confirmBox.state = "moveIn"
    }

    Connections
    {
        target: backend

        onZeroFinished:
        {
            zeroResult = value
            if (zeroResult == 0)
            {
                lowVerifyState = true
            }
            else
            {
                zeroState = true
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
                text: "Inlet Air"
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
            anchors.right: passfailText.left

            width: 35.1
            height: 35.1
            visible: zeroResult != -1
            color: Style.transparent

            Image {
                id: passfailIcon
                source: zeroResult == 0 ? "../../iconography/thumbs-up.svg" : "../../iconography/thumbs-down.svg"
                sourceSize.width: parent.width
                sourceSize.height: parent.height
                smooth: true
            }

            ColorOverlay {
                anchors.fill: passfailIcon
                source: passfailIcon
                color: zeroResult == 0 ? Style.affirmative : Style.dissident
            }
        }

        Text {
            id: passfailText
            text: zeroResult == 0 ? qsTr("Passed") : qsTr("Failed")
            anchors.verticalCenter: passfail.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 60
            leftPadding: 5
            font: Style.buttonFont
            visible: zeroResult != -1
            color: zeroResult == 0 ? Style.affirmative : Style.dissident
        }

        Rectangle
        {
            id: zeroBox
            width: parent.width * 0.2475
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
                    text: state_manager.inletAir
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
                    text: zero_manager.inletAir
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
                    zeroState = false
                    downArrowIcon.color = Style.numeric_ui_unit
                    upArrowIcon.color = Style.numeric_ui_unit
                    //backend.initZeroSensor(3)
                }
            }
        }

        Rectangle
        {
            id: verifyBox
            width: parent.width * .5
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
                anchors.right: parent.horizontalCenter
                anchors.rightMargin: 40

                Text {
                    id: actualVerifyValue
                    text: state_manager.inletAir
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                    visible: lowVerifyState || highVerifyState
                }
            }

            Text {
                id: downArrowIcon
                text: "&#x2913;"
                font: Style.setFont
                textFormat: Text.RichText
                color: Style.numeric_ui_unit
                anchors.verticalCenter: actualVerifyBox.verticalCenter
                anchors.left: actualVerifyBox.right
                anchors.leftMargin: 4
            }

            Text {
                id: actualVerifyText
                text: "Actual"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: actualVerifyBox.bottom
                anchors.horizontalCenter: actualVerifyBox.horizontalCenter
            }

            VerifyButton
            {
                id: lowVerifyButton
                anchors.top: actualVerifyText.bottom
                anchors.topMargin: 12
                anchors.right: parent.horizontalCenter
                anchors.rightMargin: 27
                enabled: lowVerifyState && state_manager.inletAir <= 30

                onClicked:
                {
                    downArrowIcon.color = Style.affirmative
                    lowVerifyState = false
                    highVerifyState = true
                }
            }

            CancelButton
            {
                id: lowVerifyCancel
                anchors.top: lowVerifyButton.bottom
                anchors.topMargin: 12
                anchors.left: lowVerifyButton.left
                enabled: lowVerifyState && !zeroState
                visible: lowVerifyState && !zeroState

                onClicked:
                {
                    downArrowIcon.color = Style.numeric_ui_unit
                    lowVerifyState = false
                    zeroState = true
                }
            }

            Rectangle
            {
                id: lastVerifyBox
                width: 80
                height: 60
                color: Style.transparent
                anchors.top: verifyTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 40

                Text {
                    id: lastVerifyValue
                    text: zero_manager.verifiedInletAir
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
            }

            Text {
                id: upArrowIcon
                text: "&#x2912;"
                font: Style.setFont
                textFormat: Text.RichText
                color: Style.numeric_ui_unit
                anchors.verticalCenter: lastVerifyBox.verticalCenter
                anchors.left: lastVerifyBox.right
                anchors.leftMargin: 4
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
                id: highVerifyButton
                anchors.top: lastVerifyText.bottom
                anchors.topMargin: 12
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: 27
                enabled: highVerifyState && state_manager.inletAir >= 31

                onClicked:
                {
                    zero_manager.addVerifiedValue(3, state_manager.inletAir)
                    upArrowIcon.color = Style.affirmative
                    highVerifyState = false
                    zeroState = true
                }
            }

            CancelButton
            {
                id: highVerifyCancel
                anchors.top: highVerifyButton.bottom
                anchors.topMargin: 12
                anchors.left: highVerifyButton.left
                enabled: highVerifyState && !lowVerifyState && !zeroState
                visible: highVerifyState && !lowVerifyState && !zeroState

                onClicked:
                {
                    upArrowIcon.color = Style.numeric_ui_unit
                    highVerifyState = false
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
                backend.sensorCalibration(0,3,0);
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

    property string airText: "If the Inlet Air Sensor is reading measurements while Air is not connected, the service technician will be required to conduct a " +
                             "thorough calibration procedure and verify that the data is accurate.<br><br>" +
                             "To zero the Inlet Air Sensor, push down on the Confirm button on the Zero Section. " +
                             "A thumbs up or down icon will be displayed on the top right of the window to indicate that the zero procedure succeeds or fails. " +
                             "After Sensor Calibration is accomplished, the low verification procedure will be available.<br><br>" +
                             "NOTE: Remove the Air gas supply line from the rear of the NVENT VITA and ensure no pressure is in the system. <br><br>" +
                             "To verify the Inlet Air Measurement is accurate, the following steps need to be conducted:<br><br>" +
                             "1. Apply 30 PSI or below to the Air gas supply line on the rear panel of the NVENT VITA. <br>" +
                             "2. Push down on the left Verify button on the Verification Section.<br>" +
                             "3. The down arrow will change to green to indicate that the measurement has been reached and high verification procedure will be available.<br>" +
                             "4. Apply 31 PSI or above to the Air gas supply line on the rear panel of the NVENT VITA. <br>" +
                             "5. Push down on the right Verify button on the Verification Section.<br>" +
                             "6. The up arrow will change to green to indicate that the measurement has been reached."

    CalibrationHelpBox
    {
        id: helpBox
        titleText: "Calibration"
        helpText: airText
    }

    WarningBanner
    {
        id: warningBanner
        anchors.horizontalCenter: parent.horizontalCenter
        y: 0
        warnings: warning_manager.displayWarnings
        visible: warnings.length > 0
        popupStack: popupStack
    }
}
