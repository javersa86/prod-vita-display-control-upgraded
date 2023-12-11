import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root_window
    color: Style.primary_dark
    objectName: "PresetsPage"

    property StackView homeStack
    property StackView popupStack
    property int numPresets
    property ListModel model: ListModel{}
    property ListModel model_page_2: ListModel{}
    property Item passCodePage;

    property Item passCodePresetPage;

    property string editPage: "EditPreset.qml"
    property string editPassCodePresetPage: "ChangePresetConfirm.qml"

    property int pageNumber: 1

    Component.onCompleted:
    {
        state_manager.preset_create_active = 0;
        populatePresets()
    }

    function populatePresets()
    {
        model.clear()
        model_page_2.clear()
        var presets = [
                    preset_manager.preset1,
                    preset_manager.preset2,
                    preset_manager.preset3,
                    preset_manager.preset4,
                    preset_manager.preset5,
                    preset_manager.preset6,
                    preset_manager.preset7,
                    preset_manager.preset8,
                    preset_manager.preset9,
                    preset_manager.preset10,
                    preset_manager.preset11,
                    preset_manager.preset12
                ];
        var i;
        if (preset_manager.numPresets >= 7)
        {
            for( i = 0 ; i < 6; i++ )
            {
                preset_manager.updatePresetNameIndex(i);
                model.append({
                                 sp1Value : presets[i][stacking_pressure_1.id],
                                 sp2Value : presets[i][stacking_pressure_2.id],
                                 it1Value : presets[i][inspiratory_time_1.id],
                                 it2Value : presets[i][inspiratory_time_2.id],
                                 rate1Value : presets[i][rate_1.id],
                                 auxValue: presets[i][aux_flow.id],
                                 rate2Value : presets[i][rate_2.id],
                                 o2Value : presets[i][oxygen.id],
                                 hum1Value : presets[i][humidity_1.id],
                                 hum2Value : presets[i][humidity_2.id],
                                 humauxValue : presets[i][humidity_aux.id],
                                 dp1Value : presets[i][driving_pressure_1.id],
                                 dp2Value : presets[i][driving_pressure_2.id],
                                 djmValue : false,
                                 pipValue : presets[i][pip.id],
                                 presetNameValue: preset_manager.presetName
                             })
            }
            for ( var j = i; j < preset_manager.numPresets; j++)
            {
                preset_manager.updatePresetNameIndex(j);
                model_page_2.append({
                                        sp1Value : presets[j][stacking_pressure_1.id],
                                        sp2Value : presets[j][stacking_pressure_2.id],
                                        it1Value : presets[j][inspiratory_time_1.id],
                                        it2Value : presets[j][inspiratory_time_2.id],
                                        rate1Value : presets[j][rate_1.id],
                                        auxValue: presets[j][aux_flow.id],
                                        rate2Value : presets[j][rate_2.id],
                                        o2Value : presets[j][oxygen.id],
                                        hum1Value : presets[j][humidity_1.id],
                                        hum2Value : presets[j][humidity_2.id],
                                        humauxValue : presets[j][humidity_aux.id],
                                        dp1Value : presets[j][driving_pressure_1.id],
                                        dp2Value : presets[j][driving_pressure_2.id],
                                        djmValue : false,
                                        pipValue : presets[j][pip.id],
                                        presetNameValue: preset_manager.presetName
                                    })
            }
        }
        else if (preset_manager.numPresets < 7)
        {
            for( i = 0 ; i < preset_manager.numPresets; i++ )
            {
                preset_manager.updatePresetNameIndex(i);
                model.append({
                                 sp1Value : presets[i][stacking_pressure_1.id],
                                 sp2Value : presets[i][stacking_pressure_2.id],
                                 it1Value : presets[i][inspiratory_time_1.id],
                                 it2Value : presets[i][inspiratory_time_2.id],
                                 rate1Value : presets[i][rate_1.id],
                                 auxValue: presets[i][aux_flow.id],
                                 rate2Value : presets[i][rate_2.id],
                                 o2Value : presets[i][oxygen.id],
                                 hum1Value : presets[i][humidity_1.id],
                                 hum2Value : presets[i][humidity_2.id],
                                 humauxValue : presets[i][humidity_aux.id],
                                 dp1Value : presets[i][driving_pressure_1.id],
                                 dp2Value : presets[i][driving_pressure_2.id],
                                 djmValue : false,
                                 pipValue : presets[i][pip.id],
                                 presetNameValue: preset_manager.presetName
                             })
            }
        }

        pageNumber = 1
    }

    Connections
    {
        target: preset_manager

        onPresetsChanged:
        {
            populatePresets();
        }
    }

    Connections
    {
        target: passCodePage
        onPassCodeCorrect:
        {
            if(root_window.passCodePage.nextPage === root_window.editPage){
                root_window.homeStack.replace(editPage, root_window.passCodePage.parameters)
            }
        }
    }

    Connections
    {
        target: passcode_manager
    }

    Rectangle {
        id: main_container
        width: root_window.width * .95
        height: root_window.height * .78
        anchors.centerIn: root_window
        color:Style.transparent

        GridView
        {
            id: presetGrid
            y: main_container.height / 5
            width: parent.width
            height: main_container.height / 2.5

            interactive: false

            model: root_window.model
            cellWidth:main_container.width / 3
            cellHeight:main_container.height / 2.5

            visible: pageNumber == 1

            delegate: Rectangle {
                PresetIcon {
                    title: presetNameValue;
                    width: main_container.width / 3.5;
                    height: main_container.height / 3;
                    sp1:sp1Value;
                    sp2: sp2Value;
                    it1:it1Value;
                    rate1:rate1Value;
                    rate2:rate2Value;
                    o2:o2Value;
                    hum1:hum1Value;
                    hum2:hum2Value;
                    aux: auxValue
                    humaux: humauxValue;
                    dp1:dp1Value;
                    dp2:dp2Value;
                    djm:djmValue;
                    pip:pipValue;
                    grid: root_window.model;
                    listIndex: index;
                    stack: homeStack;
                    popup: popupStack
                }
            }
        }

        GridView
        {
            id: presetGrid1
            y: main_container.height / 5
            width: parent.width
            height: main_container.height / 2.5

            interactive: false

            model: root_window.model_page_2
            cellWidth:main_container.width / 3
            cellHeight:main_container.height / 2.5

            visible: pageNumber == 2

            delegate: Rectangle {
                PresetIcon {
                    title: presetNameValue;
                    width: main_container.width / 3.5;
                    height: main_container.height / 3;
                    sp1:sp1Value;
                    sp2: sp2Value;
                    it1:it1Value;
                    rate1:rate1Value;
                    rate2:rate2Value;
                    o2:o2Value;
                    hum1:hum1Value;
                    hum2:hum2Value;
                    aux: auxValue
                    humaux: humauxValue;
                    dp1:dp1Value;
                    dp2:dp2Value;
                    djm:djmValue;
                    pip:pipValue;
                    grid: root_window.model_page_2;
                    listIndex: index + 6;
                    stack: homeStack;
                    popup: popupStack
                }
            }
        }
    }

    Text {
        id: pageNumberText
        text: "Page Number: " + pageNumber + " / 2"
        visible: preset_manager.numPresets > 6
        font: Style.buttonFont
        color: Style.primary_light
        anchors.verticalCenter: nextPageButton.verticalCenter
        anchors.right:  nextPageButton.left
        anchors.rightMargin: 16
    }

    SettingOptionsButton
    {
        id: nextPageButton
        title: pageNumber == 1 ? "Next" : "Last"
        height: 48
        width: 120
        anchors.right: root_window.right
        anchors.rightMargin: 16
        anchors.bottom: root_window.bottom
        anchors.bottomMargin: 16

        enabled: preset_manager.numPresets > 6
        visible: preset_manager.numPresets > 6

        onClicked:
        {
            if (pageNumber == 1)
            {
                pageNumber = 2
            }
            else
            {
                pageNumber = 1
            }
        }
    }

    Rectangle
    {
        color: Style.primary_dark
        width:parent.width
        height:presetGrid.y
        anchors.top: main_container.top
        anchors.left:main_container.left

        Text
        {
            id: titleDisplay
            text: "Presets"
            font: Style.numericUiDisplayFont
            color:Style.primary_light
        }
    }

    Rectangle
    {
        id: createButton
        anchors.top:main_container.top
        anchors.right: main_container.right
        width: 218
        height: 48
        radius: .5 * height
        color: Style.transparent
        border.color: Style.primary_light
        border.width: 2

        function delay(delayTime)
        {
            createTimer.interval = delayTime;
            createTimer.start();
        }

        Timer {
            id: createTimer
            repeat: false
            onTriggered:
            {
                if (preset_manager.numPresets < 12)
                {
                    preset_manager.updatePresetNameIndex(preset_manager.numPresets)
                    root_window.passCodePage = root_window.homeStack.push(
                                "PassCode.qml",
                                {
                                    "code": passcode_manager.presetPasscode,
                                    "nextPage": root_window.editPage,
                                    "stack":root_window.homeStack,
                                    "parameters": {
                                        "stack":root_window.homeStack,
                                        "index": preset_manager.numPresets,
                                        "dp1Val": 20,
                                        "freq1Val": 120,
                                        "it1Val": 35,
                                        "sp1Val": 24,
                                        "o2Val": 100,
                                        "pipVal": 28,
                                        "auxVal": 0,
                                        "hum1Val": 0,
                                        "titleAppend": "Create",
                                        "popupStack": popupStack
                                    }
                                })
                }
                else
                {
                    popupStack.push("PresetMaxPopup.qml",
                                    {
                                        "popupStack": root_window.popupStack
                                    });
                }
                createButton.color = Style.transparent
                createTimer.stop()
            }
        }

        Text
        {
            id: createText
            color:Style.primary_light
            font:Style.buttonFont
            text: qsTr("CREATE PRESET")
            anchors.verticalCenter: parent.verticalCenter
            x: 60
        }

        Item
        {
            id: plusItem
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter

            Image
            {
                id: plusIcon
                source: "../iconography/plus.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
                x: 10

            }

            ColorOverlay
            {
                anchors.fill: plusIcon
                source: plusIcon
                color: Style.primary_light
            }
        }

        MouseArea
        {
            id: createMouse
            anchors.fill:parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                createButton.color = Style.primary_light_selected
                createButton.delay(50)
            }
        }
    }

    HamburgerButton
    {
        id: hamburger
        x: 0
        y: -10
        onClicked: homeStack.openHamburger()
    }
}
