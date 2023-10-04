import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "ScreenlockConfirmation"
    property bool modeEnabled: state_manager.screen_lock_mode

    property StackView popupStack

    Component.onCompleted:
    {
        disconnection_confirm_box.state = "moveIn"
    }

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    SlidingBox
    {
        id: disconnection_confirm_box
        height: background.height / 2.5
        width: background.width / 2
        startX: background.width / 2 - width / 2
        desiredX: startX
        startY: - height
        desiredY: background.height / 3 - height / 2

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Text
        {
            id: title
            text: "LOCK SCREEN"
            font: Style.buttonFont
            color: Style.general_set_display
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding
        }

        Text
        {
            id: disconnected_question
            text: "To safely clean, lock your screen"
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: disconnection_confirm_box.width - leftPadding * 2
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding + title.height
            wrapMode: Text.WordWrap
        }

        Text
        {
            id: explanation
            text: "1. Press the green \"Lock Screen\" button below.\n2. Wipe screen.\n3. Press dial to unlock screen and resume use"
            lineHeight:2
            font: Style.buttonFont
            color: Style.primary_light_disabled
            width: disconnection_confirm_box.width - leftPadding * 2
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding + title.height + disconnected_question.height + .05 * disconnection_confirm_box.height
            wrapMode: Text.WordWrap
        }

        CancelButton
        {
            id: cancelButton
            onClicked:
            {
                background.popupStack.clear()
            }

            x: disconnection_confirm_box.leftPadding
            y: (disconnection_confirm_box.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2

        }



        Rectangle
        {
            id: yes_button

            height: disconnection_confirm_box.height * .16
            width: disconnection_confirm_box.width * .28
            color: Style.affirmative
            border.width: 2
            radius: 24

            x: disconnection_confirm_box.width - width - disconnection_confirm_box.leftPadding
            y: (disconnection_confirm_box.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2

            Text
            {
                id: yesStr
                text: qsTr("LOCK SCREEN")
                color: Style.primary_dark
                anchors.verticalCenter: yes_button.verticalCenter
                anchors.horizontalCenter: yes_button.horizontalCenter
                leftPadding: .2 * yes_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    yes_button.color = Style.affirmative_transluscent
                    yes_button.delay(50)
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
                    backend.setMode(3, true);
                    yes_button.color = Style.affirmative
                    timer1.stop()
                }
            }

            Item {
                id: lockIcon
                height: yes_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: yes_button.verticalCenter
                Image {
                    id: icon
                    source: "../iconography/icon_40_lockscreen.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: icon
                    source: icon
                    color: Style.primary_dark
                }
            }

        }
    }
}
