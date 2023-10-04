import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property alias titleStr: title.text
    property string timeZoneStr
    property StackView popupStack

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted: backend.setMode(ID.LISTENING_KNOB,1)
    Component.onDestruction: backend.setMode(ID.LISTENING_KNOB,0)

    Connections
    {
        target: knob

        onEncoderIncrement:
        {
            if (encoderVal === 1)
            {
                upButton.clicked()
            }
            else
            {
                downButton.clicked()
            }
        }
    }

    Rectangle
    {
        id: confirmBox
        height: 374
        width: 602
        color: Style.primary_dark
        border.color: Style.general_set_display
        border.width: 2
        anchors.centerIn: parent

        Text
        {
            id: title
            text: "Maintenance: New Time Zone"
            font: Style.settingPageTitle
            color: Style.primary_light
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 16
        }

        Rectangle
        {
            id: timeBox

            color: Style.unclickable_border
            border.color: Style.general_set_display
            border.width: 2

            width: 378
            height: 80
            anchors.top: title.bottom
            anchors.topMargin: 18
            anchors.horizontalCenter: parent.horizontalCenter

            TimeZoneText
            {
                id: timeText
                anchors.centerIn: parent

                Component.onCompleted:
                {
                    for (var i = 0; i < 12; i++)
                    {
                        if (timeZoneStr === timeText.utcTimeZones[i])
                        {
                            timeText.index = i
                        }
                    }
                }
            }
        }

        SettingOptionsButton
        {
            id: upButton
            title: "UP"
            width: 110

            y: timeBox.y + timeBox.height + 32
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 8

            onClicked:
            {
                if (timeText.index == 11)
                {
                    timeText.index = 0
                }
                else {
                    timeText.index = timeText.index + 1
                }
            }
        }
        SettingOptionsButton
        {
            id: downButton
            title: "DOWN"
            width: 110

            y: timeBox.y + timeBox.height + 32
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 8

            onClicked:
            {
                if (timeText.index == 0)
                {
                    timeText.index = 11
                }
                else {
                    timeText.index = timeText.index - 1
                }
            }
        }

        ContinueButton
        {
            id: continueButton

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            onClicked:
            {
                time_manager.updateDalyightSavingsForced(timeText.getDaylight())
                time_manager.setTimeZone(timeText.getAbbreviation(timeText.text))
                popupStack.clear()
            }
        }

        CancelButton
        {
            id: cancelButton

            anchors.right: continueButton.left
            anchors.rightMargin: 4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onClicked:
            {
                popupStack.clear()
            }
        }
    }
}
