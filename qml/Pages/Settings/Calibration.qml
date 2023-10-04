import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.transparent
    property int o2CalSuccess: state_manager.o2_cal_success

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.8 * parent.height
        y: .1 * parent.height
        color: Style.transparent

        Rectangle
        {
            id: calibrateButton
            width: 184
            height: 42
            anchors.horizontalCenter: parent.horizontalCenter
            color: enabled ? Style.affirmative : Style.affirmative_transluscent
            radius: .5*height
            y: parent.height * .15 + height
            enabled: !state_manager.oxygenControlState && !state_manager.o2_cal_mode && !state_manager.laser_mode

            MouseArea
            {
                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    calibrateButton.delay(50)
                }
            }

            function delay(delayTime)
            {
                timer1.interval = delayTime;
                timer1.start();
            }

            Timer {
                id: timer1
                repeat: false
                onTriggered:
                {
                    o2CalManager.resetCalibration();
                    backend.setMode(8,1);
                    timer1.stop()
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

            ColorOverlay {
                anchors.fill: passfailIcon
                source: passfailIcon
                color: root_window.o2CalSuccess ? Style.affirmative : Style.dissident
            }

        }

        Text {
            id: date
            text: qsTr("Last Calibration: " + o2CalManager.mostRecentTimeStamp)
            anchors.horizontalCenter: calibrateButton.horizontalCenter
            anchors.top: calibrateButton.bottom
            anchors.topMargin: 50
            color: Style.mode_label
            font: Style.titleFont
            visible: o2CalManager.numO2CalVals > 0
        }

        Rectangle
        {
            id:passfail
            anchors.top: date.bottom
            anchors.horizontalCenter: date.horizontalCenter
            width: 150
            height: 150
            visible: !state_manager.o2_cal_mode && o2CalManager.numO2CalVals > 0

            color:Style.transparent

            Image {
                id: passfailIcon
                source: root_window.o2CalSuccess ? "../../iconography/thumbs-up.svg" : "../../iconography/thumbs-down.svg"
                sourceSize.width: width
                sourceSize.height: height
                height: parent.height * .3
                width: parent.height * .3
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

        Text {
            id: replacementText
            text: qsTr("To replace the Oxygen Sensor, refer to the user manual")
            color: Style.mode_label
            font: Style.settingPageTitle
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 50
        }
    }

    Item {
        id: valueHolder
        property string helpText: "In the event of a failed automatic O2 calibration or if an additional O2 calibration is needed, a manual O2 calibration should be performed. Prior to a manual O2 calibration being performed, ensure that the Air and Oxygen supply lines are connected to the machine and the source. Limited O2 mode cannot be utilized during an O2 calibration."
    }
}
