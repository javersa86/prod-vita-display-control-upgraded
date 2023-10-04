import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"

Rectangle {
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent

    property StackView popupStack

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
        backend.saveDataToSD();
    }

    Rectangle
    {
        id: confirmBox
        height: 320
        width: 640
        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2
        x: width / 2
        y: 100

        Rectangle
        {
            id: mainContainer
            width : .9 * parent.width
            height : .85 * parent.height
            anchors.centerIn: parent
            color:Style.transparent
            Text
            {
                id: title
                text: "Export Save Data"
                font: Style.buttonFont
                color: Style.general_set_display
            }

            Text {
                id: bigText
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: parent.width
                y: title.height + 15
                wrapMode: Text.WordWrap
                text: "All data is being transferred to storage..."
            }

            ProgressBar {
                id: loadingBar
                from: 0
                to: state_manager.file_count
                value: state_manager.save_data_progress
                anchors.top: bigText.bottom
                anchors.topMargin: 40
                anchors.left: bigText.left
            }

            Text {
                id: progressText
                color: Style.primary_light
                font: Style.titleFont
                text: "Preparing Files"
                anchors.top: bigText.bottom
                anchors.topMargin: 32
                anchors.left: loadingBar.right
                anchors.leftMargin: 24
                anchors.verticalCenter: loadingBar.verticalCenter
            }

            CancelButton
            {
                id: cancelButton
                anchors.left: parent.left
                anchors.bottom : parent.bottom

               onClicked:
                {
                   popupStack.clear()
                }
            }
        }
    }
}
