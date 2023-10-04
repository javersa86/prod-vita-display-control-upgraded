import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"

Rectangle {
    id: root
    width: 150
    height: 64
    color:Style.transparent
    property bool maEnabled
    signal clicked()

    Rectangle
    {
        id: confirmButton
        height:48
        width:127
        anchors.centerIn: parent
        radius: 24
        color: Style.affirmative
        opacity: root.maEnabled ? 1.0 : 0.50

        Rectangle
        {
            id: mainContainer
            width: .68 * parent.width
            height: parent.height
            color: Style.transparent
            x: 10

            Image
            {
                id: checkmark
                anchors.verticalCenter: parent.verticalCenter
                anchors.left:parent.left
                source: "../iconography/icon_40_checkmark.svg"
                smooth: true
                sourceSize.width: width
                sourceSize.height: height

                ColorOverlay
                {
                    anchors.fill: parent
                    source: checkmark
                    color: Style.primary_dark
                }
            }

            Text
            {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: "Save"
                color: Style.primary_dark
                font: Style.buttonFont
            }
        }
    }

    MouseArea {
        id: confirm_mouse_area
        anchors.fill:parent
        enabled: root.maEnabled
        pressAndHoldInterval: 225
        onPressAndHold:
        {
            confirmButton.color = Style.affirmative_transluscent
            root.delay(50)
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
            root.clicked()
            confirmButton.color = Style.affirmative
            timer.stop()
        }
    }
}
