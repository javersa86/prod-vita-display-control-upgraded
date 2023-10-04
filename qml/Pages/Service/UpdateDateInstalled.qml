import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property string dateStr
    property StackView popupStack
    property int stateVal: 1

    signal dateSignal(string date)

    MouseArea
    {
        anchors.fill: parent
    }

    Connections {
        target: maintenance_manager

        onValidation:
        {
            if (!value)
            {
                incorrectText.visible = true
                timer.start();
                return;
            }

            dateSignal(monthText.text + "/" + dayText.text + "/" + yearText.text)
        }
    }

    Connections {
        target: datePad

        onAddSignal: {
            if (stateVal == 1)
            {
                if (monthText.index != 2)
                {
                    monthText.text = monthText.text.slice(0, monthText.index) + val.toString() + monthText.text.slice(monthText.index + 1, 2)
                    monthText.index = monthText.index + 1
                    monthText.cursorPosition = monthText.index
                }

            }
            else if (stateVal == 2)
            {
                if (dayText.index != 2)
                {
                    dayText.text = dayText.text.slice(0, dayText.index) + val.toString() + dayText.text.slice(dayText.index + 1, 2)
                    dayText.index = dayText.index + 1
                    dayText.cursorPosition = dayText.index
                }
            }
            else if (stateVal == 3)
            {
                if (yearText.index != 4)
                {
                    yearText.text = yearText.text.slice(0, yearText.index) + val.toString() + yearText.text.slice(yearText.index + 1, 4)
                    yearText.index = yearText.index + 1
                    yearText.cursorPosition = yearText.index
                }
            }
        }

        onClearSignal:
        {
            if (stateVal == 1)
            {
                monthText.text = "**"
                monthText.index = 0
                monthText.cursorPosition = 0
            }
            else if (stateVal == 2)
            {
                dayText.text = "**"
                dayText.index = 0
                dayText.cursorPosition = 0
            }
            else if (stateVal == 3)
            {
                yearText.text = "****"
                yearText.index = 0
                yearText.cursorPosition = 0
            }
        }
    }

    Connections
    {
        target: knob

        onButtonPush:
        {
            if (stateVal == 1)
            {
                monthBox.border.color = Style.unclickable_border
                monthText.cursorVisible = false

                dayBox.border.color = Style.general_set_display
                dayText.cursorVisible = true

                yearBox.border.color = Style.unclickable_border
                yearText.cursorVisible = false

                root.stateVal = 2
            }
            else if (stateVal == 2)
            {
                monthBox.border.color = Style.unclickable_border
                monthText.cursorVisible = false

                dayBox.border.color = Style.unclickable_border
                dayText.cursorVisible = false

                yearBox.border.color = Style.general_set_display
                yearText.cursorVisible = true

                root.stateVal = 3
            }
            else if (stateVal == 3)
            {
                monthBox.border.color = Style.general_set_display
                monthText.cursorVisible = true

                dayBox.border.color = Style.unclickable_border
                dayText.cursorVisible = false

                yearBox.border.color = Style.unclickable_border
                yearText.cursorVisible = false
                root.stateVal = 1
            }
        }

        onEncoderIncrement:
        {
            var valueText;
            var value;
            var tmp;
            if (stateVal == 1)
            {
                tmp = monthText.text.indexOf("*");
                if (tmp === -1)
                {
                    value = parseInt(monthText.text)
                }
                else
                {
                    valueText = monthText.text.slice(0,tmp);
                    if (valueText.length === 0)
                    {
                        valueText = "01"
                    }

                    value = parseInt(valueText);
                }

                if (encoderVal === 1)
                {
                    if (value >= 12)
                    {
                        monthText.text = "12"
                        monthText.index = 2
                        monthText.cursorPosition = 2
                        return
                    }
                    else
                    {
                        value = value + 1
                    }
                }
                else
                {
                    if (value > 12)
                    {
                        monthText.text = "12"
                        monthText.index = 2
                        monthText.cursorPosition = 2
                        return
                    }
                    else if (value <= 1)
                    {
                        monthText.text = "01"
                        monthText.index = 2
                        monthText.cursorPosition = 2
                        return
                    }
                    else
                    {
                        value = value - 1
                    }
                }

                if (value < 10)
                {
                    monthText.text = "0" + value
                }
                else
                {
                    monthText.text = value
                }
                monthText.index = 2
                monthText.cursorPosition = 2
            }
            else if (stateVal == 2)
            {
                tmp = dayText.text.indexOf("*");
                if (tmp === -1)
                {
                    value = parseInt(dayText.text)
                }
                else
                {
                    valueText = dayText.text.slice(0,tmp);
                    if (valueText.length === 0)
                    {
                        valueText = "01"
                    }
                    value = parseInt(valueText);
                }

                if (encoderVal === 1)
                {
                    if (value >= 31)
                    {
                        dayText.text = "31"
                        dayText.index = 2
                        dayText.cursorPosition = 2
                        return
                    }
                    else
                    {
                        value = value + 1
                    }
                }
                else
                {
                    if (value > 31)
                    {
                        dayText.text = "31"
                        dayText.index = 2
                        dayText.cursorPosition = 2
                        return
                    }
                    else if (value <= 1)
                    {
                        dayText.text = "01"
                        dayText.index = 2
                        dayText.cursorPosition = 2
                        return
                    }
                    else
                    {
                        value = value - 1
                    }
                }

                if (value < 10)
                {
                    dayText.text = "0" + value
                }
                else
                {
                    dayText.text = value
                }
                dayText.index = 2
                dayText.cursorPosition = 2
            }
            else if (stateVal == 3)
            {
                tmp = yearText.text.indexOf("*");
                if (tmp === -1)
                {
                    value = parseInt(yearText.text)
                }
                else
                {
                    valueText = yearText.text.slice(0,tmp);
                    if (valueText.length === 0)
                    {
                        valueText = "01"
                    }
                    value = parseInt(valueText);
                }

                if (encoderVal === 1)
                {
                    value = value + 1
                }
                else
                {
                    if (value <= 0)
                    {
                        yearText.text = "0000"
                        yearText.index = 4
                        yearText.cursorPosition = 4
                        return
                    }
                    value = value - 1
                }

                if (value < 10)
                {
                    yearText.text = "000" + value
                }
                else if (value < 100)
                {
                    yearText.text = "00" + value
                }
                else if (value < 1000)
                {
                    yearText.text = "0" + value
                }
                else
                {
                    yearText.text = value
                }
                yearText.index = 4
                yearText.cursorPosition = 4
            }
        }
    }

    Component.onCompleted:   backend.setMode(ID.LISTENING_KNOB,1)
    Component.onDestruction: backend.setMode(ID.LISTENING_KNOB,0)

    Rectangle
    {
        id: confirmBox
        height: 747
        width: 602
        color: Style.primary_dark
        border.color: Style.general_set_display
        border.width: 2

        anchors.centerIn: parent

        Text
        {
            id: title
            text: "Change Replacement Date"
            font: Style.settingPageTitle
            color: Style.primary_light
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 60
        }

        Rectangle
        {
            id: dateBox
            width: 294
            height: 84
            color: Style.primary_dark

            anchors.top: title.bottom
            anchors.topMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle
            {
                id: monthBox

                color: Style.unclickable_border
                border.color: Style.general_set_display
                border.width: 2

                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 4


                TextEdit {
                    id: monthText
                    text: dateStr.slice(0,2)
                    color:Style.primary_light
                    font:Style.settingPageTitle
                    anchors.centerIn: parent

                    textFormat: TextEdit.PlainText
                    cursorPosition: monthText.text.length
                    cursorVisible: true

                    property int index: 2
                }

                MouseArea
                {
                    id: monthMouseArea
                    anchors.fill: parent

                    onClicked:
                    {
                        monthBox.border.color = Style.general_set_display
                        monthText.cursorVisible = true

                        dayBox.border.color = Style.unclickable_border
                        dayText.cursorVisible = false

                        yearBox.border.color = Style.unclickable_border
                        yearText.cursorVisible = false
                        root.stateVal = 1

                    }
                }
            }
            Rectangle
            {
                id: dayBox

                color: Style.unclickable_border
                border.color: Style.unclickable_border
                border.width: 2

                width: 80
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: monthBox.right
                anchors.leftMargin: 4

                TextEdit {
                    id: dayText
                    text: dateStr.slice(3,5)
                    color:Style.primary_light
                    font:Style.settingPageTitle
                    anchors.centerIn: parent

                    textFormat: TextEdit.PlainText
                    cursorPosition: dayText.text.length
                    cursorVisible: false

                    property int index: 2

                }

                MouseArea
                {
                    id: dayMouseArea
                    anchors.fill: parent

                    onClicked:
                    {
                        monthBox.border.color = Style.unclickable_border
                        monthText.cursorVisible = false

                        dayBox.border.color = Style.general_set_display
                        dayText.cursorVisible = true

                        yearBox.border.color = Style.unclickable_border
                        yearText.cursorVisible = false

                        root.stateVal = 2
                    }
                }
            }

            Rectangle
            {
                id: yearBox

                color: Style.unclickable_border
                border.color: Style.unclickable_border
                border.width: 2

                width: 122
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: dayBox.right
                anchors.leftMargin: 4

                TextEdit {
                    id: yearText
                    text: dateStr.slice(6,10)
                    color:Style.primary_light
                    font:Style.settingPageTitle
                    anchors.centerIn: parent

                    textFormat: TextEdit.PlainText
                    cursorPosition: yearText.text.length
                    cursorVisible: false

                    property int index: 4
                }

                MouseArea
                {
                    id: yearMouseArea
                    anchors.fill: parent

                    onClicked:
                    {
                        monthBox.border.color = Style.unclickable_border
                        monthText.cursorVisible = false

                        dayBox.border.color = Style.unclickable_border
                        dayText.cursorVisible = false

                        yearBox.border.color = Style.general_set_display
                        yearText.cursorVisible = true

                        root.stateVal = 3
                    }
                }
            }
        }

        DatePad {
            id: datePad

            anchors.top: dateBox.bottom
            anchors.topMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: incorrectText
            text: "Date does not exist."
            color: Style.primary_light
            font: Style.buttonFont
            opacity: .7
            anchors.top: datePad.bottom
            anchors.topMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter
            visible: false
        }
        Timer {
            id: timer
            repeat: false
            interval: 5000
            onTriggered: {
                incorrectText.visible = false
                timer.stop()
            }
        }

        ContinueButton
        {
            id: continueButton

            anchors.bottom: parent.bottom
            anchors.right: parent.right

            onClicked:
            {
                maintenance_manager.isValid(monthText.text,dayText.text,yearText.text)
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
            title: "Back"

            serviceState: true
            height: 48
            width: 120

            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onClicked:
            {
                popupStack.pop()
            }
        }
    }
}
