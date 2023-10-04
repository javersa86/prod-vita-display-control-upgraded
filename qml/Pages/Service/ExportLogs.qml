/*
  Asks technician asks question of downloading all logs to external drive and to make sure drive is inserted to back of ventilator.
  Pressing continue will pop up ExportLogsConfirmed.qml
  Pressing cancel will clear page.
  */

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import "../../Styles"
import "../../CustomObjects"


Rectangle
{
    height: 800
    width: 1280
    color: Style.primary_dark_transluscent
    property StackView popupStack
    property int visibleState: 0

    Connections{
        target:backend
        onSaveLogStatusSignal:
        {
            if (exportStatus){
                question.text = "Export complete. Press continue, then eject USB Drive before removing it."
                doneButton.visible = 1
            }
            else{
                question.text = "Failed to export files."
                cancelButton.visible = 1
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        confirmBox.state = "moveIn"
    }

    SlidingBox
    {
        id: confirmBox

        color: Style.primary_dark
        border.color: Style.general_set_display
        radius: 4
        border.width: 2

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
                text: "Export Service Logs"
                font: Style.buttonFont
                color: Style.general_set_display
            }

            Text
            {
                id: question
                font: Style.numericUiDisplayFont
                color: Style.primary_light
                width: parent.width
                y: title.height + 15
                wrapMode: Text.WordWrap
                text: "Download all service logs to external drive?"
            }

            ProgressBar {
                id: loadingBar
                from: 0
                to: state_manager.file_count
                value: state_manager.save_data_progress
                anchors.top: question.bottom
                anchors.topMargin: 40
                anchors.left: question.left
                visible: visibleState

            }

            Text {
                id: progressText
                color: Style.primary_light
                font: Style.titleFont
                text: state_manager.save_data_progress + "/" + state_manager.file_count
                anchors.top: question.bottom
                anchors.topMargin: 32
                anchors.left: loadingBar.right
                anchors.leftMargin: 24
                anchors.verticalCenter: loadingBar.verticalCenter
                visible: visibleState
            }

            ContinueButton
            {
                id: continueButton
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                onClicked:
                {
                    question.text = "Download in progress."
                    continueButton.visible = 0
                    cancelButton.visible = 0
                    backend.updateFileCount()
                    visibleState = 1
                    backend.saveLogsToDrive()
                }
            }

            ContinueButton
            {
                id: doneButton
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                visible: false
                onClicked:
                {
                    popupStack.clear()
                }
            }

            CancelButton
            {
                id: cancelButton
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                onClicked:
                {
                    popupStack.clear()
                }
            }


        }
    }
}
