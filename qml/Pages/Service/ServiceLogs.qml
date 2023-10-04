/*
  Page allows the technician to export logs onto a USB stick, or erase log files.
  Pressing Export Logs to Drive button, ExportLogs.qml pops up with data stored in push parameters.
  Pressing Erase Stored Logs button, EraseLogs.qml pops up with data stored in push parameters.

  Updates:

  Remove erase button.
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
    color:Style.transparent
    property StackView popupStack
    property int visibleState: 0
    property int topY

    Connections {
        target: backend

        onDriveConnection:
        {
            if (connectionState === 0)
            {
                retryButton.visible = true
            }
            else if (connectionState === 1)
            {
                connectionButton.opacity = 1
                connectionButton.enableButton = true
                retryButton.visible = false
            }
        }

        onSaveLogStatusSignal:
        {
            if (exportStatus){
                progressText.text = "Export Complete"
                progressText.color = Style.affirmative
                backend.driveDisconnected();
            }
            else{
                progressText.text = "Loading Failed"
                progressText.color = Style.cancel
                retryButton.visible = true
            }
        }

        onDriveDisconnection:
        {
            if (disconnectionState)
            {
                retryButton.visible = true
                visibleState = 0
                progressText.text = "Loading..."
                progressText.color = Style.primary_light
                reminderText.visible = true
            }
        }
    }

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height: .75 * parent.height
        x: 100
        y: .17 * parent.height
        color: Style.transparent

        Rectangle
        {
            id: connectionBox
            color: Style.transparent
            width: .5 * parent.width
            height: .2 * parent.height
            anchors.top: parent.top
            anchors.left: parent.left

            Text {
                id: connectionTitle
                text: qsTr("Export logs to external drive.");
                font: Style.settingPageTitle
                color: Style.primary_light
                anchors.top: parent.top
                anchors.left: parent.left
            }

            Text {
                id: infoText
                text: "A FAT or EXT formatted USB drive must be inserted in the back of ventilator."
                font: Style.buttonFont
                color: Style.primary_light
                anchors.top: connectionTitle.bottom
                anchors.topMargin: 16
                anchors.left: parent.left
            }

            ContinueButton
            {
                id: connectionButton
                continueText: "Export"
                anchors.top: infoText.bottom
                anchors.topMargin: 16
                anchors.left: parent.left
                opacity: .5
                enableButton: false

                Component.onCompleted: backend.driveConnected()

                onClicked:
                {
                    progressText.text = "Loading..."
                    progressText.color = Style.primary_light
                    connectionButton.opacity = .5
                    connectionButton.enableButton = false
                    backend.updateFileCount()
                    visibleState = 1
                    backend.saveLogsToDrive()
                }
            }

            CancelButton
            {
                id: cancelButton
                anchors.left: connectionButton.right
                anchors.verticalCenter: connectionButton.verticalCenter

                onClicked:
                {
                    backend.stopProgress()
                }
            }

            SettingOptionsButton
            {
                id: retryButton
                title: "Retry Connection"
                anchors.left: cancelButton.right
                anchors.leftMargin: 16
                anchors.verticalCenter: cancelButton.verticalCenter
                visible: false
                serviceState: true

                onClicked:
                {
                    reminderText.visible = false
                    backend.driveConnected()
                }
            }

            Item {
                id: loadingBar
                width: parent.width * 0.8
                height: 8
                anchors.top: connectionButton.bottom
                anchors.topMargin: 40
                anchors.left: parent.left
                visible: visibleState

                property int value: state_manager.save_data_progress
                property int maxValue: state_manager.file_count

                Rectangle
                {
                    id: bar
                    width: loadingBar.width * (loadingBar.value / loadingBar.maxValue)
                    height: loadingBar.height
                    color: Style.primary_light
                }

                onValueChanged:
                {
                    bar.width = loadingBar.width * (value / maxValue)
                }
            }

            Text {
                id: progressText
                color: Style.primary_light
                font: Style.titleFont
                text: "Loading..."
                anchors.top: loadingBar.bottom
                anchors.topMargin: 16
                anchors.left: parent.left
                visible: visibleState
            }

            Text {
                id: reminderText
                color: Style.primary_light
                font: Style.titleFont
                text: "Files are exported and the mounted drive is ejected. Please mount new drive or previous drive to restart process."
                anchors.top: connectionButton.bottom
                anchors.topMargin: 40
                anchors.left: parent.left
                visible: false
            }
        }
    }//end of main container

}
