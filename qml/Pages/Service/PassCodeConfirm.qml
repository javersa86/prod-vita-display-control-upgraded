/**
  Page created to confirm preset or service passcode change.
  */
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
    property alias titleStr: title.text

    property StackView stack
    property StackView popupStack


    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
    }

    Rectangle
    {
        id: confirmBox
        height: 320
        width: 640
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2
        x: width / 2
        y: 100


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

            }

            Text
            {
                id: bigText
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: parent.width
                y: title.height + 15
                wrapMode: Text.WordWrap
                text: "Passcode has changed."
            }




            ContinueButton
            {
                id: changeServiceButton
                anchors.horizontalCenter : parent.horizontalCenter
                anchors.bottom: parent.bottom
                onClicked:
                {
                    popupStack.clear()

                }
            }

        }
    }
}
