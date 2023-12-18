import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "Pages"
import "CustomObjects"
import "Styles"
import IDs 1.0

ApplicationWindow
{

    id: homeWindow

    visible: true
    width: 1280;
    height: 800
    color: Style.primary_dark

    property int screenLockFlag: state_manager.screen_lock_mode
    property int powerdownFlag: state_manager.power_down_flag
    property int demoModeFlag: state_manager.demo_mode
    property int pipModeFlag: state_manager.pip_monitoring_mode

    onPowerdownFlagChanged:
    {
        if (powerdownFlag)
        {
            if(state_manager.dehumidify_mode)
            {
                backend.initiatePowerdown(0);
            }
            else
            {
                if (state_manager.manual_mode || state_manager.aux)
                {
                    popupStack.push("Pages/JetActiveConfirmation.qml", {"popupStack": popupStack, "currentText": "SHUTDOWN", "procedureId": 0})
                }
                else
                {
                    popupStack.push("Pages/ShutdownConfirmation.qml",{"popupStack": popupStack})
                }
            }
        }

        else
        {
        }

        interactionTimer.restart()
    }

    onScreenLockFlagChanged:
    {
        if (screenLockFlag && state_manager.preset_complete) popupStack.push("Pages/ScreenLockOverlay.qml", {"popupStack" : popupStack})
    }

    StackView
    {
        id: homeStack
        Component.onCompleted:
        {
            homeStack.push("Pages/StartUpProgressPage.qml", {"homeStack": homeStack} )//"Pages/SingleJet.qml", {"homeStack": homeStack, "popupStack": popupStack})
        }

        enabled: !(popupStack.depth > 0 || serviceStack.depth > 0)

        anchors.fill: parent

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

        function openSettingKeyboard(title, unit, settingID, min, max, step, helpText, warningThreshold)
        {
            while (homeStack.depth > 1)
            {
                homeStack.pop()
            }
            homeStack.push("Pages/numeric_ui.qml",{"homeStack": homeStack, "title": title, "unit": unit,
                           "setting_id": settingID, "min": min, "max": max, "step": step, "popupStack": popupStack, "helpText": helpText, "warningThreshold": warningThreshold})
        }

        function openSettingDial(title, unit, settingID, min, max, step, helpText, warningThreshold)
        {
            while (homeStack.depth > 1)
            {
                homeStack.pop()
            }
            homeStack.push("Pages/SettingDial.qml",{"homeStack": homeStack, "title": title, "unit": unit,
                           "settingID": settingID, "min": min, "max": max, "step": step, "popupStack": popupStack, "helpText": helpText, "warningThreshold": warningThreshold})
        }

        function startupComplete()
        {
            homeStack.clear();
            homeStack.push("Pages/SingleJet.qml", {"homeStack": homeStack, "popupStack": popupStack})
        }

        function openHamburger()
        {
            hambugerMenu.open()
        }



        function confirmScreenLock()
        {
            if (state_manager.dehumidify_mode === 0 && state_manager.power_down_flag ===0)
            {
                popupStack.clear()
                popupStack.push("Pages/ScreenLockConfirmation.qml", {"popupStack": popupStack})
            }
        }


        function implementPreset( settings )
        {
            while (homeStack.depth > 1)
            {
                homeStack.pop()
            }
            popupStack.push("Pages/SettingsProgressPage.qml", {"settings": settings, "popupStack": popupStack});
        }
    }


    HamburgerMenu
    {
        id: hambugerMenu
        width: 317
        height: 802

        property Item passcodePage

        Connections
        {
            target: hambugerMenu.passcodePage
            onPassCodeCorrect:
            {
                hambugerMenu.passcodePage.stack.pop()
                hambugerMenu.passcodePage.nextStack.push(hambugerMenu.passcodePage.nextPage, hambugerMenu.passcodePage.parameters);
            }
        }
        Connections
        {
            target: passcode_manager
        }
        Connections
        {
            target: part_manager
        }
        Connections
        {
            target: time_manager
        }
        Connections
        {
            target: maintenance_manager
        }
        Connections
        {
            target: contact_manager
        }

        Connections
        {
            target: version_manager
        }

        onService:
        {
            while (homeStack.depth > 1)
            {
                homeStack.pop()
            }

            if(!serviceStack.depth)
            {
                hambugerMenu.passcodePage = homeStack.push(
                            "Pages/PassCode.qml",
                            {
                                "code": passcode_manager.servicePasscode,
                                "nextPage": "Pages/ServicePage.qml",
                                "stack":homeStack,
                                "nextStack": serviceStack,
                                "parameters": {"popupStack": servicePopupStack, "homeStack": serviceStack}
                            })
            }
        }
        onHome:
        {
            serviceStack.clear()
            while (homeStack.depth > 1)
            {
                homeStack.pop()
            }
        }

        onPresets:
        {
            serviceStack.clear()
            if(homeStack.top.objectName !== "PresetsPage")
            {
                while(homeStack.depth > 1)
                {
                    homeStack.pop()
                }
                homeStack.push("Pages/PresetsPage.qml", {"homeStack": homeStack, "popupStack": popupStack})
            }
        }

        onDehumidifcation:
        {
            if(popupStack.depth === 0)
            {
                if (state_manager.manual_mode || state_manager.aux)
                {
                    popupStack.push("Pages/JetActiveConfirmation.qml", {"popupStack": popupStack, "currentText": "DEHUMIDIFICATION", "procedureId": 1})
                }
                else
                {
                    popupStack.push("Pages/DehumidificationDisconnection.qml", {"popupStack": popupStack})
                }
            }

            else if(popupStack.top.objectName !== "DehumidificationDisconnection")
            {
                while(popupStack.depth > 1)
                {
                    popupStack.pop()
                }
                if (state_manager.manual_mode || state_manager.aux)
                {
                    popupStack.push("Pages/JetActiveConfirmation.qml", {"popupStack": popupStack, "currentText": "DEHUMIDIFICATION", "procedureId": 1})
                }
                else
                {
                    popupStack.push("Pages/DehumidificationDisconnection.qml", {"popupStack": popupStack})
                }
            }

        }

        onSettings:
        {
            serviceStack.clear()
            if(homeStack.top.objectName !== "SettingsPage")
            {
                while(homeStack.depth > 1)
                {
                    homeStack.pop()
                }
                homeStack.push("Pages/SettingsPage.qml", {"homeStack": homeStack, "popupStack": popupStack})
            }

        }

        onLock:
        {
            if(homeStack.top.objectName !== "LockPanelPage")
            {
                popupStack.clear();
                popupStack.push("Pages/ScreenLockConfirmation.qml", {"popupStack": popupStack})
            }

        }

        MouseArea
        {
            anchors.fill:parent
            onPressed:
            {
                mouse.accepted = false
                interactionTimer.restart()
            }
        }
    }

    Rectangle
    {
       id: demo_icon
       x: 1135
       y:95
       width:75
       height:40
       radius:8

       visible:(demoModeFlag && !homeIcon.visible)
       color: Style.mode_active_warning
       //visible:enabled
       Text {
           id: icon_text
           text:"DEMO"
           anchors.centerIn: parent
           font: Style.titleFont
           color:Style.primary_light
       }
   }

    StackView
    {
       id: serviceStack

       enabled: servicePopupStack.depth == 0
       visible: true
       width: 1280; height: 800

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

       function openService()
       {
           if (!serviceStack.depth)
           serviceStack.push("Pages/ServicePage.qml", {"homeStack": serviceStack, "popupStack": servicePopupStack})
       }

       function openHamburger()
       {
           hambugerMenu.open()
       }
   }

    Rectangle
    {
        id: homeIcon
        x: parent.width - width
        y: -10
        width: 99.5
        height: 86
        radius: 13
        color: Style.transparent
        visible: homeStack.depth > 1 || serviceStack.depth
        MouseArea
        {
            anchors.fill:parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                parent.color = Style.primary_light_selected
                homeIcon.delay(50)
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
                parent.color = Style.transparent
                if (state_manager.preset_create_active) state_manager.preset_create_active = 0
                while(homeStack.depth > 1)
                {
                    homeStack.pop()
                }
                serviceStack.clear()
                timer.stop()
            }
        }

        Image
        {
            id: homeImage
            source: "iconography/icon_40_home.svg"
            anchors.centerIn: parent
            sourceSize.height: 80 //parent.height
            sourceSize.width: 80 //parent.width
        }

        ColorOverlay
        {
            source: homeImage
            color: Style.primary_light
            anchors.fill: homeImage
        }
    }

    //The banner at the top of the screen which shows the most severe active alert
    WarningBanner
    {
        id: warningBanner
        anchors.horizontalCenter: parent.horizontalCenter
        y: 0
        warnings: warning_manager.displayWarnings
        visible: warnings.length > 0 && state_manager.display_warnings
        popupStack: popupStack
    }

    StackView
    {
        id: popupStack

        visible: true
        width: 1280; height: 800

        property int helpBoxState: 0

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

        replaceExit: Transition {
            enabled:false
        }

        replaceEnter: Transition {
            enabled:false
        }

        function pushHelpBox(titleText,helpText)
        {
            interactionTimer.restart()
            popupStack.push("Pages/HelpBox.qml", {"popupStack": popupStack, "titleText" : titleText, "helpText": helpText})

        }

        function dehumidify()
        {
            //popupStack.clear()

            if (state_manager.manual_mode || state_manager.aux)
            {
                popupStack.push("Pages/JetActiveConfirmation.qml", {"popupStack": popupStack, "currentText": "DEHUMIDIFICATION", "procedureId": 1})
            }
            else
            {
                popupStack.push("Pages/DehumidificationDisconnection.qml", {"popupStack": popupStack})
            }
        }

        function dehumidifyComplete(value)
        {
            if(depth >= 1) clear();
            else pop()
            if(state_manager.power_down_flag !== 0)
            {
                replace("Pages/ContinueShutdown.qml",{"popupStack":popupStack, "dehumidification_complete_state":value})
            }
            else if(value === 1)
            {
                replace("Pages/DehumidificationSuccess.qml",{"popupStack":popupStack})
            }
        }

        function troubleshoot(warningTitle, troubleshootString, numSteps, steps, warningColor)
        {
            popupStack.helpBoxState = 1
            interactionTimer.restart()
            popupStack.clear()
            popupStack.push("Pages/Troubleshoot.qml", {"stack": popupStack, "numSteps": numSteps, "steps": steps,
                                "warningColor": warningColor, "warningTitle": warningTitle, "troubleshootString": troubleshootString})
        }

        function unlock(enabled)
        {
            if(enabled)
            {
                popupStack.clear();
                popupStack.push("Pages/ScreenLockOverlay.qml", {"popupStack":popupStack});
            }
            else
            {
                popupStack.clear();
            }
        }
    }

    StackView
    {
        id: servicePopupStack

        visible: true
        width: 1280; height: 800

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

        replaceExit: Transition {
            enabled:false
        }

        replaceEnter: Transition {
            enabled:false
        }

        function pushHelpBox(titleText,helpText)
        {
            popupStack.push("Pages/HelpBox.qml", {"popupStack": popupStack, "titleText" : titleText, "helpText": helpText})

        }
    }

    Rectangle
    {
        id: interactionCheck
        anchors.fill: parent
        color: Style.transparent

        MouseArea
        {
            anchors.fill:parent
            onPressed:
            {
                mouse.accepted = false
                interactionTimer.restart()
            }
        }

        Timer
        {
            id: interactionTimer
            repeat: true
            interval: 60 * 1000
            running: true
            onTriggered:
            {
                if (
                        !state_manager.start_up_flag &&
                        !state_manager.dehumidify_mode &&
                        !state_manager.screen_lock_mode &&
                        serviceStack.depth ==0 &&
                        !state_manager.preset_create_active
                    )
                {
                    while (homeStack.depth > 1)
                    {
                        homeStack.pop()
                    }
                    popupStack.clear()
                    hambugerMenu.close()

                    if (powerdownFlag)
                    {
                        backend.initiatePowerdown(0);
                    }
                }
            }
        }

        Connections
        {
            target: knob

            onEncoderIncrement:
            {
                interactionTimer.restart()
            }
            onButtonPush:
            {
                interactionTimer.restart()
            }
        }
    }
}
