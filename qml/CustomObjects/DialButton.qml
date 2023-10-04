import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: root
    width: 121
    height: 44
    color: Style.primary_dark
    signal clicked()

    Rectangle {
        id: root_area
        width: parent.width
        height: parent.height
        color: Style.transparent
        radius: 24
        border.width: 2
        border.color: Style.primary_light

        Text {
            font: Style.buttonFont
            color: Style.primary_light
            x: 59
            anchors.verticalCenter: parent.verticalCenter
            text: "DIAL"
        }
        Image {
            id: keypad_icon
            source: "../iconography/numpad_icon.svg"
            sourceSize.width: width
            sourceSize.height: height
            x: 15
            anchors.verticalCenter: parent.verticalCenter
            width: 33
            height: 35
            smooth: true
        }

        ColorOverlay {
            anchors.fill: keypad_icon
            source: keypad_icon
            color: Style.primary_light
        }
    }

    MouseArea {
        id: keypad_mouse_area
        anchors.fill:parent

        onPressed: root_area.color = Style.primary_light_selected
        onReleased: root_area.color = Style.transparent
        onClicked: {
            root.clicked()
        }
    }
}
