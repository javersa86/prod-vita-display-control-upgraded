import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"
Rectangle{
    id: root_window
    color:Style.transparent
    property int topY
    property StackView popupStack

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .75 * parent.height
        x: 100
        y: .17 * parent.height
        color: Style.transparent

        CalibrationOptionsButton
        {
            id: sp
            title: "Stacking Pressure"
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 32
            anchors.bottom: pip.top
            anchors.bottomMargin: 32
            serviceState: true

            onClicked:
            {
                popupStack.push("CalibrationSP.qml", {"popupStack": popupStack})
            }
        }

        CalibrationOptionsButton
        {
            id: pip
            title: "Peak Insp. Pressure"
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            serviceState: true

            onClicked:
            {
                popupStack.push("CalibrationPIP.qml", {"popupStack": popupStack})
            }
        }

        CalibrationOptionsButton
        {
            id: regulators
            title: "Pre Regulators"
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 32
            anchors.top: pip.bottom
            anchors.topMargin: 32
            serviceState: true

            onClicked:
            {
                //popupStack.push("CalibrationPreRegulators.qml", {"popupStack": popupStack})
            }
        }

        CalibrationOptionsButton
        {
            id: inletAir
            title: "Inlet Air"
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 32
            anchors.bottom: inletO2.top
            anchors.bottomMargin: 32
            serviceState: true

            onClicked:
            {
                popupStack.push("CalibrationInletAir.qml", {"popupStack": popupStack})
            }
        }

        CalibrationOptionsButton
        {
            id: inletO2
            title: "Inlet O<sub>2</sub>"
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            serviceState: true

            onClicked:
            {
                //popupStack.push("CalibrationInletO2.qml", {"popupStack": popupStack});
            }
        }

        CalibrationOptionsButton
        {
            id: dp
            title: "Driving Pressure"
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 32
            anchors.top: inletO2.bottom
            anchors.topMargin: 32
            serviceState: true

            onClicked:
            {
                //popupStack.push("CalibrationDrivingPressure.qml", {"popupStack": popupStack});
            }
        }
    }//end of main container
}
