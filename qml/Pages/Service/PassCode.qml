/**
  Page created to enter service passcode before changing it.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    color:Style.primary_dark
    property string code
    property string nextPage
    property int isService
    property StackView stack
    property StackView nextStack
    property var parameters
    signal passCodeCorrect();

    Connections{
        target:passcode_manager
    }

    Rectangle
    {
        id: mainContainer
        width: root.width * .95
        height: root.height * .95
        color:Style.transparent

        IncorrectPassCode
        {
            id: incorrectText
            text: "INCORRECT PASSCODE"
            width: keyboard.width
            anchors.bottom: keyboard.top
            x: keyboard.x
            keyboardX: keyboard.x
        }

        Text
        {
            id: passcodeText
            x: .06 * mainContainer.width
            y:.1 * mainContainer.height
            text: "ENTER PASSCODE"
            font: Style.numericUiDisplayFont
            color: Style.numeric_ui_unit
        }

        PassCodeKeypad
        {
            id:keyboard
            anchors.centerIn: parent
        }

        Rectangle
        {
            id: continueButtonBox
            height: .125 * mainContainer.height
            width: .25 * mainContainer.height
            x: .48* mainContainer.width
            y: .85 * mainContainer.height
            color:Style.transparent

            Rectangle
            {
                id: continueButton
                color:Style.affirmative
                height:.5 * continueButtonBox.height
                width: .9 * continueButtonBox.width
                anchors.centerIn: continueButtonBox
                radius: 24

                Text {
                    text: qsTr("CONTINUE")
                    color:Style.primary_dark
                    font:Style.buttonFont
                    anchors.verticalCenter: parent.verticalCenter
                    x: .3 * parent.width
                }

                Image {
                    id: edit_icon
                    source: "../../iconography/icon_40_checkmark.svg"
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

                onPressed: continueButton.color = Style.affirmative_transluscent
                onReleased: continueButton.color = Style.affirmative

                onClicked:
                {
                    if(root.code == keyboard.value)
                    {
                        root.passCodeCorrect()
                    }
                    else
                    {
                        keyboard.reset();
                        incorrectText.visible = true
                        incorrectText.startTime()
                    }
                }
            }
        }

        CancelButton
        {
            height: .125 * mainContainer.ehgith
            width: .18 * mainContainer.height
            x: .35 * mainContainer.width
            anchors.verticalCenter:  continueButtonBox.verticalCenter
            onClicked:
            {
                root.stack.clear();
            }
        }
    }
}
