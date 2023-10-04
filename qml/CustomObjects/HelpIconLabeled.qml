import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: hint_button
    objectName: "hint_button"
    height: 42 //35
    width: 110 //35
    radius: 20
    color: Style.primary_dark
    clip: true

    Rectangle {
        id: mainContainer
        anchors.fill: parent
        color: hint_mouse_area.pressed ? Style.help_icon_selected : Style.general_set_display
        signal clicked

        Text {
            id: helpTitle
            text: "etCO2"
            font: Style.titleFont
            color: Style.primary_dark_transluscent
            textFormat: Text.RichText
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 4

        }

        Image {
            id: hint_icon
            source: "../iconography/icon_40_help.svg"
            sourceSize.width: 70
            sourceSize.height: 70
            width: 70
            height: 70
            smooth: true
            x:54
            anchors.verticalCenter: parent.verticalCenter
        }
        ColorOverlay {
            id: hint_overlay
            anchors.fill: hint_icon
            source: hint_icon
            color: Style.general_set_display
        }

        MouseArea
        {
            id: hint_mouse_area
            anchors.fill: parent
            onClicked: {
                hint_button.clicked()
            }
        }
    }
}
