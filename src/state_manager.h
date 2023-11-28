#pragma once
#include <QObject>
#include "models/modes.h"
#include "models/settings.h"
#include "models/subsystems.h"
#include "communication/api_consts.h"
#include <QVector>

#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>

/**
 * @addtogroup stateManager
 * @{
 */

/**
 * @file state_manager.h
 * @brief Header for state_manager.cpp with info.
 */

/**
 * @file state_manager.cpp
 * @brief Manages the different states of the Display Controller.
 */


/**
 * @brief The StateManager class
 */
class StateManager : public QObject
{

    /**
     * @addtogroup stateManager
     * @{
     */

    Q_OBJECT

    //STARTUP SHUTDOWN
    /**
     * @brief power_down_flag
     */
    Q_PROPERTY (int power_down_flag READ powerdownFlag WRITE setPowerdownFlag NOTIFY powerdownFlagChanged)
    /**
     * @brief start_up_flag
     */
    Q_PROPERTY (int start_up_flag READ startupFlag NOTIFY startupComplete)
    /**
     * @brief ventilating
     */
    Q_PROPERTY (unsigned char ventilating READ ventilating NOTIFY ventilatingChanged)

    //SOFTWARE VERSIONS
    /**
     * @brief displaySoftwareVersion
     */
    Q_PROPERTY(QString displaySoftwareVersion READ getDisplaySoftwareVersion NOTIFY softwareVersionChanged)
    /**
     * @brief systemSoftwareVersion
     */
    Q_PROPERTY(QString systemSoftwareVersion READ getSystemSoftwareVersion NOTIFY softwareVersionChanged)

    //MEASURED VALUES
    /**
     * @brief notification_vector
     */
    Q_PROPERTY(QVector<double> notification_vector READ getNotificationVector NOTIFY notificationVectorChanged)

    //MODES
    /**
     * @brief laser_mode
     */
    Q_PROPERTY(unsigned char laser_mode READ laserMode NOTIFY modeChanged)
    /**
     * @brief manual_mode
     */
    Q_PROPERTY(unsigned char manual_mode READ manualMode NOTIFY modeChanged)
    /**
     * @brief pip_monitoring_mode
     */
    Q_PROPERTY(unsigned char pip_monitoring_mode READ pipMonitoringMode NOTIFY modeChanged)
    /**
     * @brief demo_mode
     */
    Q_PROPERTY(unsigned char demo_mode READ demoMode NOTIFY modeChanged)
    /**
     * @brief screen_lock_mode
     */
    Q_PROPERTY(unsigned char screen_lock_mode READ screenLockMode NOTIFY modeChanged)
    /**
     * @brief double_jet_mode
     */
    Q_PROPERTY(unsigned char double_jet_mode READ doubleJetMode NOTIFY modeChanged)
    /**
     * @brief etco2_mode
     */
    Q_PROPERTY(unsigned char etco2_mode READ etCO2Mode NOTIFY modeChanged)
    /**
     * @brief dehumidify_mode
     */
    Q_PROPERTY(unsigned char dehumidify_mode READ dehumidifyMode NOTIFY modeChanged)
    /**
     * @brief o2_cal_mode
     */
    Q_PROPERTY(unsigned char o2_cal_mode READ o2CalMode NOTIFY modeChanged)
    /**
     * @brief alarm_sounding
     */
    Q_PROPERTY(unsigned char alarm_sounding READ alarmSounding NOTIFY modeChanged)
    /**
     * @brief humidity_priming_reset_available
     */
    Q_PROPERTY(unsigned char humidity_priming_reset_available READ humidityPrimingResetAvailable NOTIFY modeChanged)
    /**
     * @brief listening_to_knob
     */
    Q_PROPERTY(unsigned char listening_to_knob READ listeningToKnob NOTIFY modeChanged)
    /**
     * @brief sound_icon
     */
    Q_PROPERTY(unsigned char sound_icon READ soundIcon NOTIFY modeChanged)
    /**
     * @brief cal_mode
     */
    Q_PROPERTY(unsigned char cal_mode READ calMode NOTIFY modeChanged)
    /**
     * @brief screen_lock_touched_mode
     */
    Q_PROPERTY(unsigned char screen_lock_touched_mode READ screenLockTouchedMode NOTIFY modeChanged)

    //SENSOR_MEASUREMENTS
    /**
     * @brief sensor_measurements
     */
    Q_PROPERTY(QVector<int> sensor_measurements READ sensorMeasurements NOTIFY sensorMeasurementsChanged)

    /**
     * @brief separatedHumidity
     */
    Q_PROPERTY(unsigned char separatedHumidity READ separatedHumidity NOTIFY separateHumidityChanged)

    //Mode Success
    /**
     * @brief limited_o2_success
     */
    Q_PROPERTY(unsigned char limited_o2_success READ limitedO2Success NOTIFY modeChanged)

    /**
     * @brief dehumidify_success
     */
    Q_PROPERTY(unsigned char dehumidify_success READ dehumidifySuccess NOTIFY modeChanged)
    /**
     * @brief o2_cal_success
     */
    Q_PROPERTY(unsigned char o2_cal_success READ o2CalSuccess NOTIFY modeChanged)
    /**
     * @brief etco2_success
     */
    Q_PROPERTY(unsigned char etco2_success READ etco2Success NOTIFY modeChanged)

    //SETTINGS
    /**
     * @brief dp1
     */
    Q_PROPERTY(unsigned char dp1 READ dp1Setting NOTIFY settingChanged)
    /**
     * @brief dp2
     */
    Q_PROPERTY(unsigned char dp2 READ dp2Setting NOTIFY settingChanged)
    /**
     * @brief rate1
     */
    Q_PROPERTY(unsigned char rate1 READ rate1Setting NOTIFY settingChanged)
    /**
     * @brief rate2
     */
    Q_PROPERTY(unsigned char rate2 READ rate2Setting NOTIFY settingChanged)
    /**
     * @brief it1
     */
    Q_PROPERTY(unsigned char it1 READ it1Setting NOTIFY settingChanged)
    /**
     * @brief it2
     */
    Q_PROPERTY(unsigned char it2 READ it2Setting NOTIFY settingChanged)
    /**
     * @brief sp1
     */
    Q_PROPERTY(unsigned char sp1 READ sp1Setting NOTIFY settingChanged)
    /**
     * @brief sp2
     */
    Q_PROPERTY(unsigned char sp2 READ sp2Setting NOTIFY settingChanged)
    /**
     * @brief o2
     */
    Q_PROPERTY(unsigned char o2 READ o2Setting NOTIFY settingChanged)
    /**
     * @brief pip
     */
    Q_PROPERTY(unsigned char pip READ pipSetting NOTIFY settingChanged)
    /**
     * @brief aux
     */
    Q_PROPERTY(unsigned char aux READ auxSetting NOTIFY settingChanged)
    /**
     * @brief hum1
     */
    Q_PROPERTY(unsigned char hum1 READ hum1Setting NOTIFY settingChanged)
    /**
     * @brief hum2
     */
    Q_PROPERTY(unsigned char hum2 READ hum2Setting NOTIFY settingChanged)
    /**
     * @brief humaux
     */
    Q_PROPERTY(unsigned char humaux READ humauxSetting NOTIFY settingChanged)
    /**
     * @brief etco2Rate
     */
    Q_PROPERTY(unsigned char etco2Rate READ etco2RateSetting NOTIFY settingChanged)
    /**
     * @brief etco2IT
     */
    Q_PROPERTY(unsigned char etco2IT READ etco2ITSetting NOTIFY settingChanged)
    /**
     * @brief etco2NumBreaths
     */
    Q_PROPERTY(unsigned char etco2NumBreaths READ etco2NumBreathsSetting NOTIFY settingChanged)
    /**
     * @brief etco2DP
     */
    Q_PROPERTY(unsigned char etco2DP READ etco2DPSetting NOTIFY settingChanged)
    /**
     * @brief laserO2Limit
     */
    Q_PROPERTY(unsigned char laserO2Limit READ laserO2Setting NOTIFY settingChanged)
    /**
     * @brief volume
     */
    Q_PROPERTY(unsigned char volume READ volumeSetting NOTIFY settingChanged)

    //SUBSYSTEMS
    /**
     * @brief primaryVentilationState
     */
    Q_PROPERTY(unsigned char primaryVentilationState READ primaryVentilationState NOTIFY subsystemStateChanged)
    /**
     * @brief secondaryVentilationState
     */
    Q_PROPERTY(unsigned char secondaryVentilationState READ secondaryVentilationState NOTIFY subsystemStateChanged)
    /**
     * @brief auxiliaryFlowState
     */
    Q_PROPERTY(unsigned char auxiliaryFlowState READ auxiliaryFlowState NOTIFY subsystemStateChanged)
    /**
     * @brief oxygenControlState
     */
    Q_PROPERTY(unsigned char oxygenControlState READ oxygenControlState NOTIFY subsystemStateChanged)
    /**
     * @brief primaryHumidificationState
     */
    Q_PROPERTY(unsigned char primaryHumidificationState READ primaryHumidificationState NOTIFY subsystemStateChanged)
    /**
     * @brief secondaryHumidificationState
     */
    Q_PROPERTY(unsigned char secondaryHumidificationState READ secondaryHumidificationState NOTIFY subsystemStateChanged)
    /**
     * @brief auxiliaryHumidificationState
     */
    Q_PROPERTY(unsigned char auxiliaryHumidificationState READ auxiliaryHumidificationState NOTIFY subsystemStateChanged)

    //IP ADDRESS
    /**
     * @brief ip_address
     */
    Q_PROPERTY(QString ip_address READ getIPAddress NOTIFY ipChanged)

    /**
     * @brief currentDPR
     */
    Q_PROPERTY(int currentDPR READ currentDPR NOTIFY dprChanged)

    /**
     * @brief inletAir
     */
    Q_PROPERTY(float inletAir READ zeroInletAir NOTIFY settingChanged)
    /**
     * @brief inletO2
     */
    Q_PROPERTY(float inletO2 READ zeroInletO2 NOTIFY settingChanged)
    /**
     * @brief zeroPIP
     */
    Q_PROPERTY(float zeroPIP READ zeroPIP NOTIFY settingChanged)
    /**
     * @brief zeroSP
     */
    Q_PROPERTY(float zeroSP READ zeroSP NOTIFY settingChanged)

    //STATE OF PRESET IMPLEMENTATION.
    /**
     * @brief preset_complete
     */
    Q_PROPERTY(unsigned char preset_complete READ getPresetComplete NOTIFY settingChanged)

    //STATE OF WARNING BANNER VISIBILITY
    /**
     * @brief display_warnings
     */
    Q_PROPERTY(unsigned char display_warnings READ getDisplayWarnings NOTIFY settingChanged)

    //STATE OF EDIT PRESET PAGE
    /**
     * @brief preset_create_active
     */
    Q_PROPERTY(unsigned char preset_create_active READ getPresetCreateActive WRITE setPresetCreateActive NOTIFY settingChanged)

    /**
     * @brief sp_line_state
     */
    Q_PROPERTY(unsigned char sp_line_state READ getSPLineState NOTIFY spLineSignal)

    //ETCO2 BUTTON STATE
    /**
     * @brief etco2_button_state
     */
    Q_PROPERTY(unsigned char etco2_button_state READ getEtco2ButtonState NOTIFY etChanged)

    //SAVE DATA
    /**
     * @brief file_count
     */
    Q_PROPERTY(int file_count READ getTotalFiles NOTIFY saveDataChanged)
    /**
     * @brief save_data_progress
     */
    Q_PROPERTY(int save_data_progress READ getSaveDataProgress() NOTIFY saveDataChanged)

    //SERVICE NOTIFICATIONS
    /**
     * @brief service_notification_vector
     */
    Q_PROPERTY(QVector<double> service_notification_vector READ getServiceNotificationVector NOTIFY notificationVectorChanged)


    private:
        //flags
        int m_powerdown_flag = 0;
        int m_startup_flag = 1;
        int m_modes[NUM_MODES] = {0};
        unsigned char m_subsystems[NUM_SUBSYSTEMS] = {1};
        unsigned char m_o2_val = 0;
        int m_modes_success[NUM_MODES] = {1};
        int m_settings[NUM_SETTINGS] = {0};
        unsigned char m_humiditySeparated = 0;
        unsigned char m_ventilating = 0;

        int m_currentDPR = 0;

        float m_inlets[4] = {0};
        float m_inlets_verified[4] = {0};

        unsigned char m_saved_dp = 0;

        unsigned char m_preset_create_active = 0;

        //unsigned char m_regulators[3] = {0};

        //software version
        QString m_systemVersion;
        //notification
        QVector<double> notification_vector = QVector<double>(NUM_SETTINGS_NOTIFICATIONS + NUM_CALCULATIONS_NOTIFICATIONS + 1,0);
        //sensor measurements
        QVector<int> m_sensor_measurements = QVector<int>(NUM_MEASURED_SENSORS);

        QString m_ip_address;
        QString m_ip_address_network;

        unsigned char m_preset_complete = 1;

        unsigned char m_display_warnings = 1;

        unsigned char m_sp_lines_state = 0;

        unsigned char m_etco2_button_state = 0;

        int m_file_count = 0;
        int m_file_progress = 0;

        QVector<double> service_notification_vector = QVector<double>(NUM_SERVICE_NOTIFICATIONS, 0);

        unsigned char m_oxygen_adjusting = 0;

    public:
        /**
        * @brief Empty Constructor
        * @param parent
        */
        explicit StateManager(QObject *parent = nullptr);

        //POWER DOWN GETTERS AND SETTERS

        /**
        * @brief Gets state of powerdown status.
        * @return int
        */
        int powerdownFlag();
        /**
        * @brief Sets state of powerdown status and emits signal for it.
        * @param flag
        */
        void setPowerdownFlag(int);
        /**
        * @brief Sets state for ventilation and emits signal for it.
        * @param state
        */
        void setVentilating(unsigned char);
        /**
        * @brief Gets state of ventilation.
        * @return unsigned char
        */
        unsigned char ventilating();

        //SOFTWARE VERSIONS
        /**
        * @brief Gets version number for display controller.
        * @return QString
        */
        QString getDisplaySoftwareVersion();
        /**
        * @brief Gets version number for system controller.
        * @return QString
        */
        QString getSystemSoftwareVersion();
        /**
        * @brief Sets version number for system controller.
        * @param version
        */
        void setSystemVersion(const QString &version);

        //START UP GETTER
        /**
        * @brief  Gets state for the startup sequence.
        * @return int
        */
        int startupFlag();
        /**
        * @brief Sets state for when startup is complete and emits signal for it.
        */
        void setStartupComplete();

        //MODE GETTERS AND SETTERS
        /**
         * @brief Gets state of Laser-Safe Mode.
         * @return unsigned char
         */
        unsigned char laserMode();
        /**
         * @brief Gets state of Manual Mode.
         * @return unsigned char
         */
        unsigned char manualMode();
        /**
         * @brief  Gets state of PIP Monitoring Mode (PIP Disconnection).
         * @return unsigned char
         */
        unsigned char pipMonitoringMode();
        /**
         * @brief  Gets state of Demo Mode.
         * @return unsigned char
         */
        unsigned char demoMode();
        /**
         * @brief  Gets state of Screen Lock Mode.
         * @return unsigned char
         */
        unsigned char screenLockMode();
        /**
         * @brief  Gets state of Double Jets Mode.
         * @return unsigned char
         */
        unsigned char doubleJetMode();
        /**
         * @brief  Gets state of End-Tidal Mode.
         * @return unsigned char
         */
        unsigned char etCO2Mode();
        /**
         * @brief  Gets state of Dehumidification Mode.
         * @return unsigned char
         */
        unsigned char dehumidifyMode();
        /**
         * @brief  Gets state of O2 Calibration Mode.
         * @return unsigned char
         */
        unsigned char o2CalMode();
        /**
         * @brief  Gets state of alarms.
         * @return unsigned char
         */
        unsigned char alarmSounding();
        /**
         * @brief  Gets state of pumps.
         * @return unsigned char
         */
        unsigned char humidityPrimingResetAvailable();
        /**
         * @brief  Gets state of knob listening.
         * @return unsigned char
         */
        unsigned char listeningToKnob();
        /**
         * @brief  Gets state of sound icon.
         * @return unsigned char
         */
        unsigned char soundIcon();
        /**
         * @brief  Gets state of Service Calibration Mode.
         * @return unsigned char
         */
        unsigned char calMode();
        /**
         * @brief  Gets state for when screen is touched in Screen Lock Mode.
         * @return unsigned char
         */
        unsigned char screenLockTouchedMode();

        /**
        * @brief Gets state for when humidity and humidity aux are unified or separated.
        * @return unsigned char
        */
        unsigned char separatedHumidity();
        /**
        * @brief Sets state for when humidity and humidity aux needs to be unified or separated and emits signal for it.
        * @param value
        */
        void setSeparateHumidity(unsigned char);

        /**
        * @brief  Gets state for when Limited O2 succeeds, fails, or other states available.
        * @return unsigned char
         */
        unsigned char limitedO2Success();
        /**
        * @brief  Gets state for when dehumidification succeeds or fails.
        * @return unsigned char
        */
        unsigned char dehumidifySuccess();
        /**
        * @brief  Gets state for when O2 Calibration succeeds or failss.
        * @return unsigned char
        */
        unsigned char o2CalSuccess();
        /**
        * @brief  Gets state for when the End-Tidal Procedure succeeds or fails.
        * @return unsigned char
        */
        unsigned char etco2Success();

        /**
        * @brief  Gets state of mode searched by id.
        * @param  modeID
        * @return unsigned char
        */
        unsigned char getModeEnabled(unsigned char);

        /**
        * @brief Sets state for mode and mode's success and emits signal for it.
        * @note  If Laser-Safe Mode or O2 Calibration Mode is enabled, a signal will be emitted to QML for when O2 needs to be adjusted.
        * @param modeID
        * @param value
        * @param success
        */
        void setMode(unsigned char, unsigned char, unsigned char);

        //SUBSYSTEM GETTERS AND SETTERS
        /**
        * @brief  Gets state of ventilation on Jet Line 1.
        * @return unsigned char
        */
        unsigned char primaryVentilationState();
        /**
        * @brief  Gets state of ventilation on Jet Line 2.
        * @return unsigned char
        */
        unsigned char secondaryVentilationState();
        /**
        * @brief  Gets state of Auxiliary Flow Line.
        * @return unsigned char
        */
        unsigned char auxiliaryFlowState();
        /**
        * @brief  Gets state of oxygen subsystem.
        * @return unsigned char
        */
        unsigned char oxygenControlState();
        /**
        * @brief  Gets state of humidification subsystem on Jet Line 1.
        * @return unsigned char
        */
        unsigned char primaryHumidificationState();
        /**
        * @brief  Gets state of humidification subsystem on Jet Line 2.
        * @return unsigned char
        */
        unsigned char secondaryHumidificationState();
        /**
        * @brief  Gets state of humidification subsystem on Auxiliary Line.
        * @return unsigned char
        */
        unsigned char auxiliaryHumidificationState();

        /**
        * @brief Sets subsystem states.
        * @param states
        */
        void setSubsystemStates(const QVector<unsigned char> &states);

        //SETTING GETTERS AND SETTERS
        /**
         * @brief  Gets value for Driving Pressure 1 Setting.
         * @return unsigned char
         */
        unsigned char dp1Setting();
        /**
         * @brief  Gets value for Driving Pressure 2 Setting.
         * @return unsigned char
         */
        unsigned char dp2Setting();
        /**
         * @brief  Gets value for Rate 1 Setting.
         * @return unsigned char
         */
        unsigned char rate1Setting();
        /**
         * @brief  Gets value for Rate 2 Setting.
         * @return unsigned char
         */
        unsigned char rate2Setting();
        /**
         * @brief  Gets value for Inspiratory Time 1 Setting.
         * @return unsigned char
         */
        unsigned char it1Setting();
        /**
         * @brief  Gets value for Inspiratory Time 2 Setting.
         * @return unsigned char
         */
        unsigned char it2Setting();
        /**
         * @brief  Gets value for Stacking Pressure 1 Setting.
         * @return unsigned char
         */
        unsigned char sp1Setting();
        /**
         * @brief  Gets value for Stacking Pressure 2 Setting.
         * @return unsigned char
         */
        unsigned char sp2Setting();
        /**
         * @brief  Gets value for Oxygen Concentration Setting.
         * @return unsigned char
         */
        unsigned char o2Setting();
        /**
         * @brief  Gets value for Peak Inspiratory Pressure Setting.
         * @return unsigned char
         */
        unsigned char pipSetting();
        /**
         * @brief  Gets value for Auxiliary Flow Setting.
         * @return unsigned char
         */
        unsigned char auxSetting();
        /**
         * @brief  Gets value for Humidity 1 Setting.
         * @return unsigned char
         */
        unsigned char hum1Setting();
        /**
         * @brief  Gets value for Humidity 2 Setting.
         * @return unsigned char
         */
        unsigned char hum2Setting();
        /**
         * @brief  Gets value for Humidity Auxiliary Setting.
         * @return unsigned char
         */
        unsigned char humauxSetting();
        /**
         * @brief  Gets value for End-Tidal Rate Setting.
         * @return unsigned char
         */
        unsigned char etco2RateSetting();
        /**
         * @brief  Gets value for End-Tidal Inspiratory Time Setting.
         * @return unsigned char
         */
        unsigned char etco2ITSetting();
        /**
         * @brief  Gets value for End-Tidal Number of Breaths Setting.
         * @return unsigned char
         */
        unsigned char etco2NumBreathsSetting();
        /**
         * @brief  Gets value for End-Tidal Driving Pressure Setting.
         * @return unsigned char
         */
        unsigned char etco2DPSetting();
        /**
         * @brief  Gets value for Laser-Safe Oxygen Concentration Setting.
         * @return unsigned char
         */
        unsigned char laserO2Setting();
        /**
         * @brief  Gets value for Volume.
         * @return unsigned char
         */
        unsigned char volumeSetting();

        /**
        * @brief Gets O2 value for Laser-Safe Mode.
        * @return unsigned char
        */
        unsigned char getSetO2Val();
        /**
        * @brief Sets O2 value for Laser-Safe Mode.
        * @param val
        */
        void setSetO2Val(unsigned char);

        //DRIVING PRESSURE REGULATOR STATE
        /**
        * @brief Gets DPR Calibration value.
        * @return int
        */
        int currentDPR();
        /**
        * @brief Sets DPR Calibration value and emits signal for it.
        * @param val
        */
        void setDPR(int);

        //INLET AIR AND O2
        /**
         * @brief  Gets calibration value for Inlet Air.
         * @return float
         */
        float zeroInletAir();

        /**
         * @brief Gets verify value for Inlet Air.
         * @return float
         */
        float verifyInletAir();

        /**
         * @brief  Gets calibration value for Inlet O2.
         * @return float
         */
        float zeroInletO2();

        /**
         * @brief Gets verify value for Inlet O2.
         * @return float
         */
        float verifyInletO2();

        //INLET PIP AND SP
        /**
         * @brief Gets calibration value for PIP.
         * @return float
         */
        float zeroPIP();

        /**
         * @brief Gets verify value for PIP.
         * @return float
         */
        float verifyPIP();

        /**
         * @brief  Gets calibration value for SP.
         * @return float
         */
        float zeroSP();

        /**
         * @brief Gets verify value for SP.
         * @return float
         */
        float verifySP();

        //SAVED DRIVING PRESSURE BEFORE DPR CALIBRATION
        /**
        * @brief Gets saved Driving Pressure setting value for when Service Calibration Mode is enabled.
        * @return unsigned char
        */
        unsigned char getSavedDP();
        /**
        * @brief Sets saved Driving Pressure setting value for when Service Calibration Mode is enabled.
        * @param val
        */
        void setSavedDP(unsigned char);

        //NOTIFICATION GETTERS AND SETTERS
        /**
        * @brief Get measured values from notifications.
        * @return QVector<double>
        */
        QVector<double> getNotificationVector();
        /**
        * @brief   Set measured values to notifications.
        * @details Sets the following values to notifications and emits signal for it:
        *          - Stacking Pressure 1
        *          - Stacking Pressure 2
        *          - Oxygen Concentration
        *          - Peak Inspiratory Pressure
        *          - Auxiliary Flow
        *          - Tidal Volume 1
        *          - Tidal Volume 2
        *          - Map
        *          - O2 Calibration Voltage
        *          - Alarm Time
        * @param   notification
        */
        void updateNotificationVector(const QVector<float> &notification);

        //SENSOR MEASUREMENTS
        /**
        * @brief Gets sensor measurements.
        * @return QVector<int>
        */
        QVector<int> sensorMeasurements();
        /**
        * @brief Sets sensor measurement by id and emits signal for it.
        * @param id
        * @param value
        */
        void setSensorMeasurement(unsigned char id, int value);

        /**
        * @brief Sets Setting by id and emits signal for it.
        * @note  Saves O2 Settings seperately for when Laser-Safe O2 Setting is set.
        * @param id
        * @param val
        */
        void setSetting(unsigned char, int);
        /**
        * @brief Sets Settings and emits signal for it.
        * @note  Saves O2 Settings seperately for when Laser-Safe O2 Setting is set.
        * @param settings
        */
        void setSettings(const QVector<int> &settings);
        /**
        * @brief Sets Pneumatic Settings and emits signal for it.
        * @param settings
        */
        void setPneumaticSettings(const QVector<int> &settings);

        //IP ADDRESS GETTER
        /**
        * @brief Gets IP Address.
        * @return QString
        */
        QString getIPAddress();

        //STATE OF PRESET IMPLEMENTATION.
        /**
        * @brief Gets state of preset implementation progress.
        * @return unsigned char
        */
        unsigned char getPresetComplete();
        /**
        * @brief Sets state of preset implementation progress and emits signal for it.
        * @param val
        */
        void setPresetComplete(unsigned char val);

        //STATE OF WARNING BANNER VISIBILITY
        /**
        * @brief Gets state of warning banner visibility.
        * @note  Function utilizied for service menu calibration page.
        * @return unsigned char
        */
        unsigned char getDisplayWarnings();
        /**
        * @brief Sets state of warnings banner visibility
        * @note  Function utilized for  service menu calibration page.
        * @param val
        */
        void setDisplayWarnings(unsigned char val);

        //STATE OF EDIT PRESET PAGE
        /**
        * @brief Gets state for when preset edit page is opened, so that page won't timeout.
        * @return unsigned char
        */
        unsigned char getPresetCreateActive();
        /**
        * @brief Sets state for when preset edit page is opened, so that page won't timeout and emits signal for it.
        * @param val
        */
        void setPresetCreateActive(unsigned char val);

        /**
         * @brief Gets state of visibility for SP Line on the graph.
         * @return unsigned char
         */
        unsigned char getSPLineState();

        //ETCO2 BUTTON STATE
        /**
         * @brief Gets the state of the functionality of the ETCO2 Button.
         * @return unsigned char
         */
        unsigned char getEtco2ButtonState();

        //SAVE DATA
        /**
         * @brief Sets total service log files and warning log files.
         * @param count
         */
        void setTotalFiles(int count);

        /**
         * @brief Gets total service log files and warning log files.
         * @return int
         */
        int getTotalFiles();

        /**
         * @brief Sets progress for exporting files to USB Drive.
         * @param count
         */
        void setSaveDataProgress(int count);

        /**
         * @brief Increments progress for exporting files by 1.
         */
        void incrementSaveDataProgress();

        /**
         * @brief Gets progress for exporting files to USB Drive.
         * @return int
         */
        int getSaveDataProgress();

        /**
         * @brief Get measured values from service notifications.
         * @return QVector<double>
         */
        QVector<double> getServiceNotificationVector();

        /**
         * @brief Get adjustment state for oxygen measurement.
         * @return int
         */
        int getOxygenAdjustmentState();

        /**
         * @brief Update adjustment state for oxygen measurement.
         */
        void adjustOxygen();

    public slots:
        /**
        * @brief  Gets setting value by id.
        * @param  id
        * @return unsigned char
        */
        unsigned char getSettingValue(unsigned char);

        /**
        * @brief Retrieves and sets IP Address from local network and emits signal for it.
        * @note  "Please Connect" will be stored to IP Address QString variable if IP Address isn't found.
        */
        void setupNetwork();
        /**
         * Sets IP Address from network.
         */
        void setIPAddress();

        /**
        * @brief  Get sensor measurement by id.
        * @param  id
        * @return unsigned char
        */
        int getZeroValue(unsigned char);

        /**
         * @brief Sets the state of visibility for SP Line on the graph.
         * @param val
         */
        void setSPLineState(unsigned char);

        //ETCO2 BUTTON STATE SET
        /**
         * @brief Sets the state of the functionality of the ETCO2 Button.
         * @param val
         */
        void setEtco2ButtonState(unsigned char);
        /**
         * @brief Slot for turning off switch for manual mode.
         */
        void forceManualOff();

        /**
        * @brief   Set measured values to service notifications.
        * @details Sets the following values to notifications and emits signal for it:
        *          - Stacking Pressure Average Data
        *          - Stackign Pressure Raw Data
        *          - Peak Inspiratory Pressure Average Data
        *          - Peak Inspiratory Pressure Raw Data
        * @param   notification
        */
        void updateServiceNotificationVector(const QVector<float> &notification);

        /**
         * @brief Sets calibration value Inlet Air and emits signal for it.
         * @param val
         */
        void setZeroInletAir(float);

        /**
         * @brief Sets verify value Inlet Air and emits signal for it.
         * @param val
         */
        void setVerifyInletAir(float);

        /**
         * @brief Sets calibration value Inlet O2 and emits signal for it.
         * @param val
         */
        void setZeroInletO2(float);

        /**
         * @brief Sets verify value Inlet O2 and emits signal for it.
         * @param val
         */
        void setVerifyInletO2(float);

        /**
         * @brief Sets calibration value PIP and emits signal for it.
         * @param val
         */
        void setZeroPIP(float);

        /**
         * @brief Sets verify value PIP and emits signal for it.
         * @param val
         */
        void setVerifyPIP(float);

        /**
         * @brief Sets calibration value SP and emits signal for it.
         * @param val
         */
        void setZeroSP(float);

        /**
         * @brief Sets verify value SP and emits signal for it.
         * @param val
         */
        void setVerifySP(float);

        void settingsCompleteTriggered();

    signals:

        /**
         * @brief Signal for state of powerdown.
         */
        void powerdownFlagChanged();
        /**
         * @brief Signal for when startup is complete.
         */
        void startupComplete();
        /**
         * @brief Signal for switch modes and mode successes.
         */
        void modeChanged();
        /**
         * @brief Signal for updating settings, preset page, sensor calibration values, and warnings.
         */
        void settingChanged();
        /**
         * @brief Signal for versions.
         */
        void softwareVersionChanged();
        /**
         * @brief Signal for updating notifications.
         */
        void notificationVectorChanged();
        /**
         * @brief Signal switching between unified and seperate humidity.
         */
        void separateHumidityChanged();
        /**
         * @brief Signal for updating subsystems.
         */
        void subsystemStateChanged();
        /**
         * @brief Signal for updating senosr measurements.
         */
        void sensorMeasurementsChanged();
        /**
         * @brief Signal for ventilation change.
         */
        void ventilatingChanged();
        /**
         * @brief Signal for updating IP Address.
         */
        void ipChanged();
        /**
         * @brief Signal for updating DPR Calibration value.
         */
        void dprChanged();
        /**
         * @brief Signal for completing preset implementations.
         */
        void settingsComplete();
        /**
         * @brief Signal for the state of the SP Line.
         */
        void spLineSignal();
        /**
         * @brief Signal for adjusting O2.
         * @param id
         */
        void oxygenAdjustmentSignal(unsigned char id);
        /**
         * @brief Signal for updating the state of the ETCO2 button.
         */
        void etChanged();
        /**
         * @brief Signal for exporting service logs.
         */
        void saveDataChanged();
        /**
         * @brief Signal for turning off switch for manual mode.
         */
        void forceManualOffSignal();

        void limitedO2State(int stateVal);
        /** @} */
};
/** @} */
