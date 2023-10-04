import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "DehumidificationDisconnection"

    property StackView popupStack

    signal disconnected()

    //property int buttonVisible

    Component.onCompleted:
    {
        disconnection_confirm_box.state = "moveIn"
    }

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    SlidingBox
    {
        id: disconnection_confirm_box
        height: background.height / 2.5
        width: background.width / 2
        startX: background.width / 2 - width / 2
        desiredX: startX
        startY: - height
        desiredY: background.height / 3 - height / 2

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Text
        {
            id: title
            text: "DEHUMIDIFICATION"
            font: Style.buttonFont
            color: Style.general_set_display
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding
        }

        Text
        {
            id: disconnected_question
            text: "Is the machine disconnected from the patient?"
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: disconnection_confirm_box.width - leftPadding * 2
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding + title.height
            wrapMode: Text.WordWrap
        }

        Text
        {
            id: explanation
            text: "Please make sure the tubes are disconnected from the patient before starting the dehumidification process."
            font: Style.buttonFont
            color: Style.primary_light_disabled
            width: disconnection_confirm_box.width - disconnection_confirm_box.leftPadding * 2
            x: disconnection_confirm_box.leftPadding
            y: disconnection_confirm_box.topPadding + title.height + disconnected_question.height + .05 * disconnection_confirm_box.height
            wrapMode: Text.Wrap
        }
        Text
        {
            id: checkText
            text: state_manager.ventilating || state_manager.aux ? "- Ventilation or Auxiliary Flow is on." : ""
            font: Style.buttonFont
            color: Style.primary_light_disabled
            width: disconnection_confirm_box.width - disconnection_confirm_box.leftPadding * 2
            x: disconnection_confirm_box.leftPadding + 16
            y: disconnection_confirm_box.topPadding + title.height + disconnected_question.height + explanation.height + .05 * disconnection_confirm_box.height
            wrapMode: Text.Wrap

        }

        Rectangle
        {
            id: no_button

            height: disconnection_confirm_box.height * .16
            width: disconnection_confirm_box.width * .16
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            signal clicked()

            x: disconnection_confirm_box.leftPadding
            y: (disconnection_confirm_box.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2

            onClicked:
            {
                popupStack.dehumidifyComplete(0)
            }

            Text
            {
                id: noStr
                text: qsTr("NO")
                color: Style.primary_light
                anchors.verticalCenter: no_button.verticalCenter
                anchors.horizontalCenter: no_button.horizontalCenter
                leftPadding: .3 * no_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                pressAndHoldInterval: 225
                onPressAndHold: {
                    no_button.color = Style.primary_light_disabled
                    no_button.delay(50)
                }
                anchors.fill: no_button
            }

            function delay(delayTime)
            {
                timer.interval = delayTime;
                timer.start();
            }

            Timer {
                id: timer
                repeat: false
                onTriggered:
                {
                    no_button.clicked()
                    no_button.color = Style.primary_light_selected
                    timer.stop()
                }
            }

            Rectangle
            {
                id: closeIconBackground
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                radius: .5 * height
                color: Style.primary_light

            }

            Item {
                id: closeIcon
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                Image {
                    id: xicon
                    source: "../iconography/icon_40_close.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: xicon
                    source: xicon
                    color: Style.primary_light_selected
                }
            }

        }

        Rectangle
        {
            id: yes_button

            height: disconnection_confirm_box.height * .16
            width: disconnection_confirm_box.width * .16
            color: !state_manager.ventilating && !state_manager.aux ? Style.affirmative : Style.affirmative_transluscent
            border.width: 2
            radius: 24

            enabled: !state_manager.ventilating && !state_manager.aux

            signal clicked()

            x: disconnection_confirm_box.width - width - disconnection_confirm_box.leftPadding
            y: (disconnection_confirm_box.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2

            onClicked:
            {
                popupStack.replace("DehumidificationChecklist.qml", {"popupStack" : popupStack})
            }

            Text
            {
                id: yesStr
                text: qsTr("YES")
                color: Style.primary_dark
                anchors.verticalCenter: yes_button.verticalCenter
                anchors.horizontalCenter: yes_button.horizontalCenter
                leftPadding: .3 * yes_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    yes_button.color = Style.affirmative_transluscent
                    yes_button.delay(50)
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
                    yes_button.clicked()
                    yes_button.color = Style.affirmative
                    timer1.stop()
                }
            }

            Item {
                id: checkIcon
                height: yes_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: yes_button.verticalCenter
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
                    color: Style.primary_dark
                }
            }

        }
    }
}
