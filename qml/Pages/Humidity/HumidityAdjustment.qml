/**
  Added help icon with description.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"
import IDs 1.0

InteractiveKnobPage
{
    id: root
    color:Style.transparent
    property StackView stack
    property StackView popupStack
    property alias separated: adjustmentSwitch.checked

    Rectangle
    {
        id: mainContainer
        width: .96 * parent.width
        height: .84 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: 89
        color: Style.transparent

        Text {
            id: setting_title
            text: qsTr("Humidity (level)")
            color: Style.primary_light
            font: Style.numericUiDisplayFont
            anchors.verticalCenter: ajustmentStr.verticalCenter
        }

        HelpIcon {
            id: hint_button
            anchors.left: setting_title.right
            anchors.verticalCenter: setting_title.verticalCenter
            onClicked:
            {
                popupStack.pushHelpBox(humidity_1.title, humidity_1.help)
            }
        }

        Text {
            id: ajustmentStr
            text: qsTr("Adjustments")
            color: Style.mode_label
            font: Style.titleFont
            anchors.right: adjustmentSwitch.left
            rightPadding: 15
            anchors.verticalCenter: adjustmentSwitch.verticalCenter
        }

        Switch {
            id: adjustmentSwitch
            anchors.right: parent.right
            checked: state_manager.separatedHumidity

            onCheckedChanged:
            {
                if(checked)
                {
                    adjustmentStack.replace("HumiditySeparatedDial.qml", {"stack": adjustmentStack, "firstPage": 0})
                }
                else
                {
                    adjustmentStack.replace("HumidityUnifiedDial.qml", {"stack": adjustmentStack})
                }
            }

            indicator: Rectangle {
                height: 42
                width: 184
                color: Style.primary_dark
                border.color: Style.primary_light
                border.width: 2
                radius: 20
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    x: adjustmentSwitch.checked ? parent.width - width - 4 : 0 + 4
                    anchors.verticalCenter: parent.verticalCenter
                    width: 88
                    height: 32
                    radius: 16
                    color: Style.primary_light
                }

                Rectangle {
                    anchors.left: parent.left
                    width: parent.width / 2
                    height: parent.height
                    color: Style.transparent

                    Text {
                        id: uncheckedText
                        text: "Unified"
                        color: adjustmentSwitch.checked ? Style.mode_inactive : Style.mode_active
                        font: Style.buttonFont
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Rectangle {
                    anchors.right: parent.right
                    width: parent.width / 2
                    height: parent.height
                    color: Style.transparent

                    Text {
                        id: checkedText
                        color: adjustmentSwitch.checked ? Style.mode_active : Style.mode_inactive
                        font: Style.buttonFont
                        text: "Separated"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }

        Rectangle
        {
            id: resetButton
            height: 42
            width: 184
            color: Style.primary_dark
            border.color: Style.primary_light
            border.width: 2
            radius: 20
            x: setting_title.x
            y: setting_title.y + setting_title.height + 15
            visible: (!state_manager.primaryHumidificationState || !state_manager.secondaryHumidificationState || !state_manager.auxiliaryHumidificationState) &&
                     state_manager.humidity_priming_reset_available

            MouseArea
            {
                id: resetMA
                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold:
                {
                    resetButton.color = Style.primary_light_selected
                    resetButton.delay(50)
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
                    backend.setMode(10,0);
                    resetButton.color = Style.primary_dark
                    timer.stop()
                }
            }

            Text {
                id: resetPumpsStr
                text: qsTr("Reset Pumps")
                anchors.centerIn: parent
                color: Style.primary_light
                font: Style.titleFont
            }
        }

        Text {
            id: resetInstructions
            text: qsTr("Humidity pump priming attempts exceeded. Press button to reset.")
            visible: resetButton.visible
            color: Style.mode_label
            font: Style.titleFont
            anchors.top:resetButton.bottom
            wrapMode: "WordWrap"
            topPadding: 15
            width: 150

        }

        StackView
        {
            id: adjustmentStack
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            property int hum_1: state_manager.hum1
            property int hum_aux: state_manager.humaux

            Component.onCompleted:
            {
                if(state_manager.separatedHumidity)
                    replace("HumiditySeparatedDial.qml", {"stack": adjustmentStack})
                else
                    replace("HumidityUnifiedDial.qml", {"stack": adjustmentStack})
            }

            function confirmSettings()
            {
                var intList = [hum_1, hum_aux];
                backend.separateHumidity(root.separated, intList)
                stack.pop()
            }

            function setHum1(val)
            {
                hum_1 = val;
            }

            function setHumAux(val)
            {
                hum_aux = val
            }

            pushEnter: Transition {
                enabled: false
            }
            pushExit: Transition {
                enabled: false
            }
            popEnter: Transition {
                enabled: false
            }
            popExit: Transition {
                enabled: false
            }

            replaceEnter: Transition {
                enabled: false
            }

            replaceExit: Transition {
                enabled: false
            }
        }

        Rectangle
        {
            anchors.verticalCenter: dehumidifyButton.verticalCenter
            width: cancel.width + save.width + 50
            height: cancel.height
            anchors.horizontalCenter: parent.horizontalCenter
            color:Style.transparent

            CancelButton
            {
                id: cancel
                anchors.left: parent.left
                onClicked:
                {
                    stack.pop()
                }
            }

            SaveButton
            {
                id: save
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                maEnabled:(adjustmentStack.hum_1 <= humidity_1.max && adjustmentStack.hum_aux <= humidity_aux.max) && // leq max
                          (adjustmentStack.hum_1 >= humidity_1.minimumOn || adjustmentStack.hum_1 === humidity_1.min) && // hum1 == min || hum1 >= min on
                          (adjustmentStack.hum_aux >= humidity_aux.minimumOn || adjustmentStack.hum_aux === humidity_aux.min ) // hum2 == min || hum2 >= min on

                onClicked:
                {
                    adjustmentStack.confirmSettings();
                }
            }
        }

        Rectangle
        {
            id: dehumidifyButton
            width: 175
            radius: .4 * width
            height : 44
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            color:Style.primary_dark
            border.width: 2
            border.color: Style.primary_light

            Text
            {
                id: dehumidifyText
                color: Style.primary_light
                text: qsTr("DEHUMIDIFY")
                font: Style.buttonFont
                x: parent.width * .35
                anchors.verticalCenter: parent.verticalCenter
            }

            Item
            {
                id: dehumidifyItem
                height: .6 * parent.height
                width: height
                x: .1 * parent.width
                anchors.verticalCenter: parent.verticalCenter
                Image
                {
                    id: dehumidifyIcon
                    source: "../../iconography/icon_40_dehumidify.svg"
                    height: parent.height
                    width: parent.width
                    sourceSize.height: height
                    sourceSize.width: width

                }

                ColorOverlay
                {
                    anchors.fill:dehumidifyIcon
                    source: dehumidifyIcon
                    color:Style.primary_light
                }
            }

            MouseArea
            {
                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold:
                {
                    dehumidifyButton.color = Style.primary_light_selected
                    dehumidifyButton.delay(50)
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
                    popupStack.dehumidify();
                    dehumidifyButton.color = Style.primary_dark
                    timer1.stop()
                }
            }
        }

        HelpIcon {
            id: hint_button_dehumidify
            anchors.left: dehumidifyButton.right
            anchors.leftMargin: 10
            anchors.verticalCenter: dehumidifyButton.verticalCenter

            onClicked:
            {
                popupStack.pushHelpBox("Dehumidification Settings",valueHolder.helpText)
            }
        }
    }

    Item {
        id: valueHolder
        property string helpText: "Prior to shutting down, the VITA should always be dehumidified to clear the machine of moisture. This is recommended to prevent the buildup of any contaminants. It is also recommended that dehumidification be performed when changing out the water supply."
    }
}
