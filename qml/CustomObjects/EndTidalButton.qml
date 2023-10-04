import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import "../Styles"
import "../CustomObjects"

Button {
    id: root
    width: 110
    height: 42

    opacity: enabled ? 1 : .3
    enabled: state_manager.etco2_button_state && !mmChecked

    signal clicked()

    property int modeID: 6
    property bool modeEnabled: state_manager.etco2_mode
    property bool mmChecked

    property color backgroundColorState: Style.primary_dark

    background: Rectangle {
        id: root_area

        width: parent.width
        height: parent.height
        color: backgroundColorState
        border.color: Style.primary_light
        border.width: 2
        radius: 20

        Text {
            id: title
            color: Style.primary_light
            text: "Start"
            font: Style.titleFont
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea
        {
            id:etco2MouseArea
            anchors.fill:parent
            pressAndHoldInterval: 225

            onPressAndHold:
            {
                root.backgroundColorState = root.modeEnabled ? Style.mode_active_warning_selected : Style.primary_light_selected
                root_area.delay(100)
            }
        }

        function delay(delayTime)
        {
            timer.interval = delayTime;
            timer.start();
        }

        Timer {
            id: timer
            repeat: false
            onTriggered:
            {
                root.clicked()
                timer.stop()
            }
        }
    }

    onModeEnabledChanged:
    {
        if(!modeEnabled)
        {
            root_area.color = Style.primary_dark
            root_area.border.color = Style.primary_light
            title.color = Style.primary_light
            title.text = "Start"
        }
        else
        {
            root_area.color = Style.mode_active_warning
            root_area.border.color = Style.mode_active_warning
            title.color = Style.primary_dark
            title.text = "Stop"
        }
    }
}
