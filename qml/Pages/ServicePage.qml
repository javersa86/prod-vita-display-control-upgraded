import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: root_window
    color: Style.primary_dark
    objectName: "ServicePage"

    property StackView homeStack
    property StackView popupStack

    MouseArea
    {
        id: background
        anchors.fill:parent
    }

    HamburgerButton
    {
        id: hamburger
        x: 0
        y: -10
        onClicked: homeStack.openHamburger()
    }

    Component.onCompleted:
    {
        backend.logsState(1);
        backend.setMode(13,1);
    }

    Component.onDestruction:
    {
        backend.setMode(13,0);
        backend.logsState(0);
    }

    Rectangle
    {
        id: mainContainer
        width: .97 * parent.width
        height: .95 * parent.height
        anchors.centerIn: parent
        color:Style.transparent

        Text
        {
            id: title
            text: qsTr("Service")
            font: Style.buttonFont
            color: Style.mode_label
            y: .08 * parent.height
        }

        Text
        {
            id: pageTitle
            font: Style.pageTitle
            color: Style.primary_light
            textFormat: Text.RichText
            anchors.top: title.bottom
        }

        HelpIcon
        {
            id: hint_button
            anchors.left: pageTitle.right
            anchors.verticalCenter: pageTitle.verticalCenter
            visible: o2calibration.selected

            onClicked:
            {
                if (o2calibration.selected)
                {
                    popupStack.pushHelpBox("Calibration", valueHolder.oxygenHelpText)
                }
            }
        }

        Rectangle
        {
            id: buttonContainer
            width: .18 * parent.width
            height: .85 * parent.height
            anchors.bottom: parent.bottom
            color:Style.transparent

            function pushSettingPage(page, args)
            {
                settingStack.clear();
                settingStack.push(page, args);
            }

            SettingOptionsButton
            {
                id: demo
                title: "Demo"
                width: buttonContainer.width
                y: .03 * parent.height

                onClicked:
                {
                    if (!selected)
                    {
                        selected = true
                        factory_settings.selected = false
                        maintenance.selected = false
                        components.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false

                        pageTitle.text = "Demo"
                        buttonContainer.pushSettingPage("Service/Demo.qml");
                    }
                }
            }

            SettingOptionsButton
            {
                id: factory_settings
                title: "Factory Settings"
                width: buttonContainer.width
                y: demo.y + demo.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false;
                        maintenance.selected = false
                        components.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false

                        pageTitle.text = "Factory"
                        buttonContainer.pushSettingPage("Service/FactorySettings.qml");
                    }
                }
            }

            SettingOptionsButton
            {
                id: maintenance
                title: "Maintenance"
                width: buttonContainer.width
                y: factory_settings.y + factory_settings.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        components.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false
                        var topY = Math.floor(y + parent.y)

                        pageTitle.text = "Maintenance"
                        buttonContainer.pushSettingPage("Service/Maintenance.qml",{"topY" : topY, "popupStack": popupStack});
                    }
                }
            }

            SettingOptionsButton
            {
                id: components
                title: "Components"
                width: buttonContainer.width
                y: maintenance.y + maintenance.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        maintenance.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false
                        var topY = Math.floor(y + parent.y)

                        pageTitle.text = "Components"
                        buttonContainer.pushSettingPage("Service/Components.qml",{"topY" : topY, "popupStack": popupStack});
                    }
                }
            }

            SettingOptionsButton
            {
                id: calibration
                title: "Calibration"
                width: buttonContainer.width
                y: components.y + components.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        maintenance.selected = false
                        components.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false
                        var topY = Math.floor(y + parent.y)

                        pageTitle.text = "Calibration"
                        buttonContainer.pushSettingPage("Service/Calibration.qml",{"topY" : topY, "popupStack": popupStack});
                    }
                }
            }

            SettingOptionsButton
            {
                id: o2calibration
                title: "O<sub>2</sub> Calibration"
                width: buttonContainer.width
                y: calibration.y + calibration.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        maintenance.selected = false
                        components.selected = false
                        calibration.selected = false
                        serviceLogs.selected = false
                        changePasscode.selected = false

                        pageTitle.text = "O<sub>2</sub> Calibration"
                        buttonContainer.pushSettingPage("Service/O2Calibration.qml");
                    }
                }
            }

            SettingOptionsButton
            {
                id: serviceLogs
                title: "Service Logs"
                width: buttonContainer.width
                y: o2calibration.y + o2calibration.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        maintenance.selected = false
                        components.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        changePasscode.selected = false
                        var topY = Math.floor(y + parent.y)

                        pageTitle.text = "Service Logs"
                        buttonContainer.pushSettingPage("Service/ServiceLogs.qml",{"topY" : topY, "popupStack": popupStack});
                    }
                }
            }

            SettingOptionsButton
            {
                id: changePasscode
                title: "Passcode"
                width: buttonContainer.width
                y: serviceLogs.y + serviceLogs.height + .03 * parent.height

                onClicked:
                {
                    if(!selected)
                    {
                        selected = true
                        demo.selected = false
                        factory_settings.selected = false
                        maintenance.selected = false
                        components.selected = false
                        calibration.selected = false
                        o2calibration.selected = false
                        serviceLogs.selected = false
                        var topY = Math.floor(y + parent.y)

                        pageTitle.text = "Passcode"
                        buttonContainer.pushSettingPage("Service/ChangePasscode.qml",{"topY" : topY, "popupStack": popupStack});
                    }
                }
            }
        }

        StackView
        {
            id: settingStack
            height: parent.height
            anchors.right:parent.right
            anchors.left: buttonContainer.right
        }
    }

    Text
    {
        id: displayDateTime
        color: Style.primary_light
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        visible: maintenance.selected
        Component.onCompleted:
        {
            displayDateTime.text = time_manager.currentDateTime
        }
    }

    Timer
    {
        id: clock
        interval: 100
        repeat: true
        running: true
        triggeredOnStart: true

        onTriggered:
        {
            displayDateTime.text = time_manager.currentDateTime
        }
    }

    Item
    {
        id: valueHolder
        property string oxygenHelpText: "In the event of a failed automatic O<sub>2</sub> calibration or if an additional O<sub>2</sub> calibration is needed, a manual O<sub>2</sub> calibration should be performed. Prior to a manual O<sub>2</sub> calibration being performed, ensure that the Air and Oxygen supply lines are connected to the machine and the source. Limited O<sub>2</sub> mode cannot be utilized during an O<sub>2</sub> calibration."
    }
}
