import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import SensorID 1.0
import "../Styles"
import "../CustomObjects"

Rectangle {
    id: background
    color: Style.primary_dark_transluscent
    objectName: "JetActiveConfirmation"

    property StackView popupStack
    property alias currentText: title.text
    property var procedureId

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    Connections
    {
        target: state_manager

        onVentilatingChanged:
        {
            getStateText()
        }
    }

    Component.onCompleted:
    {
        getStateText()
    }

    function getStateText()
    {
        if (state_manager.ventilating)
        {
            if (state_manager.manual_mode)
            {
                if (state_manager.aux)
                {
                    big_text.text = "Cannot shutdown while Manual and<br>Auxiliary Line is Active."
                    description.text = "Press TURN AUX AND MANUAL OFF to disable Manual Mode,<br>turn off Auxiliary Flow, and continue with shutdown or dehumidification."
                }
                else
                {
                    big_text.text = "Cannot shutdown while Manual Mode<br>is Active."
                    description.text = "Press TURN MANUAL OFF to disable Manual Mode<br>and continue with shutdown or dehumidification."
                }
            }
            else
            {
                if (state_manager.aux)
                {
                    big_text.text = "Cannot shutdown while Jet Line and<br>Auxiliary Line is Active."
                    description.text = "Press TURN AUX OFF to turn off Auxiliary Flow<br>and continue with shutdown or dehumidification."
                }
            }
        }
        else
        {
            if (state_manager.aux)
            {
                big_text.text = "Cannot shutdown while Auxiliary Line<br>is Active."
                description.text = "Press TURN AUX OFF to turn off Auxiliary Flow<br>and continue with shutdown or dehumidification."
            }
        }
    }

    Rectangle
    {
        id:mainContainer
        width: .95 * background.width
        height: .95 * background.height
        anchors.centerIn: background
        color:Style.transparent

        Rectangle
        {
            id: jetActiveConfirmationBox
            height: mainContainer.height / 2.5
            width: mainContainer.width / 2

            x: background.width / 2 - width / 2
            y: background.height / 3 - height / 2

            color: Style.primary_dark
            border.color: Style.general_set_display
            radius: 4
            border.width: 2

            property int leftPadding: 30
            property int topPadding: 30

            Text
            {
                id: title
                font: Style.buttonFont
                color: Style.general_set_display
                x: jetActiveConfirmationBox.leftPadding
                y: jetActiveConfirmationBox.topPadding
            }

            Text
            {
                id: big_text
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: jetActiveConfirmationBox.width - (leftPadding * 2)
                x: jetActiveConfirmationBox.leftPadding
                y: jetActiveConfirmationBox.topPadding + title.height
            }

            Text {
                id: description
                color: Style.primary_light_disabled
                font: Style.buttonFont
                width: parent.width
                y: big_text.y + big_text.height + jetActiveConfirmationBox.topPadding
                x: jetActiveConfirmationBox.leftPadding
                wrapMode: Text.WordWrap
            }

            CancelButton
            {
                id: cancelButton
                x: jetActiveConfirmationBox.leftPadding
                anchors.verticalCenter: offButtonBox.verticalCenter
                onClicked:
                {
                    if (background.procedureId === 0)
                    {
                        backend.initiatePowerdown(0);
                        if(background.popupStack.depth == 1) background.popupStack.clear();
                        else background.popupStack.pop()
                    }
                    else if (background.procedureId === 1)
                    {
                        popupStack.dehumidifyComplete(0)
                    }
                }
            }

            Rectangle
            {
                id: offButtonBox
                height: 90
                width: state_manager.aux && state_manager.manual_mode ? 300 : 210
                color: Style.transparent
                signal clicked();
                x: parent.width - width - 5
                anchors.bottom: parent.bottom

                onClicked:
                {
                    if (state_manager.aux)
                    {
                        backend.receiveSettingsUpdate(aux_flow.id,0)
                    }
                    if (state_manager.manual_mode)
                    {
                        state_manager.forceManualOff();
                    }

                    if (background.procedureId === 1)
                    {
                        popupStack.push("DehumidificationDisconnection.qml", {"popupStack": popupStack, "buttonVisible": 1})
                    }
                    else
                    {
                        popupStack.push("ShutdownConfirmation.qml",{"popupStack": popupStack})

                    }
                }

                Rectangle
                {
                    id: offButton
                    color: Style.affirmative
                    height: .5 * offButtonBox.height
                    width: .9 * offButtonBox.width
                    anchors.centerIn: offButtonBox
                    radius: 24

                    Text {
                        text: state_manager.aux && state_manager.manual_mode ?
                                  "TURN AUX AND MANUAL OFF" : state_manager.aux && !state_manager.manual_mode ?
                                      "TURN AUX OFF" : "TURN MANUAL OFF"
                        color:Style.primary_dark
                        font:Style.buttonFont
                        anchors.centerIn: parent
                    }
                }

                MouseArea
                {
                    anchors.fill: parent
                    pressAndHoldInterval: 225
                    onPressAndHold:
                    {
                        offButton.color = Style.affirmative_transluscent
                        timer.start()
                    }
                }

                Timer {
                    id: timer
                    interval: 50
                    repeat: false
                    onTriggered:
                    {
                        offButtonBox.clicked()
                        offButton.color = Style.affirmative
                        timer.stop()
                    }
                }
            }
        }
    }
}
