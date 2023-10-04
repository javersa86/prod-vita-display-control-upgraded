import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"

Rectangle
{
    id: continueButtonBox
    height: 90
    width: 200
    color:Style.transparent
    signal clicked();
    property string continueText: "CONTINUE"
    property bool enableButton: true

    Rectangle
    {
        id: continueButton
        color:Style.affirmative
        height:.5 * continueButtonBox.height
        width: .9 * continueButtonBox.width
        anchors.centerIn: continueButtonBox
        radius: 24

        Text {
            text: qsTr(continueText)
            color:Style.primary_dark
            font:Style.buttonFont
            anchors.verticalCenter: parent.verticalCenter
            x: .3 * parent.width
        }

        Image {
            id: edit_icon
            source: "../iconography/icon_40_checkmark.svg"
            sourceSize.width: width
            sourceSize.height: height
            height: parent.height * .8
            width: height
            smooth: true
            anchors.verticalCenter: parent.verticalCenter
            x: .05 * parent.width
        }

        ColorOverlay {
            anchors.fill: edit_icon
            source: edit_icon
            color: Style.primary_dark
        }
    }

    MouseArea
    {
        anchors.fill:parent
        id: continueMouseArea
        enabled: enableButton
        pressAndHoldInterval: 225
        onPressAndHold:
        {
            continueButton.color = Style.affirmative_transluscent
            continueButtonBox.delay(50)
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
            continueButtonBox.clicked()
            continueButton.color = Style.affirmative
            timer.stop()
        }
    }
}
