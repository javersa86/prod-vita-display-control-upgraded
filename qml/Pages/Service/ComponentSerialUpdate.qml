import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import Qt.labs.qmlmodels 1.0
import "../../Styles"
import "../../CustomObjects"
import "../../CustomObjects/Keyboard"

Rectangle
{
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property string name
    property string dateStr
    property Item serialPage

    Connections
    {
        target: serialPage

        onSerialSignal:
        {
            var temp = part_manager.serialNumber;
            if (temp.length === 0)
            {
                part_manager.setTempSerial("N/A");
            }
            popupStack.pop()
            popupStack.replace("ComponentsHoursReset.qml",
                            {
                                "popupStack": popupStack,
                                "name": name,
                                "dateStr": dateStr,
                                "serialStr": part_manager.serialNumber
                            })
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Rectangle
    {
        id: confirmBox
        height: 263
        width: 777
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2
        anchors.centerIn: parent

        Text {
            id: title
            text: "Would you like to update the serial number for this component?"
            color: Style.primary_light
            font: Style.settingPageTitle
            anchors.top: parent.top
            anchors.topMargin: 48
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: serialText
            text: part_manager.partNumber
            color: Style.primary_light
            font: Style.buttonFont
            anchors.top: title.bottom
            anchors.topMargin: 48
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ContinueButton
        {
            id: continueButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            continueText: "YES, UPDATE"

            onClicked:
            {
                serialPage = popupStack.push("SerialNumberPopUp.qml",
                                {
                                    "popupStack": popupStack,
                                    "name": name,
                                    "dateStr": dateStr,
                                    "serial_number": ""
                                })
            }
        }

        SettingOptionsButton
        {
            id: noButton
            title: "NO, CONTINUE"
            width: 180
            height: 45
            radius: 24
            anchors.right: continueButton.left
            anchors.verticalCenter: continueButton.verticalCenter
            serviceState: true

            onClicked:
            {
                var temp = part_manager.serialNumber;
                if (temp.length === 0)
                {
                    part_manager.setTempSerial("N/A");
                }
                popupStack.replace("ComponentsHoursReset.qml",
                                {
                                    "popupStack": popupStack,
                                    "name": name,
                                    "dateStr": dateStr,
                                    "serialStr": part_manager.serialNumber
                                })
            }
        }

        CancelButton
        {
            id: cancelButton
            anchors.right: noButton.left
            anchors.rightMargin: 10
            anchors.verticalCenter: noButton.verticalCenter

            onClicked:
            {
                popupStack.clear()
            }
        }

        SettingOptionsButton
        {
            id: backButton
            title: "Back"
            width: 120
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: cancelButton.verticalCenter

            onClicked:
            {
                popupStack.replace("ComponentsReplaced.qml", { "popupStack": popupStack, "name": name})
            }
        }
    }
}
