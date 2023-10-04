/**
  Mini Alarm for INLET Air/o2 values are triggered.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: root
    height: 30
    color:Style.transparent
    property alias descriptionText: description.text
    property alias itemChecked: checkAlarm.checked

    Rectangle
    {
        id: checkAlarm
        property bool checked: false
        width: 32
        height: 32
        radius: .5 * width
        color: checked ? Style.affirmative_transluscent : Style.transparent
        border.color: checked ? Style.affirmative : Style.cancel
        border.width: 2

        Item {
            id: checkIcon
            height: parent.height * 1.75
            width: height
            anchors.centerIn: parent
            visible: checkAlarm.checked
            Image {
                id: icon
                source: "../iconography/icon_40_checkmark.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
                visible: true
            }
            ColorOverlay {
                anchors.fill: icon
                source: icon
                color: checkAlarm.checked ? Style.affirmative : Style.cancel
            }
        }
    }

    Text {
        id: description
        font: Style.buttonFont
        color: Style.primary_light
        anchors.left: checkAlarm.right
        anchors.leftMargin: 20
        anchors.top: checkAlarm.top
        anchors.topMargin: checkAlarm.height * .1
        wrapMode: Text.Wrap
        width: .9 * parent.width
    }
}
