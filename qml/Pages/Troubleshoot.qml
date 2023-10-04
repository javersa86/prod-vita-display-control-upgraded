import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"


Rectangle
{
    id: root
    color:Style.primary_dark_transluscent
    property color warningColor
    property string warningTitle
    property string troubleshootString
    property variant steps
    property int numSteps: 100
    property StackView stack
    property ListModel model: ListModel{}

    Component.onCompleted:
    {
        for(var i = 0; i < root.numSteps; i++)
        {
            root.model.append({"step": root.steps[i]})
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Rectangle
    {
        id:mainContainer
        width: .7 * parent.width
        height: .7 * parent.height
        color: Style.primary_dark
        border.width: 2
        border.color: warningColor
        radius: width / 100
        anchors.horizontalCenter: parent.horizontalCenter
        y: .33 * parent.height - .33 * height

        Rectangle
        {
            id: borderContainer
            width: .9 * parent.width
            height: .8 * parent.height
            anchors.centerIn: parent
            color: Style.transparent

            Text {
                id: warningTitleText
                textFormat: Text.RichText
                text: warningTitle
                color: warningColor
                opacity: .6
                font: Style.warningDescFont
            }

            Text {
                id: troubleshootTitle
                text: troubleshootString
                color:Style.primary_light
                anchors.top: warningTitleText.bottom
                topPadding: 10
                font: Style.numericUiDisplayFont
            }

            ListView
            {
                y: troubleshootTitle.y + troubleshootTitle.height + 10
                width: parent.width
                height: 500
                model: root.model

                boundsBehavior: Flickable.StopAtBounds
                snapMode: ListView.SnapOneItem

                clip: true

                delegate:
                    Text {
                        textFormat: Text.RichText
                        text: index + 1 + ". " + step
                        width: parent.width
                        color: Style.primary_light
                        opacity: .7
                        font: Style.numberButtonFont
                        lineHeight: 1.5
                        wrapMode: Text.Wrap
                    }
            }

            Rectangle
            {
                id: closeButton
                width: 137
                height: 48
                radius: 24
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color:Style.primary_light_selected
                border.color:Style.primary_light
                border.width: 2

                Text {
                    id: closeText
                    text: qsTr("CLOSE")
                    anchors.right: parent.right
                    rightPadding: .2 * parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    color: Style.primary_light
                    font: Style.buttonFont
                }

                Rectangle
                {
                    id: closeIconBackground
                    width: 24
                    height: width
                    color: Style.primary_light
                    radius: .5 * width
                    x: 15
                    anchors.verticalCenter: parent.verticalCenter
                }

                Image {
                    id: keypad_icon
                    source: "../iconography/icon_40_close.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    x: 15
                    anchors.verticalCenter: parent.verticalCenter
                    width: closeIconBackground.width
                    height: closeIconBackground.height
                    smooth: true
                }

                ColorOverlay {
                    anchors.fill: keypad_icon
                    source: keypad_icon
                    color: Style.primary_dark
                }

                MouseArea
                {
                    pressAndHoldInterval: 225
                    onPressAndHold: {
                        closeButton.color = Style.primary_light_disabled
                        closeButton.delay(50)
                    }
                    anchors.fill: parent
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
                        root.stack.helpBoxState = 0;
                        root.stack.clear();
                        closeButton.color = Style.primary_light_selected
                        timer.stop()
                    }
                }

            }
        }
    }
}
