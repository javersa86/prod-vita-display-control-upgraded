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
    property string timeStr
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

        onButtonPush:
        {
            if (hourBox.border.color == Style.general_set_display)
            {
                hourBox.border.color = Style.unclickable_border
                minuteBox.border.color = Style.general_set_display
                shiftBox.border.color = Style.unclickable_border
            }
            else if (minuteBox.border.color == Style.general_set_display)
            {
                hourBox.border.color = Style.unclickable_border
                minuteBox.border.color = Style.unclickable_border
                shiftBox.border.color = Style.general_set_display
            }
            else if (shiftBox.border.color == Style.general_set_display)
            {
                hourBox.border.color = Style.general_set_display
                minuteBox.border.color = Style.unclickable_border
                shiftBox.border.color = Style.unclickable_border
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
            text: "Maintenance: New Time"
            font: Style.settingPageTitle
            color: Style.primary_light
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 16
        }

        Rectangle
        {
            id: timeBox
            width: 252
            height: 84
            color: Style.primary_dark

            anchors.top: title.bottom
            anchors.topMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle
            {
                id: hourBox

                color: Style.unclickable_border
                border.color: Style.general_set_display
                border.width: 2

                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 4

                Text
                {
                    id: hourText
                    text: timeStr.split(":")[0]
                    color:Style.primary_light
                    font:Style.settingPageTitle
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        hourBox.border.color = Style.general_set_display
                        minuteBox.border.color = Style.unclickable_border
                        shiftBox.border.color = Style.unclickable_border
                    }
                }
            }

            Rectangle
            {
                id: minuteBox

                color: Style.unclickable_border
                border.color: Style.unclickable_border
                border.width: 2

                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: hourBox.right
                anchors.leftMargin: 4

                Text
                {
                    id: minuteText
                    text: timeStr.split(":")[1]
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        hourBox.border.color = Style.unclickable_border
                        minuteBox.border.color = Style.general_set_display
                        shiftBox.border.color = Style.unclickable_border
                    }
                }
            }

            Rectangle
            {
                id: shiftBox

                color: Style.unclickable_border
                border.color: Style.unclickable_border
                border.width: 2

                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: minuteBox.right
                anchors.leftMargin: 4

                Text
                {
                    id: shiftText
                    text: timeStr.split(":")[2].split(" ")[1]
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        hourBox.border.color = Style.unclickable_border
                        minuteBox.border.color = Style.unclickable_border
                        shiftBox.border.color = Style.general_set_display
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
                if (hourBox.border.color == Style.general_set_display)
                {
                    if (hourText.text == "12")
                    {
                        hourText.text = "01"
                    }
                    else
                    {
                        if ((Number(hourText.text) + 1) < 10)
                        {
                            hourText.text = "0" + (Number(hourText.text) + 1)
                        }
                        else
                        {
                            hourText.text = (Number(hourText.text) + 1)
                        }
                    }
                }
                else if (minuteBox.border.color == Style.general_set_display)
                {
                    if (minuteText.text == "59")
                    {
                        minuteText.text = "00"
                    }
                    else
                    {
                        if ((Number(minuteText.text) + 1) < 10)
                        {
                            minuteText.text = "0" + (Number(minuteText.text) + 1)
                        }
                        else
                        {
                            minuteText.text = (Number(minuteText.text) + 1)
                        }
                    }
                }
                else if (shiftBox.border.color == Style.general_set_display)
                {
                    if (shiftText.text == "AM")
                    {
                        shiftText.text = "PM"
                    }
                    else
                    {
                        shiftText.text = "AM"
                    }
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
                if (hourBox.border.color == Style.general_set_display)
                {
                    if (hourText.text == "01")
                    {
                        hourText.text = "12"
                    }
                    else
                    {
                        if ((Number(hourText.text) - 1) < 10)
                        {
                            hourText.text = "0" + (Number(hourText.text) - 1)
                        }
                        else
                        {
                            hourText.text = (Number(hourText.text) - 1)
                        }
                    }
                }
                else if (minuteBox.border.color == Style.general_set_display)
                {
                    if (minuteText.text == "00")
                    {
                        minuteText.text = "59"
                    }
                    else
                    {
                        if ((Number(minuteText.text) - 1) < 10)
                        {
                            minuteText.text = "0" + (Number(minuteText.text) - 1)
                        }
                        else
                        {
                            minuteText.text = (Number(minuteText.text) - 1)
                        }
                    }
                }
                else if (shiftBox.border.color == Style.general_set_display)
                {
                    if (shiftText.text == "AM")
                    {
                        shiftText.text = "PM"
                    }
                    else
                    {
                        shiftText.text = "AM"
                    }
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
                time_manager.setCurrentTime(hourText.text,minuteText.text,shiftText.text)
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

        SettingOptionsButton
        {
            id: prevButton
            title: "Prev"

            serviceState: true
            height: 48
            width: 120

            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onClicked:
            {
                if (shiftBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.unclickable_border
                    minuteBox.border.color = Style.general_set_display
                    shiftBox.border.color = Style.unclickable_border
                }
                else if (minuteBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.general_set_display
                    minuteBox.border.color = Style.unclickable_border
                    shiftBox.border.color = Style.unclickable_border
                }
                else if (hourBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.unclickable_border
                    minuteBox.border.color = Style.unclickable_border
                    shiftBox.border.color = Style.general_set_display
                }
            }
        }

        SettingOptionsButton
        {
            id: nextButton
            title: "Next"

            serviceState: true
            height: 48
            width: 120

            anchors.left: prevButton.right
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onClicked:
            {
                if (hourBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.unclickable_border
                    minuteBox.border.color = Style.general_set_display
                    shiftBox.border.color = Style.unclickable_border
                }
                else if (minuteBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.unclickable_border
                    minuteBox.border.color = Style.unclickable_border
                    shiftBox.border.color = Style.general_set_display
                }
                else if (shiftBox.border.color == Style.general_set_display)
                {
                    hourBox.border.color = Style.general_set_display
                    minuteBox.border.color = Style.unclickable_border
                    shiftBox.border.color = Style.unclickable_border
                }
            }
        }
    }
}
