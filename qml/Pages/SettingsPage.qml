import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root_window
    color: Style.primary_dark
    objectName: "SettingsPage"

    property StackView homeStack
    property StackView popupStack

    property int buttonID: -1

    HamburgerButton {
        id: hamburger
        x: 0
        y: -10
        onClicked: homeStack.openHamburger()
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
            text: qsTr("Settings")
            font: Style.buttonFont
            color:Style.mode_label
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

        HelpIcon {
            id: hint_button
            anchors.left: pageTitle.right
            anchors.verticalCenter: pageTitle.verticalCenter
            visible: buttonID != -1

            onClicked:
            {
                if (buttonID == 0)
                {
                    popupStack.pushHelpBox("SP Lines on Graph",valueHolder.helpText0)
                }
                else if (buttonID == 1)
                {
                    popupStack.pushHelpBox("Oxygen Level", valueHolder.helpText1)
                }
                else if (buttonID == 2)
                {
                    popupStack.pushHelpBox("ETCO<sub>2</sub> Settings",valueHolder.helpText2)
                }
                else if (buttonID == 3)
                {
                    popupStack.pushHelpBox("Calibration Settings", valueHolder.helpText3)
                }
                else if (buttonID == 4)
                {
                    popupStack.pushHelpBox("PIP Disconnection",valueHolder.helpText4)
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

            function pushSettingPage(page,args)
            {
                settingStack.clear();
                settingStack.push(page,args);
            }

            SettingOptionsButton
            {
                id: spLine
                title: "SP Lines"
                width: buttonContainer.width
                y: .03 * parent.height

                onClicked:
                {
                    selected = true
                    laserO2Lvl.selected = false;
                    calibration.selected = false;
                    disconnection.selected = false;
                    about.selected = false;
                    etco2Settings.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = 0
                    pageTitle.text = "Stacking Pressure Lines"
                    buttonContainer.pushSettingPage("Settings/StackingPressure.qml", {"popupStack": popupStack});
                }
            }

            SettingOptionsButton
            {
                id: laserO2Lvl
                title: "Limited O<sub>2</sub>"
                y: spLine.y + spLine.height + .45 * height
                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    calibration.selected = false;
                    disconnection.selected = false;
                    about.selected = false;
                    etco2Settings.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = 1
                    pageTitle.text = "Oxygen Level"
                    buttonContainer.pushSettingPage("Settings/LaserO2.qml", {"min": laser_o2.min,"max":laser_o2.max, "unit" : laser_o2.unit, "settingId":laser_o2.id, "popupStack": popupStack, "helpText": laser_o2.help});
                }
            }

            SettingOptionsButton
            {
                id: etco2Settings
                title: "ETCO<sub>2</sub> Settings"
                y: laserO2Lvl.y + laserO2Lvl.height + .45 * height

                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    laserO2Lvl.selected = false;
                    calibration.selected = false;
                    disconnection.selected = false;
                    about.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = 2
                    pageTitle.text = "ETCO<sub>2</sub> Settings"
                    buttonContainer.pushSettingPage("Settings/ETCO2Settings.qml", {"topY" : y + parent.y, "popupStack": popupStack});
                }
            }

            SettingOptionsButton
            {
                id: calibration
                title: "O<sub>2</sub> Calibration"
                y: etco2Settings.y + etco2Settings.height + .45 * height

                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    laserO2Lvl.selected = false;
                    disconnection.selected = false;
                    about.selected = false;
                    etco2Settings.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = 3
                    pageTitle.text = "O<sub>2</sub> Calibration"
                    buttonContainer.pushSettingPage("Settings/Calibration.qml");
                }
            }

            SettingOptionsButton
            {
                id: disconnection
                title: "PIP Disconnection"
                y: calibration.y + calibration.height + .45 * height

                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    laserO2Lvl.selected = false;
                    calibration.selected = false;
                    about.selected = false;
                    etco2Settings.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = 4
                    pageTitle.text = "PIP Disconnection"
                    buttonContainer.pushSettingPage("Settings/Disconnection.qml");
                }
            }

            SettingOptionsButton
            {
                id: volumeAndBrightness
                title: "Brightness and Volume"
                y: disconnection.y + disconnection.height + .45 * height

                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    laserO2Lvl.selected = false;
                    calibration.selected = false;
                    disconnection.selected = false;
                    etco2Settings.selected = false;
                    about.selected = false;

                    buttonID = -1
                    pageTitle.text = "Brightness and Volume"
                    buttonContainer.pushSettingPage("Settings/VolumeAndBrightness.qml", {"topY" : y + parent.y, "popupStack": popupStack});
                }
            }

            SettingOptionsButton
            {
                id: about
                title: "About"
                y: volumeAndBrightness.y + volumeAndBrightness.height + .45 * height

                onClicked:
                {
                    selected = true
                    spLine.selected = false;
                    laserO2Lvl.selected = false;
                    calibration.selected = false;
                    disconnection.selected = false;
                    etco2Settings.selected = false;
                    volumeAndBrightness.selected = false;

                    buttonID = -1
                    pageTitle.text = "About"
                    buttonContainer.pushSettingPage("Settings/About.qml");
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

    Text {
        id: displayDateTime
        color: Style.primary_light
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        visible: about.selected
        Component.onCompleted:
        {
            displayDateTime.text = time_manager.currentDateTime
        }
    }

    Timer {
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

    Item {
        id: valueHolder
        property string helpText0: "The NVENT VITA allows the user to hide the blue measured line and the blue dash line for Stacking Pressure."
        property string helpText1: laser_o2.help
        property string helpText2: etco2_driving_pressure.help
        property string helpText3: "In the event of a failed automatic O<sub>2</sub> calibration or if an additional O<sub>2</sub> calibration is needed, a manual O<sub>2</sub> calibration should be performed. Prior to a manual O<sub>2</sub> calibration being performed, ensure that the Air and Oxygen supply lines are connected to the machine and the source. Limited O<sub>2</sub> mode cannot be utilized during an O<sub>2</sub> calibration."
        property string helpText4: "If PIP Disconnection is “ON” the user will be notified if no pressure is detected on the PIP pressure line for 15 seconds."
    }
}
