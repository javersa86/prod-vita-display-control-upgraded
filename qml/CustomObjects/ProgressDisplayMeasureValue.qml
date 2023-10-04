import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: background
    color: Style.transparent
    width: 80
    height: 80

    property int counter: 0
    property color colorState

    Component.onCompleted: rotationTimer.start()

    signal pressAndHold()

    PathView
    {
        id: spinner

        width: 80
        height: 80
        anchors.centerIn: parent
        model: ListModel {
            ListElement {index: 0}
            ListElement {index: 1}
            ListElement {index: 2}
            ListElement {index: 3}
            ListElement {index: 4}
            ListElement {index: 5}
            ListElement {index: 6}
            ListElement {index: 7}
            ListElement {index: 8}
            ListElement {index: 9}
            ListElement {index: 10}
            ListElement {index: 11}
            ListElement {index: 12}
            ListElement {index: 13}
            ListElement {index: 14}
            ListElement {index: 15}
        }

        delegate: Rectangle {
            width: 5
            height: width
            radius: .5 * width
            color: colorState //state_manager.laser_mode ? Style.o2_color : Style.primary_light
            opacity: Math.abs(8 - Math.abs(index - counter) % 16) / 8
        }
        path: Path {
            startX: 40
            startY: 0
            PathArc { x: 40; y: 80; radiusX: 40; radiusY: 40; useLargeArc: true}
            PathArc { x: 40; y: 0; radiusX: 40; radiusY: 40; useLargeArc: true}
        }

        Timer
        {
            id: rotationTimer
            onTriggered:  counter += 1
            interval: 100
            repeat: true
        }
    }

    MouseArea
    {
        anchors.fill: parent
        pressAndHoldInterval: 225

        onPressAndHold:
        {
            background.pressAndHold()
        }
    }
}
