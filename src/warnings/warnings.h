#pragma once

#include <QString>
#include <QVector>

/**
 * @addtogroup warningsParent
 * @{
 */

/**
 * @file warnings.h
 * @brief Header for warnings.cpp with info.
 */

/**
 * @file warnings.cpp
 * @brief The parent class for warning subclasses, which include patients, systems, and notices.
 */

/**
 * @brief Constant value for warnings that clear autonomously.
 */
#define CLEAR_AUTONOMOUSLY 0

/**
 * @brief Constant value for warnings that clear by button input.
 */
#define CLEAR_ON_DEMAND 1

/**
 * @brief Constant value for warnings that clear by fixing issue.
 */
#define CLEAR_AFTER_RESOLVED 2

/**
 * @brief Beginning index for notices sent for system.
 */
#define BEGIN_NOTICE_INDEX 52

/**
 * @brief Constant value that represent patient warnings.
 */
#define PATIENT_CLASS 0

/**
 * @brief Constant value that represent system warnings.
 */
#define SYSTEM_CLASS 1

/**
 * @brief Constant value that represent notices.
 */
#define NOTICE_CLASS 2


/**
 * @brief The Warning class
 */
class Warning
{
    /**
     * @addtogroup warningsParent
     * @{
     */
    public:
        /**
        * @brief Default constructor
        */
        Warning() = default;
        /**
        * @brief   Parent constructor used for all warnings
        * @details Initializes the following components to a warning:
        *          - The ID of the warning according to the API. Also, the only parameter required to pass in when instantiating any of the specific warning classes below.
        *          - The QVector of QStrings which describe the steps to resolve the warning.
        *          - The title of the warning, displayed in the warning banner.
        *          - The class of the warning: patient, system, notice.
        *          - The description of the warning (obsolete).
        *          - The clearing behavior of the warning: Clear on demand, clear autonomously, clear after trigger resolved.
        *          - The color of the warning banner while the warning is displayed: red, blue, yellow, green.
        *          - The text that appears in the clear button: Clear or Prime.
        *
        * @param warning_id
        * @param troubleshooting_steps
        * @param title
        * @param warning_class
        * @param desc
        * @param clearingBehavior
        * @param color
        * @param clearText
        */
        Warning(
                const int warning_id,
                const QVector<QString> &troubleshooting_steps,
                const QString &title,
                const int warning_class,
                const QString &desc,
                unsigned char clearingBehavior,
                const QString &color,
                const QString &clearText = QStringLiteral("CLEAR")
                );
        /**
        * @brief Gets the id of the warning.
        * @return int
        */
        int id() const;
        /**
        * @brief  Gets title of warning.
        * @return QString
        */
        QString title() const;
        /**
        * @brief Gets class value for warning
        * @return int
        */
        int warningClass() const;
        /**
        * @brief Gets description of warning.
        * @return QString
        */
        QString description() const;
        /**
        * @brief Gets the troubleshooting steps of the warning.
        * @return QVector<QString>
        */
        QVector<QString> troubleshootingSteps() const;
        /**
        * @brief Gets value for clearing behavior.
        * @return unsigned char
        */
        unsigned char clearingBehavior() const;
        /**
        * @brief Gets text of color.
        * @return QString
        */
        QString color() const;
        /**
        * @brief Gets clear text value for warning.
        * @return QString
        */
        QString clearText() const;

    protected:
        /**
        * @brief Sets clear text value for warning.
        * @param text
        */
        void setClearText(const QString &text);

    private:
        int m_id{-1};
        QString m_title;
        int m_warning_class{-1};
        QString m_desc;
        QString m_clear;
        QVector<QString> m_troubleshooting_steps;
        unsigned char m_clearingBehavior;
        QString m_color;
        /** @} */
};
/** @} */

/**
 * @addtogroup warningsParent
 * @{
 */

/**
 * @brief Patient Warnings are the highest priority for they relate to the patient's safety and health.
 */
class PatientWarning: public Warning
{
public:

    /**
    * @brief Constructor for patient warnings and all patient warnings are inherited from this.
    * @note  The default color for all patient colors is red.
    * @param warning_id
    * @param title
    * @param troubleshooting_steps
    * @param clearingBehavior
    * @param color
    */
    PatientWarning(
            int warning_id,
            const QString &title,
            const QVector<QString> &troubleshooting_steps,
            unsigned char clearingBehavior,
            const QString &color = QStringLiteral("#F24C26"));
};

/**
 * @brief Class for Stacking Pressure High Warnings.
 */
class StackingPressureHigh : public PatientWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    StackingPressureHigh(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The Stacking Pressure of the patient may be higher than the set SP threshold, ensure there is egress."),
                                 QStringLiteral("Patient may be gas trapping causing the stacking of breaths and/or an increased baseline."),
                                 QStringLiteral("The Jet Line may be occluded and/or pinched."),
                                 QStringLiteral("Patient may be spontaneously breathing."),
                                 QStringLiteral("The SP sensor may be defective."),
                                 QStringLiteral("Contact support @ 888-730-5463.")
                             }), const QString &title = QStringLiteral("Stacking Pressure High!"));
};
/**
 * @brief Class for PIP High Warnings.
 */
class PIPHigh : public PatientWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    PIPHigh(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The PIP of the patient may be higher than the set PIP threshold, ensure there is egress."),
                                 QStringLiteral("Patient compliance may be low, causing rapid rise of PIP. Adjust settings to allow ventilation to resume within safe parameters."),
                                 QStringLiteral("Patient may be gas trapping causing the stacking of breaths and/or an increased baseline."),
                                 QStringLiteral("The PIP line may be occluded and/or pinched."),
                                 QStringLiteral("Patient may be spontaneously breathing."),
                                 QStringLiteral("The PIP sensor may be defective."),
                                 QStringLiteral("Contact support @ 888-730-5463.")
                             }), const QString &title = QStringLiteral("PIP High!"));
};

/**
 * @brief Class for PIP Disconnection Warnings.
 */
class PIPDisconnected : public PatientWarning
{
public:
    /**
     * @brief Constructor Method.
     */
    PIPDisconnected(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Ensure the PIP line is connected to the patient."),
                                 QStringLiteral("Ensure the PIP line is connected to the NVENT Vita."),
                                 QStringLiteral("The PIP line may see no pressure even when the red line is used depending on the point of reference and how open the system is."),
                                 QStringLiteral("Monitoring of this warning may be disabled through the settings menu PIP Disconnection Page, and the PIP Adjustment Page.")
                             }), const QString &title = QStringLiteral("PIP Disconnected!"));
};
/**
 * @brief Class for No Water in Jet Line Warning.
 */
class NoWaterJet : public PatientWarning
{
public:
    /**
     * @brief Contructor Method.
     * @note  Sets clear text to "PRIME".
     */
    NoWaterJet(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Make sure distilled sterile water is connected to the machine."),
                                 QStringLiteral("Press prime in the warning banner to prime the pumps.")
                             }), const QString &title = QStringLiteral("No Water Detected in Jet Line!"));
};

/**
 * @brief Class for No Water in Aux Line Warning.
 */
class NoWaterAux : public PatientWarning
{
public:
    /**
     * @brief Contructor Method.
     * @note  Sets clear text to "PRIME".
     */
    NoWaterAux(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Make sure distilled sterile water is connected to the machine."),
                                 QStringLiteral("Press prime in the warning banner to prime the pumps.")
                             }), const QString &title = QStringLiteral("No Water Detected in Auxiliary Line!"));
};

/**
 * @brief Class for No Water in Jet and Aux Lines Warning.
 */
class NoWaterPrime : public PatientWarning
{
public:
    /**
     * @brief Contructor Method.
     * @note  Sets clear text to "PRIME".
     */
    NoWaterPrime(int warning_id, const QVector<QString> &troubleshooting =
                                QVector<QString>({
                                    QStringLiteral("Make sure distilled sterile water is connected to the machine."),
                                    QStringLiteral("Press prime in the warning banner to prime the pumps.")
                                }), const QString &title = QStringLiteral("No Water Detected in<br>Jet and Auxiliary Lines!"));
};

/**
 * @brief System warnings are second priority for they relate to issues with the system, but not directly with the patient.
 */
class SystemWarning: public Warning
{
public:

    /**
    * @brief Constructor for system warnings and all system warnings are inherited from this.
    * @note  The default color for all system colors is blue.
    * @param warning_id
    * @param title
    * @param troubleshooting_steps
    * @param clearingBehavior
    * @param color
    */
    SystemWarning(int warning_id, const QString &title, const QVector<QString> &troubleshooting_steps, unsigned char clearingBehavior, const QString &color = QStringLiteral("#4A5AE4"));
};

/**
 * @brief Class for Jet Switch Error Warning.
 */
class JetSwitchError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    JetSwitchError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Jet Switch Error!"));
};

/**
 * @brief Class for Defective Stacking Pressure Sensor Warnings.
 */
class StackingPressureSensorDefective: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    StackingPressureSensorDefective(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Stacking Pressure Sensor Defective!"));
};

/**
 * @brief Class for Defective Stacking Pressure Sensor Warnings.
 */
class StackingPressureSensorDefectiveDouble: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    StackingPressureSensorDefectiveDouble(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Stacking Pressure Sensor Defective!<br>(Second Jet Line)"));
};

/**
 * @brief Class for Stacking Pressure Disconnection Warnings.
 */
class StackingPressureDisconnected: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    StackingPressureDisconnected(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Ensure the jet line is connected to the patient."),
                                 QStringLiteral("Ensure the jet line is connected to the NVENT Vita.")
                             }), const QString &title = QStringLiteral("Stacking Pressure Internally Disconnected"));
};

/**
 * @brief Class for Inappropriate Activity for Oxygen Sensor Warnings.
 */
class InappropriateOxygenSensor: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    InappropriateOxygenSensor(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Oxygen sensor cannot be read."),
                                 QStringLiteral("Ensure that you are using a <INSERT KIND OF OXYGEN SENSOR HERE>."),
                                 QStringLiteral("Ensure the oxygen sensor is securely inserted.")}),
                              const QString &title = QStringLiteral("Inappropriate Oxygen Sensor Detected"));
};

/**
 * @brief Class for Low Air Supply Warnings.
 */
class LowAirSupply: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    LowAirSupply(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The measured inlet air pressure is too low."),
                                 QStringLiteral("Ensure that the NVENT is securely connected to the air source."),
                                 QStringLiteral("The delivered oxygen concentration may be higher than expected as a result of this warning.")
                             }), const QString &title = QStringLiteral("Low Air Supply Pressure!"));
};

/**
 * @brief Class for Low Air Supply Warnings and to not use Lasers.
 */
class LowAirSupplyNoLaser: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    LowAirSupplyNoLaser(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The delivered oxygen concentration may be higher than expected. Do not use a laser."),
                                 QStringLiteral("The measured inlet air pressure is too low."),
                                 QStringLiteral("Ensure that the NVENT is securly connected to the air source.")
                             }), const QString &title = QStringLiteral("Low Air Supply Pressure,<br>Limited O<sub>2</sub> Adjustment in Progress!"));
};

/**
 * @brief Class for Low Oxygen Supply Warnings.
 */
class LowOxygenSupply: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    LowOxygenSupply(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The measured inlet oxygen pressure is too low."),
                                 QStringLiteral("Ensure the NVENT is securely connected to the oxygen source.")
                             }), const QString &title = QStringLiteral("Low Oxygen Supply Pressure!"));
};

/**
 * @brief Class for Air Proportional Valve Error Warnings.
 */
class AirProportionalValveError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AirProportionalValveError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Air Proportional Valve Error!"));
};

/**
 * @brief Class for Air Proportional Valve Error Warnings and to not use Lasers.
 */
class AirProportionalValveErrorNoLaser: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AirProportionalValveErrorNoLaser(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Do not use a laser, 100% oxygen is delivered to the patient.")}), const QString &title = QStringLiteral("Air Proportional Valve Error,<br>Limited O<sub>2</sub> Adjustment in Progress!"));
};

/**
 * @brief Class for O2 Proportional Valve Error Warnings.
 */
class O2ProportionalValveError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    O2ProportionalValveError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Oxygen Proportional Valve Error!"));
};

/**
 * @brief Class the Air Inlet Pressure Sensor Error Warnings.
 */
class AirInletPressureSensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AirInletPressureSensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Air Inlet Pressure Sensor Error!"));
};

/**
 * @brief Class for Air Inlet Pressure Sensor Error Warnings and to not use Lasers.
 */
class AirInletPressureSensorErrorNoLaser: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AirInletPressureSensorErrorNoLaser(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Do not use a laser, 100% oxygen is delivered to the patient.")}), const QString &title = QStringLiteral("Air Inlet Pressure Sensor Error,<br>Limited O<sub>2</sub> Adjustment in Progress!"));
};

/**
 * @brief Class for O2 Inlet Pressure Sensor Error Warnings.
 */
class O2InletPressureSensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    O2InletPressureSensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Oxygen Inlet Pressure Sensor Error!"));
};

/**
 * @brief Class for Aux Switch Error Warnings.
 * @note  Dummy Class
 */
class AuxSwitchError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxSwitchError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Step 1"), QStringLiteral("Step 2"), QStringLiteral("Step 3")}), const QString &title = QStringLiteral("Auxiliary Switch Error!"));
};

/**
 * @brief Class for Aux Proportional Valve Error Warnings.
 */
class AuxProportionalValveError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxProportionalValveError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Auxiliary Proportional Valve Error!"));
};

/**
 * @brief Class for Aux Flow Senosr Error Warnings.
 */
class AuxFlowSensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxFlowSensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Auxiliary Flow Sensor Error!"));
};

/**
 * @brief Class for Speaker Defect Warnings.
 */
class SpeakerDefect: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    SpeakerDefect(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("SpeakerDefect!"));
};

/**
 * @brief Class for Heater Failure Warnings.
 */
class HeaterFailure: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    HeaterFailure(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Heater Failure!"));
};

/**
 * @brief Class for Temperature Measuring Error Warnings.
 */
class TemperatureMeasuringError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    TemperatureMeasuringError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Internal Temperature Measuring Defect!"));
};

/**
 * @brief Class for Jet Flow Sensor Error Warnings.
 */
class JetFlowSensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    JetFlowSensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Jet Flow Sensor Error!"));
};

/**
 * @brief Class for Jet Humidity Sensor Error Warnings.
 */
class JetHumiditySensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    JetHumiditySensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Jet Humidity Sensor Error!"));
};

/**
 * @brief Class for Aux Humidity Sensor Error Warnings.
 */
class AuxHumiditySensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxHumiditySensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Auxiliary Humidity Sensor Error!"));
};

/**
 * @brief Class for RTC Error Warnings.
 */
class RTCError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    RTCError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Real Time Clock Error!"));
};

/**
 * @brief Class for Exhaust Fan Error Warnings.
 */
class ExhaustFanError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    ExhaustFanError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Exhaust Fan Error!"));
};

/**
 * @brief Class for Driving Pressure Regulator Error Warnings.
 */
class DrivingPressureRegulatorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    DrivingPressureRegulatorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Driving Pressure Regulator Error!"));
};

/**
 * @brief Class for PIP Sensor Error Warnings.
 */
class PIPSensorError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    PIPSensorError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("PIP Sensor Error!"));
};

/**
 * @brief Class for FIO2 Failure Warnings.
 */
class FiO2Failure: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    FiO2Failure(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Check that Air and Oxygen supplies are connected correctly."),
                                 QStringLiteral("Attempt to recalibrate the oxygen sensor in the Settings/Oxygen Calibration Menu."),
                                 QStringLiteral("The oxygen sensor may need to be replaced.")
                             }), const QString &title = QStringLiteral("FiO<sub>2</sub> Failure!"));
};

/**
 * @brief Class for O2 Calibration Failure Warnings.
 */
class O2CalFailure: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    O2CalFailure(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Check that Air and Oxygen supplies are connected correctly."),
                                 QStringLiteral("The oxygen sensor may need to be replaced.")
                             }), const QString &title = QStringLiteral("Oxygen Calibration Failure!"));
};

/**
 * @brief Class for Disconnection Warnings.
 */
class NoComm: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    NoComm(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Unable to retrieve settings, operating in headless mode."),
                                 QStringLiteral("Restart when possible."),
                                 QStringLiteral("Contact service when possible @ 888-730-5463")
                             }), const QString &title = QStringLiteral("Display and System Disconnected!"));
};

/**
 * @brief Class for Aux Water Pump Error Warnings.
 */
class AuxWaterPumpError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxWaterPumpError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Service is required to change water pump.")}), const QString &title = QStringLiteral("Auxiliary Water Pump Defect"));
};

/**
 * @brief Class for Jet Water Pump Error Warnings.
 */
class JetWaterPumpError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    JetWaterPumpError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Service is required to change water pump.")}), const QString &title = QStringLiteral("Jet Water Pump Defect"));
};

/**
 * @brief Class for Dehumidification Warnings.
 */
class DehumidificationFailed: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    DehumidificationFailed(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Water may still be connected to the water inlet port."),
                                 QStringLiteral("The water inlet port may be plugged."),
                                 QStringLiteral("The output port may be plugged.")
                             }), const QString &title = QStringLiteral("Dehumidification failed"));
};

/**
 * @brief Class for Flash Error Warnings.
 */
class FlashError: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    FlashError(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The system has failed to restore data from memory.")}), const QString &title = QStringLiteral("Failed to Restore Memory"));
};

/**
 * @brief Class for Breath Time Failure Warnings.
 */
class BreathTimingFailure: public SystemWarning
{
public:
    /**
     * @brief Constructor Method.
     */
    BreathTimingFailure(int warning_id, const QVector<QString> &troubleshootingSteps =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Breath Timing Failure!"));
};

/**
 * @brief Class for Jet Water Sensor Failure Warnings.
 */
class JetWaterSensorFailure: public SystemWarning
{
public:
    /**
     * @brief Constructor Method.
     */
    JetWaterSensorFailure(int warning_id, const QVector<QString> &troubleshootingSteps =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Jet Water Sensor Failure!"));
};

/**
 * @brief Class for Auxiliary Water Sensor Failure Warnings.
 */
class AuxWaterSensorFailure: public SystemWarning
{
public:
    /**
     * @brief Constructor Method.
     */
    AuxWaterSensorFailure(int warning_id, const QVector<QString> &troubleshootingSteps =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Auxiliary Water Sensor Failure!"));
};

/**
 * @brief Class for Ambient Temperature Sensor Defect Warnings
 */
class AmbientTempSensorDefect: public SystemWarning
{
public:
    /**
     * @brief Constructor Method.
     */
    AmbientTempSensorDefect(int warning_id, const QVector<QString> &troubleshootingSteps =
            QVector<QString>({QStringLiteral("Contact clinical support @ 888-730-5463")}), const QString &title = QStringLiteral("Ambient Temperature Sensor Defect!"));
};

/**
 * @brief Class for Internal Temp High Warnings.
 */
class InternalTempHigh: public SystemWarning
{
public:
    /**
     * @brief Contructor Method.
     */
    InternalTempHigh(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Check that the exhaust fan (located on the device posterior) is not blocked.")}), const QString &title = QStringLiteral("Internal System Temperature High"));
};

/**
 * @brief Notices are low priority for they act as small reminders for procedure updates and small system changes.
 */
class Notice : public Warning
{
public:
    /**
    * @brief Constructor for notices and all notices are inherited from this.
    * @note  The default color for all notice colors is yellow.
    * @param warning_id
    * @param title
    * @param troubleshooting_steps
    * @param clearingBehavior
    * @param color
    */
    Notice(int warning_id, const QString &title, const QVector<QString> &troubleshooting_steps, unsigned char clearingBehavior, const QString &color = QStringLiteral("#E2C044"));
};

/**
 * @brief Class for Notice when Limited O<sub>2</sub> Mode is enabled and for when oxygen concentration is at a level for Limited O<sub>2</sub> use.
 */
class LaserOK : public Notice
{
public:
    /**
     * @brief Contructor Method.
     * @note  Sets color to green.
     */
    LaserOK(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Limited O<sub>2</sub> mode is active, excess oxygen has been flushed from the system, and the set oxygen concentration is below the set limited oxygen value.")}), const QString &title = QStringLiteral("Limited O<sub>2</sub> Prepping to 21%"));
};

/**
 * @brief Class for Notice when oxygen is adjusting to a level Limited O<sub>2</sub> laser use.
 */
class LaserPrepping : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    LaserPrepping(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Limited O<sub>2</sub> mode is active. The system is prepping for laser use.")}), const QString &title = QStringLiteral("Limited O<sub>2</sub> Prepping to 21%"));
};

/**
 * @brief Class for Low Static O2 Pressure Warnings.
 */
class LowStaticO2Pressure: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    LowStaticO2Pressure(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The input oxygen pressure is below 35 PSI.")}), const QString &title = QStringLiteral("Low Static O<sub>2</sub> Pressure"));
};

/**
 * @brief Class for Low Static Air Pressure Warnings.
 */
class LowStaticAirPressure: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    LowStaticAirPressure(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The input air pressure is below 35 PSI.")}), const QString &title = QStringLiteral("Low Static Air Pressure"));
};

/**
 * @brief Class for Notice that PIP Monitoring should be enabled in Manaual Mode.
 */
class ManualModePIPMonitoringRecommended : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    ManualModePIPMonitoringRecommended(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("Manual mode is active. Consider monitoring PIP.")}), const QString &title = QStringLiteral("Manual Mode Active, PIP Monitoring Recommended"));
};

/**
 * @brief Class for Notice that PIP Monitoring should be enabled when Rate is set below 80 BPM.
 */
class PIPMonitoringRecommended: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    PIPMonitoringRecommended(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The set breath rate is below 80 BPM. Consider monitoring PIP.")}), const QString &title = QStringLiteral("PIP Monitoring Recommended"));
};

/**
 * @brief Class for Notice that the ETCO2 Procedure is active.
 */
class ETCO2Active: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    ETCO2Active(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("End-tidal CO<sub>2</sub> is in progress.")}), const QString &title = QStringLiteral("End Tidal CO<sub>2</sub> Routine Active"));
};

/**
 * @brief Class for Notice that system is due for service.
 */
class ServiceDue: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    ServiceDue(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The system is due for servicing. Schedule an appointment.")}), const QString &title = QStringLiteral("Service Due"));
};

/**
 * @brief Class for Notice that battery is low.
 */
class BatteryReplacement : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    BatteryReplacement(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The battery is low. Schedule a servicing appointment.")}), const QString &title = QStringLiteral("Battery Replacement Due"));
};

/**
 * @brief Class for Notice that heater is defective.
 */
class HeaterHumidiferOff : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    HeaterHumidiferOff(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The heater is defective. Schedule a servicing appointment.")}), const QString &title = QStringLiteral("Heater and Humidifier Off"));
};

/**
 * @brief Class for Notice that Humidification is deactivated on Jet and Aux Lines.
 */
class HumidificationDeactivated : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    HumidificationDeactivated(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The water sensors may be defective."),
                                 QStringLiteral("The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.")
                             }), const QString &title = QStringLiteral("Humidification System Deactivated"));
};

/**
 * @brief Class for Notice that Humidification is deactivated on Jet Line.
 */
class JetHumidificationOff : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    JetHumidificationOff(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The water sensor on the jet line may be defective."),
                                 QStringLiteral("The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.")
                             }), const QString &title = QStringLiteral("Humidification Deactivated on Jet Line"));
};

/**
 * @brief Class for Notice that Humidification is deactivated on Aux Line.
 */
class AuxHumidificationOff : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxHumidificationOff(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The water sensor on the auxiliary line may be defective."),
                                 QStringLiteral("The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.")
                             }), const QString &title = QStringLiteral("Humidification Deactivated on Auxiliary Line"));
};

/**
 * @brief Class for Notice that Aux Flow is deactivated.
 */
class AuxFlowDeactivated : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    AuxFlowDeactivated(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The water sensor on the auxiliary line may be defective."),
                                 QStringLiteral("The pump priming attempts may have run out. You may be able to reset the pump priming attempts through the humidity page.")
                             }), const QString &title = QStringLiteral("Auxiliary Flow Deactivated"));
};

/**
 * @brief Class for Notice that Distilled Water should be used for Humidification.
 */
class DistilledWater : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    DistilledWater(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("Only Use Distilled Sterile Water."),
                                 QStringLiteral("Using Saline or other composite fluids WILL clog water injectors.")
                             }), const QString &title = QStringLiteral("Only Use Distilled Water For Humidification"));
};

/**
 * @brief Class for Notice that pumps are priming.
 */
class PumpsPriming : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    PumpsPriming(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The system is preparing to humidify the critical gases.")}), const QString &title = QStringLiteral("Pump System Priming"));
};

/**
 * @brief Class for Notice that system has been ventilating for 30 minutes without humidification.
 */
class HumidityReminder : public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    HumidityReminder(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The NVENT Vita has been ventilating for 30 minutes without humidification. Consider humidifying the critical gases."),}), const QString &title = QStringLiteral("Ventilating without Humidifying for 30+ minutes. Consider adding humidity."));
};

/**
 * @brief Class for Notice that O2 Calibration is in progress.
 */
class O2CalInProgress: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    O2CalInProgress(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({
                                 QStringLiteral("The system is calibrating the oxygen sensor."),
                                 QStringLiteral("You may proceed ventilation."),
                                 QStringLiteral("The oxygen controller has been temporarily suspended.")
                             }), const QString &title = QStringLiteral("Oxygen Calibration in Progress"));
};

/**
 * @brief Class for Notice that O2 Calibration is in progess and to not use lasers.
 */
class O2CalInProgressNoLaser: public Notice
{
public:
    /**
     * @brief Contructor Method.
     */
    O2CalInProgressNoLaser(int warning_id, const QVector<QString> &troubleshooting =
            QVector<QString>({QStringLiteral("The system is calibrating the oxygen sensor. Do not use a laser.")}), const QString &title = QStringLiteral("Oxygen Calibration in Progress,<br>Limited O<sub>2</sub> Adjustment in Progress!"));
};
/** @} */







