/**
  Page created to confirm passcode change.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root_window
    color: Style.transparent
    property alias titleStr: title.text


    Rectangle
    {
        id: mainContainer
        width : .9 * parent.width
        height : .8 * parent.height
        y: .1 * parent.height
        color:Style.transparent

        Text
        {
            id: title
            text: "Passcode Settings"
            textFormat: Text.RichText
            color:Style.mode_label
            font: Style.settingPageTitle
            anchors.horizontalCenter: parent.horizontalCenter

        }

        Text
        {
            id: bigText
            textFormat: Text.RichText
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: parent.width
            y: title.height + 15
            anchors.top: title.bottom
            anchors.topMargin: 100
            anchors.left: title.left
            anchors.leftMargin: -120
            text: "Preset Passcode has changed."
        }

        ContinueButton
        {
            id: changePresetButton
            anchors.top: bigText.bottom
            anchors.topMargin: 150
            anchors.horizontalCenter : parent.horizontalCenter

            onClicked:
            {
                buttonContainer.pushSettingPage("Settings/About.qml");

            }
        }

    }
}
