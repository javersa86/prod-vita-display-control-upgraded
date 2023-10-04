import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: calibrateButtonBox
    width: 200
    height: 90
    color:Style.transparent
    signal clicked()
    property bool enabled


    Rectangle
    {

        height: .5 * calibrateButtonBox.height
        width: .9 * calibrateButtonBox.width
        color: Style.affirmative
        radius: .5 * height
        opacity: calibrateButtonBox.enabled ? 1 : .5
        anchors.centerIn: parent

    MouseArea
    {
        id: mouseArea
        width : 2 * parent.width
        height: 2 * parent.height
        anchors.centerIn: parent
        enabled: calibrateButtonBox.enabled
        onClicked:
        {
            calibrateButtonBox.clicked()
        }
    }

    Text {
        id: calibrateText
        text: qsTr("CALIBRATE")
        font: Style.buttonFont
        color:Style.primary_dark
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
//    Image {
//        id: calibrationIcon
//        source: "../iconography/calibration.svg"
//        sourceSize.width: width
//        sourceSize.height: height
//        smooth: true
//        anchors.verticalCenter: parent.verticalCenter
//        x: .15 * parent.width
//    }
    }
}// end of calibrate button
