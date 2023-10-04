import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
import "../../CustomObjects/ContactKeyboard"

Rectangle{
    id: root_window
    height: 800
    width: 1280
    color: Style.primary_dark
    border.color: Style.general_set_display
    radius: 4
    border.width: 2

    property StackView popupStack

    property alias titleStr: title.text
    property alias companyName: companyNameText.text
    property alias address: addressText.text
    property alias city: cityText.text
    property alias state: stateText.text
    property alias postalCode : postalCodeText.text
    property alias email: emailText.text
    property alias phoneNumber: phoneText.text
    property int contactState

    function recentText()
    {
        if (companyNameKeyboard.visible)
        {
            if (companyNameText.text.length === 0)
            {
                if (contactState == 1)
                {
                    companyNameText.text = contact_manager.serviceCompanyName
                }
                else if (contactState == 2)
                {
                    companyNameText.text = contact_manager.salesCompanyName
                }
            }
            else
            {
                companyNameText.text = keyboardBox.hidden_text + companyNameText.text
            }
        }
        else if (addressKeyboard.visible)
        {
            if (addressText.text.length === 0)
            {
                if (contactState == 1)
                {
                    addressText.text = contact_manager.serviceStreet
                }
                else if (contactState == 2)
                {
                    addressText.text = contact_manager.salesStreet
                }
            }
            else
            {
                addressText.text = keyboardBox.hidden_text + addressText.text
            }
        }
        else if (cityKeyboard.visible)
        {
            if (cityText.text.length === 0)
            {
                if (contactState == 1)
                {
                    cityText.text = contact_manager.serviceCity
                }
                else if (contactState == 2)
                {
                    cityText.text = contact_manager.salesCity
                }
            }
            else
            {
                cityText.text = keyboardBox.hidden_text + cityText.text
            }
        }
        else if (stateKeyboard.visible)
        {
            if (stateText.text.length === 0)
            {
                if (contactState == 1)
                {
                    stateText.text = contact_manager.serviceState
                }
                else if (contactState == 2)
                {
                    stateText.text = contact_manager.salesState
                }
            }
            else
            {
                stateText.text = keyboardBox.hidden_text + stateText.text
            }
        }
        else if (postalCodeKeypad.visible)
        {
            if (postalCodeText.text.length === 0)
            {
                if (contactState == 1)
                {
                    postalCodeText.text = contact_manager.servicePostalCode
                }
                else if (contactState == 2)
                {
                    postalCodeText.text = contact_manager.salesPostalCode
                }
            }
            else
            {
                postalCodeText.text = keyboardBox.hidden_text + postalCodeText.text
            }
        }
        else if (emailKeyboard.visible)
        {
            if (emailText.text.length === 0)
            {
                if (contactState == 1)
                {
                    emailText.text = contact_manager.serviceEmail
                }
                else if (contactState == 2)
                {
                    emailText.text = contact_manager.salesEmail
                }
            }
            else
            {
                emailText.text = keyboardBox.hidden_text + emailText.text
            }
        }
        else if (phoneKeypad.visible)
        {
            if (phoneText.text.includes("*"))
            {
                phoneText.text = ""
                if (contactState == 1)
                {
                    phoneText.text = contact_manager.servicePhoneNumber
                }
                else if (contactState == 2)
                {
                    phoneText.text = contact_manager.salesPhoneNumber
                }
            }
            else
            {
                phoneText.text = keyboardBox.hidden_text + phoneText.text
            }
        }
        keyboardBox.hidden_text = ""
    }

    function switchKeyboards(keyboardId)
    {
        recentText()
        if (keyboardId === 0)
        {
            companyNameText.text = ""

            companyNameText.cursorVisible = true
            addressText.cursorVisible = false
            cityText.cursorVisible = false
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = false
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = true
            addressKeyboard.visible = false
            cityKeyboard.visible = false
            stateKeyboard.visible = false
            postalCodeKeypad.visible = false
            emailKeyboard.visible = false
            phoneKeypad.visible = false
        }
        else if (keyboardId === 1)
        {
            addressText.text = ""

            companyNameText.cursorVisible = false
            addressText.cursorVisible = true
            cityText.cursorVisible = false
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = false
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = false
            addressKeyboard.visible = true
            cityKeyboard.visible = false
            stateKeyboard.visible = false
            postalCodeKeypad.visible = false
            emailKeyboard.visible = false
            phoneKeypad.visible = false
        }
        else if (keyboardId === 2)
        {
            cityText.text = ""

            companyNameText.cursorVisible = false
            addressText.cursorVisible = false
            cityText.cursorVisible = true
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = false
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = false
            addressKeyboard.visible = false
            cityKeyboard.visible = true
            stateKeyboard.visible = false
            postalCodeKeypad.visible = false
            emailKeyboard.visible = false
            phoneKeypad.visible = false
        }
        else if (keyboardId === 3)
        {
            stateText.text = ""

            companyNameText.cursorVisible = false
            addressText.cursorVisible = false
            cityText.cursorVisible = false
            stateText.cursorVisible = true
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = false
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = false
            addressKeyboard.visible = false
            cityKeyboard.visible = false
            stateKeyboard.visible = true
            postalCodeKeypad.visible = false
            emailKeyboard.visible = false
            phoneKeypad.visible = false
        }
        else if (keyboardId === 4)
        {
            postalCodeText.text = ""

            companyNameText.cursorVisible = false
            addressText.cursorVisible = false
            cityText.cursorVisible = false
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = true
            emailText.cursorVisible = false
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = false
            addressKeyboard.visible = false
            cityKeyboard.visible = false
            stateKeyboard.visible = false
            postalCodeKeypad.visible = true
            emailKeyboard.visible = false
            phoneKeypad.visible = false

        }
        else if (keyboardId === 5)
        {
            emailText.text = ""

            companyNameText.cursorVisible = false
            addressText.cursorVisible = false
            cityText.cursorVisible = false
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = true
            phoneText.cursorVisible = false

            companyNameKeyboard.visible = false
            addressKeyboard.visible = false
            cityKeyboard.visible = false
            stateKeyboard.visible = false
            postalCodeKeypad.visible = false
            emailKeyboard.visible = true
            phoneKeypad.visible = false
        }
        else if (keyboardId === 6)
        {
            phoneText.text = "(***)***-****"

            companyNameText.cursorVisible = false
            addressText.cursorVisible = false
            cityText.cursorVisible = false
            stateText.cursorVisible = false
            postalCodeText.cursorVisible = false
            emailText.cursorVisible = false
            phoneText.cursorVisible = true

            phoneText.cursorPosition = 1

            companyNameKeyboard.visible = false
            addressKeyboard.visible = false
            cityKeyboard.visible = false
            stateKeyboard.visible = false
            postalCodeKeypad.visible = false
            emailKeyboard.visible = false
            phoneKeypad.visible = true

            phoneKeypad.index = 1
        }
    }

    function next()
    {
        if (companyNameKeyboard.visible && companyNameText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            companyNameText.text = keyboardBox.hidden_text + companyNameText.text
            companyNameText.cursorVisible = false
            companyNameKeyboard.visible = false
            companyNameKeyboard.layoutState = 0
            companyNameKeyboard.allCapState = 0
            addressText.text = ""
            addressText.cursorVisible = true
            addressKeyboard.visible = true
        }
        else if (addressKeyboard.visible && addressText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            addressText.text = keyboardBox.hidden_text + addressText.text
            addressText.cursorVisible = false
            addressKeyboard.visible = false
            addressKeyboard.layoutState = 0
            addressKeyboard.allCapState = 0
            cityText.text = ""
            cityText.cursorVisible = true
            cityKeyboard.visible = true
        }
        else if (cityKeyboard.visible && cityText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            cityText.text = keyboardBox.hidden_text + cityText.text
            cityText.cursorVisible = false
            cityKeyboard.visible = false
            cityKeyboard.layoutState = 0
            cityKeyboard.allCapState = 0
            stateText.text = ""
            stateText.cursorVisible = true
            stateKeyboard.visible = true
        }
        else if (stateKeyboard.visible && stateText.text.length == 2)
        {
            stateText.cursorVisible = false
            stateKeyboard.visible = false
            postalCodeText.text = ""
            postalCodeText.cursorVisible = true
            postalCodeKeypad.visible = true
        }
        else if (postalCodeKeypad.visible && postalCodeText.text.length == 5)
        {
            postalCodeText.cursorVisible = false
            postalCodeKeypad.visible = false
            emailText.text = ""
            emailText.cursorVisible = true
            emailKeyboard.visible = true
        }
        else if (emailKeyboard.visible && emailText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            emailText.text = keyboardBox.hidden_text + emailText.text
            emailText.cursorVisible = false
            emailKeyboard.visible = false
            emailKeyboard.layoutState = 0
            emailKeyboard.allCapState = 0
            phoneText.text = "(***)***-****"
            phoneText.cursorVisible = true
            phoneText.cursorPosition = 1
            phoneKeypad.visible = true
            phoneKeypad.index = 1
        }
        else if (phoneKeypad.visible && phoneKeypad.index === 13)
        {
            phoneText.cursorVisible = false
            phoneKeypad.visible = false
            companyNameText.text = ""
            companyNameText.cursorVisible = true
            companyNameKeyboard.visible = true

        }
    }

    function prev()
    {
        if (phoneKeypad.visible && phoneKeypad.index === 13)
        {
            phoneText.cursorVisible = false
            phoneKeypad.visible = false
            emailText.text = ""
            emailText.cursorVisible = true
            emailKeyboard.visible = true
        }
        else if (emailKeyboard.visible && emailText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            emailText.text = keyboardBox.hidden_text + emailText.text
            emailText.cursorVisible = false
            emailKeyboard.visible = false
            emailKeyboard.layoutState = 0
            emailKeyboard.allCapState = 0
            postalCodeText.text = ""
            postalCodeText.cursorVisible = true
            postalCodeKeypad.visible = true
        }
        else if (postalCodeKeypad.visible && postalCodeText.text.length == 5)
        {
            postalCodeText.cursorVisible = false
            postalCodeKeypad.visible = false
            stateText.text = ""
            stateText.cursorVisible = true
            stateKeyboard.visible = true
        }
        else if (stateKeyboard.visible && stateText.text.length == 2)
        {
            stateText.cursorVisible = false
            stateKeyboard.visible = false
            cityText.text = ""
            cityText.cursorVisible = true
            cityKeyboard.visible = true
        }
        else if (cityKeyboard.visible && cityText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            cityText.text = keyboardBox.hidden_text + cityText.text
            cityText.cursorVisible = false
            cityKeyboard.visible = false
            cityKeyboard.layoutState = 0
            cityKeyboard.allCapState = 0
            addressText.text = ""
            addressText.cursorVisible = true
            addressKeyboard.visible = true
        }
        else if (addressKeyboard.visible && addressText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            addressText.text = keyboardBox.hidden_text + addressText.text
            addressText.cursorVisible = false
            addressKeyboard.visible = false
            addressKeyboard.layoutState = 0
            addressKeyboard.allCapState = 0
            companyNameText.text = ""
            companyNameText.cursorVisible = true
            companyNameKeyboard.visible = true
        }
        else if (companyNameKeyboard.visible && companyNameText.text.length > 0)
        {
            keyboardBox.hidden_text = ""
            contact_manager.allCapKeySignal(0)
            companyNameText.text = keyboardBox.hidden_text + companyNameText.text
            companyNameText.cursorVisible = false
            companyNameKeyboard.visible = false
            companyNameKeyboard.layoutState = 0
            companyNameKeyboard.allCapState = 0
            phoneText.text = "(***)***-****"
            phoneText.cursorVisible = true
            phoneText.cursorPosition = 1
            phoneKeypad.visible = true
            phoneKeypad.index = 1
        }
    }


    Component.onCompleted:
    {
        switchKeyboards(0)
    }

    Text {
        id: title
        font: Style.settingPageTitle
        topPadding: 48
        anchors.horizontalCenter: parent.horizontalCenter
        color: Style.primary_light
    }

    Rectangle
    {
        id: mainContainer
        width: 898 //1000 //648
        height: 176 //200 //408
        anchors.top: title.bottom
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
        color: Style.transparent

        Rectangle
        {
            id: companyNameBox
            color: Style.transparent
            width: 300
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: parent.left

            Text {
                id: companyNameTitle
                text: qsTr("Company Name:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: companyNameContainer
                width: parent.width
                height: parent.height
                radius: width / 60
                color: Style.unclickable_border
                anchors.top: companyNameTitle.bottom
                anchors.left: parent.left
                clip: true

                TextEdit {
                    id: companyNameText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: companyNameText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(0)
                    }
                }
            }
        }

        Rectangle
        {
            id: addressBox
            color: Style.transparent
            width: 300
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: companyNameBox.right
            anchors.leftMargin: 16

            Text {
                id: addressTitle
                text: qsTr("Address:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: addressContainer
                width: parent.width
                height: parent.height
                radius: width / 60
                color: Style.unclickable_border
                anchors.top: addressTitle.bottom
                anchors.left: parent.left
                clip: true

                TextEdit {
                    id: addressText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: addressText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        switchKeyboards(1)
                    }
                }
            }
        }

        Rectangle
        {
            id: cityBox
            color: Style.transparent
            width: 200
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: addressBox.right
            anchors.leftMargin: 16

            Text {
                id: cityTitle
                text: qsTr("City/Town:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: cityContainer
                width: parent.width
                height: parent.height
                radius: width / 40
                color: Style.unclickable_border
                anchors.top: cityTitle.bottom
                anchors.left: parent.left
                clip: true

                TextEdit {
                    id: cityText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: cityText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(2)
                    }
                }
            }
        }

        Rectangle
        {
            id: stateBox
            color: Style.transparent
            width: 50
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: cityBox.right
            anchors.leftMargin: 16

            Text {
                id: stateTitle
                text: qsTr("State:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: stateContainer
                width: parent.width
                height: parent.height
                radius: width / 10
                color: Style.unclickable_border
                anchors.top: stateTitle.bottom
                anchors.left: parent.left

                TextEdit {
                    id: stateText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: stateText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(3)
                    }
                }
            }
        }

        Rectangle
        {
            id: postalCodeBox
            color: Style.transparent
            width: 100
            height: 50
            anchors.top: companyNameBox.bottom
            anchors.topMargin: 60
            anchors.left: parent.left

            Text {
                id: postalCodeTitle
                text: qsTr("Postal Code:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: postalCodeContainer
                width: parent.width
                height: parent.height
                radius: width / 20
                color: Style.unclickable_border
                anchors.top: postalCodeTitle.bottom
                anchors.left: parent.left

                TextEdit {
                    id: postalCodeText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: postalCodeText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(4)
                    }
                }
            }
        }

        Rectangle
        {
            id: emailBox
            color: Style.transparent
            width: 300
            height: 50
            anchors.top: companyNameBox.bottom
            anchors.topMargin: 60
            anchors.left: postalCodeBox.right
            anchors.leftMargin: 16

            Text {
                id: emailTitle
                text: qsTr("Email/Website:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: emailContainer
                width: parent.width
                height: parent.height
                radius: width / 60
                color: Style.unclickable_border
                anchors.top: emailTitle.bottom
                anchors.left: parent.left
                clip: true

                TextEdit {
                    id: emailText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: emailText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(5)
                    }
                }
            }
        }

        Rectangle
        {
            id: phoneBox
            color: Style.transparent
            width: 200
            height: 50
            anchors.top: companyNameBox.bottom
            anchors.topMargin: 60
            anchors.left: emailBox.right
            anchors.leftMargin: 16

            Text {
                id: phoneTitle
                text: qsTr("Phone Number:")
                color: Style.primary_light
                font: Style.buttonFont
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Rectangle
            {
                id: phoneContainer
                width: parent.width
                height: parent.height
                radius: width / 40
                color: Style.unclickable_border
                anchors.top: phoneTitle.bottom
                anchors.left: parent.left

                TextEdit {
                    id: phoneText
                    font: Style.numberButtonFont
                    color: Style.primary_light
                    x: 7.5
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: TextEdit.PlainText
                    cursorPosition: phoneText.text.length
                    cursorVisible: false
                }

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        switchKeyboards(6)
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: keyboardBox
        color: Style.primary_dark
        width: 1000; height: 400
        anchors.top: mainContainer.bottom
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter

        property string hidden_text: ""

        GeneralContactKeyboard
        {
            id: companyNameKeyboard

            visible: false

            Connections
            {
                target: contact_manager

                enabled: companyNameKeyboard.visible

                onAddKeySignal:
                {
                    if (companyNameKeyboard.layoutState === 0 && companyNameKeyboard.allCapState === 0)
                    {
                        companyNameKeyboard.layoutState = 1
                    }

                    if (companyNameText.text.length == 22)
                    {
                        keyboardBox.hidden_text = keyboardBox.hidden_text + companyNameText.text.charAt(0);
                        companyNameText.text = companyNameText.text.substring(1,companyNameText.text.length);
                    }

                    companyNameText.text = companyNameText.text + value
                }
                onDeleteKeySignal:
                {
                    if (companyNameText.text.length !== 0)
                    {
                        companyNameText.text = companyNameText.text.substring(0,companyNameText.text.length - 1)
                        if (keyboardBox.hidden_text.length > 0)
                        {
                            var tmp_char = ""
                            if (keyboardBox.hidden_text.length > 1)
                            {
                                tmp_char = keyboardBox.hidden_text.charAt(keyboardBox.hidden_text.length - 1)
                            }
                            else
                            {
                                tmp_char = keyboardBox.hidden_text
                            }
                            companyNameText.text = tmp_char + companyNameText.text
                            keyboardBox.hidden_text = keyboardBox.hidden_text.substring(0, keyboardBox.hidden_text.length - 1)
                        }
                    }
                }
                onShiftKeySignal:
                {
                    if (companyNameKeyboard.layoutState === 0 && companyNameKeyboard.allCapState === 0)
                    {
                        companyNameKeyboard.allCapState = 1
                        contact_manager.allCapKeySignal(1)

                    }
                    else if (companyNameKeyboard.layoutState === 0 && companyNameKeyboard.allCapState === 1)
                    {
                        companyNameKeyboard.layoutState = state
                        companyNameKeyboard.allCapState = 0
                        contact_manager.allCapKeySignal(0)
                    }
                    else {
                        companyNameKeyboard.layoutState = state
                    }

                }
                onSwitchKeySignal:
                {
                    companyNameKeyboard.layoutState = state
                }
            }

        }

        GeneralContactKeyboard
        {
            id: addressKeyboard

            visible: false

            Connections
            {
                target: contact_manager

                enabled: addressKeyboard.visible

                onAddKeySignal:
                {
                    if (addressKeyboard.layoutState === 0 && addressKeyboard.allCapState === 0)
                    {
                        addressKeyboard.layoutState = 1
                    }

                    if (addressText.text.length == 22)
                    {
                        keyboardBox.hidden_text = keyboardBox.hidden_text + addressText.text.charAt(0);
                        addressText.text = addressText.text.substring(1, addressText.text.length);
                    }

                    addressText.text = addressText.text + value
                }
                onDeleteKeySignal:
                {
                    if (addressText.text.length !== 0)
                    {
                        addressText.text = addressText.text.substring(0,addressText.text.length - 1)
                        if (keyboardBox.hidden_text.length > 0)
                        {
                            var tmp_char = ""
                            if (keyboardBox.hidden_text.length > 1)
                            {
                                tmp_char = keyboardBox.hidden_text.charAt(keyboardBox.hidden_text.length - 1)
                            }
                            else
                            {
                                tmp_char = keyboardBox.hidden_text
                            }
                            addressText.text = tmp_char + addressText.text
                            keyboardBox.hidden_text = keyboardBox.hidden_text.substring(0, keyboardBox.hidden_text.length - 1)
                        }
                    }
                }
                onShiftKeySignal:
                {
                    if (addressKeyboard.layoutState === 0 && addressKeyboard.allCapState === 0)
                    {
                        addressKeyboard.allCapState = 1
                        contact_manager.allCapKeySignal(1)

                    }
                    else if (addressKeyboard.layoutState == 0 && addressKeyboard.allCapState === 1)
                    {
                        addressKeyboard.layoutState = state
                        addressKeyboard.allCapState = 0
                        contact_manager.allCapKeySignal(0)
                    }
                    else {
                        addressKeyboard.layoutState = state
                    }

                }
                onSwitchKeySignal:
                {
                    addressKeyboard.layoutState = state
                }
            }
        }

        GeneralContactKeyboard
        {
            id: cityKeyboard

            visible: false

            Connections
            {
                target: contact_manager

                enabled: cityKeyboard.visible

                onAddKeySignal:
                {
                    if (cityKeyboard.layoutState === 0 && cityKeyboard.allCapState === 0)
                    {
                        cityKeyboard.layoutState = 1
                    }

                    if (cityText.text.length == 16)
                    {
                        keyboardBox.hidden_text = keyboardBox.hidden_text + cityText.text.charAt(0);
                        cityText.text = cityText.text.substring(1, cityText.text.length);
                    }

                    cityText.text = cityText.text + value
                }

                onDeleteKeySignal:
                {
                    if (cityText.text.length !== 0)
                    {
                        cityText.text = cityText.text.substring(0,cityText.text.length - 1)
                        if (keyboardBox.hidden_text.length > 0)
                        {
                            var tmp_char = ""
                            if (keyboardBox.hidden_text.length > 1)
                            {
                                tmp_char = keyboardBox.hidden_text.charAt(keyboardBox.hidden_text.length - 1)
                            }
                            else
                            {
                                tmp_char = keyboardBox.hidden_text
                            }
                            cityText.text = tmp_char + cityText.text
                            keyboardBox.hidden_text = keyboardBox.hidden_text.substring(0, keyboardBox.hidden_text.length - 1)
                        }
                    }
                }

                onShiftKeySignal:
                {
                    if (cityKeyboard.layoutState === 0 && cityKeyboard.allCapState === 0)
                    {
                        cityKeyboard.allCapState = 1
                        contact_manager.allCapKeySignal(1)
                    }
                    else if (cityKeyboard.layoutState === 0 && cityKeyboard.allCapState === 1)
                    {
                        cityKeyboard.layoutState = state
                        cityKeyboard.allCapState = 0
                        contact_manager.allCapKeySignal(0)
                    }
                    else {
                        cityKeyboard.layoutState = state
                    }
                }

                onSwitchKeySignal:
                {
                    cityKeyboard.layoutState = state
                }
            }
        }

        ContactKeyboardLayout
        {
            id: stateKeyboard

            visible: false

            Component.onCompleted:
            {
                createFirstRow("QWERTYUIOP")
                createSecondRow("ASDFGHJKL")
                createThirdRow("ZXCVBNM")
                createBackSpaceKey()
//                createReturnKey()
//                createCancelKey()
//                createDoneKey()
            }

            Connections
            {
                target: contact_manager

                enabled: stateKeyboard.visible

                onAddKeySignal:
                {
                    if (stateText.text.length < 2) stateText.text = stateText.text + value
                }
                onDeleteKeySignal:
                {
                    if (stateText.text.length !== 0) stateText.text = stateText.text.substring(0,stateText.text.length - 1)
                }
                onEnterKeySignal:
                {
                    if (stateText.text.length == 2)
                    {
                        stateText.cursorVisible = false
                        postalCodeText.text = ""
                        postalCodeText.cursorVisible = true
                        stateKeyboard.visible = false
                        postalCodeKeypad.visible = true
                    }
                }
            }
        }

        GeneralContactKeypad
        {
            id: postalCodeKeypad

            visible: false

            Connections
            {
                target: contact_manager

                enabled: postalCodeKeypad.visible

                onAddKeySignal:
                {
                    if (postalCodeText.text.length < 5) postalCodeText.text = postalCodeText.text + value
                }
                onDeleteKeySignal:
                {
                    if (postalCodeText.text.length !== 0) postalCodeText.text = postalCodeText.text.substring(0,postalCodeText.text.length - 1)
                }
            }
        }

        GeneralContactKeyboard
        {
            id: emailKeyboard

            visible: false

            Connections
            {
                target: contact_manager

                enabled: emailKeyboard.visible

                onAddKeySignal:
                {
                    if (emailKeyboard.layoutState === 0 && emailKeyboard.allCapState === 0)
                    {
                        emailKeyboard.layoutState = 1
                    }

                    if (emailText.text.length == 22)
                    {
                        keyboardBox.hidden_text = keyboardBox.hidden_text + emailText.text.charAt(0);
                        emailText.text = emailText.text.substring(1, emailText.text.length);
                    }

                    emailText.text = emailText.text + value
                }
                onDeleteKeySignal:
                {
                    if (emailText.text.length !== 0)
                    {
                        emailText.text = emailText.text.substring(0,emailText.text.length - 1)
                        if (keyboardBox.hidden_text.length > 0)
                        {
                            var tmp_char = ""
                            if (keyboardBox.hidden_text.length > 1)
                            {
                                tmp_char = keyboardBox.hidden_text.charAt(keyboardBox.hidden_text.length - 1)
                            }
                            else
                            {
                                tmp_char = keyboardBox.hidden_text
                            }
                            emailText.text = tmp_char + emailText.text
                            keyboardBox.hidden_text = keyboardBox.hidden_text.substring(0, keyboardBox.hidden_text.length - 1)
                        }
                    }
                }
                onShiftKeySignal:
                {
                    if(emailKeyboard.layoutState === 0 && emailKeyboard.allCapState === 0)
                    {
                        emailKeyboard.allCapState = 1
                        contact_manager.allCapKeySignal(1)
                    }
                    else if (emailKeyboard.layoutState === 0 && emailKeyboard.allCapState === 1)
                    {
                        emailKeyboard.layoutState = state
                        emailKeyboard.allCapState = 0
                        contact_manager.allCapKeySignal(0)
                    }
                    else {
                        emailKeyboard.layoutState = state
                    }
                }
                onSwitchKeySignal:
                {
                    emailKeyboard.layoutState = state
                }
            }
        }

        GeneralContactKeypad
        {
            id: phoneKeypad

            visible: false

            property int index: 13

            Connections
            {
                target: contact_manager

                enabled: phoneKeypad.visible

                onAddKeySignal:
                {
                    if (phoneKeypad.index !== 13)
                    {
                        if (phoneKeypad.index === 4 || phoneKeypad.index === 8)
                        {
                            phoneKeypad.index = phoneKeypad.index + 1
                        }

                        phoneText.text = phoneText.text.substring(0,phoneKeypad.index) + value + phoneText.text.substring(phoneKeypad.index + 1)
                        phoneKeypad.index = phoneKeypad.index + 1
                        phoneText.cursorPosition = phoneKeypad.index
                    }
                }
                onDeleteKeySignal:
                {
                    if (phoneKeypad.index !== 1)
                    {
                        if (phoneKeypad.index === 5 || phoneKeypad.index === 9)
                        {
                            phoneKeypad.index = phoneKeypad.index - 1
                        }

                        phoneKeypad.index = phoneKeypad.index - 1
                        phoneText.text = phoneText.text.substring(0,phoneKeypad.index) + "*" + phoneText.text.substring(phoneKeypad.index + 1)
                        phoneText.cursorPosition = phoneKeypad.index

                    }
                }
            }
        }
    }

    ContinueButton
    {
        id: continueButton

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onClicked:
        {
            if (
                    companyNameText.text.length > 0 &&
                    addressText.text.length > 0 &&
                    cityText.text.length > 0 &&
                    stateText.text.length == 2 &&
                    postalCodeText.text.length == 5 &&
                    emailText.text.length > 0 &&
                    phoneKeypad.index === 13
                    )
            {
                if (contactState == 1)
                {
                    contact_manager.setService(companyNameText.text,addressText.text,cityText.text,stateText.text,postalCodeText.text,emailText.text,phoneText.text)
                }
                else if (contactState == 2)
                {
                    contact_manager.setSales(companyNameText.text,addressText.text,cityText.text,stateText.text,postalCodeText.text,emailText.text,phoneText.text)
                }

                popupStack.clear()
            }
        }
    }

    CancelButton
    {
        id: cancelButton

        anchors.right: continueButton.left
        anchors.rightMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked:
        {
            popupStack.clear()
        }
    }

    SettingOptionsButton
    {
        id: prevButton
        title: "Prev"

        serviceState: true
        height: 48
        width: 120

        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked:
        {
            prev()
        }
    }

    SettingOptionsButton
    {
        id: nextButton
        title: "Next"

        serviceState: true
        height: 48
        width: 120

        anchors.left: prevButton.right
        anchors.leftMargin: 16
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked:
        {
            next()
        }
    }
}
