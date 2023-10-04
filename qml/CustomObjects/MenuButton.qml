import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
Rectangle
{
    id: menuButton
    signal clicked();
    property string iconSource
    property string title
    property int iconSize: height
    color: Style.transparent

    Rectangle
    {
        id:guidline
        height: menuButton.height
        width: 2
        x: menuButton.width / 11
        color:Style.transparent
    }

    Item {
        id: iconItem
        height: menuButton.iconSize
        width: height
        anchors.horizontalCenter: guidline.horizontalCenter
        anchors.verticalCenter: menuButton.verticalCenter
        visible: true
        opacity: menuButton.enabled ? 1 : .2
        Image {
            id: icon
            source: menuButton.iconSource
            sourceSize.width: width
            sourceSize.height: height
            width: parent.width
            height: parent.height
            smooth: true
            visible: true
        }
        ColorOverlay {
            anchors.fill: icon
            source: icon
            color: Style.primary_light
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill:parent
        pressAndHoldInterval: 225
        onPressAndHold:{
            menuButton.color = Style.primary_light_selected
            delay(300)
        }
    }

    function delay(delayTime)
    {
        timer.interval = delayTime;
        timer.start();
    }

    Timer {
        id: timer
        repeat: false
        onTriggered:
        {
            menuButton.clicked()
            menuButton.color = Style.transparent
            timer.stop()
        }
    }

    Text {
        text: menuButton.title
        font: Style.numberButtonFont
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: iconItem.right
        color: menuButton.enabled ? Style.primary_light : Style.primary_light_disabled
        leftPadding: 15
    }
}
