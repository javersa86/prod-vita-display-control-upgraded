import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "DehumidificationChecklist"

    property StackView popupStack

    MouseArea
    {
        height: background.height
        width: background.width
        onClicked:{}
    }

    Rectangle
    {
        id: dehum_checklist_box
        height: background.height / 2.5
        width: background.width / 2

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
            text: "DEHUMIDIFICATION"
            font: Style.buttonFont
            color: Style.general_set_display
            x: dehum_checklist_box.leftPadding
            y: dehum_checklist_box.topPadding
        }

        Text
        {
            id: big_text
            text: !state_manager.ventilating && !state_manager.aux ? "Before you start" : "Stop ventilating to dehumidify"
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: dehum_checklist_box.width - leftPadding * 2
            x: dehum_checklist_box.leftPadding
            y: dehum_checklist_box.topPadding + title.height
            wrapMode: Text.WordWrap
        }

        Rectangle
        {
            id: patient_disconnection_check_container
            width: dehum_checklist_box.width - dehum_checklist_box.leftPadding * 2
            height: 54 //30
            x: dehum_checklist_box.leftPadding
            y: big_text.y + big_text.height + dehum_checklist_box.topPadding - 24
            color:Style.transparent
            enabled: !state_manager.ventilating && !state_manager.aux

            Rectangle
            {
                id: patient_disconnection_check_button
                property bool checked: false
                width: 48 //24
                height: 48 //24
                radius: .5 * width
                color: Style.transparent
                border.color: Style.primary_light_disabled
                border.width: 2

                Item {
                    id: pCheckIcon
                    height: parent.height * 1.75
                    width: height
                    anchors.centerIn: parent
                    visible: patient_disconnection_check_button.checked
                    Image {
                        id: pIcon
                        source: "../iconography/icon_40_checkmark.svg"
                        sourceSize.width: width
                        sourceSize.height: height
                        width: parent.width
                        height: parent.height
                        smooth: true
                        visible: true
                    }
                    ColorOverlay {
                        anchors.fill: pIcon
                        source: pIcon
                        color: Style.primary_light
                    }
                }
            }

            Text {
                id: patient_disconnection_description
                text: qsTr("Ensure tubes are connected to the machine but not to the patient.")
                font: Style.buttonFont
                color: !state_manager.ventilating && !state_manager.aux ? Style.primary_light : Style.primary_light_disabled
                x: patient_disconnection_check_button.x + patient_disconnection_check_button.width + dehum_checklist_box.leftPadding / 2
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea
            {
                anchors.fill:patient_disconnection_check_container
                onClicked:
                {
                    patient_disconnection_check_button.checked = !patient_disconnection_check_button.checked
                }
            }
        }

        Rectangle
        {
            id: divider
            width: dehum_checklist_box.width - dehum_checklist_box.leftPadding * 2
            height: 2
            radius: 2
            color: Style.primary_light_disabled
            anchors.horizontalCenter: dehum_checklist_box.horizontalCenter
            y: (iv_disconnection_check_container.y + iv_disconnection_check_container.height - patient_disconnection_check_container.y)/2 +
               patient_disconnection_check_container.y
        }

        Rectangle
        {
            id: iv_disconnection_check_container
            x: dehum_checklist_box.leftPadding
            y: patient_disconnection_check_container.y + patient_disconnection_check_container.height + dehum_checklist_box.topPadding
            width: dehum_checklist_box.width - dehum_checklist_box.leftPadding * 2
            height: 54 //30
            color:Style.transparent
            enabled: !state_manager.ventilating && !state_manager.aux

            Rectangle
            {
                id: iv_disconnection_check_button
                property bool checked: false
                width: 48 //24
                height: 48 //24
                radius: .5 * width
                color: Style.transparent
                border.color: Style.primary_light_disabled
                border.width: 2


                Item {
                    id: ivCheckIcon
                    height: parent.height * 1.75
                    width: height
                    anchors.centerIn: parent
                    visible: iv_disconnection_check_button.checked
                    Image {
                        id: ivIcon
                        source: "../iconography/icon_40_checkmark.svg"
                        sourceSize.width: width
                        sourceSize.height: height
                        width: parent.width
                        height: parent.height
                        smooth: true
                        visible: true
                    }
                    ColorOverlay {
                        anchors.fill: ivIcon
                        source: ivIcon
                        color: Style.primary_light
                    }
                }
            }

            Text {
                id: iv_disconnection_description
                text: qsTr("Disconnect I.V. bag.")
                font: Style.buttonFont
                color: !state_manager.ventilating && !state_manager.aux ? Style.primary_light : Style.primary_light_disabled
                x: iv_disconnection_check_button.x + iv_disconnection_check_button.width + dehum_checklist_box.leftPadding / 2
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea
            {
                anchors.fill:iv_disconnection_check_container
                onClicked:
                {
                    iv_disconnection_check_button.checked = !iv_disconnection_check_button.checked
                }
            }

        }

        Rectangle
        {
            id: close_button

            height: dehum_checklist_box.height * .16
            width: dehum_checklist_box.width * .2
            color: Style.transparent
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            x: dehum_checklist_box.leftPadding
            y: (dehum_checklist_box.height - (iv_disconnection_check_container.y + iv_disconnection_check_container.height)) / 2 +
               iv_disconnection_check_container.y + iv_disconnection_check_container.height - height / 2

            Text
            {
                id: closeStr
                text: qsTr("CLOSE")
                color: Style.primary_light
                anchors.verticalCenter: close_button.verticalCenter
                anchors.horizontalCenter: close_button.horizontalCenter
                leftPadding: .3 * close_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                pressAndHoldInterval: 225
                onPressAndHold: {
                    close_button.color = Style.primary_light_selected
                    close_button.delay(50)
                }
                anchors.fill: close_button
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
                    popupStack.dehumidifyComplete(0)
                    close_button.color = Style.transparent
                    timer.stop()
                }
            }

            Rectangle
            {
                id: closeIconBackground
                height: close_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: close_button.verticalCenter
                radius: .5 * height
                color: Style.primary_light

            }

            Item {
                id: closeIcon
                height: close_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: close_button.verticalCenter
                Image {
                    id: xicon
                    source: "../iconography/icon_40_close.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: xicon
                    source: xicon
                    color: Style.primary_light_selected
                }
            }

        }

        Rectangle
        {
            id: start_button

            height: dehum_checklist_box.height * .16
            width: dehum_checklist_box.width * .45
            color: startMA.enabled ? Style.affirmative : Style.affirmative_transluscent
            radius: 24

            x: close_button.x + close_button.width + dehum_checklist_box.width * .25
            y: (dehum_checklist_box.height - (iv_disconnection_check_container.y + iv_disconnection_check_container.height)) / 2 +
               iv_disconnection_check_container.y + iv_disconnection_check_container.height - height / 2

            Text
            {
                id: startStr
                text: qsTr("START DEHUMIDIFICATION")
                color: Style.primary_dark
                anchors.verticalCenter: start_button.verticalCenter
                leftPadding: startIcon.width + startIcon.x + 10
                font: Style.buttonFont
            }

            MouseArea
            {
                id: startMA
                enabled: patient_disconnection_check_button.checked && iv_disconnection_check_button.checked &&
                         !state_manager.ventilating && !state_manager.aux
                anchors.fill: start_button
                pressAndHoldInterval: 225
                onPressAndHold: {
                    start_button.color = Style.affirmative_transluscent
                    start_button.delay(50)
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
                    backend.setMode(7, 1);
                    popupStack.replace("DehumidifyingProgressPage.qml", {"popupStack" : popupStack})
                    start_button.color = Style.affirmative
                    timer1.stop()
                }
            }

            Item {
                id: startIcon
                height: start_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: start_button.verticalCenter
                Image {
                    id: sicon
                    source: "../iconography/play.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: sicon
                    source: sicon
                    color: Style.primary_dark
                }
            }
        }
    }
}
