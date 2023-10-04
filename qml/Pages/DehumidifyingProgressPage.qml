import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import SensorID 1.0
import "../Styles"
import "../CustomObjects"
import IDs 1.0

Rectangle{
    id: background
    color: Style.primary_dark
    objectName: "DehumidifyingProgressPage"
    property int dehumidifying: state_manager.dehumidify_mode

    property StackView popupStack

    property int counter: 0
    property int dehumidification_success: 1

    Connections
    {
        target: backend

        onDehumidificationTime:
        {
            secondsToTime(dehumidificationSeconds);
        }
    }

    Component.onCompleted:
    {
        rotationTimer.start()
        backend.initDehumidification(1)
    }

    onDehumidifyingChanged:
    {
        if (!dehumidifying){
            if(state_manager.dehumidify_success)
            {
                backend.initDehumidification(0)
                popupStack.dehumidifyComplete(dehumidification_success)
            }
            else
            {
                backend.initDehumidification(0)
                popupStack.replace("DehumidificationFailure.qml", {"popupStack": popupStack})
            }
        }
    }

    function secondsToTime(duration)
    {
        var minutes = parseInt(duration / 60, 10);
        var seconds = parseInt(duration % 60, 10);

        minutes = minutes < 10 ? "0" + minutes : minutes;
        seconds = seconds < 10 ? "0" + seconds : seconds;

        humidityValue.text = minutes + ":" + seconds;
    }

    Text {
        id: humidityValue
        text: "02:00"
        font: Style.measuredFont
        color: Style.primary_light
        wrapMode: Text.WordWrap

        anchors.horizontalCenter: background.horizontalCenter
        anchors.bottom: background.verticalCenter

    }

    Item {
        id: icon
        height: spinner.height/6
        width: height
        //anchors.centerIn: background
        anchors.horizontalCenter: background.horizontalCenter
        anchors.top: background.verticalCenter
        anchors.topMargin: 40

        Image {
            id: icon_svg
            source: "../iconography/icon_40_dehumidify.svg"
            sourceSize.width: width
            sourceSize.height: height
            width: parent.width
            height: parent.height
            smooth: true
            visible: true
        }
        ColorOverlay {
            anchors.fill: icon_svg
            source: icon_svg
            color: Style.primary_light
        }
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

    CancelButton
    {
        id: cancelButton
        anchors.horizontalCenter: parent.horizontalCenter
        y: .85 * parent.height
        onClicked:
        {
            dehumidification_success = 0
            backend.setMode(ID.DEHUMIDIFY_MODE,0)
        }
    }
}
