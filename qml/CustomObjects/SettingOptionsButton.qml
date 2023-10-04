import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle
{
    id: rootButton
    radius: width / 10
    color: selected ? Style.primary_light : Style.transparent
    border.width: 2
    border.color: Style.primary_light
    height: 48
    width: 220

    property bool serviceState: false
    property string title
    property bool selected

    signal clicked();

    Text {
        id: titleDisplay
        text: qsTr(title)
        textFormat: Text.RichText
        font: Style.buttonFont
        color: rootButton.selected ? Style.primary_dark : Style.primary_light
        anchors.centerIn: parent
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill:parent
        enabled: !serviceState

        onClicked:
        {
            if(! rootButton.selected) rootButton.clicked();
        }
    }

    MouseArea
    {
        id: mouseArea1
        anchors.fill: parent
        enabled: serviceState
        pressAndHoldInterval: 225

        onPressAndHold:
        {
            rootButton.color = Style.primary_light_selected
            titleDisplay.color = Style.primary_light
            rootButton.delay(50)
        }
    }

    function delay(delayTime)
    {
        timer1.interval = delayTime;
        timer1.start();
    }

    Timer {
        id: timer1
        repeat: false
        onTriggered:
        {
            rootButton.clicked()
            rootButton.color = Style.transparent
            titleDisplay.color = Style.primary_light
            timer1.stop()
        }
    }
}
