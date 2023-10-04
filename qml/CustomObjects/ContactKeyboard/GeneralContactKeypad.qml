import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../CustomObjects"
import "../../CustomObjects/ContactKeyboard"
import "../../Styles"
import "../../iconography"

Rectangle
{
    id: root_window

    x: 350


    Rectangle
    {
        id: numberButtonLayout
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                contact_manager.addKeySignal(value)
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
                source: "../../iconography/keyboard-delete.svg"
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
                    contact_manager.deleteKeySignal()
                }
            }
        }
    }
}
