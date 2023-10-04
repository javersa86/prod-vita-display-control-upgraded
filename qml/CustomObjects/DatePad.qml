import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle {
    id: root

    color: Style.transparent
    width: 300 //132
    height: 400 //176

    signal addSignal(int val)
    signal clearSignal()

    function add(val)
    {
        addSignal(val);
    }

    function clear()
    {
        clearSignal();
    }

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

    Rectangle {
        width: 96
        height: 96
        color: mouseArea.pressed ? Style.primary_light_selected : Style.transparent
        border.color: Style.primary_light
        border.width: 4
        radius: width*0.5
        anchors.right: parent.right
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        y: 300

        Text {
            text: "C"
            font: Style.numberButtonFont
            color: Style.primary_light
            anchors.centerIn: parent
        }

        MouseArea {
            id: mouseArea
            anchors.fill:parent

            onClicked:{
                clear()
            }
        }
    }
}
