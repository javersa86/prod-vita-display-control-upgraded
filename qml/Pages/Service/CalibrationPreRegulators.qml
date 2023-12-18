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

    property bool airState: true
    property bool o2State: true

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
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
                text: "Pre Regulators"
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
            id: airBox
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.left: parent.left
            anchors.leftMargin: 60
            color: Style.transparent

            Text {
                id: airTitle
                text: "Air"
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            StartButton
            {
                id: airButton
                anchors.top: airTitle.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: airState

                onClicked:
                {
                    airState = false
                    backend.updateDPRStates(2);
                }
            }

            VerifyButton
            {
                id: airCancel
                anchors.top: airButton.bottom
                anchors.topMargin: 36
                anchors.horizontalCenter: airButton.horizontalCenter
                enabled: !airState
                confirmState: true

                onClicked:
                {
                    airState = true
                    backend.regulatorConfirmation(1,2)
                }
            }
        }

        Rectangle
        {
            id: o2Box
            width: parent.width * .33
            height: 242

            anchors.top: textBox.bottom
            anchors.topMargin: 48
            anchors.right: parent.right
            anchors.rightMargin: 60
            color: Style.transparent

            Text {
                id: o2Title
                text: "O<sub>2</sub>"
                textFormat: Text.RichText
                font: Style.buttonFont
                color: Style.mode_label
                anchors.top: parent.top
                anchors.left: parent.left
            }

            StartButton
            {
                id: o2Button
                anchors.top: o2Title.bottom
                anchors.topMargin: 12
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: o2State

                onClicked:
                {
                    o2State = false
                    backend.updateDPRStates(3);
                }
            }

            VerifyButton
            {
                id: o2Cancel
                anchors.top: o2Button.bottom
                anchors.topMargin: 36
                anchors.horizontalCenter: o2Button.horizontalCenter
                enabled: !o2State
                confirmState: true

                onClicked:
                {
                    o2State = true
                    backend.regulatorConfirmation(0,3)
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
                backend.regulatorConfirmation(0,0);
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

    property string dpText: "The service technician will have the option to conduct Air and O<sub>2</sub> Pressure Regulator Calibration.<br><br>" +
                            "Conduct the following steps to calibrate the Air Regulator:<br><br>" +
                            "1. Connect air gas supply to the NVENT VITA.<br>" +
                            "2. Connect the Jet 1 tube to the Jet 1 Port of the NVENT VITA.<br>" +
                            "3. Connect the Jet 1 tube to the external pressure measuring device.<br>" +
                            "4. Press the Start Button to set the pneumatic setting for Driving Pressure to 48, open the valve of the Air Regulator, and enable the encoder knob.<br>" +
                            "5. The pressure should read 48 PSI on the Fluke.<br>" +
                            "6. Press down on the knob on the front panel of the NVENT VITA to relief the pressure.<br>" +
                            "8. The pressure should read 48 PSI after the pressure is relieved.<br>" +
                            "9. Press the Confirm button to confirm the success of the calibration procedure.<br><br>" +
                            "Conduct the following steps to calibrate the O<sub>2</sub> Pressure Regulator:<br><br>" +
                            "1. Connect air gas supply to the NVENT VITA.<br>" +
                            "2. Connect the Jet 1 tube to the Jet 1 Port of the NVENT VITA.<br>" +
                            "3. Connect the Jet 1 tube to the external pressure measuring device.<br>" +
                            "4. Press the Start Button to set the pneumatic setting for Driving Pressure to 48, open the valve of the O<sub>2</sub> Regulator, and enable the encoder knob.<br>" +
                            "5. The pressure should read 48 PSI on the Fluke.<br>" +
                            "6. Press down on the knob on the front panel of the NVENT VITA to relief the pressure.<br>" +
                            "8. The pressure should read 48 PSI after the pressure is relieved.<br>" +
                            "9. Press the Confirm button to confirm the success of the calibration procedure."

    CalibrationHelpBox
    {
        id: helpBox
        titleText: "Calibration"
        helpText: dpText
    }
}
