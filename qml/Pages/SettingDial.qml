import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"
import IDs 1.0

InteractiveKnobPage{
    id: root
    property int value: state_manager.getSettingValue(settingID)
    property string unit
    property string title
    property string helpText
    property int settingID
    property int min
    property int max
    property int minOn
    property int step
    property int warningThreshold
    property StackView homeStack
    property StackView popupStack

    color: Style.primary_dark

    GenericDial
    {
        id: dial

        value: root.value
        unit: root.unit
        title: root.title
        settingID: root.settingID
        min: root.min
        max: root.max
        minOn: root.minOn
        stack: root.homeStack
        anchors.fill:parent
        step: root.step
        popupStack: root.popupStack
        helpText: root.helpText

        onSettingConfirmed:
        {
            if (dial.value < warningThreshold)
                confirmSetting(root.settingID,dial.value)
            else
            {
                popupStack.push("HighSettingConfirmation.qml", {"settingPage": root, "value": dial.value, "settingId": root.settingID, "settingTitle": title})
            }
        }

        onOpenKeyboard:
        {
            root.homeStack.openSettingKeyboard(root.title, root.unit, root.settingID, root.min, root.max, root.step, root.helpText, root.warningThreshold)
        }
    }

    function confirmSetting(id, value)
    {
        root.value = value
        backend.receiveSettingsUpdate(id, value)
        root.homeStack.pop()
        popupStack.clear()
    }

    function cancelSetting()
    {
        root.popupStack.clear()
    }
}
