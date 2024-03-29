import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
import "../../CustomObjects/Keyboard"

Rectangle{
    id: root_window
    height: 800
    width: 1280
    color: Style.primary_dark
    border.color: Style.general_set_display
    radius: 4
    border.width: 2

    property StackView popupStack
    property string name
    property string dateStr
    property string serial_number

    signal serialSignal()


    Text {
        id: title
        text: "Change Serial Number"
        font: Style.settingPageTitle
        topPadding: 48
        anchors.horizontalCenter: parent.horizontalCenter
        color: Style.primary_light
    }

    Rectangle
    {
        id: serialNumberBox
        color: Style.unclickable_border
        border.width: 2
        border.color: Style.general_set_display
        width: 194
        height: 84
        anchors.top: title.bottom
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter

        TextEdit {
            id: serialNumberText
            text: part_manager.serialNumber
            font: Style.numberButtonFont
            color: Style.primary_light
            anchors.centerIn: parent
            textFormat: TextEdit.PlainText
            cursorPosition: serialNumberText.text.length
            cursorVisible: true
        }
    }
    
    Rectangle
    {
        id: confirm_box
        color: Style.primary_dark
        width: 1100; height: 400
        anchors.top: serialNumberBox.bottom
        anchors.topMargin: 48
        anchors.horizontalCenter: parent.horizontalCenter

        SerialNumberKeyboardLayout
        {
            id: keyboard

            Component.onCompleted:
            {
                createFirstRow( "1234567890-")
                createSecondRow("QWERTYUIOP")
                createThirdRow( "ASDFGHJKL")
                createFourthRow("ZXCVBNM.")
                createBackSpaceKey()
            }
        }
    }

    ContinueButton
    {
        id: continueButton

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onClicked:
        {
            serialSignal()
        }
    }

    CancelButton
    {
        id: cancelButton

        anchors.right: continueButton.left
        anchors.rightMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked:
        {
            popupStack.clear()
        }

    }

    SettingOptionsButton
    {
        id: backButton
        title: "Back"

        serviceState: true
        height: 48
        width: 120

        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked:
        {
            popupStack.pop()
        }
    }
}
