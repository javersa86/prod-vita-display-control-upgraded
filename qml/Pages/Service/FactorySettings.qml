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
            id: factorySettingsModeSwitch
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * .15 + height
            modeID: 1
            uncheckedText: qsTr("Single")
            checkedText: qsTr("Double")
            checked: state_manager.double_jet_mode
            onCheckedChanged:
            {
                var enable = 0;
                if (factorySettingsModeSwitch.checked)
                {
                    enable = 1;
                }

                backend.setMode(modeID, enable)
            }
        }
    }
}
