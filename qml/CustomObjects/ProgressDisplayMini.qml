import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: background

    width: 30
    height: 30

    color: Style.transparent

    property int counter: 0

    Component.onCompleted: rotationTimer.start()

    PathView {
        id: spinner

        width: 30
        height: 30
        anchors.centerIn: parent
        model: ListModel {
            ListElement {index: 0}
            ListElement {index: 1}
            ListElement {index: 2}
            ListElement {index: 3}
            ListElement {index: 4}
            ListElement {index: 5}
        }

        delegate: Rectangle {
            width: 5
            height: width
            radius: .5 * width
            color: state_manager.laser_mode ? Style.o2_color : Style.primary_light
            opacity: Math.abs(3 - Math.abs(index - counter) % 6) / 3
        }

        path: Path {
            startX: 15
            startY: 0
            PathArc { x: 15; y: 30; radiusX: 15; radiusY: 15; useLargeArc: true }
            PathArc { x: 15; y: 0; radiusX: 15; radiusY: 15; useLargeArc: true }
        }

        Timer
        {
            id: rotationTimer
            onTriggered:  counter += 1
            interval: 100
            repeat: true
        }
    }
}
