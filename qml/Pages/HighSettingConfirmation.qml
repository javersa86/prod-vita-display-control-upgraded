import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../Styles"
import "../CustomObjects"

Rectangle{
    id: background
    color: Style.primary_dark_transluscent
    objectName: "DehumidificationDisconnection"

    property Item settingPage
    property int value
    property int settingId
    property string settingTitle

    signal disconnected()

    Component.onCompleted:
    {
        slidingBox.state = "moveIn"
    }

    SlidingBox
    {
        id: slidingBox
        height: background.height / 2.5
        width: background.width / 2
        startX: background.width / 2 - width / 2
        desiredX: startX
        startY: - height
        desiredY: background.height / 3 - height / 2

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

        property int leftPadding: 30
        property int topPadding: 30

        Text
        {
            id: title
            text: "HIGH SETTING"
            font: Style.buttonFont
            color: Style.general_set_display
            x: slidingBox.leftPadding
            y: slidingBox.topPadding
        }

        Text
        {
            id: bigText
            text: "Set " + settingTitle + " to " + value + "?"
            font: Style.numericUiDisplayFont
            color: Style.primary_light
            width: slidingBox.width - leftPadding * 2
            x: slidingBox.leftPadding
            y: slidingBox.topPadding + title.height
            wrapMode: Text.WordWrap
        }

        Text
        {
            id: explanation
            text: settingTitle + " will be set to " + value + ". Are you sure you want to set this setting so high?"
            font: Style.buttonFont
            color: Style.primary_light_disabled
            width: slidingBox.width - slidingBox.leftPadding * 2
            x: slidingBox.leftPadding
            y: slidingBox.topPadding + title.height + bigText.height + .05 * slidingBox.height
            wrapMode: Text.Wrap
        }

        Rectangle
        {
            id: no_button

            height: slidingBox.height * .16
            width: slidingBox.width * .16
            color: Style.primary_light_selected
            border.color: Style.primary_light
            border.width: 2
            radius: 24

            signal clicked()

            x: slidingBox.leftPadding
            y: (slidingBox.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2


            onClicked:
            {
                settingPage.cancelSetting()
            }

            Text
            {
                id: noStr
                text: qsTr("NO")
                color: Style.primary_light
                anchors.verticalCenter: no_button.verticalCenter
                anchors.horizontalCenter: no_button.horizontalCenter
                leftPadding: .3 * no_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                onClicked: {
                    no_button.clicked()
                }
                anchors.fill: no_button
            }

            Rectangle
            {
                id: closeIconBackground
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                radius: .5 * height
                color: Style.primary_light

            }

            Item {
                id: closeIcon
                height: no_button.height / 2
                width: height
                x: .4 * height
                anchors.verticalCenter: no_button.verticalCenter
                Image {
                    id: xicon
                    source: "../iconography/icon_40_close.svg"
                    sourceSize.width: width
                    sourceSize.height: height
                    width: parent.width
                    height: parent.height
                    smooth: true
                    visible: true
                }
                ColorOverlay {
                    anchors.fill: xicon
                    source: xicon
                    color: Style.primary_light_selected
                }
            }

        }

        Rectangle
        {
            id: yes_button

            height: slidingBox.height * .16
            width: slidingBox.width * .16
            color: Style.affirmative
            border.width: 2
            radius: 24

            signal clicked()

            x: slidingBox.width - width - slidingBox.leftPadding
            y: (slidingBox.height - (explanation.y + explanation.height)) / 2 + explanation.y + explanation.height - height / 2

            onClicked:
            {
                settingPage.confirmSetting(background.settingId, background.value)
            }

            Text
            {
                id: yesStr
                text: qsTr("YES")
                color: Style.primary_dark
                anchors.verticalCenter: yes_button.verticalCenter
                anchors.horizontalCenter: yes_button.horizontalCenter
                leftPadding: .3 * yes_button.width
                font: Style.buttonFont
            }

            MouseArea
            {
                onClicked: yes_button.clicked()
                anchors.fill:yes_button
            }

            Item {
                id: checkIcon
                height: yes_button.height / 1.5
                width: height
                x: .3 * height
                anchors.verticalCenter: yes_button.verticalCenter
                Image {
                    id: icon
                    source: "../iconography/icon_40_checkmark.svg"
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
                    color: Style.primary_dark
                }
            }

        }
    }
}
