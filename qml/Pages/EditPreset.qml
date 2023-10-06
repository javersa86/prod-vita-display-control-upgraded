import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root
    color: Style.primary_dark
    property int index

    property StackView stack
    property StackView popupStack
    property int dp1Val
    property int dp2Val
    property int freq1Val
    property int freq2Val
    property int it1Val
    property int it2Val
    property int sp1Val
    property int sp2Val
    property int o2Val
    property int pipVal
    property int auxVal
    property int hum1Val
    property int hum2Val
    property int humauxVal
    property string titleAppend

    property Item adjustmentPage

    property var values: [root.dp1Val,
        root.dp2Val,
        root.freq1Val,
        root.freq2Val,
        root.it1Val,
        root.it2Val,
        root.sp1Val,
        root.sp2Val,
        root.o2Val,
        root.pipVal,
        root.auxVal,
        root.hum1Val,
        root.hum2Val,
        root.humauxVal]

    Component.onCompleted: {
        state_manager.preset_create_active = 1;
        populateFirstRow()
        populateSecondRow()
    }

    function populateFirstRow()
    {
        firstRow.append({setting_idVal: pip.id,
                            unitVal: pip.unit,
                            titleVal: pip.title,
                            helpVal: pip.help,
                            minVal: pip.min,
                            maxVal: pip.max,
                            minOnVal: pip.minimumOn,
                            stepVal: pip.step})
        firstRow.append({setting_idVal: inspiratory_time_1.id,
                            unitVal: inspiratory_time_1.unit,
                            titleVal: inspiratory_time_1.title,
                            helpVal: inspiratory_time_1.help,
                            minVal: inspiratory_time_1.min,
                            maxVal: inspiratory_time_1.max,
                            minOnVal: inspiratory_time_1.minimumOn,
                            stepVal: inspiratory_time_1.step})
        firstRow.append({setting_idVal: driving_pressure_1.id,
                            unitVal: driving_pressure_1.unit,
                            titleVal: driving_pressure_1.title,
                            helpVal: driving_pressure_1.help,
                            minVal: driving_pressure_1.min,
                            maxVal: driving_pressure_1.max,
                            minOnVal: driving_pressure_1.minimumOn,
                            stepVal: driving_pressure_1.step})
        firstRow.append({setting_idVal: oxygen.id,
                            unitVal: oxygen.unit,
                            titleVal: oxygen.title,
                            helpVal: oxygen.help,
                            minVal: oxygen.min,
                            maxVal: oxygen.max,
                            minOnVal: oxygen.minimumOn,
                            stepVal: oxygen.step})
    }

    function populateSecondRow()
    {
        secondRow.append({setting_idVal: stacking_pressure_1.id,
                            unitVal: stacking_pressure_1.unit,
                            titleVal: stacking_pressure_1.title,
                            helpVal: stacking_pressure_1.help,
                            minVal: stacking_pressure_1.min,
                            maxVal: stacking_pressure_1.max,
                            helpVal: stacking_pressure_1.help,
                            minOnVal: stacking_pressure_1.minimumOn,
                            stepVal: stacking_pressure_1.step})
        secondRow.append({setting_idVal: humidity_1.id,
                            unitVal: humidity_1.unit,
                            titleVal: humidity_1.title,
                            helpVal: humidity_1.help,
                            minVal: humidity_1.min,
                            maxVal: humidity_1.max,
                            minOnVal: humidity_1.minimumOn,
                            stepVal: humidity_1.step})
        secondRow.append({setting_idVal: aux_flow.id,
                            unitVal: aux_flow.unit,
                            titleVal: aux_flow.title,
                            helpVal: aux_flow.help,
                            minVal: aux_flow.min,
                            maxVal: aux_flow.max,
                            minOnVal: aux_flow.minimumOn,
                            stepVal: aux_flow.step})
        secondRow.append({setting_idVal: rate_1.id,
                            unitVal: rate_1.unit,
                            titleVal: rate_1.title,
                            helpVal: rate_1.help,
                            minVal: rate_1.min,
                            maxVal: rate_1.max,
                            minOnVal: rate_1.minimumOn,
                            stepVal: rate_1.step})
    }

    Connections
    {
        target: root.adjustmentPage
        onOpenPresetKeyboard:
        {
            root.stack.pop();
            root.adjustmentPage = root.stack.push("PresetKeypad.qml", parameters)
        }

        onOpenPresetDial:
        {
            root.stack.pop();
            root.adjustmentPage = root.stack.push("PresetDial.qml", parameters)
        }

        onSettingConfirmed:
        {
            root.values[root.adjustmentPage.settingID] = root.adjustmentPage.value
            root.stack.pop()
        }
    }

    ListModel
    {
        id: firstRow
    }

    ListModel
    {
        id: secondRow
    }


    Rectangle
    {
        id: mainContainer
        width: .95 * parent.width
        height: .93 * parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: 85
        color:Style.transparent

        Text {
            text: qsTr("Presets > " + root.titleAppend)
            font: Style.numericUiDisplayFont
            color:Style.primary_light
        }

        Rectangle
        {
            id: titleBox
            color: Style.transparent
            border.width: 2
            border.color:Style.primary_light
            radius:15
            width: .4 * parent.height
            height: .05 * parent.width
            y: .15 * parent.height

            Text {
                id: presetTitle
                text: preset_manager.presetName
                font: Style.numberButtonFont
                color:Style.primary_light
                x: .05 * titleBox.width
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea
            {
                anchors.fill: parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    titleBox.color = Style.primary_light_selected
                    titleBox.delay(50)
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
                    popupStack.push("PresetNamePopup.qml", {"popupStack": root.popupStack, "previous_name": preset_manager.presetName})
                    titleBox.color = Style.transparent
                    timer.stop()
                }
            }
        }

        Text {
            id: subtitle
            text: "Select Text Box to Edit"
            font: Style.buttonFont
            color: Style.numeric_ui_unit
            anchors.top: titleBox.bottom
            anchors.topMargin: 8
            x: .05 * titleBox.width
        }

        ListView{
            width: mainContainer.width
            height: mainContainer.height / 3
            orientation:ListView.Horizontal
            interactive: false
            contentHeight: 300
            contentWidth: 600
            spacing:200
            y: titleBox.y + titleBox.height + .1* mainContainer.height

            model: firstRow
            delegate : SettingButton {
                setting_id: setting_idVal
                unit:unitVal
                title: titleVal
                measuredValueText: root.values[setting_id]
                minOn: minOnVal
                helpText: helpVal
                step: stepVal

                onClicked: {
                    root.adjustmentPage = root.stack.push(
                                "PresetDial.qml",
                                {
                                    "popupStack": root.popupStack,
                                    "homeStack": root.stack,
                                    "title": title,
                                    "unit": unit,
                                    "settingID": setting_id,
                                    "min" : minVal,
                                    "max" : maxVal,
                                    "value" : measuredValueText,
                                    "stack":root.stack,
                                    "minOn": minOn,
                                    "step" : step,
                                    "helpText": helpText
                                }
                                )
                }

                Connections
                {
                    target: root.adjustmentPage
                    onSettingConfirmed:
                    {
                        if(root.adjustmentPage.settingID === setting_id){
                            root.values[root.adjustmentPage.settingID] = root.adjustmentPage.value
                            measuredValueText = root.adjustmentPage.value
                        }
                    }
                }
            }
        }

        ListView{
            width: mainContainer.width
            height: mainContainer.height / 3
            orientation:ListView.Horizontal
            interactive: false
            contentHeight: 300
            contentWidth: 600
            spacing:200
            y: titleBox.y + titleBox.height + .32* mainContainer.height

            model: secondRow
            delegate : SettingButton {

                setting_id: setting_idVal
                unit:unitVal
                title: titleVal
                measuredValueText: root.values[setting_id]
                minOn: minOnVal
                step: stepVal
                helpText: helpVal

                onClicked: {
                    root.adjustmentPage = root.stack.push(
                                "PresetDial.qml",
                                {
                                    "popupStack": root.popupStack,
                                    "homeStack": root.stack,
                                    "title": title,
                                    "unit": unit,
                                    "settingID": setting_id,
                                    "min" : minVal,
                                    "max" : maxVal,
                                    "value" : measuredValueText,
                                    "stack":root.stack,
                                    "minOn": minOn,
                                    "step" : step,
                                    "helpText": helpText
                                }
                                )
                }

                Connections
                {
                    target: root.adjustmentPage
                    onSettingConfirmed:
                    {
                        if(root.adjustmentPage.settingID === setting_id){
                            root.values[root.adjustmentPage.settingID] = root.adjustmentPage.value
                            measuredValueText = root.adjustmentPage.value
                        }
                    }
                }
            }
        }

        SaveButton
        {
            id: saveButton
            y: .85 * mainContainer.height
            anchors.right: parent.right
            maEnabled: true
            onClicked:
            {
                state_manager.preset_create_active = 0
                preset_manager.enterPresetName();
                preset_manager.updatePreset(root.index,root.values);
                root.stack.pop();
            }
        }

        CancelButton
        {
            anchors.verticalCenter: saveButton.verticalCenter
            x: saveButton.x - width * 1.3
            onClicked:
            {
                state_manager.preset_create_active = 0
                root.stack.pop()
            }
        }
    }
}
