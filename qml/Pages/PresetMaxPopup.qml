import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"
import SettingIndex 1.0

Rectangle {
    id: background
    color: Style.primary_dark_transluscent

    property StackView popupStack

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    Rectangle
    {
        id: confirm_box
        height: 240
        width: 640
        x: background.width / 2 - width / 2
        y: background.height / 3 - height / 2 + 100

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        Text
        {
            id: title
            text: "PRESET"
            font: Style.buttonFont
            color: Style.general_set_display
            x: 30
            y: 30
        }

        Text {
            id: subtitle
            text: "The number of presets is maxed at 12."
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            x: 30
            y: 30 + title.height
        }

        Rectangle
        {
            id: no_button

            height: 51.2
            width: noStr.contentWidth + closeIconBackground.width + 40
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16

            Text
            {
                id: noStr
                text: qsTr("CLOSE")
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
    }
}
