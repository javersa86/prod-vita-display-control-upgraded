/**
  Pop up page to change date.

  Added features:

  Selecting month text shows DateMonthPad object to select months.
  Selecting year text shows DateYearPad object to enter year.
  Selecting day text when month text is February shows DateFebruaryDayPad to select day.
  Selecting day text when month text is February and year text is a leap year shows DateFebruaryLeapDayPad to select day.
  Selecting day text when month is a specific month shows DateOtherDayPad to select day.
  Otherwise, selecting day text shows DateDayPad to select day.

  Todays Date Button automatically changes date to today.

  Pressing Continue button will change date to what was entered.

  If popped up from Date & Time page, Continue Button will redirect to UpdateTime.qml

  Update from Joseph Aversa
  Created signals to maintenance page to change dates.
  Day changes if date doesn't exist.

  Added signal to change current date.
  */
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
    property string lastDate
    property int lastCheck
    property StackView popupStack

    signal enteredDate(int check, string newDate)
    signal enteredCurrentDateCorrect(string temp)

    Connections {
        target: monthPad
        onChangedMonthCorrect: monthText.text = monthPad.value
    }

    Connections {
        target: dayPad0
        onChangedDayCorrect: dayText.text = dayPad0.value
    }

    Connections {
        target: dayPad1
        onChangedDayCorrect: dayText.text = dayPad1.value
    }

    Connections {
        target: dayPad2
        onChangedDayCorrect: dayText.text = dayPad2.value
    }

    Connections {
        target: dayPad3
        onChangedDayCorrect: dayText.text = dayPad3.value
    }

    Connections {
        target: yearPad
        onChangedYearCorrect:
        {
            yearText.text = yearPad.value
            if (yearText.text.length < 4)
            {
                var count = 4 - yearText.text.length
                for (var i = 0; i < count; i++)
                {
                    yearText.text = yearText.text + "*"
                }

            }
        }
    }

    //Display specific daypad based on month and year input.
    function changeDayOptions()
    {
        //If year is divisible by 4 (leap year)
        if (Number(yearText.text) % 4 == 0)
        {
            //If month is February of a leap year.
            if(Number(monthText.text) === 2)
            {
                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = true
                dayPad3.visible = 1

            }
            //If month has 31 days (January, March, May, Jul, August, October, December)
            else if (Number(monthText.text) === 1 ||
                     Number(monthText.text) === 3 ||
                     Number(monthText.text) === 5 ||
                     Number(monthText.text) === 7 ||
                     Number(monthText.text) === 8 ||
                     Number(monthText.text) === 10 ||
                     Number(monthText.text) === 12)
            {
                dayPad0.knobEnabled = true
                dayPad0.visible = 1

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0
            }
            //If month has 30 days (April, June, September, November)
            else if (Number(monthText.text) === 4 ||
                     Number(monthText.text) === 6 ||
                     Number(monthText.text) === 9 ||
                     Number(monthText.text) === 11)
            {
                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = true
                dayPad1.visible = 1

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0
            }
        }
        else
        {
            //If month is February of a normal year.
            if(Number(monthText.text) === 2)
            {
                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = true
                dayPad2.visible = 1

                dayPad3.knobEnabled = false
                dayPad3.visible = 0
            }
            //If month has 31 days (January, March, May, July, August, October, December)
            else if (Number(monthText.text) === 1 ||
                     Number(monthText.text) === 3 ||
                     Number(monthText.text) === 5 ||
                     Number(monthText.text) === 7 ||
                     Number(monthText.text) === 8 ||
                     Number(monthText.text) === 10 ||
                     Number(monthText.text) === 12)
            {
                dayPad0.knobEnabled = true
                dayPad0.visible = 1

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0
            }
            //If month has 30 days (April, June, September, November)
            else if (Number(monthText.text) === 4 ||
                     Number(monthText.text) === 6 ||
                     Number(monthText.text) === 9 ||
                     Number(monthText.text) === 11)
            {
                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = true
                dayPad1.visible = 1

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0
            }
        }
    }

    //Resets day text to account for inputted month and year.
    function changeDayText()
    {
        //If year is divisible by 4 (leap year)
        if (Number(yearText.text) % 4 == 0)
        {
            //If month is February.
            if(Number(monthText.text) === 2)
            {
                //If day was inputted as the 30th or 31st
                if (Number(dayText.text) === 30 || Number(dayText.text) === 31)
                {
                    //The day will be Feb. 29, in a leap year
                    dayText.text = 29
                }
            }
            //If month is a month with 30 days (April, June, September, November)
            else if (Number(monthText.text) === 4 ||
                     Number(monthText.text) === 6 ||
                     Number(monthText.text) === 9 ||
                     Number(monthText.text) === 11)
            {
                //If day was inputted as the 31
                if (Number(dayText.text) === 31)
                {
                    dayText.text = 30
                }
            }
        }
        else
        {
            //If month is February of a normal year.
            if(Number(monthText.text) === 2)
            {
                //If day was inputted as the 29th, 30th, and 31st
                if (Number(dayText.text) === 29 || Number(dayText.text) === 30 || Number(dayText.text) === 31)
                {
                    //The day will be Feb. 28, in a normal year.
                    dayText.text = 28
                }
            }
            //If month is a month with 30 days (April, June, September, November)
            else if (Number(monthText.text) === 4 ||
                     Number(monthText.text) === 6 ||
                     Number(monthText.text) === 9 ||
                     Number(monthText.text) === 11)
            {
                //If day was inputted as the 31
                if (Number(dayText.text) === 31)
                {
                    dayText.text = 30
                }
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"

        backend.setMode(ID.LISTENING_KNOB,1)

        monthBox.color = Style.unclickable_border
        dayBox.color = Style.transparent
        yearBox.color = Style.transparent

        var temp = lastDate.split('/');

        monthText.text = temp[0];
        dayText.text = temp[1];
        yearText.text = temp[2];

        monthPad.visible = 1
        monthPad.val = Number(temp[0]);
        monthPad.knobEnabled = true

        dayPad0.visible = 0
        dayPad0.val = Number(temp[1]);
        dayPad0.knobEnabled = false

        dayPad1.visible = 0
        dayPad1.val = Number(temp[1]);
        dayPad1.knobEnabled = false

        dayPad2.visible = 0
        dayPad2.val = Number(temp[1]);
        dayPad2.knobEnabled = false

        dayPad3.visible = 0
        dayPad3.val = Number(temp[1]);
        dayPad3.knobEnabled = false

        yearPad.visible = 0
        yearPad.val = Number(temp[2]);
        yearPad.knobEnabled = false
    }

    Component.onDestruction: backend.setMode(ID.LISTENING_KNOB,0)

    Connections
    {
        target: knob

        onButtonPush:
        {
            if (monthPad.visible)
            {
                monthBox.color = Style.transparent
                dayBox.color = Style.unclickable_border
                yearBox.color = Style.transparent

                monthPad.knobEnabled = false
                monthPad.visible = 0

                changeDayOptions()

                yearPad.knobEnabled = false
                yearPad.visible = 0
            }
            else if (dayPad0.visible || dayPad1.visible || dayPad2.visible || dayPad3.visible)
            {
                monthBox.color = Style.transparent
                dayBox.color = Style.transparent
                yearBox.color = Style.unclickable_border

                monthPad.knobEnabled = false
                monthPad.visible = 0

                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0

                yearPad.knobEnabled = true
                yearPad.visible = 1
            }
            else if (yearPad.visible)
            {
                monthBox.color = Style.unclickable_border
                dayBox.color = Style.transparent
                yearBox.color = Style.transparent

                monthPad.knobEnabled = true
                monthPad.visible = 1

                dayPad0.knobEnabled = false
                dayPad0.visible = 0

                dayPad1.knobEnabled = false
                dayPad1.visible = 0

                dayPad2.knobEnabled = false
                dayPad2.visible = 0

                dayPad3.knobEnabled = false
                dayPad3.visible = 0

                yearPad.knobEnabled = false
                yearPad.visible = 0
            }
        }
    }

    Rectangle
    {
        id: confirmBox
        height: 480
        width: 640
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2
        x: width / 2
        y: 100

        Rectangle
        {
            id: mainContainer
            width: .9 * parent.width
            height: .85 * parent.height
            anchors.centerIn: parent
            color: Style.transparent

            Text
            {
                id: title
                font: Style.buttonFont
                color: Style.general_set_display
            }

            Text {
                id: subTitle
                text: "Would you like change date?"
                width: parent.width
                color: Style.primary_light
                font: Style.settingPageTitle
                wrapMode: Text.WordWrap
                anchors.top: title.bottom
                anchors.topMargin: 16
                anchors.left: title.left
            }

            Rectangle
            {
                id: dateBox
                width: monthBox.width + slash1.width + dayBox.width + slash2.width + yearBox.width
                height: monthBox.height
                anchors.top: subTitle.bottom
                anchors.topMargin: 54
                anchors.left: parent.left
                anchors.leftMargin: 28
                color: Style.transparent
                Rectangle
                {
                    id: monthBox
                    width: monthText.width * 4
                    height: monthText.height * 2
                    anchors.left: dateBox.left
                    Text
                    {
                        id: monthText
                        text: monthPad.value
                        color:Style.primary_light
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                    MouseArea
                    {
                        width: monthBox.width
                        height: monthBox.height
                        onClicked:
                        {
                            monthBox.color = Style.unclickable_border
                            dayBox.color = Style.transparent
                            yearBox.color = Style.transparent

                            monthPad.knobEnabled = true
                            monthPad.visible = 1

                            dayPad0.knobEnabled = false
                            dayPad0.visible = 0

                            dayPad1.knobEnabled = false
                            dayPad1.visible = 0

                            dayPad2.knobEnabled = false
                            dayPad2.visible = 0

                            dayPad3.knobEnabled = false
                            dayPad3.visible = 0

                            yearPad.knobEnabled = false
                            yearPad.visible = 0
                        }
                    }
                }
                Text
                {
                    id: slash1
                    text: "/"
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.left: monthBox.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: monthBox.verticalCenter
                }
                Rectangle
                {
                    id: dayBox
                    width: dayText.width * 4
                    height: dayText.height * 2
                    anchors.left: slash1.right
                    anchors.leftMargin: 16
                    Text
                    {
                        id: dayText
                        color: Style.primary_light
                        font: Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                    MouseArea
                    {
                        width: dayBox.width
                        height: dayBox.height
                        onClicked:
                        {
                            monthBox.color = Style.transparent
                            dayBox.color = Style.unclickable_border
                            yearBox.color = Style.transparent

                            monthPad.knobEnabled = false
                            monthPad.visible = 0

                            changeDayOptions()

                            yearPad.knobEnabled = false
                            yearPad.visible = 0
                        }
                    }
                }
                Text
                {
                    id: slash2
                    text: "/"
                    color: Style.primary_light
                    font: Style.settingPageTitle
                    anchors.left: dayBox.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: dayBox.verticalCenter
                }
                Rectangle
                {
                    id: yearBox
                    width: 55.0625 * 2
                    height: yearText.height * 2
                    anchors.left: slash2.right
                    anchors.leftMargin: 16
                    Text
                    {
                        id: yearText
                        text: yearPad.value
                        color: Style.primary_light
                        font: Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                    MouseArea
                    {
                        width: yearBox.width
                        height: yearBox.height
                        onClicked:
                        {
                            monthBox.color = Style.transparent
                            dayBox.color = Style.transparent
                            yearBox.color = Style.unclickable_border

                            monthPad.knobEnabled = false
                            monthPad.visible = 0

                            dayPad0.knobEnabled = false
                            dayPad0.visible = 0

                            dayPad1.knobEnabled = false
                            dayPad1.visible = 0

                            dayPad2.knobEnabled = false
                            dayPad2.visible = 0

                            dayPad3.knobEnabled = false
                            dayPad3.visible = 0

                            yearPad.knobEnabled = true
                            yearPad.visible = 1
                        }
                    }
                }
            }

            Rectangle
            {
                id: stateButton
                width: 96
                height: 96
                radius: 64
                color: Style.transparent
                border.width: 2
                border.color: Style.primary_light

                anchors.left: dateBox.right
                anchors.leftMargin: 78
                anchors.verticalCenter: dateBox.verticalCenter

                property bool currentState: false

                Text {
                    id: stateText
                    text: stateButton.currentState ? "Close" : "Open"
                    color: Style.primary_light
                    font: Style.numberButtonFont
                    anchors.centerIn: parent
                }

                MouseArea
                {
                    anchors.fill: parent

                    onPressed: parent.color = Style.primary_light_selected
                    onReleased: parent.color = Style.transparent

                    onClicked: {
                        stateButton.currentState = !stateButton.currentState
                        if (stateButton.currentState)
                        {
                            keypadBox.state = "moveIn"
                        }
                        else
                        {
                            keypadBox.state = "moveOut"
                        }
                    }
                }
            }

            CancelButton
            {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                onClicked:
                {
                    popupStack.clear()
                }
            }
            ContinueButton
            {
                id: otherButton
                anchors.right: continueButton.left
                anchors.rightMargin: 16
                anchors.bottom: parent.bottom

                continueText: "Today's Date"

                Component.onCompleted:
                {
                    if (lastCheck == 2)
                    {
                        otherButton.visible = 0
                    }
                    else if (lastCheck == 1)
                    {
                        otherButton.continueText = "Today's Date"
                    }
                    else if (lastCheck == 0)
                    {
                        otherButton.continueText = "Next From Last"
                    }
                }

                onClicked:
                {
                    var tmp;
                    var tmpDate;
                    if (lastCheck == 1)
                    {
                        tmp = maintenance_manager.lastTodayDate;
                        tmpDate = tmp.split("/");

                        monthText.text = tmpDate[0];
                        dayText.text = tmpDate[1];
                        yearText.text = tmpDate[2];

                        monthPad.val = Number(tmpDate[0]);
                        dayPad0.val = Number(tmpDate[1]);
                        dayPad1.val = Number(tmpDate[1]);
                        dayPad2.val = Number(tmpDate[1]);
                        dayPad3.val = Number(tmpDate[1]);
                        yearPad.val = Number(tmpDate[2]);
                    }
                    else if (lastCheck == 0)
                    {
                        tmp = maintenance_manager.nextTwelveMonthDate;
                        tmpDate = tmp.split("/");

                        monthText.text = tmpDate[0];
                        dayText.text = tmpDate[1];
                        yearText.text = tmpDate[2];

                        monthPad.val = Number(tmpDate[0]);
                        dayPad0.val = Number(tmpDate[1]);
                        dayPad1.val = Number(tmpDate[1]);
                        dayPad2.val = Number(tmpDate[1]);
                        dayPad3.val = Number(tmpDate[1]);
                        yearPad.val = Number(tmpDate[2]);
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
                    let result = yearText.text.indexOf("*");
                    if (result == -1) {
                        changeDayText();
                        if (lastCheck == 1 || lastCheck == 0)
                        {
                            root.enteredDate(lastCheck,monthText.text + "/" + dayText.text + "/" + yearText.text);
                        }
                        else if (lastCheck == 2)
                        {
                            root.enteredCurrentDateCorrect(monthText.text + "/" + dayText.text + "/" + yearText.text)
                        }
                    }
                }
            }
        }
    }

    SlidingBoxReversed
    {
        id: keypadBox

        height: 452
        desiredY: 348


        DateMonthPad
        {
            id: monthPad
            x: 440
            y: 16
        }
        DateDayPad
        {
            id: dayPad0
            x: 290
            y: 16
        }
        DateOtherDayPad
        {
            id: dayPad1
            x: 290
            y: 16
        }
        DateFebruaryDayPad
        {
            id: dayPad2
            x: 290
            y: 16
        }
        DateFebruaryLeapDayPad
        {
            id: dayPad3
            x: 290
            y: 16
        }
        DateYearPad
        {
            id: yearPad
            x: 490
            y: 16
        }
    }
}
