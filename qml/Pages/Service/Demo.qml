/**
  Updates by Joseph Aversa
  Moved switch left aligned.
  Added border and subtitle to section.
  */
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.primary_dark

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .8 * parent.height
        y: .1 * parent.height
        color: Style.transparent

        ModeSwitch
        {
            id: demoModeSwitch
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * .15 + height
            modeID: 4
            checked:state_manager.demo_mode
            uncheckedText: qsTr("Normal")
            checkedText: qsTr("Demo")
        }
    }
}
