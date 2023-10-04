import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle
{
    id: root
    color: Style.transparent

    property int min: 25
    property int max: 20
    property int value
    property int minOn


    Rectangle
    {
        id: artificialBorder
        height: root.height * .95
        anchors.centerIn: scale
        width: scale.width
        color: Style.primary_dark

        Rectangle
        {
            id: disallowedValues
            height: parent.height * (minOn - min) / (max - min)
            width: artificialBorder.width - artificialBorder.border.width * 2
            color: Style.unclickable_border
            y: parent.height - height

        }

        Rectangle
        {
            property int displayVal: root.value < root.min ? root.min : root.value > root.max ? root.max : root.value
            id: minMaxDisplay
            height: artificialBorder.height * .01
            width: artificialBorder.width - artificialBorder.border.width * 2
            color: root.value <= root.max && root.value >= root.min && (root.value >= root.minOn || root.value == root.min) ? Style.general_set_display : Style.dissident
            anchors.horizontalCenter: artificialBorder.horizontalCenter
            y: artificialBorder.height *  (1 - (displayVal - root.min) / (root.max - root.min)) - height / 2
            radius: 2
        }
    }



    Rectangle
    {
        id: scale
        height: root.height
        width: root.width * .63
        radius: 8
        border.color: Style.mode_inactive
        border.width: 2
        color: Style.transparent
        anchors.right: parent.right
        anchors.verticalCenter: root.verticalCenter


    }

    Text {
        id: minText
        text: root.min
        font: Style.buttonFont
        color: Style.unit
        anchors.right: scale.left
        anchors.bottom: scale.bottom
        rightPadding: 10
    }

    Text {
        id: maxText
        text: root.max
        font: Style.buttonFont
        color: Style.unit
        anchors.right: scale.left
        anchors.top: scale.top
        rightPadding: 10
    }
}
