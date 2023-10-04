import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"
import IDs 1.0

InteractiveKnobPage{
    id: root
    property int value
    property string unit
    property string title
    property int settingID
    property int min
    property int max
    property int minOn
    property int step
    property string helpText
    property StackView stack
    property StackView popupStack
    property int initialValue

    signal settingConfirmed();
    signal openPresetKeyboard(var parameters);

    color: Style.primary_dark

    Component.onCompleted:
    {
        initialValue = value
    }

    GenericDial
    {
        id: dial

        value: root.value
        unit: root.unit
        title: root.title
        settingID: root.settingID
        min: root.min
        max: root.max
        step: root.step
        minOn: root.minOn
        stack: root.stack
        anchors.fill:parent
        helpText: root.helpText
        popupStack: root.popupStack

        onSettingConfirmed:
        {
            root.value = dial.value
            root.settingConfirmed()
        }

        onOpenKeyboard:
        {
            if (settingID !== humidity_1.id) {
                root.openPresetKeyboard({"value" : initialValue,
                                        "unit" : unit,
                                        "title" : title,
                                        "settingID" : settingID,
                                        "min" : min,
                                        "max" : max,
                                        "stack" : stack,
                                        "minOn" : minOn,
                                        "step" : step,
                                        "helpText" : helpText,
                                        "popupStack" : popupStack});
            }
        }
    }
}
