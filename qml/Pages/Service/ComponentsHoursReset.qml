import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property alias name: nameText.text
    property alias dateStr: dateText.text
    property alias serialStr: serialText.text

    MouseArea
    {
        anchors.fill: parent
    }

    Rectangle
    {
        id: confirmBox
        height: 400
        width: 640
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 2
        border.width: 2
        anchors.centerIn: parent

        Text {
            id: title
            text: "Confirm Replacement?"
            color: Style.primary_light
            font: Style.settingPageTitle
            anchors.top: parent.top
            anchors.topMargin: 32
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle
        {
            id: nameBox
            width: textMetrics.width + 30
            height: 60
            anchors.bottom: dateBox.top
            anchors.left: dateBox.left
            color: Style.unclickable_border

            Text {
                id: nameText
                color: Style.primary_light
                font: Style.buttonFont
                anchors.centerIn: parent
            }

            TextMetrics
            {
                id: textMetrics
                font: nameText.font
                text: nameText.text
            }
        }

        Rectangle
        {
            id: dateBox
            width: nameBox.width
            height: 60
            anchors.centerIn: parent
            color: Style.unclickable_border

            Text {
                id: dateText
                color: Style.primary_light
                font: Style.buttonFont
                anchors.centerIn: parent
            }
        }

        Rectangle
        {
            id: serialBox
            width: nameBox.width
            height: 60
            anchors.top: dateBox.bottom
            anchors.left: dateBox.left
            color: Style.unclickable_border

            Text {
                id: serialText
                color: Style.primary_light
                font: Style.buttonFont
                anchors.centerIn: parent
            }
        }

        ContinueButton
        {
            id: yesResetHoursButton
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            onClicked:
            {
                var temp = time_manager.currentDateTime;

                part_manager.setNewPart(temp.split(" - ")[0])
                popupStack.clear()
            }
        }

        CancelButton
        {
            id: cancelButton
            anchors.right: yesResetHoursButton.left
            anchors.verticalCenter: yesResetHoursButton.verticalCenter

            onClicked:
            {
                popupStack.clear()
            }
        }

        SettingOptionsButton
        {
            title: "Back"
            width: 120
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: yesResetHoursButton.verticalCenter

            onClicked:
            {
                part_manager.setTempSerial("")
                popupStack.replace("ComponentSerialUpdate.qml",
                                {
                                    "popupStack": popupStack,
                                    "name": name,
                                    "dateStr": dateStr
                                })
            }
        }
    }
}
