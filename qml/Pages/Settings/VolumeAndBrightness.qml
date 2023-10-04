import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"

InteractiveKnobPage{
    id: root_window
    color:Style.transparent
    property int topY
    property StackView popupStack

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.9 * parent.height
        y: .1 * parent.height
        color: Style.transparent

        Text {
            id: title
            text: "Brightness"
            textFormat: Text.RichText
            color:Style.mode_label
            font: Style.settingPageTitle
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SettingOptionsButton
        {
            id: brightnessButton
            title: "Brightness"
            y: topY - mainContainer.y
            x: 20
            Component.onCompleted:
            {
                selected = true
                volumeButton.selected = false
            }

            onClicked: {
                if(!selected)
                {
                    selected = true
                    volumeButton.selected = false
                    adjustmentStack.replace("Brightness.qml")
                    title.text = "Brightness"
                }
            }
        }

        SettingOptionsButton
        {
            id: volumeButton
            title: "Volume"
            y: brightnessButton.y + brightnessButton.height + .45 * height
            x: 20

            onClicked:
            {
                if(!selected)
                {
                    selected = true
                    brightnessButton.selected = false
                    adjustmentStack.replace("Volume.qml")
                    title.text = "Volume"
                }
            }
        }

        StackView
        {
            id: adjustmentStack
            width: parent.width
            height: parent.height
            y: title.height + title.y + 25
            Component.onCompleted:
            {
                replace("Brightness.qml")
            }

            pushEnter: Transition {
                enabled: false
            }
            pushExit: Transition {
                enabled: false
            }
            popEnter: Transition {
                enabled: false
            }
            popExit: Transition {
                enabled: false
            }
            replaceEnter: Transition {
                enabled: false
            }
            replaceExit: Transition {
                enabled: false
            }
        }
    }
}
