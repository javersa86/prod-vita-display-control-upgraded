/**
 * Updates by Joseph Aversa
 *
 * Components page display all of the names, numbers, installation dates, and hours operating of components that need to be replaced on service appointments.
 * User will need to scroll to view all components.
 * Pressing Date Installed box for components, pushes pop up page to update installation date.
 * Hours Operating is computed based on the duration between the current date and time and the installation date.
 * Dates entered after today's date will not computer hours operating and remain 0.
 * Hours Operating text will change to red if componet is passed lifespan.
 * - Components between Oxygen Sensor and Aux Water Pump will change red and need to be replaced after 12 months.
 * - Components between the Tube from AUX humidity manifold to Front connector and the Driving Pressure Regulator will change red and need to be replaced after 3 years.
 * - Components Heater Cartridge and Jet Valve will change red and needto be replaced after 1000 hours.
 */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import Qt.labs.qmlmodels 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.primary_dark
    property int topY
    property StackView popupStack
    property ListModel model: ListModel{}

    property bool selectPartMode: false

    Component.onCompleted:
    {
        fillTable()
    }

    function substring(str)
    {
        return str.substring(0, 10);
    }

    function fillTable()
    {
        model.clear();
        for (var i = 0; i < 23; i++)
        {
            part_manager.setIndex(i);
            model.append({
                             nameValue: part_manager.partName,
                             numberValue: part_manager.partNumber,
                             dateValue: part_manager.partDateTime,
                             opValue: part_manager.hoursOperating,
                             opText: "00:00",
                             ventValue: part_manager.hoursVentilating,
                             ventText: "00:00",
                             opCountValue: 31560000 - part_manager.hoursOperating,
                             opCountText: "00:00",
                             ventCountValue: 31560000 - part_manager.hoursVentilating,
                             ventCountText: "00:00",
                             indexValue: i
                         })
        }
    }

    Component
    {
        id: partsDelegate
        Row
        {
            Rectangle
            {
                id: nameBox
                width: partsBox.width * .32
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2

                enabled: root_window.selectPartMode

                property color textColor: Style.general_set_display

                Text
                {
                    id: nameText
                    text: qsTr(nameValue)
                    color: root_window.selectPartMode ? nameBox.textColor : Style.primary_light
                    font: root_window.selectPartMode ? Style.buttonFontUnderlined : Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                }

                MouseArea
                {
                    id: nameArea
                    anchors.fill:parent
                    pressAndHoldInterval: 225
                    onPressAndHold:
                    {
                        nameBox.textColor = Style.general_set_display_selected
                        nameBox.delay(50)
                    }
                }

                function delay(delayTime)
                {
                    nameTimer.interval = delayTime
                    nameTimer.start()
                }

                Timer
                {
                    id: nameTimer
                    repeat: false
                    onTriggered:
                    {
                        part_manager.setTempIndex(indexValue);
                        root_window.popupStack.push("ComponentsReplaced.qml", { "popupStack": popupStack , "name": nameValue})
                        nameBox.textColor = Style.general_set_display
                        nameTimer.stop()
                    }
                }
            }
            Rectangle
            {
                id: numberBox
                width: partsBox.width * .16
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2
                Text
                {
                    text: numberValue
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Rectangle
            {
                id: dateButton
                width: partsBox.width * .16
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2

                Text
                {
                    id: dateText
                    text: qsTr(substring(dateValue))
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Rectangle
            {
                id: hoursBox
                width: partsBox.width * .18
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2

                property int operSeconds: opValue
                property int ventSeconds: ventValue

                Text
                {
                    id: hoursText
                    text: "Op:    " + opText
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.bottom: parent.verticalCenter
                    anchors.bottomMargin: 2
                }

                Text {
                    id: ventilatingText
                    text: "Vent: " + ventText
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.top: parent.verticalCenter
                    anchors.topMargin: 2
                }

                Timer
                {
                    id: hoursTimer
                    interval: 100
                    repeat: true
                    running: true
                    triggeredOnStart: true

                    onTriggered:
                    {
                        if (indexValue < 10)
                        {
                            if (hoursBox.operSeconds >= 31560000)
                            {
                                hoursText.color = Style.pip
                            }
                            else if (hoursBox.operSeconds >= 28404000)
                            {
                                hoursText.color = Style.tertiary;
                            }
                            else
                            {
                                hoursText.color = Style.primary_light
                            }
                        }
                        if (10 <= indexValue && indexValue < 21)
                        {
                            if (hoursBox.operSeconds >= 94608000)
                            {
                                hoursText.color = Style.pip
                            }
                            else if (hoursBox.operSeconds >= 85147200)
                            {
                                hoursText.color = Style.tertiary;
                            }
                            else
                            {
                                hoursText.color = Style.primary_light
                            }
                        }
                        if (20 <= indexValue)
                        {
                            if (hoursBox.operSeconds >= 3600000)
                            {
                                hoursText.color = Style.pip
                            }
                            else if (hoursBox.operSeconds >= 3240000)
                            {
                                hoursText.color = Style.tertiary;
                            }
                            else
                            {
                                hoursText.color = Style.primary_light
                            }
                        }
                    }
                }
            }
            Rectangle
            {
                id: countdownBox
                width: partsBox.width * .18
                height: 60
                color: Style.transparent
                border.color: Style.general_set_display
                border.width: 2

                Text
                {
                    id: hoursCountdownText
                    text: "Op:    " + opCountText
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.bottom: parent.verticalCenter
                    anchors.bottomMargin: 2
                }

                Text {
                    id: ventilatingCountText
                    text: "Vent: " + ventCountText
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    anchors.top: parent.verticalCenter
                    anchors.topMargin: 2
                }
            }
        }
    }

    Rectangle
    {
        id: replaceButton
        width: mainContainer.width * .32
        height: 50
        radius: 25
        color: root_window.selectPartMode ? Style.primary_dark : Style.affirmative
        border.color: root_window.selectPartMode ? Style.cancel : Style.unclickable_border
        border.width: 2

        property int select_deselect: 0

        anchors.right: parent.right
        y: .1 * parent.height

        Text
        {
            id: replaceText
            text: root_window.selectPartMode ? "Cancel" : "Replace Components"
            color: root_window.selectPartMode ? Style.cancel : Style.unclickable_border
            font: root_window.selectPartMode ? Style.cancel_font : Style.titleFont
            anchors.centerIn: parent
        }

        MouseArea
        {
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                replaceButton.color = root_window.selectPartMode ? Style.primary_light_selected : Style.affirmative_transluscent
                replaceButton.delay(50)
            }
        }

        function delay(delayTime)
        {
            replaceTimer.interval = delayTime
            replaceTimer.start()
        }

        Timer {
            id: replaceTimer
            repeat: false
            onTriggered:
            {
                root_window.selectPartMode = !root_window.selectPartMode
                replaceButton.color = root_window.selectPartMode ? Style.primary_dark : Style.affirmative
                replaceTimer.stop()
            }
        }
    }

    Rectangle
    {
        id: mainContainer
        width: .92 * parent.width
        height: .75 * parent.height
        x: 50
        y: .2 * parent.height
        color: Style.transparent

        Row
        {
            id: partColumns
            anchors.top: parent.top
            anchors.left: parent.left

            Rectangle
            {
                id: nameColumn
                width: mainContainer.width * .32
                height: 30
                color: Style.transparent

                Text
                {
                    text: "Part"
                    color: Style.primary_light
                    font: Style.titleFont
                    anchors.left: parent.left
                }
            }

            Rectangle
            {
                id: numberColumn
                width: mainContainer.width * .16
                height: 30
                color: Style.transparent
                Text
                {
                    text: "Serial Number"
                    color:Style.primary_light
                    font: Style.titleFont
                    anchors.left: parent.left
                }
            }
            Rectangle
            {
                id: dateColumn
                width: mainContainer.width * .16
                height: 30
                color: Style.transparent

                Text
                {
                    text: "Date Installed"
                    color: Style.primary_light
                    font: Style.titleFont
                    anchors.left: parent.left
                }
            }
            Rectangle
            {
                id: hoursColumn
                width: mainContainer.width * .18
                height: 30
                color: Style.transparent

                Text
                {
                    text: "Hours"
                    color:Style.primary_light
                    font: Style.titleFont
                    anchors.left: parent.left
                }
            }
            Rectangle
            {
                id: ventColumn
                width: mainContainer.width * .18
                height: 30
                color: Style.transparent

                Text {
                    text: "Countdown"
                    color: Style.primary_light
                    font: Style.titleFont
                    anchors.left: parent.left
                }
            }
        }

        Rectangle
        {
            id: partsBox
            color: Style.transparent
            width: parent.width
            height: 480
            anchors.top: partColumns.bottom
            anchors.left: parent.left

            ListView
            {
                id: listView
                model: root_window.model
                delegate: partsDelegate

                width: parent.width + 39
                height: partsBox.height
                anchors.left:parent.left
                anchors.top: parent.top

                boundsBehavior: Flickable.StopAtBounds
                snapMode: ListView.SnapOneItem

                clip: true

                Timer
                {
                    id: modelTimer
                    interval: 100
                    repeat: true
                    running: true
                    triggeredOnStart: true

                    onTriggered:
                    {
                        listView.incrementTime();
                    }

                }

                function incrementTime()
                {
                    for (var i = 0; i < 23; i++)
                    {
                        part_manager.setIndex(i);

                        if (i === part_manager.partIndex) {
                            model.get(i).nameValue = part_manager.partName;
                            model.get(i).numberValue = part_manager.partNumber;
                            model.get(i).dateValue = part_manager.partDateTime;
                            part_manager.partIndex = -1;
                        }

                        model.get(i).opValue = part_manager.hoursOperating;
                        model.get(i).opText = listView.secondsToTime(model.get(i).opValue);
                        model.get(i).ventValue = part_manager.hoursVentilating;
                        model.get(i).ventText = listView.secondsToTime(model.get(i).ventValue);

                        model.get(i).opCountValue = 31560000 - part_manager.hoursOperating;
                        model.get(i).opCountText = listView.secondsToTime( model.get(i).opCountValue <= 0 ? 0 : model.get(i).opCountValue );
                        model.get(i).ventCountValue = 31560000 - part_manager.hoursVentilating;
                        model.get(i).ventCountText = listView.secondsToTime( model.get(i).ventCountValue <= 0 ? 0 : model.get(i).ventCountValue );
                    }
                }

                function secondsToTime(num)
                {
                    var hours = Math.floor(num / (60 * 60));

                    var divisor_for_minutes = num % (60 * 60);
                    var minutes = Math.floor(divisor_for_minutes / 60);

                    return prependZero(hours) + ":" + prependZero(minutes)
                }

                function prependZero(num)
                {
                    if (num < 10)
                    {
                        return String("0" + num).slice(-2);
                    }
                    else return num;
                }

                ScrollBar.vertical: ScrollBar {
                    id: vbar
                    active: true
                    policy: ScrollBar.AlwaysOn
                    hoverEnabled: true

                    contentItem: Rectangle
                    {
                        implicitWidth: 32
                        radius: width / 2
                        color: vbar.pressed ? Style.numeric_ui_unit : Style.primary_light
                    }
                }
            }
        }
    }
}
