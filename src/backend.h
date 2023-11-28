#pragma once

#include <QObject>
#include <QTimer>
#include <QDirIterator>

#include "models/pneumatic_settings.h"
#include "warnings/warning_manager.h"
#include "models/mode_settings.h"
#include "logger/o2_cal_manager.h"
#include "logger/zero_manager.h"
#include "logger/time_manager.h"
#include "logger/part_manager.h"
#include "logger/dpr_manager.h"
#include <QVector>
#include <time.h>
#include "state_manager.h"
#include "models/modes.h"
#include "models/sensors.h"
#include "models/hmi_buttons.h"

/**
 * @addtogroup backendController
 * @{
 */

/**
 * @file backend.h
 * @brief Header for backend.cpp with info.
 */

/**
 * @file backend.cpp
 * @brief Backend controller is responsible for actions on teh display controller and functions connected to the API.
 */

/**
 * @brief Constant number API messages.
 */
#define NUM_API 22

/**
 * @brief Constant of warning clear.
 */
#define WARNING_CLEARED -1

using namespace std;


/**
 * @brief The Backend class
 */
class Backend : public QObject
{
    /**
     * @addtogroup backendController
     * @{
     */

    Q_OBJECT
    
    public:
        /**
         * @brief constructor method that initializes important variables
         * @details    Initializes array of functions to be called to send signals with messages to API.
         *             Constructs timer that will start when dehumidication begins and will signal countdown decrements of dehumdification time.
         *             Initializes all manager objects that referances the following:
         *             - StateManager
         *             - WarningManager
         *             - O2CalManager
         *             - ZeroManager
         *             - PartManager
         *             - DPRManager
         * @param  stateManager
         * @param  warningManager
         * @param  o2CalManager
         * @param  zerManager
         * @param  partManager
         * @param  dprManager
         * @param  parent
         */
        explicit Backend(
                StateManager* stateManager,
                WarningManager* warningManager,
                O2CalManager* o2CalManager,
                ZeroManager* zerManager,
                PartManager* partManager,
                DPRManager* dprManager,
                QObject *parent = nullptr
                );

    /**
     * @callergraph
     */
    public slots:

        /**
         * @brief   Initializes all initGet methods.
         * @details Raises the following flags for the backend program:
         *          - Get Settings
         *          - Enable Notifications
         *          - Get Modes
         *          - Get Subsystem States
         *          - Get System Versions
         * @callergraph
         */
        void init();

        /*--Resend Functionality----------------------------------------------------------*/

        /**
         * @brief Slot to resend messages waiting for a response.
         * @callergraph
         */
        void resendMessagesSlot();

        /**
         * @brief Calls array of references to functions to send request signals to API.
         * @callergraph
         */
        void resendMessages();

        /*--IP Address--------------------------------------------------------------------*/

        /**
         * @brief Checks and retrieves local ip address from local network in state object.
         * @param[out] m_stateManager
         * @callergraph
         */
        void setUpIpAddress();

        /*--Service Logs------------------------------------------------------------------*/

        /**
         * @brief Export log files to mounted USB stick.
         * @callergraph
         */
        void saveLogsToDrive();

        /**
         * @brief Checks to see if USB drive is mounted and if directories exist.
         * @callergraph
         */
        void driveConnected();

        /**
         * @brief Ejects USB Drive, and sends signal if ejection succeeds.
         * @callergraph
         */
        void driveDisconnected();

        /**
         * @brief  Returns string for name of the directory in the USB stick and saves dev port
         * @return QString
         * @callergraph
         */
        QString findPort();

        /**
         * @brief Copies all files from one directory to another.
         * @param src
         * @param dst
         * @return bool
         * @callergraph
         */
        bool exportDirectory(const QString &src, const QString &dst);

        /**
         * @brief Reads directories and saves the total amount of files.
         * @callergraph
         */
        void updateFileCount();

        /**
         * @brief Sends service log statement for entering service menu.
         * @param value
         * @callergraph
         */
        void logsState(bool);

        void stopProgress();

        /*--Dehumidification--------------------------------------------------------------*/

        /**
         * @brief      Starts or stops dehumidification timer.
         * @param  val
         * @callergraph
         */
        void initDehumidification(unsigned char);

        /**
         * @brief Raises the Service Due Warning from the display.
         * @param state
         * @callergraph
         */
        void serviceAlarmSlot(unsigned char state);

        /*--Start Up----------------------------------------------------------------------*/

        /**
         * @brief Receive signal from API to inform QML that startup was completed.
         * @callergraph
         */
        void checkStartupComplete();

        /*--Get Settings------------------------------------------------------------------*/

        //From QML
        /**
         * @brief Raises flag to send message to API to get settings.
         * @callergraph
         */
        void initGetSettings();

        //From API
        /**
         * @brief   Receives message from API for settings received from a get settings request
         * @details QVector parameter stores settings in order
         *          - driving pressure 1
         *          - driving pressure 2
         *          - rate 1
         *          - rate 2
         *          - inspiratory time 1
         *          - inspiratory time 2
         *          - stacking pressure 1
         *          - stacking pressure 2
         *          - oxygen setting
         *          - pip threshold setting
         *          - auxiliary flow settings
         *          - humidity 1 setting
         *          - humidity 2 setting
         *          - humidity aux setting
         * @param   setting_vals
         * @callergraph
         */
        void receiveGetSettingsSlot(QVector<int> setting_vals);

        /*--Enable Notifications----------------------------------------------------------*/

        //From QML
        /**
         * @brief Raises flag to send message to API to enable notifications.
         * @callergraph
         */
        void initEnableNotifications();

        /**
         * @brief Lowers flag to stop sending message to API to enable notifications.
         * @callergraph
         */
        void enableNotificationsSlot();

        /*--Get Op Modes------------------------------------------------------------------*/

        /**
         * @brief Raises flag to send message to API to get modes that need to be restored.
         * @callergraph
         */
        void initGetModes();

        /**
         * @brief Receives message from API to restore modes that were previously set.
         * @param modes
         * @callergraph
         */
        void receiveModes(QVector<int> modes);

        /*--Get Subsystem Status----------------------------------------------------------*/

        /**
         * @brief Raises flag to send message to API to get subsystem states.
         * @callergraph
         */
        void initGetSubsystemStates();

        /**
         * @brief Receives message from API to update current subsystems in state object and lowers flag.
         * @details Updates the following subsystems:
         *          - primary ventilation
         *          - secondary ventilation
         *          - auxiliary flow
         *          - oxygen concentration
         *          - primary humidification
         *          - secondary humidification
         *          - auxiliary humidity
         * @param states
         * @callergraph
         */
        void receiveSubsystemStates(const QVector<unsigned char> &states);

        /*--System Version----------------------------------------------------------------*/

        /**
         * @brief Initializes flag for resend function to get current system version.
         * @callergraph
         */
        void initGetSystemVersion();

        /**
         * @brief Emits signel to API to get current system version.
         * @callergraph
         */
        void sendGetSystemVersion();

        /**
         * @brief Initializes name of most recent system version that will be set by state object.
         * @note  Logs system version and display version to events file.
         * @param major
         * @param minor
         * @param patch
         * @callergraph
         */
        void receiveSystemVersion(unsigned char major, unsigned char minor, unsigned char patch);

        /*--Set Settings------------------------------------------------------------------*/

        /**
         * @brief      Set pneumatic setting values from preset file.
         * @param  settings
         * @callergraph
         */
        void setPneumaticSettings(const QVector<int> &settings);

        /**
         * @brief      Receive settings update from the qml pages.
         * @details    Save pneumatic settings to state object and constructor vector that will be sent to API.
         *             Updates O2 if laser safe mode is enabled and if O2 is greater than laser safe O2 setting.
         *             Raises flag to send message to API to set pneumatic settings.
         * @param  id
         * @param value
         * @callergraph
         */
        void receiveSettingsUpdate(int id, int value);

        /**
         * @brief Receives message from API that settings are set.
         * @note  Disables screen lock mode after preset implementation.
         * @callergraph
         */
        void settingsConfirmed();

        /**
         * @brief      Sets humidity and humidity aux settings in state object and raises flag to send message to API.
         * @param  separate
         * @param  hum_value
         * @param  hum_aux_value
         * @callergraph
         */
        void separateHumidity(unsigned char separate, int hum_value, int hum_aux_value);

        /**
         * @brief Sets humidity, double jet humidity, and humidity aux settings to 0.
         * @callergraph
         */
        void receiveDehumidifySettingsUpdate();

        /*--Get Measured------------------------------------------------------------------*/

        /**
         * @brief      Receive message from API to get sensor measurements.
         * @note       Used to detect water in system and get high and low O2 values from O2 calibration.
         * @param  id
         * @param  value
         * @callergraph
         */
        void receiveSensorMeasurements(unsigned char id, unsigned char value);

        /**
         * @brief      Receive message from API to get sensor measurements for O2 voltages from O2 calibration.
         * @param  id
         * @param  value
         * @callergraph
         */
        void receiveVolt(unsigned char id, float value);

        /**
         * @brief Receive message from API to get sensor measurements for water sensors for the Initiated Shutdown Procedure.
         * @param id
         * @param value
         */
        void receiveWaterSensor(unsigned char id, unsigned char value);

        /**
         * @brief Raises flags to send message to API to get measured values for O2 calibration.
         * @callergraph
         */
        void initGetO2Cals();

        /*--Clear Warnings----------------------------------------------------------------*/

        /**
         * @brief Clears warning by id and raises flag to send message to API the warning is clears.
         * @param warning_id
         * @callergraph
         */
        void initClearAlarm(int warning_id);

        /**
         * @brief Receives message from API that warning/alarm is cleared.
         * @param warning_id
         * @callergraph
         */
        void clearAlarmSlot(int warning_id);

        /*--Display Op Mode Requests------------------------------------------------------*/

        //SET BY USER
        //From QML
        /**
         * @brief      Sends message to API to enable/disable mode.
         * @note       Multiple actions will take place depending on which mode is enabled or disabled.
         * @param modeID
         * @param value
         * @callergraph
         */
        void setMode(unsigned char, unsigned char);

        //From Timer
        /**
         * @brief Sends messages to API for which modes are enabled.
         * @callergraph
         */
        void sendModeCommand();

        //From API
        /**
         * @brief      Receives message from API to inform QML pages that mode changed from display controller request.
         * @note       Multiple actions will take place depending on which mode is enabled or disbaled.
         * @param  modeID
         * @param  value
         * @callergraph
         */
        void modeConfirmed(unsigned char, unsigned char);

        /*--Display Op Modes Response-----------------------------------------------------*/

        //SET BY SYSTEM CONTROLLER
        //From API
        /**
         * @brief      Receives message from API to inform QML pages when modes changes from system controller.
         * @note       Multiple actions will take place depending on which mode is enabled or disabled.
         * @param  modeID
         * @param  value
         * @param success
         * @callergraph
         */
        void modeRequested(unsigned char, unsigned char, unsigned char);

        /*--Notifications-----------------------------------------------------------------*/

        //From API
        /**
         * @brief Receive notifications from API.
         * @note  QVector length is 6.
         * @param notification
         * @callergraph
         */
        void notificationUpdateSlot(const QVector<float> &notification);

        //Slot to receive warning updates from API. warning_id: most severe active warning id, num_active_warnings: number of active warnings
        /**
         * @brief Receive message from API to update active warnings.
         * @param warnings
         * @callergraph
         */
        void warningUpdateSlot(QVector<unsigned char> warnings);

        /*--Ventilation-------------------------------------------------------------------*/

        /**
         * @brief Receives message from API to track state of ventilation in state object.
         * @param state
         * @callergraph
         */
        void receiveVentilationStateChange(unsigned char);

        /*--HMI Button Presses------------------------------------------------------------*/

        /**
         * @brief Receives message from API for which HMI Button was pressed.
         * @param id
         * @callergraph
         */
        void receiveHMIButtonPress(unsigned char);

        /*--Shutdown----------------------------------------------------------------------*/

        //From API
        /**
         * @brief Receive signal from API. Inform QML that powerdown was initiated
         * @callergraph
         */
        void powerdownInitiated();

        /*--Shutdown Confirm--------------------------------------------------------------*/

        //From QML
        /**
         * @brief Raises flag to send message to API to powerdown and to signal Shutdown Popup Window.
         * @param powerdown
         * @callergraph
         */
        void initiatePowerdown(unsigned char);

        //From Timer
        /**
         * @brief Sends message to API to powerdown.
         * @callergraph
         */
        void sendPowerdownCommand();

        /**
         * @brief Confirms powerdown for display controller.
         * @callergraph
         */
        void powerdownConfirmed();

        /*--SERVICE CALIBRATION-----------------------------------------------------------*/

        /**
         * @brief Sends calibration values.
         * @callergraph
         */
        void serviceCalibrationSlot();

        /*--DRIVING PRESSURE REGULATOR SET CAL VAL----------------------------------------*/

        //From QML
        /**
         * @brief Raises flag to send message to API to switch between Low DPR, High DPR, Air Regulator, and O2 Regulator Calibration.
         * @note  Sets pneumatic setting for driving pressure when switching between calibration procedures.
         * @param val
         * @callergraph
         */
        void updateDPRStates(unsigned char);

        /**
         * @brief Saves current DPR value for Low Driving Pressure Regulator Calibration.
         * @note  Switches to default DPR state at end of method.
         * @param value
         * @callergraph
         */
        void lowDPRConfirmation(unsigned char);

        /**
         * @brief   Handles High DPR Calibration.
         * @details Sends set settings message to API for precise driving pressure.
         *          Saves current DPR value after completion.
         * @note    Sends signal to switch between precise and inprecise driving pressure set settings request in API class.
         *          Switches to default DPR state at end of method.
         *          Disables listening mode.
         * @param   flag
         * @param   value
         * @callergraph
         */
        void highDPRConfirmation(int id, float value);

        /**
         * @brief Switches to default DPR state at end Air and O2 Regulator Calibration.
         * @note  Disables listening mode.
         * @param val
         * @param id
         * @callergraph
         */
        void regulatorConfirmation(unsigned char,unsigned char);

        //From API
        /**
         * @brief Receives message from API that DPR Calibration state switched.
         * @callergraph
         */
        void slotDPRValue();

        /**
         * @brief End all settings and modes related to DPR Calibration.
         */
        void endDPRCalibration();

        /*--Calibrate Pressure Sensors----------------------------------------------------*/

        //From QML
        /**
         * @brief Raises flag to send message to API to get measured values for Inlet Air, Inlet O2, PIP, or SP Zero Calibration.
         * @param id
         * @param value
         * @callergraph
         */
        void initZeroSensor(unsigned char id, float value);

        //From API
        /**
         * @brief Lowers flag to disable sensor calibration.
         * @callergraph
         */
        void receiveSensorZeroed(const QVector<unsigned char> &values);


        /**
         * @brief Receive service notifications from API.
         * @note  QVector length is 8.
         * @param notification
         * @callergraph
         */
        void serviceNotificationUpdateSlot(const QVector<float> &notification);

    signals:

        /*--Save Service Logs-------------------------------------------------------------*/

        /**
         * @brief Signal for updating status of export progress on QML page.
         * @param exportStatus
         * @callgraph
         */
        void saveLogStatusSignal(int exportStatus);

        /**
         * @brief Signal for drive connecting to QML page.
         * @param connectionState
         * @callgraph
         */
        void driveConnection(int connectionState);
        void driveConnectionSuccess(int connectionState);

        /**
         * @brief Signal for drive disconnecting to QML page.
         * @param disconnectionState
         * @callgraph
         */
        void driveDisconnection(int disconnectionState);

        /*--Dehumidification Progress-----------------------------------------------------*/

        /**
         * @brief Signal for dehumiditication seconds.
         * @param dehumidificationSeconds
         * @callgraph
         */
        void dehumidificationTime(int dehumidificationSeconds);

        /*--Get Settings------------------------------------------------------------------*/

        /**
         * @brief Signal to get settings.
         * @callgraph
         */
        void sendGetSettingsSignal();

        /*--Enable Notifications----------------------------------------------------------*/

        /**
         * @brief Signal to enable notifications.
         * @param enable_disable
         * @callgraph
         */
        void sendNotificationEnableSignal(int enable_disable);

        /*--Get Op Modes------------------------------------------------------------------*/

        //obtain modes from system controller
        /**
         * @brief Signal to restore modes that ware previously set.
         * @callgraph
         */
        void getModesSignal();

        /*--Subsystems--------------------------------------------------------------------*/

        /**
         * @brief Signal to get subsystem states.
         * @callgraph
         */
        void getSubsystemStates();

        /*--System Version----------------------------------------------------------------*/

        /**
         * @brief Signal to get current system version.
         * @callgraph
         */
        void getSystemVersionFromSC();

        /*--Set Settings------------------------------------------------------------------*/

        /**
         * @brief Signal to set pneumatic settings.
         * @callgraph
         */
        void sendSettingSignal(QVector<int>);

        /*--Get Measured------------------------------------------------------------------*/

        /**
         * @brief Signal get measured values.
         * @param id
         * @callgraph
         */
        void sendGetSensorMeasurementSignal(unsigned char id);

        /*--Cleared Warnings--------------------------------------------------------------*/

        //To API
        /**
         * @brief Signal to clear warning.
         * @param warning_id
         * @callgraph
         */
        void warningClearSignal(int warning_id);

        /*--Display Op Mode Requests------------------------------------------------------*/

        //user set mode
        /**
         * @brief Signal to enable to disable mode from display controller.
         * @callgraph
         */
        void setModeSignal(unsigned char, unsigned char); //to API

        /**
         * @brief Signal to enable or disable the physical knob.
         * @callgraph
         */
        void listenToKnob(unsigned char);

        /*--HMI Button Press--------------------------------------------------------------*/

        /**
         * @brief Signal for which HMI Button was pressed.
         * @param id
         * @callgraph
         */
        void hmiButtonPressed(int id);

        /*--Shutdown Confirm--------------------------------------------------------------*/

        //TO API
        /**
         * @brief Signal to powerdown.
         * @callgraph
         */
        void powerDownCommand(int);

        /*--Service Calibration-----------------------------------------------------------*/

        /**
         * @brief Signal to send back calibration data.
         * @param data
         * @callgraph
         */
        void signalServiceCalibrations(QVector<float> data);

        /*--Calibrate DPR-----------------------------------------------------------------*/

        /**
         * @brief Signal to get last measurement for DPR Calibration.
         * @param value
         * @callgraph
         */
        void signalDPRValue(unsigned char value);

        /**
         * @brief Signal to switch between precise and inprecise driving pressure values for API messaging.
         * @param flag
         * @param value
         * @callgraph
         */
        void signalTempDP(unsigned char flag, float value);

        /**
         * @brief Signal to reset orignal driving pressure setting.
         * @callgraph
         */
        void signalCalibrationMessages(unsigned char);

        /*--Calibrate Pressure Sensors----------------------------------------------------*/

        /**
         * @brief Signal to get last measurement for Sensor Calibration.
         * @param values
         * @callgraph
         */
        void zeroSensor(QVector<float> values);

        /**
         * @brief Signal for when zero procedure is complete.
         */
        void zeroFinished(unsigned char value);

        /**
         * @brief Signal for when low dpr calibration is complete.
         */
        void lowDPRFinished();

        /**
         * @brief Signal for when high dpr calibration is complete.
         */
        void highDPRFinished();

    private:

        /**
         * @brief The state manager that stores the current states for all pneumatic settings, modes, and other features.
         */
        StateManager* m_stateManager;
        /**
         * @brief The warning manager that tracks the states for all warnings on the system.
         */
        WarningManager* m_warningManager;
        /**
         * @brief The O<sub>2</sub> Calibration Manager that stores the data from the calibration procedure.
         */
        O2CalManager* m_o2CalManager;
        /**
         * @brief The Zero Calibration Mangager that stores the data from sensor calibration.
         */
        ZeroManager* m_zeroManager;
        /**
         * @brief The manager for storing and updating part information.
         */
        PartManager* m_partManager;
        /**
         * @brief The manager the stores data from driving pressure regulator calibration.
         */
        DPRManager* m_dprManager;

        //dehumidification progress time
        /**
         * @brief Stores the total number of seconds for the dehumidication timer.
         */
        int m_dehumidification_seconds = 120; //0;
        //Timer for dehumidification progress
        /**
         * @brief Dehumidification Progress Timer for the dehumdification progress page.
         */
        QTimer *m_dehumidication_timer;

        //flags for which messages need to be sent
        /**
         * @brief Unsigned char array for the flags for which messages need to be sent to the API.
         */
        unsigned char m_message_flags[NUM_API] = {0};
        /**
         * @brief Unsigned char array for the state of modes that need to be updated.
         */
        unsigned char m_send_modes[NUM_MODES] = {0};
        /**
         * @brief Unsigned char array for the state of measurements.
         */
        unsigned char m_get_sensors[NUM_MEASURED_SENSORS] = {0};
        //Warning that needs to be cleared
        unsigned char m_warningToClear = WARNING_CLEARED;

        //send message functions
        //Timer to resend messages
        /**
         * @brief type definition for pointer.
         */
        typedef void (Backend::*resend_function_pointer)();
        /**
         * @brief Function array to send messages to API.
         */
        resend_function_pointer m_resend_functions[NUM_API] = {nullptr};

        /**
         * @brief Variable to track the current directory name for a USB drive.
         */
        QString dirName = "";
        /**
         * @brief Variable to track the current directory to eject USB drive.
         */
        QString m_eject_command_line = "";
        unsigned char copyProgressing = 0;

        /**
         * @brief Tracks the state of the ETCO<sub>2</sub> button input.
         */
        unsigned char et_button_on_startup = 1;

        /**
         * @brief Array that tracks the state of modes.
         */
        unsigned char m_activeModes[NUM_MODES] = {0};
        /**
         * @brief Tracks the state for which sensor to be calibrated.
         */
        unsigned char m_zeroSensor = 0;
        QVector<float> m_zero_values = {};

        unsigned char m_dpr_cal = 0;
        /**
         * @brief Tracks tghe state for which pressure regulator to be calibrated.
         */
        unsigned char m_dpr = 0;
        /**
         * @brief The state for exporting data.
         */
        unsigned char m_export_status = 0;
        /**
         * @brief Array of measurement ids for calibration.
         */
        int sensor_cal_vals[6] = {9,6,7,23,24,35};

        /**
         * @brief The index for array of measurement ids for calibration.
         */
        unsigned char m_calibration_index = 6;
        /**
         * @brief Vector for sending pneumatic setting updates to system.
         */
        QVector<int> settingsVector = {};

        int m_warning_to_clear{-1};

        /**
         * @brief Notifcation vector.
         */
        QVector<double> notification_vector = QVector<double>(NUM_SETTINGS_NOTIFICATIONS + NUM_CALCULATIONS_NOTIFICATIONS,0);
        Warning* m_most_severe_active_warning = nullptr;
        int m_num_active_warnings = 0;
        /**
         * @brief Flag for O<sub>2</sub> Calibration.
         */
        unsigned char m_getO2CalsFlag = 0;
        /**
         * @brief Array for low and high oxygen calibration values.
         */
        unsigned char m_O2Vals[2]{0};
        /**
         * @brief Array for low and high oxygen calibration voltages.
         */
        float m_Volts[2]{0};
        float m_DPRs[2]{0};

        unsigned char m_sp_line_hidden = 0;

        /**
         * @brief Initializes functions array to store each send messeage function
         * @note Indexes for array are based on OpCodes in api_consts.h
         */
        void initResendFunctionPointers();

        //resend functions

        /**
         * @brief Emits signal to API to change settings
         */
        void getSettings();

        /**
         * @brief Sends message back to API for when notifications is enabled.
         */
        void enableNotifications();

        /**
         * @brief Sends message to API to get modes that need to be restored.
         */
        void getModes();

        /**
         * @brief Sends message to API to get subsystem states.
         */
        void sendGetSubsystems();

        /**
         * @brief Sends message to API to set settings.
         */
        void sendSettingsUpdate();

        /**
         * @brief Sends message to API to get measured values.
         */
        void sendGetMeasured();

        /**
         * @brief Sends message to API to clear alarm for warning.
         */
        void sendClearAlarm();

        /**
         * @brief Sends message to API to get last measurement for DPR Calibration.
         */
        void sendDPRValue();

        /**
         * @brief Sends message to API to get last measurement for Sensor Calibration.
         */
        void sendZeroSensor();

        /**
         * @brief Sends message to enable or disable screen lock mode to API for preset implementation progress.
         * @param value
         */
        void setScreenLockModes(unsigned char);

        /**
         * @brief Decrements dehumidification time in dehumidification progress timer.
         */
        void sendDehumidityValue();

        /**
         * @brief Sends message to API to sensor measurements and DPR.
         * @note  Index 6 cancels message.
         */
//        void sendSensorCalibrationValues();

        //Check if modes need to be set

        /**
         * @brief Raises or lowers flag to send message to API if mode still needs to enabled or disabled.
         */
        void modesSet();

        /**
         * @brief      Gets high or low O2 calibration values.
         * @param  id
         * @param  value
         */
        void handleO2CalVals(unsigned char, unsigned char);

        /**
         * @brief      Gets high or low O2 calibration voltages and saves all O2 Calibration values and voltages.
         * @param  id
         * @param  value
         */
        void handleVoltVals(unsigned char, float);

        /**
         * @brief Raises or lowers flags for measured sensors.
         */
        void checkSensorsReceived();

        /**
         * @brief Switches humidity percentages to levels.
         * @param value
         * @return int
         */
        int getHumidityPercentage(int value);
        /**
         * @brief Switches humidity levels to percentages.
         * @param value
         * @return int
         */
        int getHumidityLevel(int value);

        /**
         * @brief Updates humidity percentages from get settings response to levels.
         * @return QVector<int>
         */
        QVector<int> updateVectorHumidity(QVector<int>);
        /** @} */
};
/** @} */
