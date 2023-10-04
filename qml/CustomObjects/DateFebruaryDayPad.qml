/**
  Object created to select day to change day when month is February.
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

    property int val
    property string value: "01"
    property bool adjustment

    signal changedDayCorrect();

    property bool knobEnabled

    function add(val){
        if (val < 10)
        {
            value = "0" + val
        }
        else
        {
            value = val
        }
        changedDayCorrect();
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
                    if (root.val == 29) root.val = 1
                }
                else
                {
                    root.val = root.val - 1
                    if (root.val == 0) root.val = 28
                }
                add(root.val)
            }
        }
    }

    Rectangle {
        id: numberButtonBox
        color: Style.transparent
        width: 700
        height: 400

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
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 2
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 102
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 3
            width: 96//40
            height: 96 //40
            anchors.right: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 52
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 4
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 5
            width: 96//40
            height: 96 //40
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 52
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 6
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 102
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 7
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 0
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 8
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 9
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 102
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 10
            width: 96//40
            height: 96 //40
            anchors.right: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 52
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 11
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 12
            width: 96//40
            height: 96 //40
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 52
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 13
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 102
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 14
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 100
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 15
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 16
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 102
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 17
            width: 96//40
            height: 96 //40
            anchors.right: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 52
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 18
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 19
            width: 96//40
            height: 96 //40
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 52
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 20
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 102
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 21
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 200
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 22
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 23
            width: 96//40
            height: 96 //40
            anchors.left: parent.left
            anchors.leftMargin: 102
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 24
            width: 96//40
            height: 96 //40
            anchors.right: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 52
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 25
            width: 96//40
            height: 96 //40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 26
            width: 96//40
            height: 96 //40
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 52
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 27
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 102
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }

        NumberButton {
            value: 28
            width: 96//40
            height: 96 //40
            anchors.right: parent.right
            anchors.leftMargin: 2
            anchors.rightMargin: 2
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            y: 300
            onClicked: {
                root.val = value
                add(value)
            }
        }
    }
}
