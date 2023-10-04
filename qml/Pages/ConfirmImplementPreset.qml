import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"
import SettingIndex 1.0

Rectangle{
    id: background
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property StackView homeStack
    property var settings

    property Item settingsComplete

    Component.onCompleted:
    {
        confirm_box.state = "moveIn"
    }

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    SlidingBox
    {
        id: confirm_box
        height: background.height / 2.5 + 200
        width: background.width / 2 + 200
        startX: background.width / 2 - width / 2
        desiredX: startX
        startY: - height
        desiredY: background.height / 3 - height / 2 + 100

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Text
        {
            id: title
            text: "PRESET"
            font: Style.buttonFont
            color: Style.general_set_display
            x: confirm_box.leftPadding
            y: confirm_box.topPadding
        }

        Text
        {
            id: disconnected_question
            text: !state_manager.ventilating && !state_manager.aux ? "Are you sure you would like to load this preset?" : "Stop Ventilating to Implement a Preset"
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: confirm_box.width - leftPadding * 2
            x: confirm_box.leftPadding
            y: confirm_box.topPadding + title.height
            wrapMode: Text.WordWrap
        }

        Text
        {
            id: explanation
            text: !state_manager.ventilating && !state_manager.aux ? "Confirm you would like to use preset:" : "Presets cannot be implemented while the system is jetting or while auxiliary flow is set to a value greater than 0."
            font: Style.numberButtonFont
            color: Style.primary_light_disabled
            width: confirm_box.width - confirm_box.leftPadding * 2
            x: confirm_box.leftPadding
            y: confirm_box.topPadding + title.height + disconnected_question.height + .025 * confirm_box.height
            wrapMode: Text.WordWrap
        }

        Text {
            id: orange_text
            text: "ORANGE: "
            font: Style.numberButtonFont
            color: Style.mode_active_warning
            anchors.top: explanation.bottom
            anchors.topMargin: 8
            anchors.left: settingsDisplay.left
            visible: !state_manager.ventilating && !state_manager.aux
        }

        Text {
            id: increased_text
            text: "Values increased from current settings."
            font: Style.numberButtonFont
            color: Style.primary_light_disabled
            wrapMode: Text.WordWrap
            anchors.top: explanation.bottom
            anchors.topMargin: 8
            anchors.left: orange_text.right
            anchors.leftMargin: 24
            visible: !state_manager.ventilating && !state_manager.aux
        }

        Text {
            id: blue_text
            text: "BLUE:   "
            font: Style.numberButtonFont
            color: Style.general_set_display
            anchors.top: orange_text.bottom
            anchors.left: settingsDisplay.left
            visible: !state_manager.ventilating && !state_manager.aux
        }

        Text {
            text: "Values decreased from current settings."
            font: Style.numberButtonFont
            color: Style.primary_light_disabled
            wrapMode: Text.WordWrap
            anchors.top: orange_text.bottom
            anchors.left: orange_text.right
            anchors.leftMargin: 24
            visible: !state_manager.ventilating && !state_manager.aux
        }

        PresetValueColumns {
            id: settingsDisplay

            anchors.horizontalCenter: parent.horizontalCenter
            y: 210

            settingNames: [
                "SP:",
                "PIP:",
                "IT:",
                "AUX:",
                "RATE:",
                "O2:",
                "HUM:",
                "DP:"
            ]
            oldSettings: [
                state_manager.sp1,
                state_manager.pip,
                state_manager.it1,
                state_manager.aux,
                state_manager.rate1,
                state_manager.o2,
                state_manager.hum1,
                state_manager.dp1
            ]
            newSettings: [
                settings[6],//sp
                settings[9],//pip
                settings[4],//it
                settings[10],//aux
                settings[2],//rate
                settings[8],//o2
                settings[11],//hum
                settings[0]//dp
            ]
        }

        Rectangle
        {
            id: no_button

            height: confirm_box.height * .16 - 32
            width: noStr.contentWidth + closeIconBackground.width + 40
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            x: confirm_box.leftPadding
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30

            Text
            {
                id: noStr
                text: !state_manager.ventilating && !state_manager.aux ? qsTr("NO") : qsTr("CLOSE")
                color: Style.primary_light
                anchors.verticalCenter: no_button.verticalCenter
                anchors.horizontalCenter: no_button.horizontalCenter
                leftPadding: .3 * no_button.width
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
                    background.popupStack.clear()
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
                    source: "../iconography/icon_40_close.svg"
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

        Rectangle
        {
            id: yes_button

            height: confirm_box.height * .16 - 32
            width: confirm_box.width * .16 - 16
            color: Style.affirmative
            border.width: 2
            radius: 24
            visible: !state_manager.ventilating && !state_manager.aux
            enabled: !state_manager.ventilating && !state_manager.aux

            x: confirm_box.width - width - confirm_box.leftPadding
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30

            Text
            {
                id: yesStr
                text: qsTr("YES")
                color: Style.primary_dark
                anchors.verticalCenter: yes_button.verticalCenter
                anchors.horizontalCenter: yes_button.horizontalCenter
                leftPadding: .3 * yes_button.width
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
                    homeStack.implementPreset(settings);
                    yes_button.color = Style.affirmative
                    timer1.stop()
                }
            }

            Item {
                id: checkIcon
                height: yes_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: yes_button.verticalCenter
                Image {
                    id: icon
                    source: "../iconography/icon_40_checkmark.svg"
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
