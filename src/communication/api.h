#pragma once

#include <QThread>
#include <QObject>
#include <QString>
#include <QVector>
#include <time.h>
#include <QtDebug>

// C library headers
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <cstdint>

#include "serial.h"
#include "api_consts.h"
#include "../models/settings.h"
#include "../models/sensors.h"
#include "../communication/devices.h"
#include "message_queue.h"

/**
 * @addtogroup apiModule
 * @{
 */

/**
 * @brief Constant value for buffer size for message sent to api.
 */
#define INPUT_BUFFER_SIZE 512

/**
 * @brief Constant character that appears at the beginning of all messages.
 */
#define START_CHAR 255

/**
 * @file api.h
 * @brief The header file for api.cpp
 */

/**
 * @file api.cpp
 * @brief Manages the requests and responses communicating through the Serial Port.
 */

/**
 * @brief The API class
 */
class API : public QThread
{
    /**
     * @addtogroup apiModule
     * @{
     */

    Q_OBJECT

    public:

        /**
         * @brief Default Constructor.
         *
         * @param portname
         * @param baudrate
         */
        API(const QString &portname, int baudrate);

        /**
         * @brief Gets the serial portname.
         * @return QString
         */
        QString getPortname() const;

        /**
         * @brief Gets the serial baudrate.
         * @return int
         */
        int getBaudrate() const;

        /**
         * @brief Initiates the serial communication between the display and system controller.
         * @details Starts the infinite loop of the API thread.
         *          The period of a loop should ideally be 30 milliseconds, with 25 millisecond rest period for the system controller to process the data.
         *          Incoming bytes are read and processed from the system controller and outgoing bytes of the output buffer are sent to the system controller.
         *          Events of the main loop are conducted in the following order:
         *          1) Read and processes bytes from the MCU (This is where handleRequest is called from.)
         *          2) Request subsequent requests from Backend for messages awaiting responses: examples include set settings, get settings, enable notifications, etc.
         *          3) Write queued messages to the MCU.
         *          4) Sleep
         * @note Checks for the USB connection between the display and system controller on each loop.
         */
        void run();

        /**
         * @brief Variable used to check if display controller is disconnected to system controller.
         */
        int _signal_warning = 1;

        /**
         * @brief Variable stores portname.
         */
        QString myPortName;

        /**
         * @brief Variable stores port number.
         */
        int port_num = 0;

    public slots:

        /* get settings */

        /**
         * @brief Queues get setting request into the tx buffer.
         * @callergraph
         */
        void sendGetSettingsSlot();
        /* enable notifications */

        /**
         * @brief Slot connected to the backend. Queues enable notification request into the TX Buffer.
         * @note Lowers notification_request_confirmed to indicate that no response from the MCU has been received.
         * @callergraph
         */
        void sendNotificationSlot(int); //backend telling to enable/disable

        /**
         * @brief Slot connected to the backend. Queues enable notification request into the TX Buffer if notifications haven't been enabled yet.
         * @note Does not mutate the notification_request_confirmed flag and should still be low.
         * @callergraph
         */
        void resendNotificationSlot(int); //backend telling to enable/disable

        /* get modes */

        /**
         * @brief Queues request into the TX Buffer to get modes.
         * @callergraph
         */
        void getModesSlot();

        /* subsystem states */

        /**
         * @brief Queues a getSubsystemStates request.
         * @callergraph
         */
        void getSubsystemStates();

        /* System Version */

        /**
         * @brief Queues get system version request into the TX Buffer.
         * @callergraph
         */
        void queryVersion();

        /* set settings */

        /**
         * @brief Queues set setting request into the TX Buffer.
         * @callergraph
         */
        void sendSettingsSlot(const QVector<int> &settings);//backend telling to set settings

        /* get measured */

        /**
         * @brief Requests measured value to the system controller.
         * @param id
         * @callergraph
         */
        void getMeasured(unsigned char id);

        /* warnings */

        /**
         * @brief Receives a clear warning signal from the main thread and adds a clear warning message to the outgoing buffer.
         * @details Repeatedly sent clear messages are be handled in the QML.
         *          A QTimer will send it until receiving a warning update signal and reset.
         * @note The main thread will send a warning id which will silence a warning to the MCU.
         * @param warning_id
         * @callergraph
         */
        void clearWarningSlot(int);// the main thread will send a warning id which will silence a warning to the MCU

        /* modes */

        /**
         * @brief Queues request from the user to the TX Buffer to set a mode.
         * @param id
         * @param enable
         * @callergraph
         */
        void sendModeSlot(unsigned char, unsigned char);

        /* Powerdown */

        /**
         * @brief Queues a confirmPowerdown command to TX Buffer with a confirm/cancel flag.
         * @param powerdown
         * @callergraph
         */
        void confirmPowerdown(unsigned char);

        /* Service Calibration Values */

        /**
         * @brief slotServiceCalibrationResponse
         * @param calibration_data
         * @callergraph
         */
        void slotServiceCalibrationResponse(QVector<float>);

        /* dpr */

        /**
         * @brief Retrieved signal from backend to enable DPR calibration.
         * @param enable_disabled
         * @callergraph
         */
        void slotDPR(unsigned char enable_disabled);

        /**
         * @brief Retrieved signal from backend to request DPR state change to the system controller.
         * @param value
         * @callergraph
         */
        void slotDPRValue(unsigned char value);

        /**
         * @brief Saves DP Setting value as float for DPR calibration.
         * @param flag
         * @param value
         * @callergraph
         */
        void slotTempDP(unsigned char flag, float value);

        /**
         * @brief Flag Raised to prevent notification and subsystem statu update messages to the tx buffer during service calibration.
         * @param value
         * @callergraph
         */
        void slotCalibrationMessages(unsigned char);

        /* sensor zero */

        /**
         * @brief Queues zero sensor request into TX Buffer.
         * @param sensorId
         * @callergraph
         */
        void zeroSensor(QVector<float> values);


    signals:

        /**
         * @brief Emits signal for get settings response to backend program.
         * @param settings
         * @callgraph
         */
        void updateSettingsSignal(QVector<int> settings);

        /**
         * @brief Sends signal to backend to reenable notifications.
         * @callgraph
         */
        void resendNotificationSignal(); //backend telling to enable/disable

        /**
         * @brief Sends signal to backend to enable notifications.
         * @callgraph
         */
        void enableNotificationSignal();

        /**
         * @brief Sends signal with modes to the backend program.
         * @callgraph
         */
        void sendModesSignal(QVector<int>);

        /* subsystem states */

        /**
         * @brief Sends signal to backend program with subsystem changes.
         * @callgraph
         */
        void subsystemStatesChangeReceived(QVector<unsigned char>);

        /* system version */

        /**
         * @brief Sends signal to the backend program with system verion.
         * @param major
         * @param minor
         * @param patch
         * @callgraph
         */
        void systemVersion(unsigned char major, unsigned char minor, unsigned char patch);

        //request the main thread send the setSettings signal again becuase MCU didn't respond

        /**
         * @brief Signal for set settings response to the backend program.
         * @callgraph
         */
        void settingsConfirmed();

        /* get measured */

        /**
         * @brief Sends signal to backend program with measurement.
         * @param id
         * @param value
         * @callgraph
         */
        void receiveMeasuredValue(unsigned char id, unsigned char value);
        /**
         * @brief Sends signal to backend program with calibration voltages.
         * @param id
         * @param value
         * @callgraph
         */
        void receiveVoltValue(unsigned char id, float value);
        /**
         * @brief Sends signal to backend program with water sensor detection value.
         * @param id
         * @param value
         */
        void receiveWaterSensorValue(unsigned char id, unsigned char value);
        /**
         * @brief Sends signal to backend program that warning id was cleared.
         * @param warning_id
         * @callgraph
         */
        void clearWarningSignal(int warning_id); //API telling backend system controller acknowledged clear with the warning id

        /* modes */

        /**
         * @brief Sends signal to backend program that mode set from display was enabled.
         * @callgraph
         */
        void modeSetSignal(unsigned char, unsigned char);//modes set from display confirmation

        /**
         * @brief Sends signal to backend program that mode set from system was enabled.
         * @callgraph
         */
        void setModeSignal(unsigned char, unsigned char, unsigned char);//modes set from system controller information

        /**
         * @brief Sends signal to backend program to resend messages to API.
         * @callgraph
         */
        void resendMessagesSignal();

        /**
         * @brief Sends signal to backend program with notifications.
         * @param notifications
         * @callgraph
         */
        void notificationUpdateSignal(QVector<float>);

        /* warnings */  //report warnings changes to backend
        //API telling backend most severe warning and number of warnings. Warning ID will be -1 if no active warnings. Only sent on warning change

        /**
         * @brief Sends signal to backend program with warning states.
         * @details API telling backend most severe warning and number of warnings. Warning ID will be -1 if no active warnings. Only sent on warning change.
         * @callgraph
         */
        void warningUpdateSignal(QVector<unsigned char>);

        /* ventilation state */

        /**
         * @brief Sends signal to backend program with ventilation state change.
         * @callgraph
         */
        void ventilationStateChangeReceived(unsigned char);

        /* HMI button press */

        /**
         * @brief Sends signal to backend program for which HMI Button was pressed.
         * @param id
         * @callgraph
         */
        void HMIButtonPushReceived(unsigned char id);

        /* power down */

        /**
         * @brief Sends signal to backend program to initiate shutdown procedure.
         * @callgraph
         */
        void initPowerdown();

        /**
         * @brief Sends signal to the backend program to confirm or cancel powerdown procedure.
         * @callgraph
         */
        void powerdownConfirmed(unsigned char);

        /* service calibration */

        /**
         * @brief Sends signal to the backend program for service calibration values.
         * @callgraph
         */
        void serviceCalibrationSignal();

        /* dpr */

        /**
         * @brief Sends signal to backend program to confirm DPR Value change.
         * @callgraph
         */
        void signalDPRValue(); //, unsigned char regAirValue, unsigned char regO2Value, float setValue);

        /* sensor zero */

        /**
         * @brief Sends signal to backend that sensor is zeroing.
         * @callgraph
         */
        void sensorZeroed(QVector<unsigned char>);

        /**
         * @brief Sends signal to backend program with service notifications.
         * @param notifications
         * @callgraph
         */
        void serviceNotificationUpdateSignal(QVector<float>);

    private:

        Comm serial;

        unsigned char settings_set = 1;
        unsigned char get_settings_confirmed = 0;
        unsigned char notification_request_confirmed = 0;
        unsigned char dpr_flag = 0;
        float temp_dp_value = 0;
        unsigned char temp_dp_value_flag = 0;
        unsigned char service_flag = 0;
        int m_num_of_notifications = -1;

        MessageQueue request_queue;
        MessageQueue response_queue;

        QString _portname = QString::fromStdString("");
        int _baudrate = -1;

        //__processBytes data
        unsigned char _index = 0;
        unsigned char _op_code = 255;
        unsigned char _in_progress = 0;
        QVector<unsigned char> input_buffer = QVector<unsigned char>(INPUT_BUFFER_SIZE); //[INPUT_BUFFER_SIZE] = {};
        int _ndx = 0;
        int _message_length = 0;

        unsigned long _cycle_period = 30; // api run method should take 30 ms each cycle

        const int max_messages = 5;
        const unsigned long ms_count = 35;
        const int port_name_sub_length = 11;

        unsigned char power_cycle_response[(int)txLengths::DISPLAY_POWER_ON_RECEIVED] = {(unsigned char)txOpCodes::DISPLAY_POWER_ON_RECEIVED};
        unsigned char get_settings_request[(int)txLengths::DISPLAY_GET_SETTINGS_REQUEST] = {(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST};
        unsigned char notification_request[(int)txLengths::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST] = {(int)txOpCodes::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST, 0};
        unsigned char get_op_modes_request[(int)txLengths::DISPLAY_GET_OP_MODES_REQUEST] = {(unsigned char) txOpCodes::DISPLAY_GET_OP_MODES_REQUEST};
        unsigned char get_subsystem_request[(int)txLengths::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST] = {(unsigned char) txOpCodes::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST};
        unsigned char version_message[(int)txLengths::DISPLAY_GET_SYSTEM_VERSION_REQUEST] = {(unsigned char)txOpCodes::DISPLAY_GET_SYSTEM_VERSION_REQUEST};

        QVector<unsigned char> set_request = QVector<unsigned char>((int) txLengths::DISPLAY_SET_SETTINGS_REQUEST);

        unsigned char measured_request[(int)txLengths::DISPLAY_GET_MEASURED_REQUEST] = {(unsigned char)txOpCodes::DISPLAY_GET_MEASURED_REQUEST, 0};
        unsigned char clear_warning_request[(int)txLengths::DISPLAY_CLEAR_WARNING_REQUEST] = {(unsigned char)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST,0};
        unsigned char display_set_mode_request[(int)txLengths::DISPLAY_ENABLE_OP_MODE_REQUEST] = {0};
        unsigned char system_set_mode_request[(int)txLengths::DISPLAY_ENABLE_OP_MODE_RESPONSE] = {0};
        unsigned char notification_response[(int)txLengths::DISPLAY_NOTIFICATION_RECEIVED] = {(unsigned char)txOpCodes::DISPLAY_NOTIFICATION_RECEIVED};
        unsigned char subsystem_response[(int)txLengths::DISPLAY_SUBSYSTEM_STATUS_RECEIVED] = {(unsigned char) txOpCodes::DISPLAY_SUBSYSTEM_STATUS_RECEIVED};
        unsigned char ventilation_response[(int)txLengths::DISPLAY_VENTILATION_STATUS_RECEIVED] = {(unsigned char) txOpCodes::DISPLAY_VENTILATION_STATUS_RECEIVED};
        unsigned char hmi_response[(int)txLengths::DISPLAY_HMI_BUTTON_PUSHED_RECEIVED] = {(unsigned char) txOpCodes::DISPLAY_HMI_BUTTON_PUSHED_RECEIVED, 0};
        unsigned char shutdown_request[(int)txLengths::DISPLAY_SHUTDOWN_RECEIVED] = {(unsigned char) txOpCodes::DISPLAY_SHUTDOWN_RECEIVED};
        unsigned char shutdown_confirm_request[(int)txLengths::DISPLAY_SHUTDOWN_CONFIRM_SEND] = {(unsigned char) txOpCodes::DISPLAY_SHUTDOWN_CONFIRM_SEND, 0};

        QVector<unsigned char> data_request = QVector<unsigned char>((int)txLengths::DISPLAY_SERVICE_CALIBRATION_RESPONSE); //[(int)txLengths::DISPLAY_SERVICE_CALIBRATION_RESPONSE] = {0};

        unsigned char dpr_request[(int)txLengths::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = {(unsigned char) txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST, 0};
        unsigned char zero_request[(int)txLengths::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST] = {0};

        /**
         * @brief Checks for the USB connection between the display and system controller.
         * @details If the display controller is disconnected from system controller, it will need to be reconnected.
         *          When the display controller is reconnected with the system controller, the API will reopen and reconfigure the device under a new portname.
         * @note The portname for the system controller will flip between "ttyUSB0" and "ttyUSB1".
         * @param success
         * @return int
         */
        int checkUSB(int success);


        /**
         * @brief Handles new incoming bytes in linear and overflow mode.
         */
        void process();

        /**
         * @brief Processes incoming messages byte by byte.
         * @details The process is persistent so it may stop halfway through a message and continue on the next serial read
         *          ProcessBytes depends on the following:
         *              getMessageLength(op_code) to provide the message length per op_code,
         *              checkCRC(unsigned char*) to verify the validity of the parsed message,
         *              and handleRequest(unsigned char*) to handle the parsed requests after verified.
         * @param byte
         */
        void processBytes(unsigned char);

        /**
         * @brief Translates a float to a byte array.
         * @param src
         * @param dst
         */
        static void floatToBytes(float,unsigned char*);

        /**
         * @brief Translate byte array into float.
         * @param src
         * @return float
         */
        static float bytesToFloat(const unsigned char*);

        /**
         * @brief Calls handler methods depending on the proveded message and assumes first element is op code.
         * @param buffer
         */
        void handleRequest(unsigned char*);

        /**
         * @brief Associates the length of each message w.r. to the op_code provided.
         * @param op_code
         * @return int
         */
        static int getMessageLength(unsigned char);

        /**
         * @brief Adds start character and CRC to comm array, then adds it to the outgoing messages.
         * @param buffer
         * @param n
         */
        void sendComm(unsigned char*, int);

        /**
         * @brief Adds start character and CRC to comm array, then adds it to the outgoing messages.
         * @param buffer
         * @param n
         */
        void sendComm1(unsigned char*, int);

        /**
         * @brief Calculate a xor crc with a 341 generator.
         *
         * @param buffer
         * @param n
         * @return unsigned char
         */
        static unsigned char calculateCRC(unsigned char*,int);

        /**
         * @brief Valid crcs will produce 0.
         * @param buffer
         * @param n
         * @return int
         */
        static int checkCRC(unsigned char*,int);

        /*POWER CYCLE PATHWAY*/

        /**
         * @brief Queues a power cycle response into the TX Buffer.
         */
        void queuePowerCycleResponse();

        /**
         * @brief Handles power cycle request parsed from the MCU.
         */
        void handlePowerCycle();

        /*GET SETTINGS PATHWAY*/

        /**
         * @brief Queues get setting request into the TX Buffer.
         */
        void queueGetSettingsRequest();

        /**
         * @brief Handles get setting response parsed from the MCU.
         */
        void handleGetSettingsResponse(unsigned char*);

        /*ENABLE NOTIFICATION PATHWAY*/

        /**
         * @brief Queues enable notification request into the TX Buffer.
         */
        void queueNotificationRequest(unsigned char);

        /**
         * @brief Handles enable notification response parsed from the MCU.
         */
        void handleEnabledNotifications();

        /*GET OP MODES PATHWAY*/

        /**
         * @brief Emits signal to backend program with the list of modes enabled and disabled.
         * @param buffer
         */
        void handleGetModesResponse(unsigned char*);

        /*GET SUBSYSTEM STATUS PATHWAY*/

        /**
         * @brief Emits subsystem states change received signal with a
         * @note QVector<unsigned char> representing the subsystem states.
         * @param buffer
         */
        void handleGetSubsystemStates(unsigned char* buffer); /* handle subsystem state changed */

        /* SYSTEM VERSION PATHWAY */

        /**
         * @brief Handles system version response and emits signal with the system version to the backend program.
         * @param buffer
         */
        void handleSystemVersionResponse(unsigned char* buffer); /* handle system version response */

        /*SET SETTINGS PATHWAY*/

        /**
         * @brief Queues a set settings request into the TX Buffer.
         */
        void setSettings(const QVector<int>&);

        /**
         * @brief Handles set settings response parsed from the MCU.
         */
        void handleSetResponse();

        /* GET MEASURED PATHWAY*/

        /**
         * @brief Handles sensore measurement responses from the system controller.
         * @details Sends signal to backend with the measurement and specific signals for lowest and highest voltage calibration values, the sensor values, and DPR.
         * @param buffer
         */
        void handleGetSensorMeasurementResponse(unsigned char* buffer);

        /*CLEAR WARNING PATHWAY*/

        /**
         * @brief Handles top warning to be clears and sends signal to backend program.
         * @param buffer
         */
        void handleClearWarning(unsigned char*);

        /*DISPLAY OP MODE REQUEST PATHWAY*/

        /**
         * @brief Handles responses received from the system controller in regards to mode commands and emits a signal with the mode id and mode value to the backend program.
         * @param buffer
         */
        void handleModeResponse(unsigned char*); //mode set from display controller

        /*DISPLAY OP MODE RESPONSE PATHWAY*/

        /**
         * @brief Handles requests to set modes from the system controller and emit signal to the backend with the mode id and the mode value.
         * @note Queues mode confirmation to TX Buffer.
         * @param buffer
         */
        void handleModeRequest(unsigned char*); //mode set from system controller

        /**
         * @brief Queues and adds a mode confirmation response to the TX Buffer.
         * @param modeID
         * @param value
         */
        void queueModeResponse(unsigned char, unsigned char); //respond to system controller mode request

        /*NOTIFICATION PATHWAY*/

        /**
         * @brief Receives notifications from the system controller.
         * @details Confirms that notifications have been successfully enabled, thus preventing further unecessary requests.
         *          Queues response to inform MCU that the notification has been successfully received,
         *          and then populates QThread-compatible QVectors with the settings and calculations derived from the notification contents.
         *          Handles warnings on the warning section of the notification vector and emit siganl to backend program.
         * @param buffer
         * @note Handles silence time as well.
         */
        void handleNotification(unsigned char*);

        /**
         * @brief Handles warnings from notifications.
         * @details First populates a QVector<unsigned char> with the warning information,
         *          then calls findMostSevereWarning to find the ID of the most severe warning and assigns the returned value to int first_warning,
         *          then calls numberActiveWarnings to find the number of active warnings and assigns the returned value to int new_num_active_warnings,
         *          if the most severe warning id or the number of active warnings has changed since the last notification, the member variables are updated and a
         *          warningUpdateSignal is emitted with the new values.
         * @note The buffer is a pointer to the first warning element in a notification.
         * @param buffer
         */
        void handleWarnings(const unsigned char*);

        /**
         * @brief Adds a notification response to the outgoing queue when a notification is received.
         */
        void queueNotificationResponse();

        /*SUBSYSTEM STATES PATHWAY*/

        /**
         * @brief Calls queueSubsystemStateChangedResposne and handleGetSubsystemStates as they are the same request on the Display Controller end.
         * @param buffer
         */
        void handleSubsystemStateChange(unsigned char* buffer);

        /**
         * @brief Queues subsystem state changed response to TX Buffer.
         */
        void queueSubsystemStateChangedResponse();

        /*VENTILATION PATHWAY*/

        /**
         * @brief Queues a ventilation status response and emits a ventilation status signal to the backend.
         * @param buffer
         */
        void handleVentilationStatusUpdate(unsigned char *buffer); /* handle ventilation status update */

        /**
         * @brief Queues ventilation status response into TX Buffer.
         */
        void queueVentilationStatusResponse();

        /*HMI BUTTON PUSH PATHWAY*/

        /**
         * @brief Calls queueHMIButtonPushResponse and emits HMI Button Pushed signal with the ID of the HMI button.
         * @param buffer
         */
        void handleHMIButtonPush(unsigned char *);

        /**
         * @brief Queues response into TX Buffer to HMI Button Push communications from the system controller.
         * @param id
         */
        void queueHMIButtonPushResponse(unsigned char);

        /*SHUTDOWN PATHWAY*/

        /**
         * @brief Queues response to the shutdown initiated.
         */
        void queueInitPowerdownOk(); /* Power Down */

        /**
         * @brief Emits an initPowerdown signal to the backend. This is used when the user presses the powerdown button.
         */
        void handleInitPowerdown();

        /*SHUTDOWN CONFIRM PATHWAY*/

        /**
         * @brief Emits a powerdownConfirmed signal with a confirm/cancel flag.
         * @param buffer
         */
        void handleInitPowerdownCommandOK(unsigned char* buffer);

        /* SERVICE CALIBRATION VALUES */

        /**
         * @brief Emits calibration value request.
         *
         */
        void handleServiceCalibrationRequest();

        /*DRIVING PRESSURE REGULATOR SET CAL VAL*/

        /**
         * @brief Retrives DPR state change confirm from system controller and emits signal to backend to confirm DPR state.
         * @param buffer
         */
        void handleDPRValSetResponse(unsigned char *);

        /* ZERO PRESSURE SENSOR PATHWAY */

        /**
         * @brief Emits sensor zeroed response to backend program.
         * @param buffer
         */
        void handleSensorZeroResponse(unsigned char* buffer);

        /**
         * @brief Receives service notifications from the system controller.
         * @param buffer
         */
        void handleServiceNotifications(unsigned char* buffer);
};

/** @} */

