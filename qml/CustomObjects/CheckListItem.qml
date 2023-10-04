/**
  Updates by Joseph Aversa

  First line of text is aligned with check icon.

  Increased size of check icon.
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
    height: 30 //30
    color:Style.transparent
    property alias descriptionText: description.text
    property alias itemChecked: checkButton.checked

    Rectangle
    {
        id: checkButton
        property bool checked: true
        width: 16 //32
        height: 16 //32
        radius: .5 * width
        color: Style.transparent
        border.color: Style.primary_light_disabled
        border.width: 2

        Item {
            id: checkIcon
            height: parent.height * 1.75
            width: height
            anchors.centerIn: parent
            visible: checkButton.checked
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
                color: Style.primary_light
            }
        }
    }

    Text {
        id: description
        font: Style.buttonFont
        color: Style.primary_light
        anchors.left: checkButton.right
        anchors.leftMargin: 20
        //anchors.top: checkButton.top
        //anchors.topMargin: checkButton.height * .1
        wrapMode: Text.Wrap
        width: .9 * parent.width
    }

//    MouseArea
//    {
//        anchors.fill:root
//        onClicked:
//        {
//            checkButton.checked = !checkButton.checked
//        }
//    }
}
