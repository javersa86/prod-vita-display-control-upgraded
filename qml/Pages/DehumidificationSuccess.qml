import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent

    property StackView popupStack

    MouseArea
    {
        anchors.fill: parent
    }

    Rectangle
    {
        id: popupBox
        height: background.height / 2.5
        width: background.width / 2

        x: background.width / 2 - width / 2
        y: background.height / 3 - height / 2

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Rectangle
        {
            id: mainContainer
            height: .9 * parent.height
            width: .9 * parent.width
            anchors.centerIn: parent
            color: Style.transparent

            Text
            {
                id: title
                text: "DEHUMIDIFICATION"
                font: Style.buttonFont
                color: Style.general_set_display
            }

            Text
            {
                id: bigText
                text: "Dehumidification Succeeded"
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: mainContainer.width
                y: title.height
                topPadding: 15
                wrapMode: Text.WordWrap
            }

            Text
            {
                id: explanation
                text: "Water is no longer detected in the system."
                font: Style.buttonFont
                color: Style.primary_light_disabled
                width: mainContainer.width
                y: bigText.height + bigText.y
                topPadding: 15
                wrapMode: Text.WordWrap
            }

            ContinueButton
            {
                id: continueButton
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                onClicked:
                {
                    popupStack.clear()
                }

            }
        }
    }
}
