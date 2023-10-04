import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Styles"

Switch {
    id: control

    property alias checkedText: checkedText.text
    property alias uncheckedText: uncheckedText.text

    onCheckedChanged:
    {
        var enable = 1
        if (control.checked)
        {
            enable = 0;
        }

        time_manager.automatic = enable
    }

    indicator: Rectangle {
        height: 48
        width: 220
        color: Style.primary_dark
        border.color: control.checked ? Style.mode_active_warning : Style.primary_light
        border.width: 2
        radius: width / 10

        Rectangle {
            x: control.checked ? parent.width - width - 4 : 0 + 4
            anchors.verticalCenter: parent.verticalCenter
            width: 106
            height: 35
            radius: width / 5
            color: control.checked ? Style.mode_active_warning : Style.primary_light
        }

        Rectangle {
            anchors.left: parent.left
            width: parent.width / 2
            height: parent.height
            color: Style.transparent

            Text {
                id: uncheckedText
                text: "Default"
                color: control.checked ? Style.mode_inactive : Style.mode_active
                font: Style.buttonFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            anchors.right: parent.right
            width: parent.width / 2
            height: parent.height
            color: Style.transparent

            Text {
                id: checkedText
                text: "Set"
                color: control.checked ? Style.mode_active : Style.mode_inactive
                font: Style.buttonFont
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
