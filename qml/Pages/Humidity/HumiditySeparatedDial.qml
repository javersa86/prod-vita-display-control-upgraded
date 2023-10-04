import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../../Styles"
import "../../CustomObjects"

Rectangle
{
    id: root
    property StackView stack
    color:Style.transparent

    property int firstPage: 1

    Component.onCompleted:
    {
        hum_jet1.selected = true
        hum_aux.selected = false

        stack.setHum1(state_manager.hum1)
        if (firstPage)
        {
            stack.setHumAux(state_manager.humaux)
        }
        else
        {
            stack.setHumAux(0)
        }
    }

    Rectangle
    {
        id: dialBox
        width: parent.width * .8
        height: hum_jet1.height
        color:Style.transparent
        anchors.horizontalCenter: parent.horizontalCenter
        y: .2 * parent.height

        Text {
            id: jetStr
            text: qsTr("Jet")
            color: Style.mode_label
            font: Style.titleFont
            x: hum_jet1.x + 165 - .5 * width
            anchors.bottom: hum_jet1.top
            bottomPadding: 15
        }


        SelectableDial
        {
            id: hum_jet1
            min: humidity_1.min
            max: humidity_1.max
            value: stack.hum_1
            minOn: humidity_1.minimumOn
            step: humidity_1.step

            onValueChanged:
            {
                stack.setHum1(value)
            }

            onSettingConfirmed:
            {
                hum_jet1.selected = false;
                hum_aux.selected = true;
            }

            onClicked:
            {
                hum_jet1.selected = true;
                hum_aux.selected = false;
            }
        }

        Text {
            id: auxStr
            text: qsTr("Auxiliary")
            color: Style.mode_label
            font: Style.titleFont
            x: hum_aux.x + 165 - .5 * width
            anchors.bottom: hum_aux.top
            bottomPadding: 15
        }

        SelectableDial
        {
            id: hum_aux
            min: humidity_aux.min
            max: humidity_aux.max
            value: stack.hum_aux
            anchors.right: parent.right
            minOn: humidity_aux.minimumOn
            step: humidity_aux.step

            onValueChanged:
            {
                stack.setHumAux(value)
            }

            onSettingConfirmed:
            {
                if (!hum_jet1.selected && hum_aux.selected)
                {
                    stack.confirmSettings()
                }
            }

            onClicked:
            {
                hum_jet1.selected = false;
                hum_aux.selected = true;
            }
        }
    }
}
