import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import SensorID 1.0
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "ShutdownConfirmation"

    property StackView popupStack

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    Rectangle
    {
        id:mainContainer
        width: .95 * background.width
        height: .95 * background.height
        anchors.centerIn: background
        color:Style.transparent


        Rectangle
        {
           id: shutdownConfirmationBox
           height: mainContainer.height / 2.5
           width: mainContainer.width / 2

           x: background.width / 2 - width / 2
           y: background.height / 3 - height / 2

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
               text: state_manager.ventilating || state_manager.aux ? "Cannot shutdown while ventilating." : "Done for the day?"
               font: Style.numericUiDisplayFont
               color: Style.primary_light
               width: shutdownConfirmationBox.width - leftPadding * 2
               x: shutdownConfirmationBox.leftPadding
               y: shutdownConfirmationBox.topPadding + title.height
               wrapMode: Text.WordWrap
           }

           Text
           {
               id: description
               text: state_manager.ventilating || state_manager.aux ? "In order to shutdown, stop ventilation." : qsTr("If this machine is done for the day, get a start on dehumidification.")
               color: Style.primary_light_disabled
               font: Style.buttonFont
               y: big_text.y + big_text.height + shutdownConfirmationBox.topPadding
               x: shutdownConfirmationBox.leftPadding
           }

           Text {
               id: water_sensed
               property bool sensed : state_manager.sensor_measurements[SensorID.WATER_SENSOR_1] || state_manager.sensor_measurements[SensorID.WATER_SENSOR_AUX]
               text: sensed ? qsTr("Water is sensed in the system.") : qsTr("Water is not sensed in the system.")
               color: sensed ? Style.dissident : Style.primary_light_disabled
               font: Style.buttonFont
               x: shutdownConfirmationBox.leftPadding
               y: description.y + description.height + shutdownConfirmationBox.topPadding
           }

           CancelButton
           {
               id: cancelButton
               x: shutdownConfirmationBox.leftPadding
               anchors.verticalCenter: powerDownButtonBox.verticalCenter
               onClicked:
               {
                   backend.initiatePowerdown(0);
                   if(background.popupStack.depth >= 1) background.popupStack.clear();
                   else background.popupStack.pop()
               }
           }

           Rectangle
           {
               id: powerDownButtonBox
               height: 90
               width: 210
               anchors.bottom: parent.bottom
               x: dehumidifyButtonBox.x - width - 5
               color:Style.transparent
               enabled: !state_manager.ventilating && !state_manager.aux
               opacity: state_manager.ventilating || state_manager.aux ? .7 : 1


               Rectangle
               {
                   id: powerDownButton

                   width: .95 * powerDownButtonBox.width
                   height: .5 * powerDownButtonBox.height
                   border.color:Style.primary_light
                   radius: 20
                   anchors.centerIn: parent

                   color: Style.primary_light_selected

                   Rectangle
                   {
                       id: xIconBackground
                       height: powerDownButton.height / 2
                       width: height
                       x: .4 * height
                       anchors.verticalCenter: powerDownButton.verticalCenter
                       radius: .5 * height
                       color: Style.primary_light

                   }

                   Item {
                       id: xIconItem
                       height: powerDownButton.height / 2
                       width:height
                       x: .4 * height
                       anchors.verticalCenter: powerDownButton.verticalCenter

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
                       id: powerDownDesc

                       text: qsTr("NO, POWER DOWN")
                       color:Style.primary_light
                       font:Style.buttonFont
                       anchors.verticalCenter: parent.verticalCenter
                       x: xIconItem.x + xIconItem.width + 10
                   }
               }

               MouseArea
               {
                   anchors.fill:parent
                   id: continueMouseArea
                   pressAndHoldInterval: 225
                   onPressAndHold:
                   {
                       powerDownButton.color = Style.primary_light_disabled
                       powerDownButtonBox.delay(50)
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
                       backend.initiatePowerdown(1);
                       background.popupStack.push("ShutdownProgressPage.qml");
                       powerDownButton.color = Style.primary_light_selected
                       timer.stop()
                   }
               }
           }

           Rectangle
           {
               id: dehumidifyButtonBox
               height: 90
               width: 210
               anchors.bottom: parent.bottom
               x: parent.width - width - 10
               color:Style.transparent
               enabled: !state_manager.ventilating && !state_manager.aux


               Rectangle
               {
                   id: dehumidifyButton

                   width: .95 * dehumidifyButtonBox.width
                   height: .5 * dehumidifyButtonBox.height
                   radius: 20
                   anchors.centerIn: parent
                   color: !state_manager.ventilating && !state_manager.aux ? Style.affirmative : Style.affirmative_transluscent

                   Item {
                       id: dehumidifyIconItem
                       height: powerDownButton.height / 2
                       width:height
                       x: .4 * height
                       anchors.verticalCenter: dehumidifyButton.verticalCenter

                       Image {
                            id: dehumidifyIcon
                            source: "../iconography/icon_40_dehumidify.svg"
                            width: parent.width
                            height: parent.height
                            sourceSize.width: width
                            sourceSize.height: height
                            smooth: true
                            visible: true
                       }
                       ColorOverlay {
                            anchors.fill: dehumidifyIcon
                            source: dehumidifyIcon
                            color: Style.primary_dark
                       }
                   }

                   Text
                   {
                       id: dehumidifyDesc

                       text: qsTr("YES, DEHUMIDIFY")
                       color:Style.primary_dark
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
                       dehumidifyButton.color = Style.affirmative_transluscent
                       dehumidifyButtonBox.delay(50)
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
                       background.popupStack.dehumidify();
                       dehumidifyButton.color = Style.affirmative
                       timer1.stop()
                   }
               }
           }
        }
    }
}
