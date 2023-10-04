import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id:root
    property string title
    property int pip
    property int sp1
    property int sp2
    property int it1
    property int it2
    property int rate1
    property int rate2
    property int o2
    property int hum1
    property int hum2
    property int humaux
    property int dp1
    property int dp2
    property int aux
    property bool djm
    property int listIndex
    property string code: "8"
    property ListModel grid
    property StackView stack
    property StackView popup
    property Item passCodePage;
    property string deletePage: "delete"
    property string editPage: "../Pages/EditPreset.qml"

    color: Style.transparent

    property int option: 0

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
            if (option == 0)
            {
                main_icon.color = Style.primary_dark
                root.popup.push("../Pages/ConfirmImplementPreset.qml",
                                {
                                    "popupStack": root.popup,
                                    "homeStack": root.stack,
                                    settings: [
                                        dp1,
                                        dp2,
                                        rate1,
                                        rate2,
                                        it1,
                                        it2,
                                        sp1,
                                        sp2,
                                        o2,
                                        pip,
                                        aux,
                                        hum1,
                                        hum2,
                                        hum1
                                    ]
                                })
            }
            else if (option == 1)
            {
                delete_item_area.color = Style.primary_dark
                delete_item.deleteSignal()
                root.passCodePage = stack.push(
                            "../Pages/PassCode.qml",
                            {
                                "code": passcode_manager.presetPasscode,
                                "nextPage": root.deletePage,
                                "stack":root.stack
                            })
            }
            else if (option == 2)
            {
                edit_item_area.color = Style.primary_dark
                preset_manager.updatePresetNameIndex(root.listIndex)
                root.passCodePage = stack.push(
                            "../Pages/PassCode.qml",
                            {
                                "code": passcode_manager.presetPasscode,
                                "nextPage": root.editPage,
                                "stack":root.stack,
                                "parameters": {
                                    "stack":stack,
                                    "index": root.listIndex,
                                    "dp1Val": root.dp1,
                                    "freq1Val": root.rate1,
                                    "it1Val": root.it1,
                                    "sp1Val": root.sp1,
                                    "o2Val": root.o2,
                                    "pipVal": root.pip,
                                    "auxVal":root.aux,
                                    "hum1Val":root.hum1,
                                    "titleAppend": "Edit",
                                    "popupStack": root.popup
                                }
                            })
            }

            timer.stop()
        }
    }

    Connections
    {
        target: root.passCodePage
        onPassCodeCorrect:
        {
            if(root.passCodePage.nextPage === deletePage){
                preset_manager.deletePreset(listIndex)
                root.stack.pop()
            }
            else if (root.passCodePage.nextPage === editPage)
            {
                root.stack.replace(editPage, root.passCodePage.parameters)
            }
        }
    }
    Connections
    {
        target: passcode_manager
    }

    Rectangle
    {
        id: main_icon

        border.color:Style.primary_light
        color: Style.primary_dark
        width: root.width
        height: .8 * root.height
        radius: 8

        MouseArea {
            id: setPresetMouseArea
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold: {
                option = 0
                main_icon.color = Style.primary_light_selected
                delay(50)
            }
        }

        Text {
            id: titleDisplay
            text: root.title
            font: Style.numberButtonFont
            color:Style.primary_light
            anchors.top: main_icon.top
            anchors.left:main_icon.left
            leftPadding: main_icon.width * .06
            topPadding: main_icon.height * .088
        }

        Rectangle
        {
            id:settingsDisplayDJM
            visible: root.djm
        }

        Rectangle
        {
            id:settingsDisplaySJM
            visible: ! root.djm
            color:Style.transparent

            height: main_icon.height * .36
            width: main_icon.width * .8
            x: titleDisplay.leftPadding
            y: titleDisplay.y + titleDisplay.height + .05 * main_icon.height

            property int paddingTop: 25

            Rectangle
            {
                id:leftSJM
                color:Style.transparent
                height: settingsDisplaySJM.height
                width: settingsDisplaySJM.width / 2

                property int guideline: .4 * leftSJM.width

                Rectangle{
                    id: spBox
                    color:Style.transparent

                    Text
                    {
                        id: spTitle
                        text:"SP:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: spBox.left
                    }

                    Text
                    {
                        id: spVal
                        text: root.sp1
                        x: leftSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: spUnit
                        text: qsTr("cmH<sub>2</sub>O")
                        textFormat: Text.RichText
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:spVal.right
                        leftPadding: 2
                    }
                } //SP BOX

                Rectangle{
                    id: pipBox
                    color:Style.transparent
                    y: spBox.y + spBox.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: pipTitle
                        text:"PIP:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: pipBox.left

                    }

                    Text
                    {
                        id: pipVal
                        text: root.pip
                        x:leftSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: pipUnit
                        text: qsTr("cmH<sub>2</sub>O")
                        textFormat: Text.RichText
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:pipVal.right
                        leftPadding: 2
                    }
                } //PIP BOX

                Rectangle{
                    id: itBox
                    color:Style.transparent
                    y: pipBox.y + pipBox.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: itTitle
                        text:"IT:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: itBox.left

                    }

                    Text
                    {
                        id: itVal
                        text: root.it1
                        x: leftSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: itUnit
                        text: qsTr("%")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:itVal.right
                        leftPadding: 2
                    }
                } //IT BOX

                Rectangle{
                    id: auxBox
                    color:Style.transparent
                    y: itBox.y + itBox.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: auxTitle
                        text:"AUX:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: auxBox.left

                    }

                    Text
                    {
                        id: auxVal
                        text: root.aux
                        x: leftSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: auxUnit
                        text: qsTr("LPM")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:auxVal.right
                        leftPadding: 2
                    }
                } //IT BOX
            } //SJM LEFT BOX

            Rectangle
            {
                id:rightSJM
                color:Style.transparent
                height: settingsDisplaySJM.height
                width: settingsDisplaySJM.width / 2
                x: width + 15
                property int guideline: .4 * rightSJM.width

                Rectangle{
                    id: freqBox
                    color:Style.transparent

                    Text
                    {
                        id: freqTitle
                        text:"Rate:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: freqBox.left

                    }

                    Text
                    {
                        id: freqVal
                        text: root.rate1
                        x:rightSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: freqUnit
                        text: qsTr("BPM")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:freqVal.right
                        leftPadding: 2
                    }
                }// FREQ BOX

                Rectangle{
                    id: o2Box
                    color:Style.transparent
                    y: freqBox.y + freqBox.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: o2Title
                        text:"O2:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: o2Box.left

                    }

                    Text
                    {
                        id: o2Val
                        text: root.o2
                        x:rightSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: o2Unit
                        text: qsTr("%")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:o2Val.right
                        leftPadding: 2
                    }
                }// O2 BOX

                Rectangle{
                    id: humBox
                    color:Style.transparent
                    y: o2Box.y + o2Box.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: humTitle
                        text:"HUM:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: humBox.left

                    }

                    Text
                    {
                        id: humVal
                        text: root.hum1
                        x:rightSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: humUnit
                        text: qsTr("level")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:humVal.right
                        leftPadding: 2
                    }
                }// HUM BOX

                Rectangle{
                    id: dpBox
                    color:Style.transparent
                    y: humBox.y + humBox.height + settingsDisplaySJM.paddingTop

                    Text
                    {
                        id: dpTitle
                        text:"DP:"
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left: dpBox.left

                    }

                    Text
                    {
                        id: dpVal
                        text: root.dp1
                        x:rightSJM.guideline
                        font: Style.buttonFont
                        color:Style.primary_light
                    }

                    Text
                    {
                        id: dpUnit
                        text: qsTr("PSI")
                        font: Style.buttonFont
                        color:Style.numeric_ui_unit
                        anchors.left:dpVal.right
                        leftPadding: 2
                    }
                }// DP BOX

            }// RIGHT SJM BOX
        }// SJM VALUE DISPLAY BOX
    }

    Item {
        id: delete_item
        height: root.height / 4 //6
        width: height

        anchors.right: root.right
        y: root.height - height / 2

        signal deleteSignal()

        Rectangle{
            id: delete_item_area
            height: parent.height
            width:height
            radius: .5*height
            border.width: 1
            border.color: Style.primary_light
            color: Style.primary_dark

            Image {
                id: delete_icon
                source: "../iconography/delete.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width * .8
                height: width
                smooth: true
                anchors.centerIn: parent
            }

            ColorOverlay {
                anchors.fill: delete_icon
                source: delete_icon
                color: Style.primary_light
            }

            MouseArea {
                id: delete_mouse_area

                anchors.fill:parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    option = 1
                    delete_item_area.color = Style.primary_light_selected
                    delay(50)
                }
            }
        }
    }

    Item {
        id: edit_item
        height: root.height / 4 //6
        width: height

        anchors.right: delete_item.left
        anchors.rightMargin: 16
        y: root.height - height / 2

        signal editSignal();

        Rectangle{
            id: edit_item_area
            height: parent.height
            width:height
            radius: .5*height
            border.width: 1
            border.color: Style.primary_light
            color: Style.primary_dark

            Image {
                id: edit_icon
                source: "../iconography/edit.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width * .8
                height: width
                smooth: true
                anchors.centerIn: parent
            }

            ColorOverlay {
                anchors.fill: edit_icon
                source: edit_icon
                color: Style.primary_light
            }

            MouseArea {
                id: edit_mouse_area

                anchors.fill: parent
                pressAndHoldInterval: 225
                onPressAndHold: {
                    option = 2
                    edit_item_area.color = Style.primary_light_selected
                    delay(50)
                }
            }
        }
    }
} // ROOT
