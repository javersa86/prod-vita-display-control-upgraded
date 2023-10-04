import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"
import IDs 1.0

InteractiveKnobPage
{
    id:root_window
    color: Style.transparent

    property int value
    property string settingTitle
    property int settingId
    property int min
    property int max
    property string unit
    property int setValue
    property int step
    property string helpText
    property int topY
    property StackView popupStack

    property bool dialOpen: true

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .9 * parent.height
        y: .1 * parent.height
        color: Style.transparent

        Text {
            id: title
            text: root_window.settingTitle
            textFormat: Text.RichText
            color:Style.mode_label
            font: Style.settingPageTitle
            anchors.horizontalCenter: parent.horizontalCenter
        }

        StackView
        {
            id: adjustmentStack
            width: parent.width
            height: .5 * parent.height
            y: title.y + title.height + 25
            anchors.horizontalCenter: parent.horizontalCenter

            Component.onCompleted:
            {
                adjustmentStack.push("../../CustomObjects/ModeSettingDial.qml", {"valueHolder": valueHolder,"value": valueHolder.value, "stack": adjustmentStack})
            }

            function settingConfirmed()
            {
                if (valueHolder.min <= valueHolder.value && valueHolder.value <= valueHolder.max)
                {
                    backend.receiveSettingsUpdate(valueHolder.settingId, valueHolder.value);
                    buttonContainer.pushSettingPage("Settings/ETCO2Settings.qml", {"topY" : topY, "popupStack": popupStack});
                }
            }

            function openKeyboard()
            {
                adjustmentStack.clear()
                adjustmentStack.push("../../CustomObjects/ModeSettingKeypad.qml",{"valueHolder": valueHolder, "value": valueHolder.min, "stack": adjustmentStack})
                dialOpen = false
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
            id: buttonBox
            width: cancelButton.width + saveButton.width + 50
            height: cancelButton.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            color: Style.transparent

            CancelButton
            {
                id: cancelButton
                anchors.left: parent.left
                onClicked:
                {
                    buttonContainer.pushSettingPage("Settings/ETCO2Settings.qml", {"topY" : topY, "popupStack": popupStack});
                }
            }

            SaveButton
            {
                id:saveButton
                anchors.right: parent.right
                anchors.verticalCenter: cancelButton.verticalCenter
                maEnabled: valueHolder.min <= valueHolder.value && valueHolder.value <= valueHolder.max //true
                onClicked:
                {
                    backend.receiveSettingsUpdate(valueHolder.settingId, valueHolder.value);
                    buttonContainer.pushSettingPage("Settings/ETCO2Settings.qml", {"topY" : topY, "popupStack": popupStack});
                }
            }
        }

        KeypadButton
        {
            visible: dialOpen
            anchors.right: parent.right
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 16
            onClicked:
            {
                adjustmentStack.clear()
                adjustmentStack.push("../../CustomObjects/ModeSettingKeypad.qml",{"valueHolder": valueHolder, "value": valueHolder.min, "stack": adjustmentStack})
                dialOpen = false
            }
        }

        DialButton
        {
            visible: !dialOpen
            anchors.right: parent.right
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 16

            onClicked:
            {
                adjustmentStack.clear()
                adjustmentStack.push("../../CustomObjects/ModeSettingDial.qml", {"valueHolder": valueHolder,"value": valueHolder.setValue, "stack": adjustmentStack})
                dialOpen = true
            }
        }
    }

    Item {
        id: valueHolder
        property int value: root_window.value
        property int settingId: root_window.settingId
        property int min: root_window.min
        property int max: root_window.max
        property string unit: root_window.unit
        property int setValue: root_window.setValue
        property int step: root_window.step
        property string helpText: root_window.helpText
    }
}
