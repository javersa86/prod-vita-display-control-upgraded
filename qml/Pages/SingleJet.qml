/**
  Added Help Icons for modes.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12

import "../CustomObjects"
import "../Styles"

Rectangle {
    id: root_window
    objectName: "single_jet_page"
    color: Style.primary_dark

    property Item updateSwitch

    property StackView homeStack
    property StackView popupStack
    property real time: 0
    property int tv1_val
    property int map_val

    property int max_pip: 0
    property int max_sp: 0

    property int rate_millis: state_manager.rate1Setting > 0 ? (60 / state_manager.rate1Setting) * 1000 : 1000
    property bool received_notification: false
    
    property int notificationSP1: 0
    property int notificationSP2: 1
    property int notificationO2: 2
    property int notificationPIP: 3
    property int notificationAux: 4
    property int notificationTV1: 5
    property int notificationTV2: 6
    property int notificationMAP: 7

    //...

    Component.onCompleted: {
        graph_timer.start();
        pip_update_timer.start();
        maintenance_manager.startTimer();
        version_manager.logVersions();

        if (state_manager.laser_mode) lm_switch.checked = true
    }

    Connections
    {
        target: state_manager

        onForceManualOffSignal:
        {
            if (mm_switch.checked === true)
            {
                mm_switch.checked = false
            }
        }
    }

    HamburgerButton {
        id: hamburger
        x: 0 //19
        y: -10 //14
        onClicked: homeStack.openHamburger()
    }

    Timer
    {
        id: pip_update_timer
        onTriggered:
        {
            pip_button.measuredValueText = max_pip
            max_pip = 0
            sp1_button.measuredValueText = max_sp
            max_sp = 0
        }
        interval: rate_millis
        repeat: true
    }

    Timer {
        id: graph_timer
        onTriggered:
        {
            var index = Math.round(time) % 10000

            if (state_manager.sp_line_state)
            {
                graph.addData(index, state_manager.notification_vector[ notificationPIP ], 0)
            }
            else
            {
                graph.addData(index, state_manager.notification_vector[ notificationPIP ], state_manager.notification_vector[ notificationSP1 ])
            }

            if(max_pip < state_manager.notification_vector[ notificationPIP ])
            {
                max_pip = Math.round(state_manager.notification_vector[ notificationPIP ])
            }

            if(max_sp < state_manager.notification_vector[ notificationSP1 ])
            {
                max_sp = Math.round(state_manager.notification_vector[ notificationSP1 ])
            }

            time += graph_timer.interval
        }
        interval: 30
        repeat: true
    }

    PneumaticButton {
        id: pip_button
        objectName: "pip_button"
        x: 27
        y: 82
        setting_id: pip.id

        unit: pip.unit
        title: pip.title
        setValueText: state_manager.pip
        measuredValueText: "0"
        gradientBelowVisible: true
        measuredColor: Style.pip
        setColor: Style.pip
        measuredDisplayColor: Style.pip
        min: pip.min
        max: pip.max
        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit, "helpText": pip.help,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step": pip.step, "popupStack": popupStack, "warningThreshold": pip.warningThreshold})
        }
        Rectangle {
            id:pip_mode_indicator
            width: 30
            height:30
            color:Style.primary_dark
            border.color:Style.pip
            border.width: 2
            radius: 20
            //visible:true
            visible:(pipModeFlag && !homeIcon.visible)
            //x:172
            x:15
            //y:53
            y:15

          Image {
            id: pip_mode_icon
            visible:(pipModeFlag && !homeIcon.visible)

            source: "../iconography/icon_40_alarm_3.svg"
            width:pip_mode_indicator.width
            height:pip_mode_indicator.height
            smooth: true
            anchors.fill:pip_mode_indicator

            ColorOverlay {
                anchors.fill: pip_mode_icon
                source: pip_mode_icon
                color: Style.pip
            }

           }
        }


    }

    PneumaticButton {
        id: sp1_button
        objectName: "sp1_button"
        x: 27
        y: 264
        setting_id: stacking_pressure_1.id

        unit: stacking_pressure_1.unit
        title: stacking_pressure_1.title
        setValueText: state_manager.sp1
        measuredValueText: "0" //Math.round(state_manager.notification_vector[ notificationSP1 ])
        gradientBelowVisible: true
        measuredColor: Style.sp
        setColor: Style.sp
        measuredDisplayColor: Style.sp
        min: stacking_pressure_1.min
        max: stacking_pressure_1.max

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step": stacking_pressure_1.step, "popupStack": popupStack,
                               "helpText": stacking_pressure_1.help, "warningThreshold": stacking_pressure_1.warningThreshold})
        }
    }

    PneumaticButton {
        id: aux_flow_button
        objectName: "aux_flow_button"
        x: 27
        y: 446
        setting_id: aux_flow.id
        unit: aux_flow.unit
        title: aux_flow.title
        measuredValueText: Math.round(state_manager.notification_vector[ notificationAux ])
        setValueText: state_manager.aux
        min: aux_flow.min
        max: aux_flow.max
        minOn: aux_flow.minimumOn

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "minOn": minOn, "value" : setValueText, "step": aux_flow.step, "popupStack": popupStack,
                               "helpText": aux_flow.help, "warningThreshold": aux_flow.warningThreshold})
        }
    }

    HumidityIcon {
        id: hum1_button
        objectName: "hum1_button"
        x: 27
        y: 628
        separated: state_manager.separatedHumidity

        onClicked: {
            homeStack.push("Humidity/HumidityAdjustment.qml", {"stack": homeStack, "popupStack":popupStack})
        }
    }

    PneumaticButton {
        id: dp1_button
        objectName: "dp1_button"
        x: 340
        y: 446
        setting_id: driving_pressure_1.id
        unit: driving_pressure_1.unit
        title: driving_pressure_1.title
        measuredValueText: etco2_button.modeEnabled ? state_manager.etco2DP: state_manager.dp1
        setValueText: etco2_button.modeEnabled ? state_manager.etco2DP: state_manager.dp1
        min: driving_pressure_1.min
        max: driving_pressure_1.max

        locked: etco2_button.modeEnabled
        borderColor: etco2_button.modeEnabled ? Style.mode_active_warning : Style.primary_light

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step" : driving_pressure_1.step, "popupStack": popupStack,
                               "helpText":driving_pressure_1.help, "warningThreshold": driving_pressure_1.warningThreshold})
        }
    }

    PneumaticButton {
        id: freq1_button
        objectName: "freq1_button"
        x: 340
        y: 628
        setting_id: rate_1.id
        unit: rate_1.unit
        title: rate_1.title
        measuredValueText: etco2_button.modeEnabled ? state_manager.etco2Rate : state_manager.rate1
        setValueText: etco2_button.modeEnabled ? state_manager.etco2Rate : state_manager.rate1
        min: rate_1.min
        max: rate_1.max

        locked: etco2_button.modeEnabled
        borderColor: etco2_button.modeEnabled ? Style.mode_active_warning : Style.primary_light

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step": rate_1.step, "popupStack": popupStack,
                               "helpText": rate_1.help, "warningThreshold": rate_1.warningThreshold})
        }
    }

    PneumaticButton {
        id: it1_button
        objectName: "it1_button"
        x: 654
        y: 446
        setting_id: inspiratory_time_1.id
        unit: inspiratory_time_1.unit
        title: inspiratory_time_1.title
        measuredValueText: etco2_button.modeEnabled ? state_manager.etco2IT: state_manager.it1
        setValueText: etco2_button.modeEnabled ? state_manager.etco2IT: state_manager.it1
        min: inspiratory_time_1.min
        max: inspiratory_time_1.max

        locked: etco2_button.modeEnabled
        borderColor: etco2_button.modeEnabled ? Style.mode_active_warning : Style.primary_light

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step": inspiratory_time_1.step, "popupStack": popupStack,
                               "helpText": inspiratory_time_1.help, "warningThreshold": inspiratory_time_1.warningThreshold})
        }
    }

    PneumaticButton {
        id: o2_button
        objectName: "o2_button"
        x: 654
        y: 628
        setting_id: oxygen.id
        unit: oxygen.unit
        title: oxygen.title

        measuredValueText: Math.round(state_manager.notification_vector[ notificationO2 ])
        setValueText: state_manager.o2
        min: oxygen.min
        max: lm_switch.checked? state_manager.laserO2Limit : oxygen.max

        borderColor: lm_switch.checked? warningDisplayed : Style.primary_light
        setColor: lm_switch.checked? warningDisplayed : Style.primary_light
        measuredDisplayColor: lm_switch.checked? warningDisplayed : Style.primary_light
        measuredColor: lm_switch.checked? warningDisplayed : Style.primary_light
        warningDisplayed: warning_manager.laserWarning === 0 ? Style.o2_color :
                          warning_manager.laserWarning === 1 ? Style.notice :
                                                               Style.primary_light

        onClicked: {
            homeStack.push("SettingDial.qml", {"homeStack": homeStack, "title": title, "unit": unit,
                               "settingID": setting_id, "min" : min, "max" : max, "value" : setValueText, "step": oxygen.step, "popupStack": popupStack,
                               "helpText": oxygen.help, "warningThreshold": oxygen.warningThreshold})
        }
    }

    StatisticDisplay {
        id: map_display
        objectName: "map_display"
        title: Strings.map
        unit: "(" + Strings.cmh2o + ")"
        value: state_manager.notification_vector[ notificationMAP ] > 9999 ? 9999 : state_manager.notification_vector[ notificationMAP ]
        x: 970
        y: 447
    }

    StatisticDisplay {
        id: tv_display
        objectName: "tv_display"
        title: Strings.tv
        unit: "(" + Strings.ml + ")"
        value: state_manager.notification_vector[ notificationTV1 ] > 9999 ? 9999 : state_manager.notification_vector[ notificationTV1 ]
        x: 1075
        y: 447
    }

    StatisticDisplay {
        id: mv_display
        objectName: "mv_display"
        title: Strings.mv
        unit: "(" + Strings.lpm + ")"
        value: (state_manager.notification_vector[ notificationTV1 ] * state_manager.rate1 / 1000) > 9999 ? 9999 : (state_manager.notification_vector[ notificationTV1 ] * state_manager.rate1 / 1000)
        x: 1180
        y: 447
    }

    Rectangle {
        id: etco2_box
        x: 955
        width: 115
        height: 60
        radius: 5
        anchors.verticalCenter: etco2_button.verticalCenter
        color: Style.transparent
        clip: true

        signal clicked()

        Text {
            id: etco2_title
            color: Style.mode_label
            font: Style.titleFont
            text: "ETCO<sub>2</sub>"
            textFormat: Text.RichText
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
        }

        HelpIcon {
            id: hint_etco2
            x: 55
            anchors.verticalCenter: parent.verticalCenter
            pressColor: Style.general_set_display
            releaseColor: Style.general_set_display
            onClicked:
            {
                etco2_box.clicked()
            }
        }

        MouseArea
        {
            id: mouseAreaHelpBox1
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                etco2_box.color = Style.primary_light_selected
                hint_etco2.state = 1
                etco2_box.delay(50)
            }
        }

        function delay(delayTime)
        {
            etco2_box_timer.interval = delayTime;
            etco2_box_timer.start();
        }

        Timer {
            id: etco2_box_timer
            repeat: false
            onTriggered:
            {
                popupStack.pushHelpBox("ETCO<sub>2</sub> Mode", valueHolder.helpTextET)
                etco2_box.color = Style.transparent
                hint_etco2.state = 0
                etco2_box_timer.stop()
            }
        }
    }

    EndTidalButton {
        id: etco2_button
        x: 1078
        y: 586

        mmChecked: mm_switch.checked

        onClicked:
        {
            if (etco2_button.modeEnabled === false)
            {

                root_window.updateSwitch = root_window.popupStack.push("../CustomObjects/ModeSwitchConfirm.qml",
                                                                       {
                                                                           'modeID': 6,
                                                                           "modeText": "Switching to End-Tidal"
                                                                       })
            }
            else
            {
                backend.setMode(modeID,0)
            }

        }

        onModeEnabledChanged:
        {
            if(!etco2_button.modeEnabled && state_manager.etco2_success === 1)
            {
                etco2_time.seconds = 0;
                etco2_timer.stop();
                etco2_timer.start();
            }
        }
    }

    Item {
        id: etco2_item
        width: 35
        height:40
        x: 1190
        y: 585
        Image {
            id: timer_icon
            source: "../iconography/icon_40_progress.svg"
            sourceSize.width: width
            sourceSize.height: height
            width: parent.width
            height: parent.height
            smooth: true
            visible: false
        }

        ColorOverlay {
            anchors.fill: timer_icon
            source: timer_icon
            color: Style.mode_label
        }
    }

    Text {
        id: etco2_time
        font: Style.titleFont
        color: Style.primary_light
        property var seconds: 0
        text: "00:00"
        width: 35
        height:24
        x: 1226
        y: 595

        function secondsToTime()
        {
            var hours = Math.floor(etco2_time.seconds / (60 * 60));

            var divisor_for_minutes = etco2_time.seconds % (60 * 60);
            var minutes = Math.floor(divisor_for_minutes / 60);

            etco2_time.text =
                    prependZero(hours)  +
                    ":" +
                    prependZero(minutes)
        }

        function prependZero(num)
        {
            if(num < 10)
            {
                return String("0" + num).slice(-2);
            }
            else return num
        }
    }

    Timer {
        id: etco2_timer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true

        onTriggered:
        {
            etco2_time.secondsToTime()
            etco2_time.seconds =  etco2_time.seconds + 1
        }
    }

    Rectangle {
        id: lm_box
        x: 955
        width: 115
        height: 75
        radius: 5
        anchors.verticalCenter: lm_switch.verticalCenter
        color: Style.transparent
        clip: true

        signal clicked

        Text
        {
            id: lm_title
            color: Style.mode_label
            font: Style.titleFont
            text: "Limited<br>O<sub>2</sub>"
            textFormat: Text.RichText
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
        }

        HelpIcon {
            id: hint_lm
            x: 55
            anchors.verticalCenter: parent.verticalCenter
            pressColor: Style.general_set_display
            releaseColor: Style.general_set_display
            onClicked:
            {
                lm_box.clicked()
            }
        }

        MouseArea
        {
            id: mouseAreaHelpBox2
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                lm_box.color = Style.primary_light_selected
                hint_lm.state = 1
                lm_box.delay(50)
            }
        }

        function delay(delayTime)
        {
            lm_box_timer.interval = delayTime;
            lm_box_timer.start();
        }

        Timer {
            id: lm_box_timer
            repeat: false
            onTriggered:
            {
                popupStack.pushHelpBox("Limited O<sub>2</sub> Mode", valueHolder.helpTextLM)
                lm_box.color = Style.transparent
                hint_lm.state = 0
                lm_box_timer.stop()
            }
        }
    }
    
    ModeSwitch {
        id: lm_switch
        x: 1078
        y: 667
        checkedText: "On"
        uncheckedText: "Off"
        modeID: 0
        modeColor: o2_button.warningDisplayed
        enabled: !state_manager.manual_mode && !state_manager.o2_cal_mode
        opacity: enabled ? 1 : .3
        popupEnabled: true

        onConfirmSignal:
        {
            root_window.updateSwitch = root_window.popupStack.push("../CustomObjects/ModeSwitchConfirm.qml",
                                                                   {
                                                                       'modeID': 0,
                                                                       "modeText": "Switching to Limited O<sub>2</sub> Mode"
                                                                   })
        }
    }

    Rectangle {
        id: mm_box
        x: 955
        width: 115
        height: 60
        radius: 5
        anchors.verticalCenter: mm_switch.verticalCenter
        color: Style.transparent
        clip: true

        signal clicked

        Text {
            id: mm_title
            color: Style.mode_label
            font: Style.titleFont
            text: "System"
            textFormat: Text.RichText
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.verticalCenter: parent.verticalCenter
        }

        HelpIcon {
            id: hint_mm
            x: 55
            anchors.verticalCenter: parent.verticalCenter
            pressColor: Style.general_set_display
            releaseColor: Style.general_set_display

            onClicked:
            {
                mm_box.clicked()
            }
        }

        MouseArea
        {
            id: mouseAreaHelpBox3
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                mm_box.color = Style.primary_light_selected
                hint_mm.state = 1
                mm_box.delay(50)
            }
        }

        function delay(delayTime)
        {
            mm_box_timer.interval = delayTime;
            mm_box_timer.start();
        }

        Timer {
            id: mm_box_timer
            repeat: false
            onTriggered:
            {
                popupStack.pushHelpBox("Manual Mode",valueHolder.helpTextMM)
                mm_box.color = Style.transparent
                hint_mm.state = 0
                mm_box_timer.stop()
            }
        }
    }

    ModeSwitch {
        id: mm_switch
        x: 1078
        y: 746
        checkedText: "Manual"
        uncheckedText: "Auto"
        modeID: 2
        enabled: !state_manager.etco2_mode
        opacity: state_manager.etco2_mode ? .3 : 1
        popupEnabled: true


        onPressed: if (mm_switch.checked && state_manager.etco2_button_state && !state_manager.etco2_mode) state_manager.setEtco2ButtonState(0)


        onConfirmSignal:
        {
            root_window.updateSwitch = root_window.popupStack.push("../CustomObjects/ModeSwitchConfirm.qml",
                                                                   {
                                                                       'modeID': 2,
                                                                       "modeText": "Switching to Manual Mode"
                                                                   })
        }

        onCheckedChanged: etco2_button.mmChecked = mm_switch.checked

    }

    Connections
    {
        target: updateSwitch

        onExit:
        {
            if (itemCheck === 1)
            {
                if (modeID === 0)
                {
                    lm_switch.checked = true
                }
                if (modeID === 2)
                {
                    mm_switch.checked = true
                }
            }

            if (itemCheck === 1 && modeID === 6)
            {
                backend.setMode(modeID,1)
            }
            else if (itemCheck === 0 && modeID === 6)
            {
                etco2_button.backgroundColorState = etco2_button.modeEnabled ? Style.mode_active_warning : Style.primary_dark
            }

            popupStack.clear()
        }
    }
    
    Rectangle {
        id: graph_box
        width: 885
        height: 344
        x: 339
        y: 80
        color: Style.transparent



        Graph {
            id: graph
            width: graph_border.width * .99
            height: graph_border.height * .95
            anchors.centerIn: parent
            pipSetting: state_manager.pip
            sp1Setting: Math.round(state_manager.sp1)
            ymax: Math.max(state_manager.pip, state_manager.sp1) * 1.2
            borderWidth: graph_border.border.width
            lineVisible: !state_manager.sp_line_state

        }

        Rectangle {
            id: graph_border
            objectName: "graph_box"
            anchors.fill: parent
            color: Style.transparent
            border.color: Style.unclickable_border
            border.width: 4
            radius: 8


        }

    }
    Item {
        id: valueHolder
        property string helpTextET: etco2_rate.help
        property string helpTextLM: laser_o2.help
        property string helpTextMM: "Manual Mode disables automatic ventilation control to the operator. Ventilation only occurs when the rotary knob is being pressed by the operator. The inspiratory time and breath rate are controlled by the user by how fast and how long they press on the rotary knob. The internal driving pressure will still be controlled by the NVENT and is adjustable. The Peak Inspiratory Pressure and Stacking Pressure thresholds are still monitored by the machine. The LED ring surrounding the rotary knob will glow orange to indicate that the knob will allow the user to control ventilation. Additionally, the start/stop button will not be illuminated and is deactivated while manual mode is active."
    }
}
