import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    color:Style.transparent
    property StackView stack

    Component.onCompleted:
    {
        stack.setHum1(state_manager.hum1)
        stack.setHumAux(state_manager.hum1)
    }

    Rectangle
    {
        id: dialBox
        width: parent.width * .8
        height: dial.height
        color:Style.transparent
        x: parent.width * .17
        y: .15 * parent.height

        Text {
            id: jetStr
            text: qsTr("Jet and Aux")
            color: Style.mode_label
            font: Style.titleFont
            x: dial.x + (dial.height * 1.1 - width) * .5
            anchors.bottom: dial.top
            bottomPadding: 15
        }


        SelectableDial
        {
            id: dial
            min: humidity_1.min
            max: humidity_1.max
            height: 400
            value: state_manager.hum1
            anchors.horizontalCenter: parent.horizontalCenter
            selected: true
            step: humidity_1.step
            minOn: humidity_1.minimumOn

            onValueChanged:
            {
                stack.setHum1(value)
                stack.setHumAux(value)
            }

            onSettingConfirmed:
            {
                stack.confirmSettings()
            }
        }
    }
}
