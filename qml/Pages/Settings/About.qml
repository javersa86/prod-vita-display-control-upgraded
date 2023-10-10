/*
  QML update by Joseph Aversa:

  Added Passcode settings section, giving the user the ability to change his/her passcode to modify presets
  Added Change Preset Passcode button to Passcode settings
    - clicking button will push new page AboutPresetPassCode

  Dates change from time manager.
  Next service date changes color if past due date.
  */

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color:Style.transparent

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .75 * parent.height
        x: 100
        y: .17 * parent.height
        color: Style.transparent

        Rectangle
        {
            id: contactBox
            color: Style.transparent
            width: .5 * parent.width
            height: .4 * parent.height
            anchors.top: parent.top
            anchors.left: parent.left

            Text {
                id: contactTitle
                text: qsTr("Contact Information")
                font: Style.settingPageTitle
                color:Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: serviceContactBox
                color: Style.transparent
                width: .5 * parent.width
                height: parent.height
                anchors.left: parent.left
                anchors.top: contactTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: serviceTitle
                    text: qsTr("Service Contact: ")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: servicecontact
                    color:Style.primary_light
                    font: Style.buttonFont
                    opacity: .7
                    lineHeight: 1.35
                    text: contact_manager.serviceCompanyName + "\n" +
                          contact_manager.serviceStreet + "\n" +
                          contact_manager.serviceCity + ", " + contact_manager.serviceState + " " + contact_manager.servicePostalCode + "\n" +
                          contact_manager.serviceEmail + "\n" +
                          contact_manager.servicePhoneNumber
                    anchors.top: serviceTitle.bottom
                    anchors.left: parent.left
                }

            }


            Rectangle
            {
                id: salesContactBox
                color: Style.transparent
                width: .5 * parent.width
                height: parent.height
                anchors.left: serviceContactBox.right
                anchors.top: contactTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: salesTitle
                    text: qsTr("Sales Contact: ")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Text {
                    id: salescontact
                    color:Style.primary_light
                    font: Style.buttonFont
                    opacity: .7
                    lineHeight: 1.3
                    text: contact_manager.salesCompanyName + "\n" +
                          contact_manager.salesStreet + "\n" +
                          contact_manager.salesCity + ", " + contact_manager.salesState + " " + contact_manager.salesPostalCode + "\n" +
                          contact_manager.salesEmail + "\n" +
                          contact_manager.salesPhoneNumber
                    anchors.top: salesTitle.bottom
                    anchors.left: parent.left
                }
            }
        }

        Rectangle
        {
            id: serviceDates
            color:Style.transparent
            width: .5 * parent.width
            height: .3 * parent.height
            anchors.top: contactBox.bottom
            anchors.left: parent.left

            Text {
                id: serviceDatesTitle
                text: qsTr("Service Dates")
                font: Style.settingPageTitle
                color:Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: lastServiceBox
                color: Style.transparent
                width: .5 * parent.width
                height: parent.height
                anchors.left:parent.left
                anchors.top: serviceDatesTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: lastServiceTitle
                    text: qsTr("Last service:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    width: .8 * parent.width
                    height: .4 * parent.height
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: lastServiceTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: lastServiceDate
                        text: maintenance_manager.lastServiceDate
                        color:Style.primary_light
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }

                }

            }

            Rectangle
            {
                id: nextServiceBox
                color: Style.transparent
                width: .5 * parent.width
                height: parent.height
                anchors.right:parent.right
                anchors.top: serviceDatesTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: nextServiceTitle
                    text: qsTr("Next service:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    width: .8 * parent.width
                    height: .4 * parent.height
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: nextServiceTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: nextServiceDate
                        text: maintenance_manager.nextServiceDate
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                    Component.onCompleted:
                    {
                        var tmpDateTimeText = time_manager.currentDateTime;
                        var dateTimeText = tmpDateTimeText.split(" ")[0];
                        var currentDate = new Date(dateTimeText);
                        var someDate = Date.fromLocaleString(Qt.locale(), maintenance_manager.nextServiceDate, "MM/dd/yyyy")
                        if (someDate - currentDate > 0)
                        {
                            nextServiceDate.color = Style.primary_light
                        }
                        else
                        {
                            nextServiceDate.color = Style.pip
                        }
                    }
                }
            }
        }
        Rectangle
        {
            id: changePassCodeBox
            color:Style.transparent
            width: .3 * parent.width
            height: .3 * parent.height
            anchors.top: parent.top
            anchors.right: parent.right

            Text {
                id: changePassCodeTitle
                text: qsTr("Passcode Settings")
                font: Style.settingPageTitle
                color:Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            SettingOptionsButton
            {
                id: changePresetButton
                title: "Create"
                height: 48
                width: 120
                anchors.top: changePassCodeTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                serviceState: true

                onClicked:
                {
                    buttonContainer.pushSettingPage(
                                "Settings/PassCode.qml",
                                {
                                    "code" : passcode_manager.presetPasscode,
                                    "nextPage": "Settings/PassCodeChange.qml",
                                    "finalPage": "Settings/PassCodeConfirm.qml"
                                });
                }
            }
        }

        Rectangle
        {
            id: daylightBox
            color:Style.transparent
            width: .3 * parent.width
            height: .3 * parent.height
            anchors.top: contactBox.bottom
            anchors.left: changePassCodeBox.left

            Text {
                id: daylightTitle
                text: qsTr("Daylight Savings")
                font: Style.settingPageTitle
                color:Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            DaylightSwitch
            {
                id: daylightSwitch
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: daylightTitle.bottom
                anchors.topMargin: 16
            }

            Text {
                id: description
                text: qsTr("Switch to Daylight Savings Time")
                font: Style.unitFont
                color: Style.general_set_display
                anchors.top: daylightSwitch.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                topPadding: title.height
            }
        }

        Rectangle
        {
            id: softwareVersionsBox
            color:Style.transparent
            width: parent.width
            height: .3 * parent.height
            anchors.top: serviceDates.bottom
            anchors.left: parent.left

            Text {
                id: softwareVersionsTitle
                text: qsTr("Software Versions")
                font: Style.settingPageTitle
                color:Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: displayVersionBox
                color: Style.transparent
                width: .5 * (.5 * parent.width)
                height: parent.height
                anchors.left:parent.left
                anchors.top: softwareVersionsTitle.bottom
                anchors.topMargin: 16


                Text {
                    id: displayVersionTitle
                    text: qsTr("Display Controller:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: displayVersionTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: displayVersion
                        text: state_manager.displaySoftwareVersion
                        color:Style.primary_light
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }

                }

            }

            Rectangle
            {
                id: systemVersionBox
                color: Style.transparent
                width: .5 * (.5 * parent.width)
                height: parent.height
                anchors.left: displayVersionBox.right
                anchors.top: softwareVersionsTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: systemVersionTitle
                    text: qsTr("System Controller:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: systemVersionTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: systemVersionDate
                        text: state_manager.systemSoftwareVersion
                        color:Style.primary_light
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                }
            }

            Rectangle
            {
                id: ipAddressBox
                color: Style.transparent
                width: .5 * (.5 * parent.width)
                height: systemVersionBox.height
                anchors.left: systemVersionBox.right
                anchors.top: softwareVersionsTitle.bottom
                anchors.topMargin: 16

                Component.onCompleted: {
                    backend.setUpIpAddress();
                }

                Text {
                    id: ipAddressTitle
                    text: qsTr("IP Address (Ethernet Connection Required):")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    id: ipAddressContainer
                    height: .4 * parent.height
                    width: parent.width
                    anchors.top: ipAddressTitle.bottom
                    anchors.left: parent.left
                    radius: width / 15
                    color: Style.unclickable_border

                    Text {
                        id: ipAddressDate
                        text: state_manager.ip_address
                        color:Style.primary_light
                        font:Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                }
                Rectangle
                {
                    id: refreshIpAddress
                    radius: width / 10
                    color: Style.transparent
                    border.width: 2
                    border.color: Style.primary_light
                    height: 48
                    width: 120
                    anchors.left: ipAddressContainer.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: ipAddressContainer.verticalCenter

                    Text {
                        id: title
                        text: "Refresh"
                        textFormat: Text.RichText
                        font: Style.buttonFont
                        color: Style.primary_light
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        id: refreshIpAddressMouseArea
                        anchors.fill: parent
                        pressAndHoldInterval: 225
                        onPressAndHold:
                        {
                            refreshIpAddress.color = Style.primary_light_selected
                            refreshIpAddress.delay(50)
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
                            backend.setUpIpAddress();
                            if (state_manager.ip_address === "Please Connect") {
                                ipAddressErrorMessage.visible = true
                                timer0.start()
                            }
                            else {
                                ipAddressErrorMessage.visible = false
                            }
                            refreshIpAddress.color = Style.transparent
                            timer1.stop()
                        }
                    }
                }

                Text {
                    id: ipAddressErrorMessage
                    text: qsTr("Connection Failed, try again.")
                    color:Style.primary_light
                    font: Style.buttonFont
                    opacity: .7
                    lineHeight: 1.35
                    anchors.top: ipAddressContainer.bottom
                    anchors.topMargin: 4
                    anchors.left: ipAddressContainer.left
                    visible: false
                }
                Timer {
                    id: timer0
                    repeat: false
                    interval: 1000
                    onTriggered:
                    {
                        ipAddressErrorMessage.visible = false
                        timer0.stop()
                    }
                }
            }

            Rectangle
            {
                id: hmiVersionBox
                width: .5 * (.5 * parent.width)
                height: parent.height
                color: Style.transparent
                anchors.left:parent.left
                anchors.top: displayVersionBox.verticalCenter
                anchors.topMargin: 8

                Text {
                    id: hmiVersionTitle
                    text: qsTr("HMI Controller:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: hmiVersionTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: hmiVersion
                        text: version_manager.hmiVersion
                        color: Style.primary_light
                        font: Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                }
            }

            Rectangle
            {
                id: serialNumberBox
                width: .5 * (.5 * parent.width)
                height: parent.height
                color: Style.transparent
                anchors.left: hmiVersionBox.right
                anchors.top: displayVersionBox.verticalCenter
                anchors.topMargin: 8

                Text {
                    id: serialNumberTitle
                    text: qsTr("Serial Number:")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    id: serialNumberContainer
                    height: .4 * parent.height
                    width: .8 * parent.width
                    radius: width / 15
                    color: Style.unclickable_border
                    anchors.top: serialNumberTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: serialNumber
                        text: version_manager.serialNumber
                        color: Style.primary_light
                        font: Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                }
            }

            Rectangle
            {
                id: hoursOperatingBox
                width: .5 * (.5 * parent.width)
                height: parent.height
                color: Style.transparent
                anchors.left: serialNumberBox.right
                anchors.top: ipAddressBox.bottom
                anchors.topMargin: 8

                Text {
                    id: hoursOperatingTitle
                    text: qsTr("Hours Operating")
                    color:Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left

                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    color: Style.transparent
                    anchors.top: hoursOperatingTitle.bottom
                    anchors.left: parent.left

                    Text {
                        text: "00:00"
                        color: Style.primary_light
                        font: Style.settingPageTitle
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
