#include <QtDebug>

#include "backend.h"
#include <stdio.h>
#include <QDebug>
#include <QFile>
#include <QTime>
#include <QCoreApplication>
#include <QStorageInfo>


Backend::Backend(StateManager* stateManager, WarningManager* warningManager, O2CalManager* o2CalManager, ZeroManager* zeroManager, PartManager* partManager, DPRManager* dprManager, QObject *parent)
    : QObject(parent)
{
    initResendFunctionPointers();

    m_stateManager = stateManager;
    m_warningManager = warningManager;
    m_o2CalManager = o2CalManager;
    m_zeroManager = zeroManager;
    m_partManager = partManager;
    m_dprManager = dprManager;

    m_dehumidication_timer = new QTimer(this);
    m_dehumidication_timer->setInterval(1000);
    m_dehumidication_timer->setSingleShot(false);
    connect(m_dehumidication_timer, &QTimer::timeout, this, &Backend::sendDehumidityValue);
}

void Backend::initResendFunctionPointers()
{
    m_resend_functions[(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST] = &Backend::getSettings;
    m_resend_functions[(int)txOpCodes::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST] = &Backend::enableNotifications;
    m_resend_functions[(int)txOpCodes::DISPLAY_GET_OP_MODES_REQUEST] = &Backend::getModes;
    m_resend_functions[(int)txOpCodes::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST] = &Backend::sendGetSubsystems;
    m_resend_functions[(int)txOpCodes::DISPLAY_GET_SYSTEM_VERSION_REQUEST] = &Backend::sendGetSystemVersion;
    m_resend_functions[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = &Backend::sendSettingsUpdate;
    m_resend_functions[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = &Backend::sendGetMeasured;
    m_resend_functions[(int)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST] = &Backend::sendClearAlarm;
    m_resend_functions[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] = &Backend::sendModeCommand;
    m_resend_functions[(int)txOpCodes::DISPLAY_SHUTDOWN_CONFIRM_SEND] = &Backend::sendPowerdownCommand;
    m_resend_functions[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = &Backend::sendDPRValue;
    m_resend_functions[(int)txOpCodes::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST] = &Backend::sendZeroSensor;
}

void Backend::init()
{
    initGetSettings();
    initEnableNotifications();
    initGetModes();
    initGetSubsystemStates();
    initGetSystemVersion();
}

/*----------------------RESEND MESSAGES-----------------------------*/

void Backend::resendMessagesSlot()
{
    resendMessages();
}

void Backend::resendMessages()
{
    for (int i = 0; i< NUM_API; i++)
    {
        if(m_message_flags[i] == 1 && this->m_resend_functions[i] != nullptr)
        {
            (this->*m_resend_functions[i])();
        }
    }
}

void Backend::setUpIpAddress(){
    m_stateManager->setupNetwork();
}

/*________________________LOG MESSAGES______________________________*/

/**
 * @brief msdelay Start loop to delay running progress
 * @param millisecondsWait
 */
inline void msdelay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void Backend::saveLogsToDrive()
{
    msdelay(60);

    QString serviceDirName = dirName + "/NVENT_FILES/NV_Vita_events";
    QString warningDirName = dirName + "/NVENT_FILES/NV_Vita_warnings";

    if (!exportDirectory("/media/NVENT_FILES/NV_Vita_events",serviceDirName))
    {
        //Sends signal to QML if service logs failed to be exported.
        saveLogStatusSignal(0);
        return;
    }
    if (!exportDirectory("/media/NVENT_FILES/NV_Vita_warnings",warningDirName))
    {
        //Sends signal to QML if warning logs failed to be exported.
        saveLogStatusSignal(0);
        return;
    }
    //Sends signal to QML if service logs and warning logs were exported successfully.
    saveLogStatusSignal(1);
}

void Backend::driveConnected()
{
    msdelay(100);
    dirName = findPort();
    if (dirName == "")
    {
        //Sends signal to QML if USB drive is not mounted.
        driveConnection(0);
        return;
    }
    //Sends signal to QML if USB Drive is mounted and if directories exist.
    driveConnection(1);
}

void Backend::driveDisconnected()
{
    msdelay(100);
    emit driveDisconnection(!system(m_eject_command_line.toStdString().c_str()));
}

QString Backend::findPort()
{
    QDirIterator it("/run/media", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        if (it.fileName() != "" && it.fileName() != "." && it.fileName() != ".." && it.fileName() != "mmcblk0p1" && it.fileName() != "mmcblk0p2" && it.fileName() != "mmcblk1p1")
        {
            if (QDir("/run/media/" + it.fileName()).exists() && QFile("/dev/" + it.fileName()).exists())
            {
                m_eject_command_line = "eject /dev/" + it.fileName();
                return "/run/media/" + it.fileName();
            }
        }
        it.next();
    }
    return "";
}

bool Backend::exportDirectory(QString src, QString dst)
{
    QDir sourceDir(src);
    QDir destDir(dst);

    if (!destDir.exists())
        destDir.mkpath(".");

    QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::NoDot | QDir::NoDotAndDotDot);

    foreach (const QString& fileName, fileNames) {

                if (copyProgressing)
                {
                    copyProgressing = 0;
                    return false;
                }

                QString srcFilePath = sourceDir.filePath(fileName);
                QString destFilePath = destDir.filePath(fileName);

                if (!QFile::exists(destFilePath))
                {
                    if (QFile::copy(srcFilePath, destFilePath)) {
                        m_stateManager->incrementSaveDataProgress();
                        msdelay(5);
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    m_stateManager->incrementSaveDataProgress();
                }
            }
    return true;
}

void Backend::updateFileCount()
{
    QDir serviceDir("/media/NVENT_FILES/NV_Vita_events");
    QDir warningDir("/media/NVENT_FILES/NV_Vita_warnings");

    m_stateManager->setTotalFiles(serviceDir.count() + warningDir.count() - 6);
    m_stateManager->setSaveDataProgress(0);
}

void Backend::logsState(bool value)
{
    if (value)
    {
        qInfo() << "NVENT" << "," << "SERVICE" << "," << "Service Events Activated.";
    }
    else
    {
        qInfo() << "NVENT" << "," << "SERVICE" << "," << "Service Events Deactivated.";
    }
}

void Backend::stopProgress()
{
    copyProgressing = 1;
}

/*-----------------------DEHUMIDIFICATION PROGRESS-------------------------*/

void Backend::initDehumidification(unsigned char val)
{
    m_dehumidification_seconds = 120; //0;
    if (val)
    {
        m_dehumidication_timer->start();
    }
    else
    {
        m_dehumidication_timer->stop();
    }
}

void Backend::sendDehumidityValue()
{
    if (m_dehumidification_seconds > 0) m_dehumidification_seconds = m_dehumidification_seconds - 1;
    emit dehumidificationTime(m_dehumidification_seconds);
}

void Backend::serviceAlarmSlot(unsigned char state)
{
    m_warningManager->updateServiceAlarm(state);
}

/*------------------------START UP PATHWAY--------------------------*/

void Backend::checkStartupComplete()
{
    unsigned char startupInProgress = 0;
    for(int i = 0; i< NUM_API; i++)
    {
        startupInProgress = startupInProgress | m_message_flags[i];
    }
    if(! startupInProgress) m_stateManager->setStartupComplete();
}

/*------------------------GET SETTINGS PATHWAY----------------------*/

void Backend::getSettings()
{
    emit sendGetSettingsSignal();
}

void Backend::initGetSettings()
{
    getSettings();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST] = 1;
}

void Backend::receiveGetSettingsSlot(QVector<int> setting_vals)
{
    setting_vals = updateVectorHumidity(setting_vals);

    m_stateManager->setSettings(setting_vals);
    m_warningManager->setStateValues(setting_vals);

    if(m_message_flags[(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST])
    {
        m_message_flags[(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST] = 0;

        QString logData = "";
        for (int i = 0; i < NUM_SETTINGS - 1; i++)
        {
            logData.append(QString::fromStdString( settingNameMap.at(i) ) + " " + QString::number(setting_vals.at(i)) + " ; ");
        }

        logData.append(QString::fromStdString( settingNameMap.at(NUM_SETTINGS - 1) ) + " - " + QString::number(setting_vals.at(NUM_SETTINGS - 1)));
        qInfo() << "NVENT" << "," << "RESTORE SETTINGS" << "," << logData;
    }

    if (m_stateManager->getSettingValue((unsigned char)SettingIds::HUM_1) != m_stateManager->getSettingValue((unsigned char)SettingIds::HUM_AUX))
    {
        m_stateManager->setSeparateHumidity(1);
    }
}

QVector<int> Backend::updateVectorHumidity(QVector<int> setting_vals)
{
    for (int i = 0; i < setting_vals.size(); i++)
    {
        if (i == (int)SettingIds::HUM_1 || i == (int)SettingIds::HUM_AUX)
        {
            setting_vals.replace(i,getHumidityLevel(setting_vals.at(i)));
        }
    }
    return setting_vals;
}

int Backend::getHumidityLevel(int value)
{
    if (value == 100)
    {
        return 4;
    }
    else if (value == 70)
    {
        return 3;
    }
    else if (value == 50)
    {
        return 2;
    }
    else if (value == 30)
    {
        return 1;
    }
    return 0;

}

/*------------------------ENABLE NOTIFICATION PATHWAY---------------*/

void Backend::initEnableNotifications()
{
    enableNotifications();
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST] = 1;
}

void Backend::enableNotifications()
{
    emit sendNotificationEnableSignal(1);
}

void Backend::enableNotificationsSlot()
{
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST] = 0;
}

/*------------------------GET OP MODES PATHWAY---------------------*/

void Backend::initGetModes()
{
    getModes();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_OP_MODES_REQUEST] = 1;
}

void Backend::receiveModes(QVector<int> modes)
{
    if (modes.length() == NUM_MODES && m_message_flags[(int)txOpCodes::DISPLAY_GET_OP_MODES_REQUEST])
    {
        for (int i = 0; i < NUM_MODES; i ++)
        {
            //Reset modes that weren't changed by knob.
            if (i != (int) ModeIDs::LISTENING_KNOB)
            {
                if (i == (int) ModeIDs::LASER_MODE)
                {
                    m_stateManager->setMode(i, modes.at(i), 0);
                }
                else
                {
                    m_stateManager->setMode(i, modes.at(i), 1);
                }
            }
            //Reset modes that were changed by knob.
            else if(modes[(int) ModeIDs::LISTENING_KNOB] != m_stateManager->listeningToKnob())
            {
                setMode((int) ModeIDs::LISTENING_KNOB, m_stateManager->listeningToKnob());
            }
        }
        //Initializes flag the confirm restored modes.
        m_message_flags[(int)txOpCodes::DISPLAY_GET_OP_MODES_REQUEST] = 0;

        //Logs which modes were restored in event files
        QString logData = "";
        for (int i = 0; i < NUM_MODES - 1; i++)
        {
            logData.append(QString::fromStdString( modeNameMap.at(i) ) + " " + QString::number(modes.at(i)) + " ; ");
        }
        logData.append(QString::fromStdString( modeNameMap.at(NUM_MODES - 1) ) + " - " + QString::number(modes.at(NUM_MODES - 1)));
        qInfo() << "NVENT" << "," << "RESTORE MODES" << "," << logData;
    }
}

void Backend::getModes()
{
    emit getModesSignal();
}

/*------------------------GET SUBSYSTEM STATUS PATHWAY-----------------*/

void Backend::initGetSubsystemStates()
{
    sendGetSubsystems();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST] = 1;
}

void Backend::receiveSubsystemStates(QVector<unsigned char> states)
{
    m_stateManager->setSubsystemStates(states);
    if (!states.at(0) && !m_stateManager->getEtco2ButtonState() && et_button_on_startup)
    {
        et_button_on_startup = 0;
        receiveVentilationStateChange(1);
    }
    m_message_flags[(int)txOpCodes::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST] = 0;
}

void Backend::sendGetSubsystems()
{
    emit getSubsystemStates();
}

/*------------------------SYSTEM VERSION PATHWAY------------------------*/

void Backend::initGetSystemVersion()
{
    sendGetSystemVersion();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_SYSTEM_VERSION_REQUEST] = 1;
}

void Backend::sendGetSystemVersion()
{
    emit getSystemVersionFromSC();
}

void Backend::receiveSystemVersion(unsigned char major, unsigned char minor, unsigned char patch)
{
    QString versionString = "v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch);
    m_message_flags[(int)txOpCodes::DISPLAY_GET_SYSTEM_VERSION_REQUEST] = 0;
    m_stateManager->setSystemVersion(versionString);
    qInfo() << "NVENT" << "," << "SYSTEM VERSION" << "," << versionString;
    qInfo() << "NVENT" << "," << "DISPLAY VERSION" << "," << m_stateManager->getDisplaySoftwareVersion();
}

/*------------------------SET SETTINGS PATHWAY------------------------*/

void Backend::setPneumaticSettings(QVector<int> settings)
{
    //Starts screen lock mode
    m_stateManager->setPresetComplete(0);
    setScreenLockModes(1);

    //Updates current setting values for state object and warnings object
    m_stateManager->setPneumaticSettings(settings);
    m_warningManager->setStateValues(settings);


    settingsVector = {};
    for(unsigned char i = 0; i< NUM_SETTINGS; i++)
    {
        if ( i == (unsigned char)SettingIds::HUM_1 || i == (unsigned char)SettingIds::HUM_AUX)
        {
            settingsVector.append(getHumidityPercentage(m_stateManager->getSettingValue(i)));
        }
        else
        {
            settingsVector.append(m_stateManager->getSettingValue(i));
        }
    }

    //Writes string for service log
    QString msg = "";
    for (int i = 0; i< NUM_SETTINGS - 1; i ++)
    {
        msg += QString::fromStdString(settingNameMap.at(i)) + " ";
        msg += QString::number(m_stateManager->getSettingValue(i)) + "; ";
    }
    msg += QString::fromStdString(settingNameMap.at(NUM_SETTINGS - 1 )) + " ";

    sendSettingsUpdate();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;

    qInfo() << "NVENT " << "," << "PRESET" << "," << "IMPLEMENT" << msg;
}

void Backend::setScreenLockModes(unsigned char value)
{
    m_stateManager->setMode((unsigned char) ModeIDs::SCREEN_LOCK_MODE, value, 2);
    m_send_modes[(unsigned char) ModeIDs::SCREEN_LOCK_MODE] = 1;

    m_stateManager->setMode((unsigned char) ModeIDs::SCREEN_LOCK_TOUCHED_MODE, value, 2);
    m_send_modes[(unsigned char) ModeIDs::SCREEN_LOCK_TOUCHED_MODE] = 1;

    sendModeCommand();
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] = 1;

    qInfo() << "NVENT" << "," << "MODE" << "," << "REQUEST" << QString::fromStdString(modeNameMap.at((unsigned char) ModeIDs::SCREEN_LOCK_MODE)) << (value ? "ENABLED" : "DISABLED");
    qInfo() << "NVENT" << "," << "MODE" << "," << "REQUEST" << QString::fromStdString(modeNameMap.at((unsigned char) ModeIDs::SCREEN_LOCK_TOUCHED_MODE)) << (value ? "ENABLED" : "DISABLED");
}

void Backend::receiveSettingsUpdate(int id, int value)
{
    //Save to state machine
    m_stateManager->setSetting(id, value);
    m_warningManager->setStateValue(id,value);

    //Updates o2 if in laser safe mode and if o2 is greater that laser o2 setting
    if(id == (int)SettingIds::LASER_O2 && value < m_stateManager->o2Setting() && m_stateManager->laserMode())
    {
        int o2_val = m_stateManager->getSetO2Val();
        m_stateManager->setSetting((int)SettingIds::O2, value);
        m_warningManager->setStateValue((int)SettingIds::O2, value);
        m_stateManager->setSetO2Val(o2_val);
    }

    //Constructs vector that will be sent to api;
    settingsVector = {};
    for(unsigned char i = 0; i< NUM_SETTINGS; i++)
    {
        if ( i == (unsigned char)SettingIds::HUM_1 || i == (unsigned char)SettingIds::HUM_AUX)
        {
            settingsVector.append(getHumidityPercentage(m_stateManager->getSettingValue(i)));
        }
        else
        {
            settingsVector.append(m_stateManager->getSettingValue(i));
        }
    }

    //Raise flag to send to message to API
    sendSettingsUpdate();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;

    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at(id)) << value;
}

void Backend::settingsConfirmed()
{
    //Sends signal to preset implementation progress page to end.
    if (!m_stateManager->getPresetComplete())
    {
        m_stateManager->setPresetComplete(1);
        setScreenLockModes(0);
        emit m_stateManager->settingsComplete();
    }

    if(m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST])
    {
        m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 0;

        qInfo() << "NVENT" << "," << "SETTING" << "," << "CONFIRMED";
    }
}

void Backend::sendSettingsUpdate()
{
    emit sendSettingSignal(settingsVector);
}

void Backend::separateHumidity(unsigned char separate, int hum_value, int hum_aux_value)
{
    m_stateManager->setSeparateHumidity(separate);

    m_stateManager->setSetting((int)SettingIds::HUM_1,hum_value);
    m_warningManager->setStateValue((int)SettingIds::HUM_1,hum_value);

    m_stateManager->setSetting((int)SettingIds::HUM_AUX,hum_aux_value);
    m_warningManager->setStateValue((int)SettingIds::HUM_AUX,hum_aux_value);

    settingsVector = {};
    for(unsigned char i = 0; i< NUM_SETTINGS; i++)
    {
        if ( i == (unsigned char)SettingIds::HUM_1 || i == (unsigned char)SettingIds::HUM_AUX)
        {
            settingsVector.append(getHumidityPercentage(m_stateManager->getSettingValue(i)));
        }
        else
        {
            settingsVector.append(m_stateManager->getSettingValue(i));
        }
    }

    sendSettingsUpdate();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;

    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at((int)SettingIds::HUM_1)) << hum_value;
    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at((int)SettingIds::HUM_AUX)) << hum_aux_value;

}

int Backend::getHumidityPercentage(int value)
{
    if (value == 4)
    {
        return 100;
    }
    else if (value == 3)
    {
        return 70;
    }
    else if (value == 2)
    {
        return 50;
    }
    else if (value == 1)
    {
        return 30;
    }
    return 0;
}

void Backend::receiveDehumidifySettingsUpdate()
{
    m_stateManager->setSetting((int)SettingIds::HUM_1,0);
    m_warningManager->setStateValue((int)SettingIds::HUM_1,0);

    m_stateManager->setSetting((int)SettingIds::HUM_2,0);
    m_warningManager->setStateValue((int)SettingIds::HUM_2,0);

    m_stateManager->setSetting((int)SettingIds::HUM_AUX,0);
    m_warningManager->setStateValue((int)SettingIds::HUM_AUX,0);

    settingsVector = {};
    for(unsigned char i = 0; i< NUM_SETTINGS; i++)
    {
        settingsVector.append(m_stateManager->getSettingValue(i));
    }

    //m_settings_flag = 1;
    sendSettingsUpdate();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;

    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at((int)SettingIds::HUM_1)) << 0;
    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at((int)SettingIds::HUM_2)) << 0;
    qInfo() << "NVENT " << "," << "SETTING" << "," << "REQUEST" << QString::fromStdString(settingNameMap.at((int)SettingIds::HUM_AUX)) << 0;
}

/*------------------------GET MEASURED PATHWAY----------------------*/

void Backend::receiveSensorMeasurements(unsigned char id, unsigned char value)
{
    m_get_sensors[id] = 0;
    m_stateManager->setSensorMeasurement(id, value);
    checkSensorsReceived();

    if(m_getO2CalsFlag)
    {
        handleO2CalVals(id, value);
    }
}

void Backend::receiveVolt(unsigned char id, float value)
{
    m_get_sensors[id] = 0;
    m_stateManager->setSensorMeasurement(id,value);
    checkSensorsReceived();

    if(m_getO2CalsFlag)
    {
        handleVoltVals(id, value);
    }
}

void Backend::receiveWaterSensor(unsigned char id, unsigned char value)
{
    m_get_sensors[id] = 0;
    m_stateManager->setSensorMeasurement(id, value);
    checkSensorsReceived();

    if (id == 17)
    {
        m_get_sensors[(int)MeasuredIDs::WATER_SENSOR_AUX] = 1;

        sendGetMeasured();
        m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
    }
}

void Backend::handleO2CalVals(unsigned char id, unsigned char value)
{
    if (id == (int)MeasuredIDs::O2_LOWER_CAL_VAL)
    {
        m_O2Vals[0] = value;
        m_get_sensors[(int)MeasuredIDs::O2_UPPER_CAL_VAL] = 1;

        sendGetMeasured();
        m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
    }

    else if (id == (int)MeasuredIDs::O2_UPPER_CAL_VAL)
    {
        m_O2Vals[1] = value;
        m_get_sensors[(int)MeasuredIDs::O2_LOWER_BOUND] = 1;

        sendGetMeasured();
        m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
    }
}

void Backend::handleVoltVals(unsigned char id, float value)
{
    if (id == (int)MeasuredIDs::O2_LOWER_BOUND)
    {
        m_Volts[0] = value;
        m_get_sensors[(int)MeasuredIDs::O2_UPPER_BOUND] = 1;

        sendGetMeasured();
        m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
    }
    else if (id == (int)MeasuredIDs::O2_UPPER_BOUND)
    {
        m_Volts[1] = value;

        //If calibration values and voltage were never set, create new calibration values and voltage.
        if (!m_get_sensors[(int)MeasuredIDs::O2_LOWER_CAL_VAL] && !m_get_sensors[(int)MeasuredIDs::O2_UPPER_CAL_VAL]
            && !m_get_sensors[(int)MeasuredIDs::O2_LOWER_BOUND] && !m_get_sensors[(int)MeasuredIDs::O2_UPPER_BOUND])
        {
            m_o2CalManager->addO2CalVals(m_O2Vals[0], m_O2Vals[1], m_Volts[0], m_Volts[1]);
            m_getO2CalsFlag = 0;
        }
    }
}

void Backend::checkSensorsReceived()
{
    for (int i = 0; i < NUM_MEASURED_SENSORS; i++)
    {
        if (m_get_sensors[i])
        {
            m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
            return;
        }

        m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 0;
    }
}

void Backend::sendGetMeasured()
{
    for (int i = 0; i < NUM_MEASURED_SENSORS; i++)
    {
        if(m_get_sensors[i])
        {
            emit sendGetSensorMeasurementSignal(i);
        }
    }
}

void Backend::initGetO2Cals()
{
    m_getO2CalsFlag = 1;
    m_get_sensors[(int)MeasuredIDs::O2_LOWER_CAL_VAL] = 1;

    sendGetMeasured();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
}

/*------------------------CLEAR WARNING PATHWAY-----------------------------*/

void Backend::initClearAlarm(int warning_id)
{
    m_warningManager->clearWarning(warning_id);

    if (warning_id == 59)
    {
        m_warningManager->updateServiceAlarm(0);
        return;
    }

    m_warning_to_clear = warning_id;
    sendClearAlarm();
    m_message_flags[(int)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST] = 1;
}

void Backend::sendClearAlarm()
{
    emit warningClearSignal(m_warning_to_clear);
}

void Backend::clearAlarmSlot(int warning_id)
{
    if (m_message_flags[(int)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST])
    {
        m_message_flags[(int)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST] = 0;
    }
    qInfo() << "NVENT" << "," << "CLEAR WARNING" << "," << "Warning Cleared: " + QString::number(warning_id);
}

/*------------------------DISPLAY OP MODE REQUEST PATHWAY---------------------*/

void Backend::modesSet()
{
    for (int i = 0; i < NUM_MODES; i++)
    {
        if (m_send_modes[i])
        {
            m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] = 1;
            return;
        }
    }
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] = 0;
}

void Backend::setMode(unsigned char modeID, unsigned char value)
{
    //Section of code that prevents modes from being enabled.
    //ETCO2 Mode can't be enabled if system is ventilating and Manual Mode is active.
    if (modeID == (unsigned char) ModeIDs::ETCO2_MODE)
    {
        if (!m_stateManager->ventilating() || m_stateManager->manualMode())
        {
            return;
        }
    }
    //Manual Mode can't be enabled if ETCO2 Mode is enabled.
    else if (modeID == (unsigned char) ModeIDs::MANUAL_MODE)
    {
        if (m_stateManager->etCO2Mode())
        {
            return;
        }

        if (value && !m_stateManager->getSPLineState())
        {
            m_stateManager->setSPLineState(1);
            m_sp_line_hidden = 0;
        }
        else if (value && m_stateManager->getSPLineState())
        {
            m_stateManager->setSPLineState(1);
            m_sp_line_hidden = 1;
        }
        else if (!value)
        {
            m_stateManager->setSPLineState(m_sp_line_hidden);
        }

    }
    unsigned char tmp_success = 2;
    if (modeID == (unsigned char)ModeIDs::LASER_MODE && value)
    {
        tmp_success = 1;
    }
    else if (modeID == (unsigned char)ModeIDs::LASER_MODE && !value)
    {
        tmp_success = 0;
    }

    //State objects sets which mode that needs to be enabled
    m_stateManager->setMode(modeID, value, tmp_success);
    //Sets which mode that needs to be changed
    m_send_modes[modeID] = 1;

    sendModeCommand();
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] = 1;

    //Emits signal from knob to change mode
    QString temp = "";
    if(modeID == (unsigned char)ModeIDs::LISTENING_KNOB)
    {
        emit(listenToKnob(value));
    }
    //If laser mode need to be changed
    else if (modeID == (unsigned char) ModeIDs::LASER_MODE && value)
    {
        //If oxygen setting value is greater than oxygen setting value when laser mode is enabled
        if (m_stateManager->o2Setting() > m_stateManager->laserO2Setting())
        {
            //O2 value for laser mode changes
            unsigned char o2_val = m_stateManager->o2Setting();
            receiveSettingsUpdate((unsigned char) SettingIds::O2, m_stateManager->laserO2Setting());
            m_stateManager->setSetO2Val(o2_val);
        }
    }
    //If laser mode does not need to be changed
    else if (modeID == (unsigned char) ModeIDs::LASER_MODE && !value)
    {
        //O2 value changes
        receiveSettingsUpdate((unsigned char) SettingIds::O2, m_stateManager->getSetO2Val());
    }
    //If calibration mode is active
    else if (modeID == (unsigned char) ModeIDs::O2_CALIBRATION_MODE)
    {
        //Changes highest and lowest calibration values
        QVector<int> calvals = m_o2CalManager->getMostRecentO2CalVal();
        temp = "; Low Calibration value: " + QString::number(calvals.at(0)) + "; High Calibration value: " + QString::number(calvals.at(1));
    }
    else if (modeID == (unsigned char) ModeIDs::CALIBRATION_MODE && value)
    {
        m_warningManager->pauseDisconnection(value);
        m_stateManager->setDisplayWarnings(0);
        m_stateManager->setSavedDP(m_stateManager->dp1Setting());
        emit signalCalibrationMessages(value);

        m_dpr = 4;
        sendDPRValue();
        m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;

        qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: Default";
    }
    else if (modeID == (unsigned char) ModeIDs::CALIBRATION_MODE && !value)
    {
        m_warningManager->pauseDisconnection(value);
        receiveSettingsUpdate(0,m_stateManager->getSavedDP());
        m_stateManager->setDisplayWarnings(1);
        emit signalCalibrationMessages(value);
    }
    else if (modeID == (unsigned char) ModeIDs::HUMIDITY_PRIMING_RESET_AVAILABLE && !value)
    {

        m_stateManager->setSetting((int)SettingIds::HUM_1,0);
        m_warningManager->setStateValue((int)SettingIds::HUM_1,0);

        m_stateManager->setSetting((int)SettingIds::HUM_AUX,0);
        m_warningManager->setStateValue((int)SettingIds::HUM_AUX,0);

        settingsVector = {};
        for(unsigned char i = 0; i< NUM_SETTINGS; i++)
        {
            settingsVector.append(m_stateManager->getSettingValue(i));
        }

        sendSettingsUpdate();
        m_message_flags[(int) txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;
    }
    else if (modeID == (unsigned char) ModeIDs::DEHUMIDIFY_MODE && !value)
    {
        initDehumidification(0);
    }

    //Logs mode enabled/disabled
    qInfo() << "NVENT" << "," << "MODE" << "," << "REQUEST" << QString::fromStdString(modeNameMap.at(modeID)) + temp << (value ? "ENABLED" : "DISABLED");

}

void Backend::sendModeCommand()
{
    for(int i = 0; i < NUM_MODES; i++)
    {
        if (m_send_modes[i])
        {
            emit setModeSignal(i, m_stateManager->getModeEnabled(i));
        }
    }
}

void Backend::modeConfirmed(unsigned char modeID, unsigned char value)
{
    //check if the mode needs to be set

    QString temp = "";
    if(m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST] && m_send_modes[modeID])
    {
        //check that mode was set to correct value
        if(m_stateManager->getModeEnabled(modeID) == value)
        {
            m_send_modes[modeID] = 0;
            if (value)
            {
                m_stateManager->setMode(modeID,value, 2);
            }
        }
        if (modeID == (unsigned char) ModeIDs::O2_CALIBRATION_MODE)
        {
            QVector<int> calvals = m_o2CalManager->getMostRecentO2CalVal();
            temp = "; Low Calibration value: " + QString::number(calvals.at(0)) + "; High Calibration value: " + QString::number(calvals.at(1));
        }
        qInfo() << "NVENT" << "," << "MODE" << "," << "CONFIRMED" + temp;
    }

    //if all modes have been set, lower set mode flag
    modesSet();
}

/*------------------------DISPLAY OP MODE RESPONSE PATHWAY---------------------*/

void Backend::modeRequested(unsigned char modeID, unsigned char value, unsigned char success)
{
    m_send_modes[modeID] = 0;
    modesSet();
    m_stateManager->setMode(modeID, value, success);

    qInfo() << "NVENT" << "," << "MODE" << "," << "AUTOMATED CHANGE" << QString::fromStdString(modeNameMap.at(modeID)) << (value ? "ENABLED" : "DISABLED") << (success ? "SUCCESSFUL" : "UNSUCCESSFUL");

    //Updates humidity values
    if(modeID == (unsigned char)ModeIDs::DEHUMIDIFY_MODE)
    {
        receiveDehumidifySettingsUpdate();
    }

    //Updates oxygen calibration values
    else if (modeID == (unsigned char)ModeIDs::O2_CALIBRATION_MODE)
    {
        if (success == 1)
        {
            initGetO2Cals();
        }
        else
        {
            qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "Oxygen Calibration failed and no new values were saved.";
        }
    }
}

/*------------------------NOTIFICATION PATHWAY--------------------------------------------*/

void Backend::notificationUpdateSlot(QVector<float> notification)
{
    m_stateManager->updateNotificationVector(notification);

}

void Backend::warningUpdateSlot(QVector<unsigned char> warnings)
{
    m_warningManager->updateWarnings(&warnings);
}

/*------------------------VENTILATION PATHWAY---------------------------------------------*/

void Backend::receiveVentilationStateChange(unsigned char state)
{
    m_stateManager->setVentilating(state);
    m_stateManager->setEtco2ButtonState(state); //Tracks state for ETCO2 Button
    m_partManager->setVentilationState(state); //Tracks for components manager.

    qInfo() << "NVENT" << "," << "VENTILATION" << "," << "State: " + QString::number(state);
}

/*------------------------HMI BUTTON PUSH PATHWAY-----------------------------------------*/

void Backend::receiveHMIButtonPress(unsigned char id)
{
    QString bName;
    switch(id)
    {
    case POWER:
        bName = "POWER";
        break;
    case START_STOP:
        bName = "VENT START/STOP";
        break;
    case ALARM_MUTE:
        bName = "ALARM SILENCE";
        break;
    case DIAL_PUSH:
        bName = "DIAL PUSH";
        break;
    default:
        bName = "UNDEFINED";
        break;
    }

    qInfo() << "NVENT" << "," << "HMI BUTTON" << "," << "PRESS" << bName;
    emit hmiButtonPressed(id);
}

/*------------------------SHUTDOWN PATHWAY-----------------------------------------------*/

void Backend::powerdownInitiated()
{
    if (not m_stateManager->powerdownFlag()){
        m_stateManager->setPowerdownFlag(1);
    }

    m_get_sensors[(int)MeasuredIDs::WATER_SENSOR_1] = 1;

    sendGetMeasured();
    m_message_flags[(int)txOpCodes::DISPLAY_GET_MEASURED_REQUEST] = 1;
}

/*------------------------SHUTDOWN CONFIRM PATHWAY----------------------------------------*/

void Backend::initiatePowerdown(unsigned char powerdown)
{
    if (powerdown)
    {
        qInfo() << "NVENT" << "," << "SHUTDOWN" << "," << "Power down confirmed.";
    }
    m_stateManager->setPowerdownFlag(powerdown);

    sendPowerdownCommand();
    m_message_flags[(int)txOpCodes::DISPLAY_SHUTDOWN_CONFIRM_SEND] = 1;
}

void Backend::sendPowerdownCommand()
{
    emit powerDownCommand(m_stateManager -> powerdownFlag());
}

void Backend::powerdownConfirmed()
{
    m_message_flags[(int)txOpCodes::DISPLAY_SHUTDOWN_CONFIRM_SEND] = 0;
    if(m_stateManager->powerdownFlag())
    {
        system("shutdown -h now");
    }
}

/*------------------------SERVICE CALIBRATION----------------------------------------------*/

void Backend::serviceCalibrationSlot()
{
    QVector<float> data = QVector<float>();
    data.append(m_zeroManager->getZeroSP());
    data.append(m_zeroManager->getZeroPIP());
    data.append(m_o2CalManager->getMostRecentVoltVal().at(0).toFloat());
    data.append(m_o2CalManager->getMostRecentVoltVal().at(1).toFloat());
    data.append(0);
    data.append(0);
    data.append(0);
    data.append(0);
    emit signalServiceCalibrations(data);

}

/*------------------------DRIVING PRESSURE REGULATOR SET CAL VAL---------------------------*/

void Backend::updateDPRStates(unsigned char val)
{
    QString temp = "";
    if (val == 0)
    {
        temp = "Low Driving Pressure Regulator";
        receiveSettingsUpdate(0,0);
    }
    else if (val == 1)
    {
        temp = "High Driving Pressure Regulator";
        setMode((unsigned char) ModeIDs::LISTENING_KNOB,1);
        receiveSettingsUpdate(0,45);
    }
    else if (val == 2 || val == 3)
    {
        if (val == 2)
        {
            temp = "Air Regulator";
        }
        else if (val == 3)
        {
            temp = "O2 Regulator";
        }
        setMode((int)ModeIDs::LISTENING_KNOB,1);
        receiveSettingsUpdate(0,48);
    }
    m_dpr = val;
    sendDPRValue();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;

    qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: " + temp;
}

void Backend::lowDPRConfirmation(unsigned char value)
{
    //Saves Actual value if Calibration is done, not cancelled
    if (value)
    {
        m_dprManager->addDPRVal(m_stateManager->currentDPR());
    }

    m_dpr = 4;
    sendDPRValue();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;
}

void Backend::highDPRConfirmation(int flag, float value)
{
    if (flag == 1)
    {
        //Sends signal float to API
        emit signalTempDP(flag,value);

        sendSettingsUpdate();
        m_message_flags[(int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST] = 1;
    }
    else if (flag == 2)
    {
        emit signalTempDP(0,value);
        m_dprManager->addDPRVal(m_stateManager->currentDPR());

        setMode((unsigned char) ModeIDs::LISTENING_KNOB, 0);

        m_dpr = 4;
        sendDPRValue();
        m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;
        qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: Default";
    }
    else if (flag == 0)
    {
        emit signalTempDP(flag,value);


        setMode((unsigned char) ModeIDs::LISTENING_KNOB, 0);

        m_dpr = 4;
        sendDPRValue();
        m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;
        qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: Default";
    }
}

void Backend::regulatorConfirmation(unsigned char val,unsigned char id)
{
    if (val)
    {
        if (id == 2)
        {
            qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Confirm Calibration for Air Regulator Calibration.";
        }
        if (id == 3)
        {
            qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Confirm Calibration for Oxygen Regulator Calibration.";
        }
    }
    setMode((int)ModeIDs::LISTENING_KNOB,0);

    m_dpr = 4;
    sendDPRValue();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;
    qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: Default";
}

void Backend::sendDPRValue()
{
    emit signalDPRValue(m_dpr);
}

void Backend::slotDPRValue()
{
    if (m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST])
    {
        m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 0;
        qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Pressure Regulator State Change Confirmed";
    }

    if (m_dpr == 0)
    {
        lowDPRConfirmation(1);
        emit lowDPRFinished();
    }
}

void Backend::endDPRCalibration()
{
    setMode((unsigned char) ModeIDs::LISTENING_KNOB, 0);

    m_dpr = 4;
    sendDPRValue();
    m_message_flags[(int)txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST] = 1;
    qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Change Pressure Regulator State: Default";
}

/*------------------------ZERO PRESSURE SENSOR PATHWAY--------------------------------------------*/

void Backend::initZeroSensor(unsigned char id, float value)
{
    m_zeroSensor = id;
    QString temp = "";

    m_zero_values = {};
    m_zero_values.append((float) id);

    if (id == 0)
    {
        temp = " (PIP)";
        m_stateManager->setVerifyPIP(value);
        m_zero_values.append(m_stateManager->zeroPIP());
    }
    else if (id == 1)
    {
        temp = " (SP)";
        m_stateManager->setVerifySP(value);
        m_zero_values.append(m_stateManager->zeroSP());
    }

    sendZeroSensor();
    m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST] = 1;

    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Zero Sensor: " + QString::number(id) + temp;
}

void Backend::sendZeroSensor()
{
    emit zeroSensor(m_zero_values);
}

void Backend::receiveSensorZeroed(QVector<unsigned char> values)
{
    QString temp = "";
    unsigned char result = 0;

    if (m_zeroSensor == 0 && values.at(0) == 0)
    {
        temp = "PIP ";
        result = values.at(1) ? 1 : 0;
        if (result)
        {
            m_zeroManager->addZeroValue(0, m_stateManager->zeroPIP());
            m_zeroManager->addVerifiedValue(0, m_stateManager->verifyPIP());
        }
    }
    else if (m_zeroSensor == 1 && values.at(0) == 1)
    {
        temp = "SP ";
        result = values.at(1) ? 1 : 0;
        if (result)
        {
            m_zeroManager->addZeroValue(1, m_stateManager->zeroSP());
            m_zeroManager->addVerifiedValue(1, m_stateManager->verifySP());
        }
    }

    if (m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST])
    {
        m_message_flags[(int)txOpCodes::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST] = 0;

        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << temp + "Sensor Zeroed";
    }

    emit zeroFinished(result);
}

/*------------------------SERVICE NOTIFICATION PATHWAY------------------------------------*/


void Backend::serviceNotificationUpdateSlot(QVector<float> notification)
{
    m_stateManager->updateServiceNotificationVector(notification);
}
