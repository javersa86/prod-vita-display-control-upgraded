import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import Qt.labs.qmlmodels 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property string name
    property Item datePage

    Connections
    {
        target: datePage

        onDateSignal:
        {
            part_manager.setTempName(name);
            part_manager.setTempDate(date);
            popupStack.pop()
            popupStack.replace("ComponentSerialUpdate.qml", { "popupStack": popupStack, "name": name, "dateStr": date})
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Rectangle
    {
        id: confirmBox
        height: 480
        width: 480
        color: Style.primary_dark
        border.color: Style.general_set_display
        border.width: 2
        anchors.centerIn: parent

        Text {
            id: title
            text: "Continue with today's date?"
            font: Style.settingPageTitle
            color: Style.primary_light
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 48
        }

        Text {
            id: date
            text: time_manager.currentDateTime.split(" ")[0]
            color: Style.primary_light
            font: Style.buttonFont
            anchors.top: title.bottom
            anchors.topMargin: 36
            anchors.horizontalCenter: parent.horizontalCenter

        }

        ContinueButton
        {
            id: continueButton
            anchors.top: date.bottom
            anchors.topMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked:
            {
                part_manager.setTempName(name);
                part_manager.setTempDate(date.text);
                popupStack.replace("ComponentSerialUpdate.qml", { "popupStack": popupStack, "name": name, "dateStr": date.text})
            }
        }

        SettingOptionsButton
        {
            id: updateDateButton
            width: 180
            height: 45
            radius: 24
            title: "Change Date"
            anchors.top: continueButton.bottom
            anchors.topMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter
            serviceState: true

            onClicked:
            {
                datePage = popupStack.push("UpdateDateInstalled.qml", {"popupStack": root.popupStack, "dateStr": date.text})
            }
        }

        CancelButton
        {
            id: cancelButton
            anchors.top: updateDateButton.bottom
            anchors.topMargin: 48
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked:
            {
                popupStack.clear()
            }
        }
    }
}
