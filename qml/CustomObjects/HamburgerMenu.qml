import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Popup
{
    id: topLevelContainer
    width: parent.width
    height: parent.height

    background: Rectangle {
        height: topLevelContainer.height
        width: topLevelContainer.width
        color: Style.menu_color
    }
    leftPadding: 0

    signal home();
    signal presets();
    signal dehumidifcation();
    signal settings();
    signal lock();
    signal service();

    Rectangle
    {
        id: closeBox
        width: 99.5
        height: 86
        x: 0
        y: -20
        color: Style.transparent

        Item {
            id: closeIcon
            height: 44
            width: height
            anchors.centerIn: parent
            Image {
                id: icon
                source: "../iconography/icon_40_close.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
                visible: true
            }
            ColorOverlay {
                anchors.fill: icon
                source: icon
                color: Style.primary_light
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill:parent
            pressAndHoldInterval: 225
            onPressAndHold:{
                closeBox.color = Style.primary_light_selected
                closeBox.delay(300)
            }
        }

        function delay(delayTime)
        {
            timer1.interval = delayTime;
            timer1.start();
        }

        Timer {
            id: timer1
            repeat: false
            onTriggered:
            {
                topLevelContainer.close()
                closeBox.color = Style.transparent
                timer1.stop()
            }
        }
    }

    Rectangle
    {
        id: serviceButton
        color: Style.transparent
        width: topLevelContainer.width // * .9
        height: topLevelContainer.height / 20
        y:topLevelContainer.height - height * 2
        x: (topLevelContainer.width - width) / 2

        Text {
            text: qsTr("Service")
            color: Style.primary
            font: Style.buttonFont
            anchors.left:parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea
        {
            id: serviceMouseArea
            anchors.fill:serviceButton
            pressAndHoldInterval: 225
            onPressAndHold:{
                serviceButton.color = Style.primary_light_selected
                serviceButton.delay(300)
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
                topLevelContainer.service();
                topLevelContainer.close();
                serviceButton.color = Style.transparent
                timer.stop()
            }
        }
    }

    ColumnLayout
    {
        id: generalButtonContainer
        height: topLevelContainer.height / 2.64
        width: topLevelContainer.width

        y: topLevelContainer.height / 5.94

        spacing: (height / 60.8)
        property int buttonHeight: (height / 5)


        MenuButton
        {
            id: homeButton
            Layout.preferredHeight: generalButtonContainer.buttonHeight
            Layout.preferredWidth:  topLevelContainer.width
            iconSource: "../iconography/icon_40_home.svg"
            title: "Home"

            onClicked:
            {
                topLevelContainer.home();
                topLevelContainer.close();
            }

        }

        MenuButton
        {
            id: presetsButton
            Layout.preferredHeight: generalButtonContainer.buttonHeight
            Layout.preferredWidth:  topLevelContainer.width
            iconSource: "../iconography/icon_40_presets.svg"
            title: "Presets"

            onClicked:
            {
                topLevelContainer.presets();
                topLevelContainer.close();
            }
        }

        MenuButton
        {
            id: dehumidificationButton
            Layout.preferredHeight: generalButtonContainer.buttonHeight
            Layout.preferredWidth:  topLevelContainer.width
            iconSource: "../iconography/icon_40_dehumidify.svg"
            iconSize: 40
            title: "Dehumidify"
            //enabled: !state_manager.ventilating && !state_manager.aux

            onClicked:
            {
                topLevelContainer.dehumidifcation();
                topLevelContainer.close();
            }

        }

        MenuButton
        {
            id: settingsButton
            Layout.preferredHeight: generalButtonContainer.buttonHeight
            Layout.preferredWidth:  topLevelContainer.width
            iconSource: "../iconography/icon_40_settings.svg"
            title: "Settings"

            onClicked:
            {
                topLevelContainer.settings();
                topLevelContainer.close();
            }

        }

        MenuButton
        {
            id: lockButton
            Layout.preferredHeight: generalButtonContainer.buttonHeight
            Layout.preferredWidth:  topLevelContainer.width
            iconSource: "../iconography/icon_40_lockscreen.svg"
            title: "Lock Panel"

            onClicked:
            {
                topLevelContainer.lock();
                topLevelContainer.close();
            }

        }
    }
}
