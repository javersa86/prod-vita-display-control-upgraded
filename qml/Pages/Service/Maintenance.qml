/**
  Created page to perform the following actions:

  Display the last service date and the next service date.
  Clicking on either will allow the user to change dates, pushing UpdateDate.qml
  Display current software versions.
  Display name, serial number, date installed, and hours operating for each componet.

  Update from Joseph Aversa:

  Removed componesnts list.
  Created slots for service date changes.
  Next service date color changes if past due date.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import Qt.labs.qmlmodels 1.0
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.primary_dark
    property int topY
    property StackView popupStack
    property Item updateDatePage

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
            width: .38 * parent.width
            height: .3 * parent.height
            anchors.top: parent.top
            anchors.left: parent.left

            Text {
                id: contactTitle
                text: qsTr("Contact Information")
                font: Style.settingPageTitle
                color: Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            SettingOptionsButton
            {
                id: serviceContactButton
                title: "Service"
                height: 48
                width: 120
                anchors.top: contactTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                serviceState: true

                onClicked:
                {
                    root_window.popupStack.push("ContactPopup.qml",
                                                {
                                                    "popupStack" : popupStack,
                                                    "titleStr" : "Maintenance: Service Contact Information",
                                                    "companyName" : contact_manager.serviceCompanyName,
                                                    "address" : contact_manager.serviceStreet,
                                                    "city" : contact_manager.serviceCity,
                                                    "state" : contact_manager.serviceState,
                                                    "postalCode" : contact_manager.servicePostalCode,
                                                    "email" : contact_manager.serviceEmail,
                                                    "phoneNumber" : contact_manager.servicePhoneNumber,
                                                    "contactState" : 1
                                                })
                }
            }

            SettingOptionsButton
            {
                id: salesContactButton
                title: "Sales"
                height: 48
                width: 120
                anchors.top: contactTitle.bottom
                anchors.topMargin: 16
                anchors.left: serviceContactButton.right
                anchors.leftMargin: 16

                serviceState: true

                onClicked:
                {
                    root_window.popupStack.push("ContactPopup.qml",
                                                {
                                                    "popupStack" : popupStack,
                                                    "titleStr" : "Maintenance: Sales Contact Information",
                                                    "companyName" : contact_manager.salesCompanyName,
                                                    "address" : contact_manager.salesStreet,
                                                    "city" : contact_manager.salesCity,
                                                    "state" : contact_manager.salesState,
                                                    "postalCode" : contact_manager.salesPostalCode,
                                                    "email" : contact_manager.salesEmail,
                                                    "phoneNumber" : contact_manager.salesPhoneNumber,
                                                    "contactState" : 2
                                                })
                }
            }
        }

        Rectangle
        {
            id: timeBox
            color: Style.transparent
            width: .5 * parent.width
            height: .3 * parent.height
            anchors.top: parent.top
            anchors.left: contactBox.right

            Text {
                id: timeTitle
                text: qsTr("Date & Time")
                color: Style.primary_light
                font: Style.settingPageTitle
                anchors.top: parent.top
                anchors.left: parent.left
            }

            SettingOptionsButton
            {
                id: dateButton
                title: "Date"
                height: 48
                width: 120
                anchors.top: timeTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left

                serviceState: true

                onClicked:
                {
                    root_window.popupStack.push("DatePopup.qml",
                                                {
                                                    "popupStack" : popupStack,
                                                    "titleStr" : "Maintenance: New Date",
                                                    "dateStr" : time_manager.currentDateTime.split(" ")[0],
                                                    "check" : 3
                                                });
                }
            }

            SettingOptionsButton
            {
                id: timeButton
                title: "Time"
                height: 48
                width: 120
                anchors.top: timeTitle.bottom
                anchors.topMargin: 16
                anchors.left: dateButton.right
                anchors.leftMargin: 16

                serviceState: true

                onClicked:
                {
                    root_window.popupStack.push("UpdateTime.qml",
                                                {
                                                    "popupStack" : popupStack,
                                                    "titleStr" : "Maintenance: New Time",
                                                    "timeStr" : time_manager.currentDateTime.substring(11)
                                                });
                }
            }

            SettingOptionsButton
            {
                id: timeZoneButton
                title: "Time Zone"
                height: 48
                width: 120
                anchors.top: timeTitle.bottom
                anchors.topMargin: 16
                anchors.left: timeButton.right
                anchors.leftMargin: 16

                serviceState: true

                onClicked:
                {
                    root_window.popupStack.push("UpdateTimeZone.qml",
                                                {
                                                    "popupStack" : popupStack,
                                                    "titleStr" : "Maintenance: New Time Zone",
                                                    "timeZoneStr" : time_manager.currentDateTime.substring(25)
                                                })
                }
            }
        }

        Rectangle
        {
            id: serviceDates
            color:Style.transparent
            width: parent.width
            height: .3 * parent.height
            anchors.top: contactBox.bottom
            anchors.left: parent.left

            Text {
                id: serviceDatesTitle
                text: qsTr("Service Dates (Tap to Change Dates)")
                color: Style.primary_light
                font: Style.settingPageTitle
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: lastServiceBox
                color: Style.transparent
                width: .25 * parent.width
                height: parent.height
                anchors.left:parent.left
                anchors.top: serviceDatesTitle.bottom
                anchors.topMargin: 16

                Text {
                    id: lastServiceTitle
                    text: qsTr("Last service:")
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    id: lastServiceContainer
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
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            root_window.popupStack.push("DatePopup.qml",
                                                        {
                                                            "popupStack" : popupStack,
                                                            "titleStr": "Maintenance: Last Service Date",
                                                            "dateStr" : lastServiceDate.text,
                                                            "check" : 1
                                                        });
                        }

                        onPressed: lastServiceContainer.color = Style.primary_light_selected
                        onReleased: lastServiceContainer.color = Style.unclickable_border
                    }
                }

            }

            Rectangle
            {
                id: nextServiceBox
                color: Style.transparent
                width: .25 * parent.width
                height: parent.height
                anchors.top: serviceDatesTitle.bottom
                anchors.topMargin: 16
                anchors.left: lastServiceBox.right

                Text {
                    id: nextServiceTitle
                    text: qsTr("Next service:")
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    id: nextServiceContainer
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
                        var currentDate = new Date();
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
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            root_window.popupStack.push("DatePopup.qml",
                                                        {
                                                            "popupStack" : popupStack,
                                                            "titleStr" : "Maintenance: Next Service Date",
                                                            "dateStr" : nextServiceDate.text,
                                                            "check" : 2
                                                        });
                        }

                        onPressed: nextServiceContainer.color = Style.primary_light_selected
                        onReleased: nextServiceContainer.color = Style.unclickable_border
                    }
                }
            }

            Rectangle
            {
                id: hoursOperatingBox
                color: Style.transparent
                width: .25 * parent.width
                height: parent.height
                anchors.top: serviceDatesTitle.bottom
                anchors.topMargin: 16
                anchors.left: nextServiceBox.right

                Text {
                    id: hoursOperatingTitle
                    text: qsTr("Hours of Operation:")
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    id: hoursOperatingContainer
                    width: .8 * parent.width
                    height: .4 * parent.height
                    radius: width /15
                    color: Style.unclickable_border
                    anchors.top: hoursOperatingTitle.bottom
                    anchors.left: parent.left

                    Text {
                        id: hoursOperating
                        text: "00:00"
                        font: Style.settingPageTitle
                        color: Style.primary_light
                        anchors.centerIn: parent
                    }
                }
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
                color: Style.primary_light
                font: Style.settingPageTitle
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
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    anchors.top: displayVersionTitle.bottom
                    radius: width / 15
                    color: Style.unclickable_border
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
                    color: Style.primary_light
                    font: Style.buttonFont
                    anchors.top: parent.top
                    anchors.left: parent.left
                }

                Rectangle
                {
                    height: .4 * parent.height
                    width: .8 * parent.width
                    anchors.top: systemVersionTitle.bottom
                    radius: width / 15
                    color: Style.unclickable_border
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
                    color: Style.primary_light
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
                    color: refreshIpAddressMouseArea.pressed ? Style.primary_light : Style.transparent
                    border.width: 2
                    border.color: Style.primary_light
                    height: 48
                    width: 120
                    anchors.left: ipAddressContainer.right
                    anchors.leftMargin: 16
                    anchors.verticalCenter: ipAddressContainer.verticalCenter

                    Text {
                        id: refreshIpAddressTitle
                        text: "Refresh"
                        textFormat: Text.RichText
                        font: Style.buttonFont
                        color: refreshIpAddressMouseArea.pressed ? Style.primary_dark : Style.primary_light
                        anchors.centerIn: parent
                    }

                    MouseArea
                    {
                        id: refreshIpAddressMouseArea
                        anchors.fill: parent
                        onClicked:
                        {
                            backend.setUpIpAddress();
                            if (state_manager.ip_address === "Please Connect") {
                                ipAddressErrorMessage.visible = true
                                timer0.start()
                            }
                            else {
                                ipAddressErrorMessage.visible = false
                            }
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
                    anchors.top: refreshIpAddress.bottom
                    anchors.topMargin: 4
                    anchors.left: refreshIpAddress.left
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
        }
    }
}
