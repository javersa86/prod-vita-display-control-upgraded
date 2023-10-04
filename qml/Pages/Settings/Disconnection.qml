/*
  Joseph Aversa update: HelpIcon added.
*/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle{
    id: root_window
    color: Style.transparent
    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.8 * parent.height
        y: .1 * parent.height
        color:Style.transparent

        ModeSwitch {
            id: lm_switch
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * .15 + height
            checkedText: "On"
            uncheckedText: "Off"
            modeID: 5
            checked:state_manager.pip_monitoring_mode
            onCheckedChanged:
            {
                var enable = 0;
                if (lm_switch.checked)
                {
                    enable = 1;
                }

                backend.setMode(modeID, enable)
            }
        }

        Text {
            id: description
            text: qsTr("When PIP disconnection is \"ON\" the user will be alerted after 30 seconds of the absence of pressure detection on the PIP monitoring line.")
            wrapMode: Text.WordWrap
            width: 198.078125 * 1.9
            font: Style.unitFont
            color: Style.general_set_display
            anchors.top: lm_switch.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: title.height
        }
    }

    Item {
        id: valueHolder
        property string helpText: "If PIP Disconnection is “ON” the user will be notified if no pressure is detected on the PIP pressure line for 15 seconds."
    }
}
