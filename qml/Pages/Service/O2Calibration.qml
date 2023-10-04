/**
  * Update by Joseph Aversa
  *
  * Displays all the values for o2 calibration:
  * - Oxygen
  * - Current voltage
  * - current high value
  * - current low value
  * - current high voltage
  * - current low voltage
  * - last high value
  * - last low value
  * - last high voltage
  * - last low voltage
  *
  * Changed page to InteractiveKnobPage Page to utilize GenericDial object.
  *
  * Can now enable/disable knob.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"
import NotificationIndex 1.0
import IDs 1.0

InteractiveKnobPage{
    id: root_window
    color: Style.transparent
    property int o2CalSuccess: state_manager.o2_cal_success

    property int value: state_manager.getSettingValue(oxygen.id)
    property string unit: oxygen.unit
    property string title: oxygen.title
    property int settingID: oxygen.id
    property int min: oxygen.min
    property int max: state_manager.laser_mode ? state_manager.laserO2Limit : oxygen.max
    property int step: oxygen.step
    property int warningThreshold: oxygen.warningThreshold
    property StackView homeStack
    property StackView popupStack

    property bool startCheck: true


    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .75 * parent.height

        x: 100
        y: .2 * parent.height
        color: Style.transparent


        Rectangle
        {
            id: dataBox
            color: Style.transparent
            width: parent.width //469
            height: 216
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left

            Rectangle
            {
                id: lowVoltBox
                width: .5 * parent.width
                height: .5 * parent.height
                color: Style.transparent

                anchors.top: parent.top
                anchors.left: parent.left

                Text {
                    id: label1
                    text: "21% V"
                    color: Style.mode_inactive
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: lowVoltValue
                    text: o2CalManager.mostRecentVoltVal[0] + " mV"
                    font: Style.buttonFont
                    color: Style.primary_light
                    anchors.left: label1.right
                    anchors.leftMargin: 16 + 9.65625
                    anchors.verticalCenter: label1.verticalCenter
                }

                Text {
                    id: lowVoltTime
                    text: o2CalManager.mostRecentTimeStamp
                    font: Style.buttonFont
                    color: Style.mode_inactive
                    anchors.top: lowVoltValue.bottom
                    anchors.topMargin: 8
                    anchors.left: lowVoltValue.left
                    width: .5 * parent.width
                    wrapMode: Text.Wrap
                }
            }

            Rectangle
            {
                id: highVoltBox
                width: .5 * parent.width
                height: .5 * parent.height
                color: Style.transparent

                anchors.top: lowVoltBox.bottom
                anchors.left: parent.left

                Text {
                    id: label2
                    text: "100% V"
                    color: Style.mode_inactive
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: highVoltValue
                    text: o2CalManager.mostRecentVoltVal[1] + " mV"
                    font: Style.buttonFont
                    color: Style.primary_light
                    anchors.left: label2.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: label2.verticalCenter
                }

                Text {
                    id: highVoltTime
                    text: o2CalManager.mostRecentTimeStamp
                    font: Style.buttonFont
                    color: Style.mode_inactive
                    anchors.top: highVoltValue.bottom
                    anchors.topMargin: 8
                    anchors.left: highVoltValue.left
                    width: .5 * parent.width
                    wrapMode: Text.Wrap
                }
            }

            Rectangle
            {
                id: lastlowVoltBox
                width: .5 * parent.width
                height: .5 * parent.height
                color: Style.transparent

                anchors.top: parent.top
                anchors.right: parent.right

                Text {
                    id: label3
                    text: "Last 21% V"
                    color: Style.mode_inactive
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: lastlowVoltValue
                    text: o2CalManager.lastVoltVal[0] + " mV"
                    font: Style.buttonFont
                    color: Style.primary_light
                    anchors.left: label3.right
                    anchors.leftMargin: 16 + 9.65625
                    anchors.verticalCenter: label3.verticalCenter
                }

                Text {
                    id: lastlowVoltTime
                    text: o2CalManager.lastTimeStamp
                    font: Style.buttonFont
                    color: Style.mode_inactive
                    anchors.top: lastlowVoltValue.bottom
                    anchors.topMargin: 8
                    anchors.left: lastlowVoltValue.left
                    width: .5 * parent.width
                    wrapMode: Text.Wrap
                }
            }

            Rectangle
            {
                id: lasthighVoltBox
                width: .5 * parent.width
                height: .5 * parent.height
                color: Style.transparent

                anchors.top: lastlowVoltBox.bottom
                anchors.right: parent.right

                Text {
                    id: label4
                    text: "Last 100% V"
                    color: Style.mode_inactive
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: lasthighVoltValue
                    text: o2CalManager.lastVoltVal[1] + " mV"
                    font: Style.buttonFont
                    color: Style.primary_light
                    anchors.left: label4.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: label4.verticalCenter
                }

                Text {
                    id: lasthighVoltTime
                    text: o2CalManager.lastTimeStamp
                    font: Style.buttonFont
                    color: Style.mode_inactive
                    anchors.top: lasthighVoltValue.bottom
                    anchors.topMargin: 8
                    anchors.left: lasthighVoltValue.left
                    width: .5 * parent.width
                    wrapMode: Text.Wrap
                }
            }

        }

        Rectangle
        {
            id: currentValueBox

            width: 193
            height: 51
            color: Style.transparent

            anchors.top: dataBox.bottom
            anchors.topMargin: 60
            anchors.left: dataBox.left

            Text {
                id: currentValueText
                text: qsTr("Current")
                color: Style.mode_inactive
                font: Style.buttonFont
                anchors.left: currentValueBox.left
                anchors.verticalCenter: currentValueBox.verticalCenter
            }

            Rectangle
            {
                id: currentValueContainer

                width: 120
                height: 51
                color: Style.transparent

                border.color: Style.primary_light
                border.width: 2

                anchors.top: parent.top
                anchors.right: parent.right

                Text {
                    id: currentValueDisplay
                    text: state_manager.service_notification_vector[4].toFixed(3) + " mV"
                    font: Style.buttonFont
                    color: Style.primary_light
                    anchors.centerIn: parent
                }
            }
        }

        Rectangle
        {
            id:passfail

            anchors.left: currentValueBox.right
            anchors.leftMargin: 16
            anchors.verticalCenter: currentValueBox.verticalCenter

            width: 50
            height: 35.1
            visible: !state_manager.o2_cal_mode && o2CalManager.numO2CalVals > 0

            color:Style.transparent

            Image {
                id: passfailIcon
                source: root_window.o2CalSuccess ? "../../iconography/thumbs-up.svg" : "../../iconography/thumbs-down.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: 35.1
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
                x: .3 * parent.width
            }

            ColorOverlay {
                anchors.fill: passfailIcon
                source: passfailIcon
                color: root_window.o2CalSuccess ? Style.affirmative : Style.dissident
            }

            Text {
                id: passfailText
                text: root_window.o2CalSuccess ? qsTr("Passed") : qsTr("Failed")
                anchors.left:passfailIcon.right
                anchors.verticalCenter: passfailIcon.verticalCenter
                leftPadding: 5
                font:Style.buttonFont
                color: root_window.o2CalSuccess ? Style.affirmative : Style.dissident
            }
        }

        GenericDialMini
        {
            id: dial

            value: root_window.value
            unit: root_window.unit
            title: root_window.title
            settingID: root_window.settingID
            min: root_window.min
            max: root_window.max
            stack: root_window.homeStack
            step: root_window.step
            popupStack: root_window.popupStack

            anchors.top: dataBox.bottom
            anchors.topMargin: 24
            anchors.left: passfail.right
            anchors.leftMargin: 120

            onDialSignal:
            {
                backend.receiveSettingsUpdate(root_window.settingID,dial.value)
            }
        }

        Rectangle
        {
            id: calibrateButton
            width: 184
            height: 42
            color: enabled ? Style.affirmative : Style.affirmative_transluscent
            radius: .5*height
            enabled: !state_manager.oxygenControlState && !state_manager.o2_cal_mode && !state_manager.laser_mode

            anchors.left: dial.right
            anchors.leftMargin: 172
            anchors.verticalCenter: passfail.verticalCenter

            MouseArea
            {
                id: mouseArea

                anchors.fill: parent

                onClicked:
                {
                    o2CalManager.resetCalibration();
                    backend.setMode(8,1);
                }
            }

            Text {
                id: calibrateText
                text: qsTr("CALIBRATE")
                font: Style.buttonFont
                color:Style.primary_dark
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }
}
