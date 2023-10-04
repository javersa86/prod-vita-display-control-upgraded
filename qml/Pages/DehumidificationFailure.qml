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
        anchors.fill:parent
        height: background.height
        width: background.width
        onClicked:{}
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
            text: "Dehumidification Failed"
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
            text: "Water is still detected. Ensure no water is applied to the system and try again."
            font: Style.buttonFont
            color: Style.primary_light_disabled
            width: mainContainer.width
            y: bigText.height + bigText.y
            topPadding: 15
            wrapMode: Text.WordWrap
        }

        CancelButton
        {
            id: cancelButton
            anchors.bottom: parent.bottom
            anchors.left:parent.left

            onClicked:
            {
                popupStack.dehumidifyComplete(0)
            }

        }

        Rectangle
        {
            id: start_button

            height: popupBox.height * .16
            width: popupBox.width * .45
            color: enabled ? Style.affirmative : Style.affirmative_transluscent
            radius: 24

            anchors.verticalCenter: cancelButton.verticalCenter
            anchors.right:parent.right
            enabled: !state_manager.ventilating && !state_manager.aux

            Text
            {
                id: startStr
                text: qsTr("START DEHUMIDIFICATION")
                color: Style.primary_dark
                anchors.verticalCenter: start_button.verticalCenter
                leftPadding: startIcon.width + startIcon.x + 10
                font: Style.buttonFont
            }

            MouseArea
            {
                anchors.fill: start_button
                pressAndHoldInterval: 225
                onPressAndHold: {
                    start_button.color = Style.affirmative_transluscent
                    start_button.delay(50)
                }
            }

            function delay(delayTime)
            {
                timer1.interval = delayTime;
                timer1.start();
            }

            Timer {
                id: timer1
                repeat: false
                onTriggered:
                {
                    backend.setMode(7, 1);
                    popupStack.replace("DehumidifyingProgressPage.qml", {"popupStack" : popupStack})
                    start_button.color = Style.affirmative
                    timer1.stop()
                }
            }

            Item {
                id: startIcon
                height: start_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: start_button.verticalCenter
                Image {
                    id: sicon
                    source: "../iconography/play.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: sicon
                    source: sicon
                    color: Style.primary_dark
                }
            }
        }
        }
    }
}
