import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Styles"
import "../CustomObjects"


Rectangle
{
    id: background
    color: Style.primary_dark

    ProgressDisplay
    {
        id: spinner
        imageSource: "../iconography/lantern-logo.svg"
        anchors.centerIn: parent
    }
}
