import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import "../Styles"

T.Button {
    id: control
    property var value
    property alias title: title.text
    property alias unit: unit.text

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6
    horizontalPadding: padding + 2
    spacing: 6

    icon.width: 24
    icon.height: 24
    icon.color: control.checked || control.highlighted ? control.palette.brightText :
                control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: control.checked || control.highlighted ? control.palette.brightText :
               control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        visible: !control.flat || control.down || control.checked || control.highlighted
        
        radius: 8
        width: 81; height: 116
        color: Style.transparent
        border.color: Style.unclickable_border
        border.width: 4

        Text {
            id: valueText
            text: Math.round(control.value)/*control.value < 10 ? Math.round(control.value *100)/100 :
                                      control.value < 100 ? Math.round(control.value * 10)/10 :
                                      Math.round(control.value)*/
            color: Style.primary_light
            font: Math.round(control.value) < 1000 ? Style.statisticFont : Style.statisticFontSmaller
            anchors.horizontalCenter: parent.horizontalCenter
            y: 21
        }

        Text {
            id: title
            text: "MAP"
            color: Style.primary_light
            font: Style.titleFont
            anchors.horizontalCenter: parent.horizontalCenter
            y: 67.44
        }

        Text {
            id: unit
            text: "(cmH<sub>2</sub>O)"
            textFormat: Text.RichText
            color: Style.unit
            font: Style.unitFont
            anchors.horizontalCenter: parent.horizontalCenter
            y: 86.23
        }
    }
}
