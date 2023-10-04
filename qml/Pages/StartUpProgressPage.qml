import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Styles"
import "../CustomObjects"


Rectangle
{
    id: background
    color: Style.primary_dark
    property StackView homeStack

    Component.onCompleted:
    {
        startupCheck.start();
    }

    Connections
    {
        target: state_manager;
        onStartupComplete:
        {
            homeStack.startupComplete()
        }
    }

    Timer
    {
        id: startupCheck
        repeat: true
        interval: 30
        onTriggered:
        {
            backend.checkStartupComplete();
        }
    }

    ProgressDisplay
    {
        id: spinner
        imageSource: "../iconography/lantern-logo.svg"
        anchors.centerIn: parent
    }
}
