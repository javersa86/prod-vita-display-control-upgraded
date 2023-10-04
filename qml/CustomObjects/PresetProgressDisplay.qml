import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.transparent

    property int counter: 0

    Component.onCompleted:
    {
        rotationTimer.start()
    }

    Text {
        id: center_text
        text: "Preset"
        x: -150
        y: -90
        width: 200
        font: Style.loadingText
        color: Style.primary_light
        wrapMode: Text.WordWrap
    }
    Text {
        text: "Loading..."
        x: -150
        anchors.top: center_text.bottom
        width: 200
        font: Style.loadingText
        color: Style.primary_light
        wrapMode: Text.WordWrap
    }

    PathView {
        id: spinner
        width: 400
        height: 400
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
            width: 15
            height: width
            radius: .5 * width
            color: Style.primary_light
            opacity: Math.abs(8 - Math.abs(index - counter) % 16) / 9

        }
        path: Path {
            startX: 200
            startY: 0
            PathArc { x: 200; y: 400; radiusX: 200; radiusY: 200; useLargeArc: true }
            PathArc { x: 200; y: 0; radiusX: 200; radiusY: 200; useLargeArc: true }
        }
    }

    Timer
    {
        id: rotationTimer
        onTriggered: counter += 1
        interval: 250
        repeat: true
    }
}
