import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: root
    property int value
    property string unit
    property string title
    property string helpText
    property int settingID
    property int min
    property int max
    property int minOn
    property StackView stack
    property StackView popupStack
    property int step

    property int updateStep: 0

    signal settingConfirmed();
    signal openKeyboard();
    signal dialSignal();

    color: Style.primary_dark

    Text {
        id: nameUnit
        text: qsTr(root.title + " (" + root.unit + ")")
        textFormat: Text.RichText
        font:Style.numericUiDisplayFont
        color: Style.primary_light
        x: 25
        y: 80
    }

    HelpIcon {
        id: hint_button
        anchors.left: nameUnit.right
        anchors.verticalCenter: nameUnit.verticalCenter

        onClicked:
        {
            popupStack.pushHelpBox(title,helpText)
        }
    }

    Component.onCompleted:
    {
        //Checks if rate increment needs to be updated.
        if (root.settingID === rate_1.id || root.settingID === rate_2.id)
        {
            if (root.value < 30)
            {
                root.step = 1;
            }
            else if (root.value > 30)
            {
                root.step = 5;
            }
            else
            {
                root.updateStep = 1;
            }
        }

        if(root.value > root.max)
        {
            root.value = root.max
        }
        if(root.value < root.min)
        {
            root.value = root.min
        }

        if (!minOn)
        {
            minOn = min
        }
    }

    DialDisplay
    {
        id: dialDisplay
        value: root.value
        unit: root.unit
        diameter: root.height / 2
        anchors.centerIn: root

        onClicked:
        {
            root.openKeyboard();
        }
    }

    Connections
    {
        target: knob
        onEncoderIncrement:
        {
            if (root.updateStep)
            {
                //For Rate, if value increases from 30, increments is 5.
                if (encoderVal > 0)
                {
                    root.step = 5;
                }
                //For Rate, if value decreases from 30, increments is 1.
                else if(encoderVal < 0)
                {
                    root.step = 1;
                }
                root.updateStep = 0;
            }

            var currStep = Math.round(root.value / step) * step
            if (root.value < root.minOn && encoderVal > 0)
            {
                root.value = root.minOn;
            }
            else if(root.value <= minOn && encoderVal < 0)
            {
                root.value = root.min;
            }

            else if (currStep + encoderVal * root.step <= root.max && currStep + encoderVal * root.step >= root.minOn)
            {
                root.value = currStep + encoderVal * root.step;
            }
            root.dialSignal();

            //For Rate, when dial value hits 30, increment changes based on dial turn.
            if (root.value == 30 && (root.settingID === rate_1.id || root.settingID === rate_2.id))
            {
                root.updateStep = 1;
            }
        }
        onButtonPush:
        {
            root.settingConfirmed()
        }
    }

    VerticalIndicator
    {
        id: scale
        height: 305
        width: 61
        x: 972
        y: 212
        min: root.min
        max: root.max
        value: root.value
        minOn:root.minOn
    }

    Rectangle
    {
        width: cancelButton.width + saveButton.width + 50
        height: cancelButton.height
        anchors.horizontalCenter: parent.horizontalCenter
        y: .96 * parent.height - height
        color: Style.transparent

        CancelButton
        {
            id: cancelButton
            onClicked:
            {
                if(stack) stack.pop()
            }
            anchors.left: parent.left
        }

        SaveButton
        {
            id: saveButton
            onClicked: {
                root.settingConfirmed()
            }
            maEnabled: true
            anchors.right: parent.right
            anchors.verticalCenter: cancelButton.verticalCenter
        }
    }

    Rectangle {
        id: dial_button
        objectName: "dial_button"
        x: 1129
        y: 729
        width: 135
        height: 44
        color: Style.primary_dark
        visible: settingID !== humidity_1.id
        enabled: settingID !== humidity_1.id

        Rectangle {
            id: dial_button_area
            width: parent.width
            height: parent.height
            color: Style.transparent
            radius: 24
            border.width: 2
            border.color: Style.primary_light

            Text {
                font: Style.buttonFont
                color: Style.primary_light
                x: 59
                anchors.verticalCenter: parent.verticalCenter
                text: "KEYPAD"
            }
            Image {
                id: keypad_icon
                source: "../iconography/numpad_icon.svg"
                sourceSize.width: width
                sourceSize.height: height
                x: 15
                anchors.verticalCenter: parent.verticalCenter
                width: 33
                height: 35
                smooth: true
            }

            ColorOverlay {
                anchors.fill: keypad_icon
                source: keypad_icon
                color: Style.primary_light
            }
        }

        MouseArea {
            id: keypad_mouse_area
            anchors.fill:parent

            onPressed: dial_button_area.color = Style.primary_light_selected
            onReleased: dial_button_area.color = Style.transparent
            onClicked: {
                root.openKeyboard();
            }
        }
    }

    Rectangle
    {
        id: pipDisconnectionButton
        height: 42
        width: 300
        color: Style.primary_dark
        border.color: Style.primary_light
        border.width: 2
        radius: 20
        anchors.left: nameUnit.left
        anchors.leftMargin: root.width * .02
        y: nameUnit.y + nameUnit.height + 15
        visible: settingID === 9 && state_manager.pip_monitoring_mode === 1 && !state_manager.preset_create_active

        MouseArea
        {
            id: pipDisconnectionMA
            anchors.fill: parent
            pressAndHoldInterval: 225
            onPressAndHold:
            {
                pipDisconnectionButton.color = Style.primary_light_selected
                pipDisconnectionButton.delay(50)
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
                backend.setMode(5,0);
                pipDisconnectionButton.color = Style.primary_dark
                timer.stop()
            }
        }

        Text {
            id: pipDisconnectionText
            text: qsTr("Disable PIP Disconnection")
            anchors.centerIn: parent
            color: Style.primary_light
            font: Style.titleFont
        }
    }

    Text
    {
        id: pipDisconnectionInstruction
        text: qsTr("PIP Disconnection is \"ON\". Press button to disable.")
        visible: pipDisconnectionButton.visible
        color: Style.mode_label
        font: Style.titleFont
        anchors.top: pipDisconnectionButton.bottom
        anchors.left: pipDisconnectionButton.left
        wrapMode: "WordWrap"
        topPadding: 15
        width: 230
    }
}
