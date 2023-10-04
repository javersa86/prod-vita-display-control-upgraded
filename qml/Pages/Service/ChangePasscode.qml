/*
  Page where technician can change passcode to preset page, and passcode to service page.
  Pressing the Service Passcode button, PassCode.qml pops up.
  Pressing the Preset Passcode button, ChangePassCode.qml pops up.

  Moved buttons to their own bordered sections with instructions below.
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

    property StackView homeStack
    property StackView popupStack
    property int topY

    property Item passCodePage;
    property Item passCodeChangePage;

    Connections
    {
        target: passCodePage
        onPassCodeCorrect:
        {
            if (root_window.passCodePage.nextPage === "PassCodeChange.qml")
            {
                root_window.passCodeChangePage = root_window.popupStack.push(
                            "PassCodeChange.qml",
                            {
                                "code" : passcode_manager.servicePasscode,
                                "nextPage" : "PassCodeConfirm.qml",
                                "isService" : root_window.passCodePage.isService,
                                "stack" : root_window.popupStack,
                                "parameters" : {
                                    "stack" : root_window.homeStack,
                                    "popupStack" : popupStack
                                }
                            });
            }
        }
    }

    Connections
    {
        target: passCodeChangePage
        onPassCodeChangeCorrect:
        {
            if (root_window.passCodeChangePage.nextPage === "PassCodeConfirm.qml")
            {
                root_window.popupStack.replace("PassCodeConfirm.qml", root_window.passCodeChangePage.parameters)
            }
        }
    }

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .75 * parent.height
        anchors.verticalCenter: parent.verticalCenter
        y: .1 * parent.height
        color: Style.transparent

        Rectangle
        {
            id: box1
            width: .5 * parent.width
            height: .75 * parent.height + 15
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 30
            color: Style.transparent

            Text {
                id: title1
                text: qsTr("Change Service Passcode:")
                textFormat: Text.RichText
                color:Style.primary_light
                font: Style.settingPageTitle
                anchors.left: box1.left
                topPadding: 8
            }

            SettingOptionsButton
            {
                id: changeServiceButton
                title: "Continue"
                anchors.top: title1.bottom
                anchors.topMargin: 32
                anchors.left: parent.left

                Component.onCompleted:
                {
                    selected = false;
                    changePresetButton.selected = false;
                }
                onClicked:
                {
                    if(!selected)
                    {
                        selected = true;
                        changePresetButton.selected = false;
                        root_window.passCodePage = root_window.popupStack.push(
                                    "PassCode.qml",
                                    {
                                        "code" : passcode_manager.servicePasscode,
                                        "nextPage" : "PassCodeChange.qml",
                                        "isService" : 1,
                                        "stack" : root_window.popupStack,
                                        "parameters" : {
                                            "stack" : root_window.homeStack,
                                            "popupStack" : popupStack
                                        }
                                    });
                        selected = false;
                    }

                }
            }
            Text
            {
                id: steps1
                anchors.top: changeServiceButton.bottom
                anchors.topMargin: 32
                anchors.left: parent.left
                font: Style.buttonFont
                color:Style.primary_light
                text: "1. Please enter previous Passcode.\n" +
                      "2. Please enter new Passcode with the following criteria:\n" +
                      "   1. Cannot enter previous Passcode.\n" +
                      "   2. 4-digit length required."
                lineHeight: 1.5
            }
        }

        Rectangle
        {
            id: box2
            width: .5 * parent.width
            height: .75 * parent.height + 15
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: box1.right
            anchors.leftMargin: 1
            color: Style.transparent

            Text {
                id: title2
                text: qsTr("Change Preset Passcode:")
                textFormat: Text.RichText
                color:Style.primary_light
                font: Style.settingPageTitle
                anchors.left: box2.left
                topPadding: 8
            }

            SettingOptionsButton
            {
                id: changePresetButton
                title: "Continue"
                anchors.top: title2.bottom
                anchors.topMargin: 32
                anchors.left: parent.left

                Component.onCompleted:
                {
                    selected = false;
                    changeServiceButton.selected = false;
                }
                onClicked:
                {
                    if(!selected)
                    {
                        selected = true;
                        changeServiceButton.selected = false;
                        root_window.passCodeChangePage = root_window.popupStack.push(
                                    "PassCodeChange.qml",
                                    {
                                        "code" : "",
                                        "nextPage" : "PassCodeConfirm.qml",
                                        "isService" : 0,
                                        "stack" : root_window.popupStack,
                                        "parameters" : {
                                            "stack" : root_window.homeStack,
                                            "popupStack" : popupStack
                                        }
                                    });
                        selected = false;
                    }
                }
            }
            Text
            {
                id: steps2
                anchors.top: changePresetButton.bottom
                anchors.topMargin: 32
                anchors.left: parent.left
                font: Style.buttonFont
                color:Style.primary_light
                text: "1. Changing Passcode does not require previous one.\n" +
                      "2. Please enter new Passcode with the following criteria:\n" +
                      "   1. 4-digit length required."
                lineHeight: 1.5
            }
        }
    }
}
