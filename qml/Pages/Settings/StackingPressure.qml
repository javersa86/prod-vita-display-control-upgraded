import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.transparent
    property StackView popupStack

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.8 * parent.height
        y: .1 * parent.height
        color:Style.transparent

        LineButton {
            id: lineButton
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * .15 + height

        }

        Text {
            id: description
            text: qsTr("Hide SP Lines on Graph.")
            font: Style.unitFont
            color: Style.general_set_display
            anchors.top: lineButton.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: title.height
        }
    }

    Item {
        id: valueHolder
        property string helpText: "The NVENT VITA allows the user to hide the blue measured line and the blue dash line for Stacking Pressure."
    }
}
