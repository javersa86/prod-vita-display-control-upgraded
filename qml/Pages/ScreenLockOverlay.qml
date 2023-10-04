import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"
import IDs 1.0

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "ShutdownConfirmation"
    property int locked: state_manager.screen_lock_mode
    property int beginningKnobState

    property StackView popupStack

    MouseArea
    {
        anchors.fill:parent
        onPressed:
        {
            backend.setMode(ID.SCREEN_LOCK_TOUCHED_MODE, 1)
            noTouchReminder.opacity = 1
            noTouchTimer.stop()
        }

        onReleased:
        {
            backend.setMode(ID.SCREEN_LOCK_TOUCHED_MODE, 0)
            noTouchTimer.stop()
            noTouchTimer.start()
        }
    }

    Connections
    {
        target: backend

        onHmiButtonPressed:
        {
            if (id === 3)
            {
                wetScreenReminder.opacity = 1
                wetScreenTimer.stop()
                wetScreenTimer.start()
            }

            noTouchReminder.opacity = 1
            noTouchTimer.stop()
            noTouchTimer.start()
        }
    }

    Rectangle {
        id: noTouchReminder
        width: parent.width * .75
        height: 80
        color: Style.primary_dark
        border.width: 2
        border.color: Style.mode_active_warning
        y: .33 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 15
        opacity: 0
        OpacityAnimator{
            target: noTouchReminder
            id: animator
            from: 1;
            to: 0;
            duration: 1000
        }

        Text {
            text: "Screen lock mode is active. Press the dial to unlock and interact with the screen."
            anchors.centerIn: parent
            font: Style.warningTitle
            color: Style.mode_active_warning
        }

        Timer
        {
            id: noTouchTimer
            interval: 5000
            repeat: false
            onTriggered:
            {
                animator.start()
            }
        }
    }

    Rectangle {
        id: wetScreenReminder
        width: parent.width * .75
        height: 80
        color: Style.primary_dark
        border.width: 2
        border.color: Style.mode_active_warning
        y: noTouchReminder.y + noTouchReminder.height + 15
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 15
        opacity: 0
        OpacityAnimator {
            target: wetScreenReminder
            id: animator1
            from: 1;
            to: 0;
            duration: 1000
        }

        Text {
            text: "Moisture detected on panel. Please dry off screen."
            anchors.centerIn: parent
            font: Style.warningTitle
            color: Style.mode_active_warning
        }

        Timer
        {
            id: wetScreenTimer
            interval: 5000
            repeat: false
            onTriggered:
            {
                animator1.start()
            }
        }
    }

    onLockedChanged:
    {
        if(! locked)
        popupStack.unlock()
    }

    Component.onCompleted:
    {
        beginningKnobState = state_manager.listening_to_knob
        backend.setMode(ID.LISTENING_KNOB,0)
    }

    Component.onDestruction:
    {
        backend.setMode(ID.LISTENING_KNOB,beginningKnobState)
    }

    Rectangle {
        id: lockedDisplay
        width: .4 * parent.width
        height: .1 * width
        x: parent.width - width - .3 * height
        color: Style.transparent
        y: 15
        visible: state_manager.screen_lock_mode

        Rectangle
        {
            anchors.fill:parent
            color: Style.mode_active_warning
            radius: 8
        }

        Text {
            id: screenLockedText
            text: qsTr("Screen Locked. Press dial to unlock.")
            anchors.right: parent.right
            rightPadding: .05 * parent.width
            anchors.verticalCenter: parent.verticalCenter
            color:Style.primary_dark
            font: Style.warningTitle
            opacity: 1
        }

        Item {
            width: 40
            height: 40
            x: .05 * parent.width
            y: parent.height - height * 1.2

            Image {
                id: screenLockedIcon
                source: "../iconography/icon_40_lockscreen.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
            }

            ColorOverlay {
                anchors.fill: screenLockedIcon
                source: screenLockedIcon
                color: Style.primary_dark
            }
        }
    }
}
