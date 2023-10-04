#include <QApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QVector>

#include "src/backend.h"
#include "src/communication/api.h"
#include "src/gpio/knob.h"
#include "src/state_manager.h"
#include "src/models/pneumatic_settings.h"
#include "src/models/settings.h"
#include "src/logger/log_manager.h"
#include "src/logger/preset_manager.h"
#include "src/logger/brightness_manager.h"
#include "src/models/QML_IDS.h"
#include "src/models/QML_notifications.h"
#include "src/models/QML_settings.h"
#include "src/logger/o2_cal_manager.h"
#include "src/logger/dpr_manager.h"
#include "src/logger/part_manager.h"
#include "src/logger/zero_manager.h"
#include "src/logger/maintenance_manager.h"
#include "src/logger/contact_manager.h"
#include "src/logger/version_manager.h"
#include "src/logger/passcode_manager.h"
#include "src/logger/time_manager.h"

/**
 * @addtogroup main
 * @brief Main application where everything begins.
 * @{
 */

/**
 * @file main.cpp
 * @brief Main for main window: @ref HomeWindow.qml
 */

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    //This initiates the logging of qDebug messages to a file.
    //Note the file /home/root/logs does not exist, logs will not be saved.
    qInstallMessageHandler(log);

    //This initiates the application
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //Objects that communicate with the QML code
    //The time manager manages the current date, time, and time zone of the device. Passes data to QML, and saves data to CSV file.
    TimeManager timeManager;
    //With CSV file for time created and CSV data stored, service and warning logs will be generated.
    startLogs();
    //State Manager holds the state of the device, ie. set points and modes
    //Note that the state manager states are not set directly by the QML. They are set by the backend
    StateManager stateManager;
    //Warning Manager holds the warnings to display.
    WarningManager warningManager;
    //API acts as the middle man between the system controller and the display controller.
    API api(QString("/dev/ttyUSB0"), 115200);
    //O2 Calibration Manager manages the o2 calibration values. It passes the most recent O2 cal vals to the QML, and saves cal vals to a csv file.
    O2CalManager o2CalManager;
    //DPR Manager manages the dpr values. It passes the most recent DPR vals (high or low), and saves DPR vals to a csv file.
    DPRManager dprManager;
    //Zero Manager manages the PIP and SP value for zero calibration. It passes the most recent vals to the QML, and saves cal vals to csv files.
    ZeroManager zeroManager;
    //Part Manager manages the operating times for parts.
    PartManager partManager;
    //The backend acts as the middle man between the QML and the calibration manager, the state manager, the warning manager, and zero manager. It also sends and recieves signals from the API
    Backend backend(&stateManager, &warningManager, &o2CalManager, &zeroManager, &partManager, &dprManager);
    //The preset manager manages the presets. It passes presets to the QML, and saves presets to a CSV file.
    PresetManager presetManager;
    //The brightness manager manages the brightness of the display. Brightness in Linux is represented by a brightness file in the file system
    BrightnessManager brightnessManager;
    //The passcode manager manages the passcode needed for preset page and service page. Passes passcodes to QML, and saves passcode to CSV file.
    PasscodeManager passcodeManager;
    //The maintenance manager manages the services dates for when technician arrives to fix device.
    MaintenanceManager maintenanceManager;
    //The contact manager manages the contact information for the service company and the sales company.
    ContactManager contactManager;
    //The version manager manages the HMI version and the serial number on the device.
    VersionManager versionManager;

    //These are the settings used by the QML for constant values such as minimum, maximum, step,  and so on.
    DrivingPressure dp1((int)SettingIds::DRIVING_PRESSURE_1);
    DrivingPressure dp2((int)SettingIds::DRIVING_PRESSURE_2);
    Rate rate1((int)SettingIds::RATE_1);
    Rate rate2((int)SettingIds::RATE_2);
    InspiratoryTime it1((int)SettingIds::INSPIRATORY_TIME_1);
    InspiratoryTime it2((int)SettingIds::INSPIRATORY_TIME_2);
    StackingPressure sp1((int)SettingIds::STACKING_PRESSURE_1);
    StackingPressure sp2((int)SettingIds::STACKING_PRESSURE_2);
    O2 o2((int)SettingIds::O2);
    PIP pip((int)SettingIds::PIP);
    AuxFlow aux((int)SettingIds::AUX_FLOW);
    Humidity hum1((int)SettingIds::HUM_1);
    Humidity hum2((int)SettingIds::HUM_2);
    Humidity humaux((int)SettingIds::HUM_AUX);
    ETCO2Rate etco2Rate((int)SettingIds::ETCO2_RATE);
    ETCO2IT etco2IT((int)SettingIds::ETCO2_IT);
    ETCO2Breaths etco2Breaths((int)SettingIds::ETCO2_NUM_BREATHS);
    ETCO2DP etco2DP((int)SettingIds::ETCO2_DP);
    LaserO2 laserO2((int)SettingIds::LASER_O2);
    Volume volume((int)SettingIds::VOLUME);

    QObject::connect(&api, &API::resendMessagesSignal,
                     &backend, &Backend::resendMessagesSlot,
                     Qt::QueuedConnection);

    //The following define the connections for the various signals
    //SET
    //This connects the setting request from the QML to the API to send the setting to the system controller
    QObject::connect(&backend, &Backend::sendSettingSignal,
            &api, &API::sendSettingsSlot,
                     Qt::QueuedConnection);
    //This connects the setting confirmation from the API to the backend to stop sending setting requests
    QObject::connect(&api, &API::settingsConfirmed,
                     &backend, &Backend::settingsConfirmed,
                              Qt::QueuedConnection);

    //MODES
    //Modes set by user
    //This connects the setting request from the QML to the API to send the mode request to the system controller
    QObject::connect(&backend, &Backend::setModeSignal,
                     &api, &API::sendModeSlot,
                     Qt::QueuedConnection);
    //This connected the mode set confirmation from the API to the backend to stop sending mode requests
    QObject::connect(&api, &API::modeSetSignal,
                     &backend, &Backend::modeConfirmed,
                     Qt::QueuedConnection);

    //Modes set by system controller
    //This connects the api to the backend object to set the state for the various modes when the system controller initiates a mode state change
    QObject::connect(&api, &API::setModeSignal,
                     &backend, &Backend::modeRequested,
                     Qt::QueuedConnection);

    //Get Modes
    //This connects the backend mode request to the API to initiate getting the modes from the system controller. This is used during start up
    QObject::connect(&backend,&Backend::getModesSignal,
                     &api, &API::getModesSlot,
                     Qt::QueuedConnection);
    //This connects the API get mode response to the backed to complete getting the modes from the system controller. This is used during start up
    QObject::connect(&api,&API::sendModesSignal,
                     &backend, &Backend::receiveModes);


    // GET SETTINGS
    //This connects the backend setting request to the API to initiate getting the settings from the system controller. This is used during start up.
    QObject::connect(&backend, &Backend::sendGetSettingsSignal,
            &api, &API::sendGetSettingsSlot,
                     Qt::QueuedConnection);
    //This connects the API get setting response to complete setting all settings from the system controller. This is used during start up.
    QObject::connect(&api, &API::updateSettingsSignal,
            &backend, &Backend::receiveGetSettingsSlot,
                Qt::QueuedConnection);

    //GET MEASUREMENTS
    //This is used to initiate getting sensor measurements from the system controller
    QObject::connect(&backend, &Backend::sendGetSensorMeasurementSignal,
                     &api, &API::getMeasured,
                     Qt::QueuedConnection);
    //This is used to handle receiving sensor measurements from the system controller
    QObject::connect(&api, &API::receiveMeasuredValue,
                     &backend, &Backend::receiveSensorMeasurements,
                     Qt::QueuedConnection);
    //This is used to handle receiving mV sensor measurements from the system controller
    QObject::connect(&api, &API::receiveVoltValue,
                     &backend, &Backend::receiveVolt,
                     Qt::QueuedConnection);

    //SERVICE NOTIFICATION
    QObject::connect(&api, &API::serviceNotificationUpdateSignal,
                     &backend, &Backend::serviceNotificationUpdateSlot,
                     Qt::QueuedConnection);

    //This is used to handle receiving the water sensor detection value from the system controller
    QObject::connect(&api, &API::receiveWaterSensorValue,
                     &backend, &Backend::receiveWaterSensor,
                     Qt::QueuedConnection);

    //This is used to set the setting for Driving Pressure as a proper float value.
    QObject::connect(&backend, &Backend::signalTempDP,
                     &api, &API::slotTempDP,
                     Qt::QueuedConnection);

    // NOTIFICATIONS
    //This is used to request notifications from the system controller
    QObject::connect(&backend, &Backend::sendNotificationEnableSignal,
            &api, &API::sendNotificationSlot,
                     Qt::QueuedConnection);
    QObject::connect(&api, &API::enableNotificationSignal,
                     &backend, &Backend::enableNotificationsSlot,
                     Qt::QueuedConnection);

    //This is used to handle notifications from the system controller
    QObject::connect(&api, &API::notificationUpdateSignal,
            &backend, &Backend::notificationUpdateSlot,
            Qt::QueuedConnection);

    //WARNINGS
    //This is used to send notifications from the API to the backend object
    QObject::connect(&api, &API::warningUpdateSignal,
                     &backend, &Backend::warningUpdateSlot,
                     Qt::QueuedConnection);
    //This is used to send warning clear requests from the QML to the system controller
    QObject::connect(&backend, &Backend::warningClearSignal,
                     &api, &API::clearWarningSlot,
                     Qt::QueuedConnection);
    //This is used to confirm that a warning has been cleared so as to stop sending warning clear requests to the system controller
    QObject::connect(&api, &API::clearWarningSignal,
                     &backend, &Backend::clearAlarmSlot,
                     Qt::QueuedConnection);

    //PRESSURE SENSOR ZERO
    //This is used to send a pressure sensor zero request to the system controller
    QObject::connect(&backend, &Backend::zeroSensor,
                     &api, &API::zeroSensor,
                     Qt::QueuedConnection);
    //This is used to stop sending pressure sensor zero requests to the system controller
    QObject::connect(&api, &API::sensorZeroed,
                     &backend, &Backend::receiveSensorZeroed,
                     Qt::QueuedConnection);

    //DRIVING PRESSURE REGULATOR
    //This connects the Set DPR VAL request from the QML to the API to update the current calibration to the system controller
    QObject::connect(&backend, &Backend::signalDPRValue,
                     &api, &API::slotDPRValue,
                     Qt::QueuedConnection);
    //This connects the DPR VAL Set response from the API to the backend to change calibration from high DPR, low DPR, air regulator and o2 regulator.
    QObject::connect(&api, &API::signalDPRValue,
                     &backend, &Backend::slotDPRValue,
                     Qt::QueuedConnection);

    QObject::connect(&backend, &Backend::signalCalibrationMessages,
                     &api, &API::slotCalibrationMessages,
                     Qt::QueuedConnection);


    //SUBSYSTEM STATES
    //This is used to get the subsystem states on startup of the NVENT Vita
    QObject::connect(&backend, &Backend::getSubsystemStates,
                     &api, &API::getSubsystemStates,
                     Qt::QueuedConnection);
    //This is used to update subsystem states as they are updated by the system controller
    QObject::connect(&api, &API::subsystemStatesChangeReceived,
                     &backend, &Backend::receiveSubsystemStates,
                     Qt::QueuedConnection);

    //SOFTWARE VERSION
    //This is used to receive the system version from the system controller
    QObject::connect(&api, &API::systemVersion,
                     &backend, &Backend::receiveSystemVersion,
                     Qt::QueuedConnection);
    //This is used to request the system version from the system controller
    QObject::connect(&backend, &Backend::getSystemVersionFromSC,
                     &api, &API::queryVersion,
                     Qt::QueuedConnection);

    //HMI BUTTONS
    //This is used to receive HMI button pushed from the system controller.
    //This is used for logging and for reminders to unlock the screen during screen lock mode
    QObject::connect(&api, &API::HMIButtonPushReceived,
                     &backend, &Backend::receiveHMIButtonPress,
                     Qt::QueuedConnection);

    //GPIO
    //The knob sends increments(+/-1) and button push signals. This is used directly by the API.
    Knob knob{9, 57, 55};\
// These are the calculations for figuring out what the pin numbers are.
// There's further description of how the knob works in the knob related files
//   (b-1) * 32 + nn
//    b_b=2
//    b_nn=25 // b is 57
//    a_b=1
//    a_nn=9 // a is 9
//    switch_b=2
//    switch_nn=23 // switch is 55

    //This allows the developer to send QML signals with QVectors of floats.
    qRegisterMetaType<QVector<float> >("QVector<float>");

    //SHUTDOWN
    //This initiates the powerdown process when the signal is sent to the API. It is used to request user confirmation of shutdown
    QObject::connect(&api, &API::initPowerdown,
                     &backend, &Backend::powerdownInitiated);
    //This is used to confirm or cancel shutdown based on user input
    QObject::connect(&backend, &Backend::powerDownCommand,
                     &api, &API::confirmPowerdown);
    //This is used to stop sending shutdown requests to the system controller, and to initiate a shutdown of the display
    QObject::connect(&api, &API::powerdownConfirmed,
                     &backend, &Backend::powerdownConfirmed);

    //This is used to listen to the knob or not. (used when the display controller is using the knob to adjust some parameter)
    QObject::connect(&backend, &Backend::listenToKnob,
                     &knob, &Knob::listen);
    //This is used to change the saved ventilation state. This is generally used to disallow functions that cannot be used while the system is ventilating.
    QObject::connect(&api, &API::ventilationStateChangeReceived,
                     &backend, &Backend::receiveVentilationStateChange);

    QObject::connect(&warningManager, &WarningManager::o2CalibrationSignal,
                     &o2CalManager, &O2CalManager::calibrationState);

    //These are used to expose certain enum classes to the QML
    //This is the setting IDs and Mode Ids
    IDs::declareQML();
    //This is the Sensor IDs
    SensorIDs::declareQML();
    //These are the notification indexes, ie where the PIP, SP, O2 measurements are in the array passed to the QML when notifications are received.
    NotificationIndex::declareQML();
    //These are the settings threshold indexes, ie where PIP, SP, O2, etc. measurements are in array passed to the QML when thresholds are set.
    SettingIndex::declareQML();

    //These connect the various objects used to communicate with the QML to the QML
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("state_manager", &stateManager);
    engine.rootContext()->setContextProperty("warning_manager", &warningManager);
    engine.rootContext()->setContextProperty("preset_manager", &presetManager);
    engine.rootContext()->setContextProperty("brightness_manager", &brightnessManager);
    engine.rootContext()->setContextProperty("o2CalManager", &o2CalManager);
    engine.rootContext()->setContextProperty("dprManager", &dprManager);
    engine.rootContext()->setContextProperty("zero_manager", &zeroManager);
    engine.rootContext()->setContextProperty("passcode_manager", &passcodeManager);
    engine.rootContext()->setContextProperty("part_manager", &partManager);
    engine.rootContext()->setContextProperty("time_manager", &timeManager);
    engine.rootContext()->setContextProperty("maintenance_manager", &maintenanceManager);
    engine.rootContext()->setContextProperty("contact_manager", &contactManager);
    engine.rootContext()->setContextProperty("version_manager", &versionManager);

    engine.rootContext()->setContextProperty("driving_pressure_1", &dp1);
    engine.rootContext()->setContextProperty("driving_pressure_2", &dp2);
    engine.rootContext()->setContextProperty("rate_1", &rate1);
    engine.rootContext()->setContextProperty("rate_2", &rate2);
    engine.rootContext()->setContextProperty("inspiratory_time_1", &it1);
    engine.rootContext()->setContextProperty("inspiratory_time_2", &it2);
    engine.rootContext()->setContextProperty("stacking_pressure_1", &sp1);
    engine.rootContext()->setContextProperty("stacking_pressure_2", &sp2);
    engine.rootContext()->setContextProperty("oxygen", &o2);
    engine.rootContext()->setContextProperty("pip", &pip);
    engine.rootContext()->setContextProperty("aux_flow", &aux);
    engine.rootContext()->setContextProperty("humidity_1", &hum1);
    engine.rootContext()->setContextProperty("humidity_2", &hum2);
    engine.rootContext()->setContextProperty("humidity_aux", &humaux);
    engine.rootContext()->setContextProperty("etco2_rate", &etco2Rate);
    engine.rootContext()->setContextProperty("etco2_inpiratory_time", &etco2IT);
    engine.rootContext()->setContextProperty("etco2_num_breaths", &etco2Breaths);
    engine.rootContext()->setContextProperty("laser_o2", &laserO2);
    engine.rootContext()->setContextProperty("etco2_driving_pressure", &etco2DP);
    engine.rootContext()->setContextProperty("volume", &volume);

    engine.rootContext()->setContextProperty("knob", &knob);

    backend.init();

    //This loads the application, startin from the home window
    engine.load(QUrl("qrc:/qml/HomeWindow.qml"));

    //This starts the API thread
    api.start();

    return app.exec();
}

/** @} */
