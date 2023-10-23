import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import NotificationIndex 1.0
import IDs 1.0

Rectangle{
    id: root
    color: Style.transparent

    property int warningClass
    property int warningBehavior
    property bool warningActive
    property color warningColor
    property int numActiveWarnings
    property string title
    property string description
    property int warningID
    property string clearText
    property int warningIndex

    property bool rounded

    property StackView popupStack

    property bool warningExpanded

    property bool laserMinState: false
    property bool laserMinReached: false

    onLaserMinStateChanged:
    {
        if (!laserMinState)
        {
            limitedO2Timer.stop()
            laserText.limitedO2Seconds = 45;
        }
    }

    Connections
    {
        target: state_manager

        onLimitedO2State:
        {
            if (warningID == 52) //47
            {
                if (stateVal === 2)
                {
                    console.log("At min")
                    if (!limitedO2Timer.running && !laserMinState)
                    {
                        console.log("At min")
                        root.title = "Limited O<sub>2</sub> Prepping at 21%";
                        laserMinState = true;
                        laserText.limitedO2Seconds = 45;
                        limitedO2Timer.start();
                    }
                }
                else if (stateVal === 3)
                {
                    console.log("To Set");
                    laserMinState = true;
                    laserMinReached = true;
                    limitedO2Timer.stop();
                    root.title = "Limited O<sub>2</sub> Prepping to " + state_manager.o2 + "%";
                }
                else if (stateVal === 4)
                {
                    console.log("Safe");
                    laserMinState = true;
                    laserMinReached = true;
                    limitedO2Timer.stop();
                    root.title = "Limited O<sub>2</sub> Safe";
                }
            }
        }

        onOxygenAdjustmentSignal:
        {
            laserMinState = false
            laserMinReached = false
        }
    }

    Rectangle{
        visible: rounded
        id: roundedBackground
        radius: 16
        color: warningColor
        anchors.fill:parent
    }

    Rectangle{
        id: sharpBackground
        visible: rounded
        height: roundedBackground.radius
        anchors.top: roundedBackground.top
        anchors.left: roundedBackground.left
        anchors.right: roundedBackground.right
        color: warningColor
    }

    Rectangle
    {
        id: expandedBackground
        color: warningColor
        anchors.fill:parent
        visible: !rounded
    }

    Text {
        textFormat: Text.RichText
        font: Style.warningTitle
        x: 91
        anchors.verticalCenter: parent.verticalCenter
        text: title
        color: Style.primary_light
        width: .4 * parent.width
        maximumLineCount: 2
        wrapMode: Text.WordWrap
    }

    Text {
        id: calibrationTimeText
        text: o2CalManager.calibrationProgressTime
        textFormat: Text.RichText
        font: Style.warningTitle
        x: 91 + (.4 * parent.width) + 16
        anchors.verticalCenter: parent.verticalCenter
        color: Style.primary_light
        visible: warningID == 70 || warningID == 71
    }

    Text {
        id: laserText
        text: "00" + ":" + prependZero(limitedO2Seconds)
        textFormat: Text.RichText
        font: Style.warningTitle
        x: 91 + (.4 * parent.width) + 16
        anchors.verticalCenter: parent.verticalCenter
        color: Style.primary_light
        visible: (warningID == 52 && laserMinState) && !laserMinReached

        property int limitedO2Seconds: 45

        function prependZero(num)
        {
            if(num < 10)
            {
                return String("0" + num).slice(-2);
            }
            else return num
        }
    }

    Timer {
        id: limitedO2Timer
        repeat: true
        running: false
        interval: 1000

        onTriggered:
        {
            laserText.limitedO2Seconds = laserText.limitedO2Seconds - 1;
            if (laserText.limitedO2Seconds == 0)
            {
                laserMinReached = true
                limitedO2Timer.stop()
            }
        }
    }

    Rectangle {
        id: silenceButton
        property int warningBehavior: warning_manager.getWarningBehavior(warningID)
        border.width: 2
        radius: 24
        height: 48
        width: 150
        x: root.width - width - .02 * root.width - 400 - (warningExpanded ? 39 : 0)
        anchors.verticalCenter: clearButton.verticalCenter
        color: Style.primary_light_selected
        border.color: enabled ? Style.primary_light : Style.primary_light_disabled
        enabled: state_manager.alarm_sounding
        visible: (state_manager.notification_vector[Index.ALARM_SILENCE_TIMER] || state_manager.alarm_sounding) && (warningIndex == 0)

        Timer {
            id: timer2
            repeat: false
            onTriggered:
            {
                backend.setMode(ID.ALARM_SOUNDING, 0)
                silenceButton.color = Style.primary_light_selected
                timer2.stop()
            }
        }

        function delay(delayTime)
        {
            timer2.interval = delayTime;
            timer2.start();
        }

        MouseArea {
            id: silenceMouseArea
            pressAndHoldInterval: 225
            anchors.fill:parent
            onPressAndHold: {
                silenceButton.color = Style.primary_light_disabled
                silenceButton.delay(50)
            }
        }

        Rectangle{
            anchors.centerIn: parent
            height: parent.height
            width: parent.width - 50
            color: Style.transparent

            TextMetrics {
                    id:     silence_metrics
                    font:   silenceText.font
                    text:   silenceText.text
                }

            Text{
                id: silenceText
                text: state_manager.notification_vector[Index.ALARM_SILENCE_TIMER] && !state_manager.alarm_sounding ? timerString : "SILENCE"
                anchors.verticalCenter: parent.verticalCenter
                font: Style.buttonFont
                anchors.horizontalCenter: parent.horizontalCenter
                color: silenceButton.enabled ? Style.primary_light : Style.primary_light_disabled

                property string timerString: prependZero(Math.floor(state_manager.notification_vector[Index.ALARM_SILENCE_TIMER] / 60)) + ":" +
                                             prependZero(state_manager.notification_vector[Index.ALARM_SILENCE_TIMER] % 60)

                function prependZero(num)
                {
                    if(num < 10)
                    {
                        return String("0" + num).slice(-2);
                    }
                    else return num
                }

            }
        }
    }

    Rectangle {
        id: troubleshootButton
        anchors.verticalCenter: clearButton.verticalCenter
        border.width: 2
        radius: 24
        height: 48
        width: troubleshooting_metrics.tightBoundingRect.width + 90
        x: warningBehavior == 0 ?
               parent.width - width - .02 * parent.width - (warningExpanded ? 39 : 0) :
               parent.width - (parent.width - clearButton.x - (warningExpanded ? 39 : 0)) -  width - .02 * parent.width - (warningExpanded ? 39 : 0)
        color: Style.primary_light_selected
        border.color: enabled ? Style.primary_light : Style.primary_light_disabled

        Timer {
            id: timer
            repeat: false
            onTriggered:
            {
                popupStack.troubleshoot(title, "Troubleshoot Alarm", warning_manager.getWarningInformation(warningID).length, warning_manager.getWarningInformation(warningID),
                                        warning_manager.getWarningColor(warningID))
                troubleshootButton.color = Style.primary_light_selected
                timer.stop()
            }
        }

        function delay(delayTime)
        {
            timer.interval = delayTime;
            timer.start();
        }

        MouseArea {
            id: troubleshootMouseArea
            pressAndHoldInterval: 225
            anchors.fill:parent

            onPressAndHold:{
                troubleshootButton.color = Style.primary_light_disabled
                troubleshootButton.delay(50)
            }
        }

        Rectangle{
            anchors.centerIn: parent
            height: parent.height
            width: parent.width - 50
            color: Style.transparent
            Text{
                text: "1"
                anchors.verticalCenter: parent.verticalCenter
                font: Style.numberButtonFont
                anchors.left: parent.left
                color: troubleshootButton.enabled ? Style.primary_light : Style.primary_light_disabled

            }

            TextMetrics {
                    id:     troubleshooting_metrics
                    font:   troubleshootText.font
                    text:   troubleshootText.text
                }

            Text{
                id: troubleshootText
                text: warningClass == 2 ? "INFO" : "TROUBLESHOOT"
                anchors.verticalCenter: parent.verticalCenter
                font: Style.buttonFont
                anchors.right: parent.right
                color: troubleshootButton.enabled ? Style.primary_light : Style.primary_light_disabled

            }
        }
    }

    Rectangle {
        id: clearButton
        enabled: (warningBehavior == 2) ? (! warningActive) : true
        border.width: 2
        radius: 24
        height: 48
        width: 137
        x: parent.width - width - .02 * parent.width - (warningExpanded ? 39 : 0)
        y: parent.height *.5 - .5 * height
        visible: warningBehavior != 0
        color: Style.primary_light_selected
        border.color: enabled ? Style.primary_light : Style.primary_light_disabled

        Component.onCompleted: clearMouseArea.pressAndHoldInterval = 225

        Timer {
            id: timer1
            repeat: false
            onTriggered:
            {
                backend.initClearAlarm(warningID)
                clearButton.color = Style.primary_light_selected
                timer1.stop()
            }
        }

        function delay1(delayTime)
        {
            timer1.interval = delayTime;
            timer1.start();
        }

        MouseArea {
            enabled: true
            id: clearMouseArea
            anchors.fill:parent

            onPressAndHold:{
                clearButton.color = Style.primary_light_disabled
                clearButton.delay1(50)
            }
        }

        Rectangle{
            anchors.centerIn: parent
            height: parent.height
            width: parent.width - 50
            color: Style.transparent
            Text{
                text: "2"
                anchors.verticalCenter: parent.verticalCenter
                font: Style.numberButtonFont
                anchors.left: parent.left
                color: clearButton.enabled ? Style.primary_light : Style.primary_light_disabled
            }

            Text{
                text: root.clearText
                anchors.verticalCenter: parent.verticalCenter
                font: Style.buttonFont
                anchors.right: parent.right
                color: clearButton.enabled ? Style.primary_light : Style.primary_light_disabled

            }
        }
    }
}
