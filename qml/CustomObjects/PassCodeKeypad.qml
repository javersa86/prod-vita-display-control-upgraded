import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: keyboard_root
    width: 288
    height: 487
    color: Style.transparent

    property string value: value_display.value
    property int maxDigits: 6
    property bool adjustment

    function reset()
    {
        value_display.value = "";
        valueText.text = ""
    }

    Rectangle {
        id: value_display
        width: parent.width
        height: 57
        color: Style.transparent
        border.color: Style.general_set_display
        border.width: 2
        radius: 4
        x: 0
        y:0
        property string value:""
        Text {
            id: valueText
            color: Style.general_set_display
            anchors.centerIn:parent
            font: Style.numericUiDisplayFont
        }

        function add(val){
            if (value.length < maxDigits)
            {
                valueText.text += "*"
                value += val

            }
        }

        function backspace(){
            value = value.slice(0,-1)
            valueText.text = valueText.text.slice(0,-1)
        }
    }

    Rectangle {
        id: numberButtonBox
        height: 392
        width: parent.width
        y: 95
        color: Style.transparent

        NumberButton {
            value: 1
            anchors.left: parent.left
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 2
            anchors.horizontalCenter: parent.horizontalCenter
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 3
            anchors.right: parent.right
            y: 0
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 4
            anchors.left: parent.left
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 5
            anchors.horizontalCenter: parent.horizontalCenter
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 6
            anchors.right: parent.right
            y: 104
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 7
            anchors.left: parent.left
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 8
            anchors.horizontalCenter: parent.horizontalCenter
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 9
            anchors.right: parent.right
            y: 208
            onClicked: {
                value_display.add(value)
            }
        }

        NumberButton {
            value: 0
            anchors.horizontalCenter: parent.horizontalCenter
            y: 312
            onClicked: {
                value_display.add(value)
            }
        }

        Item {
            width: 45
            height: 45
            x: 225
            y: 329

            signal clicked();

            onClicked: {
                value_display.backspace()
            }
            Image {
                id: lock_icon
                source: "../iconography/keyboard-delete.svg"
                sourceSize.width: width
                sourceSize.height: height
                width: parent.width
                height: parent.height
                smooth: true
            }

            ColorOverlay {
                anchors.fill: lock_icon
                source: lock_icon
                color: Style.primary_light
            }

            MouseArea {
                id: mouseArea
                anchors.fill:parent

                onClicked:{
                    value_display.backspace()
                }
            }
        }
    }
}
