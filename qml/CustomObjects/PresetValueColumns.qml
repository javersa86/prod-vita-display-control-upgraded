import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"
import SettingIndex 1.0

Rectangle
{
    id: root

    color: Style.transparent

    property int paddingTop: 50

    property ListModel leftModel: ListModel{}
    property ListModel rightModel: ListModel{}

    property var settingNames
    property var oldSettings
    property var newSettings

    width: 630
    height: 208

    Component.onCompleted:
    {
        leftModel.clear()
        rightModel.clear()
        for (var i = 0; i < 4; i++) {
            leftModel.append({
                                 titleValue: settingNames[i],
                                 oldValue: oldSettings[i],
                                 newValue: newSettings[i],
                                 stateValue: oldSettings[i] < newSettings[i] ? 1 :
                                             oldSettings[i] > newSettings[i] ? 2 :
                                                                               0
                             })
        }
        for (i = 4; i < 8; i++) {
            rightModel.append({
                                  titleValue: settingNames[i],
                                  oldValue: oldSettings[i],
                                  newValue: newSettings[i],
                                  stateValue: oldSettings[i] < newSettings[i] ? 1 :
                                              oldSettings[i] > newSettings[i] ? 2 :
                                                                                0
                              })
        }
    }

    Component
    {
        id: presetDelegate

        Row {
            Rectangle {
                id: titleBox
                width: 315 * .20
                height: 52
                color: Style.transparent
                Text {
                    text: titleValue
                    font: Style.numberButtonFont
                    color:Style.numeric_ui_unit
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Rectangle {
                id: oldBox
                width: 315 * .20
                height: 52
                color: Style.transparent
                Text {
                    text: oldValue
                    font: Style.numberButtonFont
                    color:Style.numeric_ui_unit
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: arrowBox
                width: 315 * .10
                height: 52
                color: Style.transparent
                Text {
                    text: "&#x2192;"
                    textFormat: Text.RichText
                    font: Style.numberButtonFont
                    color:Style.numeric_ui_unit
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: newBox
                width: 315 * .20
                height: 52
                color: Style.transparent
                Text {
                    text: newValue
                    font: Style.numberButtonFont
                    color: stateValue === 1 ? Style.mode_active_warning : stateValue === 2 ? Style.general_set_display : Style.numeric_ui_unit
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id: stateBox
                width: 315 * .05
                height: 52
                color: Style.transparent
                Text {
                    text: stateValue === 1 ? "&#x2191;" : stateValue === 2 ? "&#x2193;" : ""
                    font: Style.numberButtonFont
                    textFormat: Text.RichText
                    color: stateValue === 1 ? Style.mode_active_warning : stateValue === 2 ? Style.general_set_display : Style.numeric_ui_unit
                    anchors.centerIn: parent
                }
            }
        }
    }

    Rectangle
    {
        id: settingsDisplay
        color: Style.transparent

        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left

        Rectangle
        {
            id: leftDisplay
            color:Style.transparent
            height: parent.height
            width: parent.width / 2
            anchors.top: parent.top
            anchors.left: parent.left

            ListView
            {
                model: root.leftModel
                delegate: presetDelegate
                anchors.fill: parent
            }
        }

        Rectangle
        {
            id: rightDisplay
            color:Style.transparent
            width: parent.width / 2
            height: parent.height
            anchors.top: parent.top
            anchors.right: parent.right

            ListView
            {
                model: root.rightModel
                delegate: presetDelegate
                anchors.fill: parent
            }
        }
    }
}
