import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root
    color: Style.primary_dark_transluscent
    objectName: "ShutdownConfirmation"

    property StackView popupStack
    property int dehumidification_complete_state

    function sendPowerdownCommand(flag)
    {
        backend.initiatePowerdown(flag);
    }

    MouseArea
    {
        height: root.height
        width: root.width
        onClicked:{}
    }

    Rectangle
    {
        id:mainContainer
        width: .95 * root.width
        height: .95 * root.height
        anchors.centerIn: root
        color:Style.transparent


        Rectangle
        {
           id: shutdownConfirmationBox
           height: mainContainer.height / 3
           width: mainContainer.width / 2

           x: root.width / 2 - width / 2
           y: root.height / 3 - height / 2

           color: Style.primary_dark
           border.color: Style.general_set_display
           radius: 4
           border.width: 2

           property int leftPadding: 30
           property int topPadding: 30

           Text
           {
               id: title
               text: "SHUTDOWN"
               font: Style.buttonFont
               color: Style.general_set_display
               x: shutdownConfirmationBox.leftPadding
               y: shutdownConfirmationBox.topPadding
           }

           Text
           {
               id: big_text
               text: state_manager.ventilating || state_manager.aux ? "Stop ventilating to continue shutting down." : "All done. Would you like to continue powering down?"
               font: Style.numericUiDisplayFont
               color: Style.primary_light
               width: shutdownConfirmationBox.width - leftPadding * 2
               x: shutdownConfirmationBox.leftPadding
               y: shutdownConfirmationBox.topPadding + title.height
               wrapMode: Text.WordWrap
           }

           Text {
               id: dehumidifcation_status
               text: root.dehumidification_complete_state ? "Dehumidification Succeeded" : "Dehumidification Failed"
               font: Style.buttonFont
               color: Style.primary_light_disabled
               width: mainContainer.width
               x: shutdownConfirmationBox.leftPadding
               y: big_text.height + big_text.y
               topPadding: 15
               wrapMode: Text.WordWrap
           }

           Rectangle
           {
               id: noButtonBox
               height: 90
               width: 95
               anchors.bottom: parent.bottom
               x: shutdownConfirmationBox.leftPadding
               color:Style.transparent
               visible: !state_manager.ventilating && !state_manager.aux

               Rectangle
               {
                   id: noButton

                   width: .95 * noButtonBox.width
                   height: .5 * noButtonBox.height
                   border.color:Style.primary_light
                   border.width: 2
                   radius: 20
                   anchors.centerIn: parent

                   color:Style.primary_light_selected

                   Rectangle
                   {
                       id: xIconBackground
                       height: noButton.height / 2
                       width: height
                       x: .4 * height
                       anchors.verticalCenter: noButton.verticalCenter
                       radius: .5 * height
                       color: Style.primary_light

                   }

                   Item {
                       id: xIconItem
                       height: noButton.height / 2
                       width:height
                       x: .4 * height
                       anchors.verticalCenter: noButton.verticalCenter

                       Image {
                            id: xicon
                            source: "../iconography/icon_40_close.svg"
                            width: parent.width
                            height: parent.height
                            sourceSize.width: width
                            sourceSize.height: height
                            smooth: true
                            visible: true
                       }
                       ColorOverlay {
                            anchors.fill: xicon
                            source: xicon
                            color: Style.primary_dark
                       }
                   }

                   Text
                   {
                       id: noDesc

                       text: qsTr("NO")
                       color:Style.primary_light
                       font:Style.buttonFont
                       anchors.verticalCenter: parent.verticalCenter
                       x: xIconItem.x + xIconItem.width + 10
                   }
               }

               MouseArea
               {
                   anchors.fill:parent
                   pressAndHoldInterval: 225
                   onPressAndHold:
                   {
                       noButton.color = Style.primary_light_disabled
                       noButtonBox.delay(50)
                   }
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
                       root.sendPowerdownCommand(0);
                       if(root.popupStack.depth == 1) root.popupStack.clear();
                       else root.popupStack.pop()
                       noButton.color = Style.primary_light_selected
                       timer.stop()
                   }
               }
           }

           CancelButton
           {
               id: cancelButton
               x: shutdownConfirmationBox.leftPadding
               y: parent.height - height - shutdownConfirmationBox.leftPadding
               visible: state_manager.ventilating || state_manager.aux
               onClicked:
               {
                   root.sendPowerdownCommand(0);
                   root.popupStack.clear();
               }
           }

           Rectangle
           {
               id: yesButtonBox
               height: 90
               width: 95
               anchors.bottom: parent.bottom
               color:Style.transparent
               x: shutdownConfirmationBox.width - shutdownConfirmationBox.leftPadding - width
               visible: !state_manager.ventilating && ! state_manager.aux

               Rectangle
               {
                   id: yesButton

                   width: .95 * yesButtonBox.width
                   height: .5 * yesButtonBox.height
                   radius: 20
                   anchors.centerIn: parent

                   color:Style.primary_light_selected
                   border.color: Style.affirmative
                   border.width: 2

                   Item {
                       id: yesIconItem
                       height: yesButton.height / 1.3
                       width:height
                       x: .2 * height
                       anchors.verticalCenter: yesButton.verticalCenter

                       Image {
                            id: yesIcon
                            source: "../iconography/icon_40_checkmark.svg"
                            width: parent.width
                            height: parent.height
                            sourceSize.width: width
                            sourceSize.height: height
                            smooth: true
                            visible: true
                       }
                       ColorOverlay {
                            anchors.fill: yesIcon
                            source: yesIcon
                            color: Style.affirmative
                       }
                   }

                   Text
                   {
                       id: yesDesc

                       text: qsTr("YES")
                       color:Style.affirmative
                       font:Style.buttonFont
                       anchors.verticalCenter: parent.verticalCenter
                       x: xIconItem.x + xIconItem.width + 10
                   }
               }

               MouseArea
               {
                   anchors.fill:parent
                   pressAndHoldInterval: 225
                   onPressAndHold:
                   {
                       yesButton.color = Style.affirmative_transluscent
                       yesButtonBox.delay(50)
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
                       root.sendPowerdownCommand(1);
                       root.popupStack.push("ShutdownProgressPage.qml");
                       yesButton.color = Style.affirmative
                       timer1.stop()
                   }
               }
           }
        }
    }
}
