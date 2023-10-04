/**
  Confirmation pop up when enable/disable modes.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle
{
    id: root_window
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack
    property int modeID
    property alias modeText: bigText.text

    signal exit(int modeID, int itemCheck);

    MouseArea {
        anchors.fill: parent
    }
    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
    }

    Rectangle
    {
        id: confirmBox
        height: 240
        width: 600
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2
        anchors.horizontalCenter: parent.horizontalCenter
        y: 100
//        x: width / 2
//        y: 100


        Rectangle
        {
            id: mainContainer
            width : .9 * parent.width
            height : .85 * parent.height
            anchors.centerIn: parent
            color:Style.transparent
            Text
            {
                id: title
                font: Style.buttonFont
                color: Style.general_set_display
                text: "Mode Confirmation"

            }

            Text
            {
                id: bigText
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: parent.width
                y: title.height + 15
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
            }

            Text
            {
                id: smallText
                text: "Press Continue to confirm."
                font: Style.buttonFont
                color: Style.primary_light_disabled
                y: bigText.y + bigText.height + 15
            }

            ContinueButton
            {
                id: continueButton
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                onClicked: {
                    root_window.exit(modeID,1)
                }
            }

            CancelButton
            {
                id: cancelButton
                anchors.left: parent.left
                anchors.leftMargin: 4
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked:
                {
                    root_window.exit(modeID,0)
                }
            }
        }
    }

}
