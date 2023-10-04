/*
  Joseph Aversa update: HelpIcon added.
*/
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12
import QtQml 2.12
import IDs 1.0
import "../../Styles"
import "../../CustomObjects"
import "../../Pages"

Rectangle{
    id: root_window
    color:Style.transparent
    property int topY
    property StackView popupStack

    Rectangle
    {
        id: mainContainer
        width: .9 * parent.width
        height:.8 * parent.height
        y: .1 * parent.height
        color: Style.transparent

        PneumaticButton
        {
            id: dp_button
            objectName: "dp_button"
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 12 + 190
            setting_id: etco2_driving_pressure.id
            unit: etco2_driving_pressure.unit
            title: "Driving Pressure"
            measuredValueText: state_manager.etco2DP
            setValueText: state_manager.etco2DP
            min: etco2_driving_pressure.min
            max: etco2_driving_pressure.max

            onClicked:
            {
                var tmpValue = state_manager.etco2DP > etco2_driving_pressure.max ? etco2_driving_pressure.max :
                               state_manager.etco2DP < etco2_driving_pressure.min ? etco2_driving_pressure.min :
                                                                                    state_manager.etco2DP

                buttonContainer.pushSettingPage(
                            "Settings/ETCO2Dial.qml",
                            {
                                "value": tmpValue,
                                "settingTitle": "ETCO<sub>2</sub> Driving Pressure (" + etco2_driving_pressure.unit + ")",
                                "settingId": etco2_driving_pressure.id,
                                "min": etco2_driving_pressure.min,
                                "max": etco2_driving_pressure.max,
                                "unit": etco2_driving_pressure.unit,
                                "setValue": state_manager.etco2DP,
                                "step": etco2_driving_pressure.step,
                                "helpText": etco2_driving_pressure.help,
                                "topY": topY,
                                "popupStack": popupStack
                            });
            }
        }

        PneumaticButton
        {
            id: it_button
            objectName: "it_button"
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 12
            setting_id: etco2_inpiratory_time.id
            unit: etco2_inpiratory_time.unit
            title: "Inspiratory Time"
            measuredValueText: state_manager.etco2IT
            setValueText: state_manager.etco2IT
            min: etco2_inpiratory_time.min
            max: etco2_inpiratory_time.max

            onClicked:
            {
                var tmpValue = state_manager.etco2IT > etco2_inpiratory_time.max ? etco2_inpiratory_time.max :
                               state_manager.etco2IT < etco2_inpiratory_time.min ? etco2_inpiratory_time.min :
                                                                                    state_manager.etco2IT

                buttonContainer.pushSettingPage(
                            "Settings/ETCO2Dial.qml",
                            {
                                "value": tmpValue,
                                "settingTitle": "ETCO<sub>2</sub> Inspiratory Time (" + etco2_inpiratory_time.unit + ")",
                                "settingId": etco2_inpiratory_time.id,
                                "min": etco2_inpiratory_time.min,
                                "max": etco2_inpiratory_time.max,
                                "unit": etco2_inpiratory_time.unit,
                                "setValue": state_manager.etco2IT,
                                "step": etco2_inpiratory_time.step,
                                "helpText": etco2_inpiratory_time.help,
                                "topY": topY,
                                "popupStack": popupStack
                            });
            }
        }

        PneumaticButton
        {
            id: freq_button
            objectName: "freq_button"
            anchors.top: dp_button.bottom
            anchors.topMargin: 24 + 118
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 12 + 190
            setting_id: etco2_rate.id
            unit: etco2_rate.unit
            title: "Rate"
            measuredValueText: state_manager.etco2Rate
            setValueText: state_manager.etco2Rate
            min: etco2_rate.min
            max: etco2_rate.max

            onClicked:
            {
                var tmpValue = state_manager.etco2Rate > etco2_rate.max ? etco2_rate.max :
                               state_manager.etco2Rate < etco2_rate.min ? etco2_rate.min :
                                                                                    state_manager.etco2Rate

                buttonContainer.pushSettingPage(
                            "Settings/ETCO2Dial.qml",
                            {
                                "value": tmpValue,
                                "settingTitle": "ETCO<sub>2</sub> Rate (" + etco2_rate.unit + ")",
                                "settingId": etco2_rate.id,
                                "min": etco2_rate.min,
                                "max": etco2_rate.max,
                                "unit": etco2_rate.unit,
                                "setValue": state_manager.etco2Rate,
                                "step": etco2_rate.step,
                                "helpText": etco2_rate.help,
                                "topY": topY,
                                "popupStack": popupStack
                            });
            }
        }

        PneumaticButton
        {
            id: breaths_button
            objectName: "breaths_button"
            anchors.top: it_button.bottom
            anchors.topMargin: 24 + 118
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 12
            setting_id: etco2_num_breaths.id
            unit: etco2_num_breaths.unit
            title: "Number of Breaths"
            measuredValueText: state_manager.etco2NumBreaths
            setValueText: state_manager.etco2NumBreaths
            min: etco2_num_breaths.min
            max: etco2_num_breaths.max

            onClicked:
            {
                var tmpValue = state_manager.etco2NumBreaths > etco2_num_breaths.max ? etco2_num_breaths.max :
                               state_manager.etco2NumBreaths < etco2_num_breaths.min ? etco2_num_breaths.min :
                                                                                    state_manager.etco2NumBreaths

                buttonContainer.pushSettingPage(
                            "Settings/ETCO2Dial.qml",
                            {
                                "value": tmpValue,
                                "settingTitle": "ETCO<sub>2</sub> Number of Breaths",
                                "settingId": etco2_num_breaths.id,
                                "min": etco2_num_breaths.min,
                                "max": etco2_num_breaths.max,
                                "unit": etco2_num_breaths.unit,
                                "setValue": state_manager.etco2NumBreaths,
                                "step": etco2_num_breaths.step,
                                "helpText": etco2_num_breaths.help,
                                "topY": topY,
                                "popupStack": popupStack
                            });
            }
        }
    }
}
