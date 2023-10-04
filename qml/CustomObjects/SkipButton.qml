import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import "../Styles"
Rectangle
{
    id: skipButtonBox

    color:Style.transparent
    height: 50
    width: 200

    signal clicked();
    property bool enabled

    Rectangle
    {
        id: skipButton
        color:Style.transparent
        anchors.fill: parent
        anchors.centerIn: skipButtonBox
        radius: 24
        border.width:2
        border.color: Style.affirmative
        opacity: skipButtonBox.enabled ? 1 : .5

        Text {
            text: qsTr("Skip Verification")
            color:Style.affirmative
            font:Style.cancel_font
            anchors.centerIn: parent
        }


    }

    MouseArea
    {
        height: 1.1 * parent.height
        width: 1.1 * parent.width
        id: skipMouseArea
        enabled: skipButtonBox.enabled

        onClicked:
        {
            skipButtonBox.clicked();
        }
    }
}
