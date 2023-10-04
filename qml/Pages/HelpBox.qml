import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "DehumidificationDisconnection"
    property alias titleText: title.text
    property alias helpText: help.text

    property StackView popupStack

    signal disconnected()

    Component.onCompleted:
    {
        help_box.state = "moveIn"
    }

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    SlidingBox
    {
        id: help_box

        width: .7 * background.width
        height: .7 * background.height

        startX: background.width / 2 - width / 2
        desiredX: startX
        startY: - height
        desiredY: .33 * background.height - .33 * height

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Text
        {
            id: title
            textFormat: Text.RichText
            font: Style.buttonFont
            color: Style.general_set_display
            x: help_box.leftPadding
            y: help_box.topPadding
        }

        Item {
            x: help_box.leftPadding
            y: help_box.topPadding + title.height + .05 * help_box.height

            Flickable {
                id: frame

                width: help_box.width - help_box.leftPadding * 2
                height: 320
                anchors.left: parent.left
                anchors.top: parent.top
                contentHeight: help.height

                boundsBehavior: Flickable.StopAtBounds

                clip: true

                ScrollBar.vertical:  ScrollBar {
                    id: vbar
                    active: true
                    policy: ScrollBar.AsNeeded
                    hoverEnabled: true
                    visible: help.height > 320

                    contentItem: Rectangle
                    {
                        implicitWidth: 32
                        radius: width / 2
                        color: vbar.pressed ? Style.numeric_ui_unit : Style.primary_light
                    }
                }

                Text {
                    id: help
                    width: 740
                    font: Style.numberButtonFont
                    color: Style.primary_light_disabled
                    wrapMode: Text.Wrap
                    textFormat: Text.RichText
                    lineHeight: 1.5
                }
            }
        }

        Rectangle
        {
            id: close_button

            height: 50
            width: help_box.width * .16
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            x: parent.width - width - 15
            y: parent.height - height - 15
            radius: 24

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
                anchors.verticalCenter: close_button.verticalCenter
                anchors.horizontalCenter: close_button.horizontalCenter
                leftPadding: .3 * close_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                pressAndHoldInterval: 225
                onPressAndHold: {
                    close_button.color = Style.primary_light_disabled
                    close_button.delay(50)
                }
                anchors.fill: close_button
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
                    popupStack.helpBoxState = 0
                    close_button.clicked()
                    close_button.color = Style.primary_light_selected
                    timer.stop()
                }
            }

            Rectangle
            {
                id: closeIconBackground
                height: close_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: close_button.verticalCenter
                radius: .5 * height
                color: Style.primary_light

            }

            Item {
                id: closeIcon
                height: close_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: close_button.verticalCenter
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
