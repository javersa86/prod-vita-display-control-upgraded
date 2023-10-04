/**
  Object created to enter year to change year.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: Style.transparent

    property int maxDigits: 4
    property bool adjustment

    property int val
    property string value: "2022"

    signal changedYearCorrect();

    property bool knobEnabled

    property int inputCount: 4

    function add(val){
        if (value.length < maxDigits)
        {
            value += val
            root.val = value

        }
        else if (value.length === maxDigits)
        {
            value = value.substring(1) + val
            root.val = value
        }

        changedYearCorrect();
    }

    function backspace(){
        value = value.slice(0,-1);
        root.val = value;
        changedYearCorrect();
    }

    Connections
    {
        target: knob

        onEncoderIncrement:
        {
            if (knobEnabled)
            {
                if (encoderVal === 1)
                {
                    root.val = root.val + 1
                }
                else
                {
                    root.val = root.val - 1
                }
                value = root.val
                while (value.length < maxDigits)
                {
                    value = "0" + value
                }

                changedYearCorrect();
            }
        }
    }

    Rectangle {
        id: numberButtonBox
        width: 300 //132
        height: 400 //176
        color: Style.transparent

        NumberButton {
            value: 1
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 2
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 3
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 4
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 5
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 6
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 7
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 8
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 9
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                add(value)
            }
        }

        NumberButton {
            value: 0
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                add(value)
            }
        }

        Item {
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300

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
                    backspace()
                }
            }
        }
    }
}
