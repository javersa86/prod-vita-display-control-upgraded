import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtGraphicalEffects 1.12
import "../Styles"

Rectangle
{
    id: root
    width: 290; height: 158
    property bool separated

    color: Style.transparent

    property int setting_id

    signal clicked();

    PneumaticButton
    {
        id: pneumaticButton
        visible: !separated

        setting_id: humidity_1.id
        unit: humidity_1.unit
        title: humidity_1.title
        measuredValueText: state_manager.hum1
        setValueText: state_manager.hum1
        min: humidity_1.min
        max: humidity_1.max
        onClicked:
        {
            parent.clicked()
        }
    }

    Rectangle
    {
        anchors.fill:parent
        visible: separated
        color: mouseArea.pressed ? Style.primary_light_selected : Style.transparent
        border.color: Style.primary_light
        border.width: 4
        radius: 8

        Rectangle
        {
            id: jet1Val
            width: .3 * parent.width
            height: .5 * parent.height
            y: 15
            x: .15 * parent.width

            color: Style.unclickable_border
            radius: 10
            Text {
                y: 10
                text: state_manager.hum1
                font: Style.statisticFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Jet"
                font: Style.titleFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom:parent.bottom
                bottomPadding: 5
            }
        }

        Rectangle
        {
            id: jetAuxVal
            width: .3 * parent.width
            height: .5 * parent.height
            y: 15
            x: .55 * parent.width

            color: Style.unclickable_border
            radius: 10
            Text {
                y:10
                text: state_manager.humaux
                font: Style.statisticFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "Aux"
                font: Style.titleFont
                color: Style.primary_light
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom:parent.bottom
                bottomPadding: 5
            }
        }

        Rectangle{
            id: measuredUnitTitleBox
            height: 150
            width: 194
            anchors.horizontalCenter: parent.horizontalCenter
            color: Style.transparent

            Text{
                id: title
                font: Style.titleFont
                y: 99
                text: humidity_1.title
                anchors.horizontalCenter: parent.horizontalCenter
                color: Style.primary_light
            }

            Text{
                id: unit
                font: Style.unitFont
                text: humidity_1.unit
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: title.bottom
                topPadding: 5
                color: Style.unit
            }
        }
        MouseArea
        {
            anchors.fill: parent
            id: mouseArea
            onClicked:
            {
                root.clicked()
            }
        }
    }
}
