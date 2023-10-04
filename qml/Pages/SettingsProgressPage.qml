import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import SensorID 1.0
import "../Styles"
import "../CustomObjects"
import IDs 1.0

Rectangle{
    id: background
    color: Style.primary_dark

    property StackView popupStack
    property var settings

    Component.onCompleted:
    {
        backend.setPneumaticSettings(background.settings)
        progressTimer.start();
    }

    Connections
    {
        target: state_manager;

        onSettingsComplete:
        {
            popupStack.clear();
        }
    }

    Timer
    {
        id: progressTimer
        repeat: true
        interval: 30
    }

    PresetProgressDisplay
    {
        id: spinner
        anchors.centerIn: parent
    }
}
