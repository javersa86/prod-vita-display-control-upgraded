#pragma once
#include "../communication/api_consts.h"
#include "warnings.h"
#include <QObject>
#include <QVector>
#include <QString>
#include <QTimer>

#include "../models/settings.h"

/**
 * @addtogroup warningsManager
 * @{
 */

/**
 * @file warning_manager.h
 * @brief Header for warning_manager.cpp with info.
 */

/**
 * @file warning_manager.cpp
 * @brief Manages all of the warnings and alarms on the system.
 */

/**
 * @brief Constant value for no warnings.
 */
#define NO_WARNINGS -1

/**
 * @brief ID for the Disconnection warning.
 */
#define NO_COMMUNICATION 40

constexpr int INTERVAL_THREE_SECONDS = 3000;

/**
 * @brief The WarningManager class
 */
class WarningManager : public QObject
{
    /**
     * @addtogroup warningsManager
     * @{
     */

    Q_OBJECT

    /**
     * @brief displayWarnings
     */
    Q_PROPERTY(QVector<int> displayWarnings READ getWarningBanners NOTIFY warningChanged)
    /**
     * @brief laserWarning
     */
    Q_PROPERTY(int laserWarning READ getLaserWarning NOTIFY warningChanged)

    public:

        /**
        * @brief      Constructor Method
        * @details    Constructs the following vectors for the warning manager: active warnings, inactive warnings, notices, auto clearable warnings and pneumatic settings for when top warning is triggered.
        *             Sets auto clearing warnings.
        *             Constructs disconneciton timer to raise a disconnect warning after 3 seconds with no warning updates.
        * @param clearable
        * @param parent
        */
        WarningManager(QVector <unsigned char> *clearable = nullptr, QObject *parent = nullptr);

        /**
        * @brief Gets vector of ids for active warnings, inactive warnings and notices to be displayed in the warning banner.
        * @return QVector<int>
        */
        QVector<int> getWarningBanners();

        /**
        * @brief      Received warning updates from notification message in API to stop and receive disconnection timer and set active warnings.
        * @details    Timer will not stop and continue to progress message is not sent from API.
        *             If timer does stop, then disconnection warning will be lowered.
        * @note  The disconnection warning indicates that there is no communication between the display controller and the system controller.
        * @param warnings
        */
        void updateWarnings(QVector <unsigned char> *warnings);

        /**
        * @brief Constructs vector for pneumatic settings.
        */
        void initStateValues();

        /**
        * @brief Sets the vector for pneumatic settings.
        * @param temp
        */
        void setStateValues(QVector<int>);

        /**
        * @brief Sets the pneumatic setting by ID on vector.
        * @param id
        * @param value
        */
        void setStateValue(int id, int value);

        /**
         * @brief For when the user enters the service menu, the disconnection timer will not raise disconnection.
         * @param value
         */
        void pauseDisconnection(unsigned char value);

    public slots:
        //Communicate with QML
        /**
        * @brief  Gets the number of active warnings, inactive warnings, and notices.
        * @return int
        * @callergraph
        */
        int getNumActiveWarnings();
        /**
        * @brief  Gets the title of the warning searched by ID.
        * @param  i
        * @return QString
        * @callergraph
        */
        QString getWarningTitle(unsigned char);
        /**
        * @brief  Gets the description of the warning searched by ID.
        * @param  i
        * @return QString
        * @callergraph
        */
        QString getWarningDesc(unsigned char);
        /**
        * @brief  Gets the troublshooting steps, or relevant information for the warning searched by ID.
        * @param  i
        * @return QVector<QString>
        * @callergraph
        */
        QVector<QString> getWarningInformation(unsigned char);
        /**
        * @brief  Gets the class of the warning searched by ID.
        * @note   Classes include PATIENT, SYSTEM, or NOTICE.
        * @param  i
        * @return int
        * @callergraph
        */
        int getWarningClass(unsigned char);
        /**
        * @brief  Gets the color of the warning banner for the warning searched by ID.
        * @note   Colors include RED, BLUE, YELLOW, or GREEN.
        * @param  i
        * @return QString
        * @callergraph
        */
        QString getWarningColor(unsigned char);
        /**
        * @brief Clears warning from the warnings by occurance list.
        * @note  If the alert is not a notice, and the warning is not active, remove warning from the warnings by occurance list.
        * @param id
        * @callergraph
        */
        void clearWarning(unsigned char clear_id);
        /**
        * @brief Returns if warning ID is active, false if warning ID is inactive.
        * @param i
        * @return bool
        * @callergraph
        */
        bool getWarningActive(unsigned char);
        /**
        * @brief Gets the clearing behavior of the warning searched by ID.
        *        - state 0: CLEAR_AUTONOMOUSLY
        *        - state 1: CLEAR_ON_DEMAND
        *        - state 2: CLEAR_AFTER_RESOLVED
        * @param i
        * @return int
        * @callergraph
        */
        int getWarningBehavior(unsigned char);
        /**
        * @brief  Gets the text that goes in the clear button of the warning searched by ID.
        * @note   Text will be PRIME or CLEAR.
        * @param  i
        * @return QString
        * @callergraph
        */
        QString getWarningClearText(unsigned char);

        /**
        * @brief   Gets state for which Laser-Safe Mode related warning is raised.
        * @details The following states will be returned:
        *          - State 0: Laser OK
        *          - State 1: Laser Prepping
        *          - State 2: Neither is up
        * @return  int
        * @callergraph
        */
        int getLaserWarning();

        /**
         * @brief Updates Service Due Warning.
         * @param state
         * @callergraph
         */
        void updateServiceAlarm(unsigned char state);

    signals:
        /**
         * @brief Signal for raising or clearing active warnings.
         * @callgraph
         */
        void warningChanged();
        /**
         * @brief Signal for making blue lines visible on graph when SP High is raised.
         * @callgraph
         */
        void spWarning();

        /**
         * @brief Signal for O2 Calibration progress.
         * @callgraph
         */
        void o2CalibrationSignal();

    private:

        /**
         * @brief Constant array for all warnings on the system.
         */
        const Warning m_warnings[NUM_WARNINGS] = {
            PIPHigh(0),
            StackingPressureHigh(1),
            StackingPressureHigh(2),
            PIPDisconnected(3),
            NoWaterJet(4),
            NoWaterJet(5),
            NoWaterAux(6),
            NoWaterPrime(7),

            JetSwitchError(8),
            JetSwitchError(9),
            StackingPressureSensorDefective(10),
            StackingPressureSensorDefectiveDouble(11),
            StackingPressureDisconnected(12),
            StackingPressureDisconnected(13),
            InappropriateOxygenSensor(14),
            LowAirSupply(15),
            LowAirSupplyNoLaser(16),
            LowOxygenSupply(17),
            AirProportionalValveError(18),
            AirProportionalValveErrorNoLaser(19),
            O2ProportionalValveError(20),
            AirInletPressureSensorError(21),
            AirInletPressureSensorErrorNoLaser(22),
            O2InletPressureSensorError(23),
            AuxProportionalValveError(24),
            AuxFlowSensorError(25),
            SpeakerDefect(26),
            HeaterFailure(27),
            TemperatureMeasuringError(28),
            JetFlowSensorError(29),
            JetFlowSensorError(30),
            JetHumiditySensorError(31),
            JetHumiditySensorError(32),
            AuxHumiditySensorError(33),
            RTCError(34),
            ExhaustFanError(35),
            DrivingPressureRegulatorError(36),
            DrivingPressureRegulatorError(37),
            PIPSensorError(38),
            FiO2Failure(39),
            NoComm(40),
            O2CalFailure(41),
            AuxWaterPumpError(42),
            JetWaterPumpError(43),
            JetWaterPumpError(44),
            FlashError(45),
            DehumidificationFailed(46),
            BreathTimingFailure(47),
            JetWaterSensorFailure(48),
            AuxWaterSensorFailure(49),
            AmbientTempSensorDefect(50),
            InternalTempHigh(51),

            LaserOK(52),
            LaserPrepping(53),
            LowStaticO2Pressure(54),
            LowStaticAirPressure(55),
            ManualModePIPMonitoringRecommended(56),
            PIPMonitoringRecommended(57),
            ETCO2Active(58),
            ServiceDue(59),
            BatteryReplacement(60),
            HeaterHumidiferOff(61),
            HumidificationDeactivated(62),
            JetHumidificationOff(63),
            JetHumidificationOff(64),
            AuxHumidificationOff(65),
            AuxFlowDeactivated(66),
            DistilledWater(67),
            PumpsPriming(68),
            HumidityReminder(69),
            O2CalInProgressNoLaser(70),
            O2CalInProgress(71)
        };

        int m_top_warning = NO_WARNINGS;
        int m_num_active_warnings_flag = NO_WARNINGS;

        QVector<int> m_active_warnings = QVector<int>(NUM_WARNINGS);
        QVector<int> m_notices = QVector<int>(NUM_WARNINGS - BEGIN_NOTICE_INDEX);
        QVector<int> m_inactive_by_occurance = QVector<int>();
        QVector<int> m_autoclearing_warnings = QVector<int>(NUM_WARNINGS);
        QVector<int> m_currentStateValues = QVector<int>();

        QTimer *m_disconnectTimer;

        unsigned char m_o2_calibration_flag = 0;
        unsigned char m_o2_laser_in_progress_calibration_flag = 0;

        unsigned char m_service_state = 0;

        unsigned char m_service_due_state = 0;

        const int SERVICE_ID = 59;
        const int SERVICE_NOTICE_ID = 7;
        const int CALIBRATION_ID = 19;
        const int CALIBRATION_LIMITED_ID = 20;

        /**
        * @brief Raise a "No Comm" warning if warnings are not updated.
        */
        void raiseDisconnectWarning();

        /**
        * @brief      Sets all active warnings in the system.
        * @details    For all warnings, excluding notices, updates the active warnings list to match the received array and log the included Pneumatic Settings.
        *             If a warning was raised and is not in the inactive_by_occurance list yet, appends the warning id to the end of the list.
        *             If a warning was lowered and autoclears, removes all occurances of the warning id from inactive_by_occurance list.
        *             For all notices, updates the list of active notices to match the received array and log the included Pneumatic Settings.
        *             If warnings are changed, a signal is emitted that warnings have changed and number count of warnings is set.
        * @note       This is called everytime there is a notification update.
        * @param warnings
        */
        void setActiveWarnings(QVector<unsigned char> *);

        unsigned char setActiveAlarms(unsigned char, QVector<unsigned char> *);
        unsigned char setActiveNotices(unsigned char, QVector<unsigned char> *);

        /**
        * @brief      Sets the vector for which warnings are autoclearing or not.
        * @details    There two state for a autoclearing warning.
        *              - state 1: autoclearing
        *              - state 0: not autoclearing
        * @note  Clear at any point warnings are the same as autoclearing warnings on the display, for they are lowered as soon as the system controller lowers them.
        * @note  Warnings that should drop on the DC when they drop on the SC; includes things like Service Due, and notices like Laser Prepping.
        * @param clearable_warnings
        */
        void setAutoClearingWarnings(QVector<unsigned char> *);

        /**
        * @brief  Returns true if there are any active warnings, false otherwise.
        * @return bool
        */
        bool activeWarnings();

        /**
        * @brief Return true if there are any notices, false otherwise.
        * @return bool
        */
        bool notices();

        /**
         * @brief Checks if O2 Cal In Progress are active and sends signal to O2 Cal Manager to trigger timer.
         * @param o2_index
         */
        void setCalibrationProgress(int o2_index);
        /** @} */
};
/** @} */
