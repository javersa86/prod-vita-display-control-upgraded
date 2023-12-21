#include <QtDebug>

#include "state_manager.h"
#include "../nventConfig.h"

StateManager::StateManager(QObject *parent)
    : QObject(parent)
{
}

QString StateManager::getSystemSoftwareVersion()
{
    return m_systemVersion;
}

void StateManager::setSystemVersion(const QString &version)
{
    m_systemVersion = version;
}

QString StateManager::getDisplaySoftwareVersion()
{
    QString result = "v" + QString::number(nvent_vita_display_VERSION_MAJOR) +
            "." + QString::number(nvent_vita_display_VERSION_MINOR) + "." +
            QString::number(nvent_vita_display_VERSION_PATCH);
    return result;
}

/*----Start Up----------------------------------------------*/

void StateManager::setStartupComplete()
{
    m_startup_flag = 0;
    emit startupComplete();
}

int StateManager::startupFlag() const
{
    return m_startup_flag;
}

/*----Power Down--------------------------------------------*/

void StateManager::setPowerdownFlag(int flag)
{
    m_powerdown_flag = flag;
    emit powerdownFlagChanged();
}

int StateManager::powerdownFlag() const
{
    return m_powerdown_flag;
}

void StateManager::setVentilating(unsigned char state)
{
    m_ventilating = state;
    emit ventilatingChanged();
}

unsigned char StateManager::ventilating() const
{
    return m_ventilating;
}

/*---Humidity Separation------------------------------------*/

void StateManager::setSeparateHumidity(unsigned char value)
{
    m_humiditySeparated = value;
    emit separateHumidityChanged();
}

unsigned char StateManager::separatedHumidity() const
{
    return m_humiditySeparated;
}

/*---Notifications------------------------------------------*/

void StateManager::updateNotificationVector(const QVector<float> &notification)
{
    if (notification.size() == NUM_SETTINGS_NOTIFICATIONS + NUM_CALCULATIONS_NOTIFICATIONS + 1)
    {
        QVector<double> temp;
        temp.reserve(notification.size());

        std::transform(notification.begin(), notification.end(), std::back_inserter(temp), [](float value) -> double
        {
            return static_cast<double>(value);
        });

        notification_vector = std::move(temp);

        emit notificationVectorChanged();
        adjustOxygen();
    }
}

QVector<double> StateManager::getNotificationVector()
{
    return notification_vector;
}

/*---Sensor Measurements____________________________________*/

QVector<int> StateManager::sensorMeasurements()
{
    return m_sensor_measurements;
}

void StateManager::setSensorMeasurement(unsigned char sensor_id, int value)
{
    m_sensor_measurements[sensor_id] = value;
    emit sensorMeasurementsChanged();
}
/*---Modes--------------------------------------------------*/

/*~The following are get methods for enabled/disbaled modes~*/
unsigned char StateManager::laserMode()
{
    return m_modes.at((int) ModeIDs::LASER_MODE);
}
unsigned char StateManager::manualMode()
{
    return m_modes.at((int) ModeIDs::MANUAL_MODE);
}

unsigned char StateManager::pipMonitoringMode()
{
    return m_modes.at((int)ModeIDs::PIP_MONITORING_MODE);
}

unsigned char StateManager::demoMode()
{
    return m_modes.at((int)ModeIDs::DEMO_MODE);
}

unsigned char StateManager::screenLockMode()
{
    return m_modes.at((int)ModeIDs::SCREEN_LOCK_MODE);
}

unsigned char StateManager::doubleJetMode()
{
    return m_modes.at((int)ModeIDs::DOUBLE_JET_MODE);
}

unsigned char StateManager::etCO2Mode()
{
    return m_modes.at((int)ModeIDs::ETCO2_MODE);
}

unsigned char StateManager::dehumidifyMode()
{
    return m_modes.at((int)ModeIDs::DEHUMIDIFY_MODE);
}

unsigned char StateManager::humidityPrimingResetAvailable()
{
    return m_modes.at((int)ModeIDs::HUMIDITY_PRIMING_RESET_AVAILABLE);
}

unsigned char StateManager::o2CalMode()
{
    return m_modes.at((int)ModeIDs::O2_CALIBRATION_MODE);
}

unsigned char StateManager::alarmSounding()
{
    return m_modes.at((int)ModeIDs::ALARM_SOUNDING);
}

unsigned char StateManager::listeningToKnob()
{
    return m_modes.at((int)ModeIDs::LISTENING_KNOB);
}

unsigned char StateManager::soundIcon()
{
    return m_modes.at((int)ModeIDs::SOUND_ICON);
}

unsigned char StateManager::calMode()
{
    return m_modes.at((int)ModeIDs::CALIBRATION_MODE);
}

unsigned char StateManager::screenLockTouchedMode()
{
    return m_modes.at((int)ModeIDs::SCREEN_LOCK_TOUCHED_MODE);
}

unsigned char StateManager::getModeEnabled(unsigned char modeID)
{
    return m_modes.at(modeID);
}

void StateManager::setMode(unsigned char modeID, unsigned char value, unsigned char success)
{
    m_modes[modeID] = value;
    m_modes_success[modeID] = success;
    emit modeChanged();

    if (modeID == (int)ModeIDs::LASER_MODE)
    {
        emit limitedO2State(success);
    }
}

unsigned char StateManager::o2CalSuccess()
{
    return m_modes_success.at((int)ModeIDs::O2_CALIBRATION_MODE);
}

unsigned char StateManager::dehumidifySuccess()
{
    return m_modes_success.at((int)ModeIDs::DEHUMIDIFY_MODE);
}

unsigned char StateManager::etco2Success()
{
    return m_modes_success.at((int)ModeIDs::ETCO2_MODE);
}

unsigned char StateManager::limitedO2Success()
{
    return m_modes_success.at((int)ModeIDs::LASER_MODE);
}

/*---Subsystems---------------------------------------------*/

//GETTERS (used by QML for Q_PROPERTIES)

unsigned char StateManager::primaryVentilationState()
{
    return m_subsystems.at((int)SubsystemIDs::PRIMARY_VENTILATION);
}

unsigned char StateManager::secondaryVentilationState()
{
    return m_subsystems.at((int)SubsystemIDs::SECONDARY_VENTILATION);
}

unsigned char StateManager::auxiliaryFlowState()
{
    return m_subsystems.at((int)SubsystemIDs::AUXILIARY_FLOW);
}

unsigned char StateManager::oxygenControlState()
{
    return m_subsystems.at((int)SubsystemIDs::OXYGEN_CONTROL);
}

unsigned char StateManager::primaryHumidificationState()
{
    return m_subsystems.at((int)SubsystemIDs::PRIMARY_HUMIDIFICATION);
}

unsigned char StateManager::secondaryHumidificationState()
{
    return m_subsystems.at((int)SubsystemIDs::SECONDARY_HUMIDIFICATION);
}

unsigned char StateManager::auxiliaryHumidificationState()
{
    return m_subsystems.at((int)SubsystemIDs::AUXILIARY_HUMIDITY);
}

void StateManager::setSubsystemStates(const QVector<unsigned char> &states)
{
    if (states.length() == NUM_SUBSYSTEMS)
    {
        for(int i = 0; i < NUM_SUBSYSTEMS; i++)
        {
            m_subsystems[i] = states.at(i);
        }
    }
    emit subsystemStateChanged();
}

/*---Settings-----------------------------------------------*/
/*~The following are get methods for setting values~*/
unsigned char StateManager::dp1Setting()
{
    return m_settings.at((int)SettingIds::DRIVING_PRESSURE_1);
}

unsigned char StateManager::dp2Setting()
{
    return m_settings.at((int)SettingIds::DRIVING_PRESSURE_2);
}

unsigned char StateManager::rate1Setting()
{
    return m_settings.at((int)SettingIds::RATE_1);
}

unsigned char StateManager::rate2Setting()
{
    return m_settings.at((int)SettingIds::RATE_2);
}

unsigned char StateManager::it1Setting()
{
    return m_settings.at((int)SettingIds::INSPIRATORY_TIME_1);
}

unsigned char StateManager::it2Setting()
{
    return m_settings.at((int)SettingIds::INSPIRATORY_TIME_2);
}

unsigned char StateManager::sp1Setting()
{
    return m_settings.at((int)SettingIds::STACKING_PRESSURE_1);
}

unsigned char StateManager::sp2Setting()
{
    return m_settings.at((int)SettingIds::STACKING_PRESSURE_2);
}

unsigned char StateManager::o2Setting()
{
    return m_settings.at((int)SettingIds::O2);
}

unsigned char StateManager::pipSetting()
{
    return m_settings.at((int)SettingIds::PIP);
}
unsigned char StateManager::auxSetting()
{
    return m_settings.at((int)SettingIds::AUX_FLOW);
}

unsigned char StateManager::hum1Setting()
{
    return m_settings.at((int)SettingIds::HUM_1);
}

unsigned char StateManager::hum2Setting()
{
    return m_settings.at((int)SettingIds::HUM_2);
}

unsigned char StateManager::humauxSetting()
{
    return m_settings.at((int)SettingIds::HUM_AUX);
}

unsigned char StateManager::etco2RateSetting()
{
    return m_settings.at((int)SettingIds::ETCO2_RATE);
}

unsigned char StateManager::etco2ITSetting()
{
    return m_settings.at((int)SettingIds::ETCO2_IT);
}

unsigned char StateManager::etco2NumBreathsSetting()
{
    return m_settings.at((int)SettingIds::ETCO2_NUM_BREATHS);
}

unsigned char StateManager::etco2DPSetting()
{
    return m_settings.at((int)SettingIds::ETCO2_DP);
}

unsigned char StateManager::laserO2Setting()
{
    return m_settings.at((int)SettingIds::LASER_O2);
}

unsigned char StateManager::volumeSetting()
{
    return m_settings.at((int)SettingIds::VOLUME);
}

unsigned char StateManager::getSettingValue(unsigned char setting_id)
{
    if(setting_id < NUM_SETTINGS)
    {
        return m_settings.at(setting_id);
    }
    return 0;
}

void StateManager::setSetting(unsigned char setting_id, int val)
{
    if(setting_id < NUM_SETTINGS)
    {
        m_settings[setting_id] = val;
    }

    if(setting_id == (unsigned char)SettingIds::O2)
    {
        m_o2_val = val;
    }

    emit settingChanged();
}

void StateManager::setSetO2Val(unsigned char val)
{
    m_o2_val = val;
}

unsigned char StateManager::getSetO2Val() const
{
    return m_o2_val;
}

void StateManager::setSettings(const QVector<int> &settings)
{
    if (settings.length() == NUM_SETTINGS)
    {
        for(int i = 0; i< NUM_SETTINGS; i++)
        {
            if(i == (unsigned char)SettingIds::O2)
            {
                m_o2_val = settings.at(i);
            }
            m_settings[i] = settings.at(i);
        }
    }
    emit settingChanged();
}

void StateManager::setPneumaticSettings(const QVector<int> &settings)
{
    if (settings.length() == NUM_PNEUMATIC_SETTINGS)
    {
        for(int i = 0; i< NUM_PNEUMATIC_SETTINGS; i++)
        {
            m_settings[i] = settings.at(i);
        }
    }
    emit settingChanged();
}

QString StateManager::getIPAddress()
{
    return m_ip_address;
}

void StateManager::setupNetwork()
{
    QNetworkConfigurationManager mgr;
    m_ip_address = QString::fromStdString("Please Connect");
    if (mgr.isOnline()){
        QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
        QRegExp regularExpression(QString::fromStdString("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$"));
        if (!addresses.empty())
        {
            for (auto & address : addresses)
            {
                if (regularExpression.exactMatch(address.toString()) && address.toString() != QString::fromStdString("127.0.0.1"))
                {
                    m_ip_address = address.toString();
                }
            }
        }
    }
    emit ipChanged();
}

void StateManager::setIPAddress()
{
    QNetworkConfigurationManager mgr;
    if (mgr.isOnline()){
        m_ip_address = m_ip_address_network;
    }
    else
    {
        m_ip_address = QString::fromStdString("");
    }
}

int StateManager::currentDPR() const
{
    return m_currentDPR;
}

void StateManager::setDPR(int val)
{
    m_currentDPR = val;
    emit dprChanged();
}

/* Getter and setter methods for inlet air and o2 */
float StateManager::zeroInletAir()
{
    return m_inlets[0];
}
float StateManager::verifyInletAir()
{
    return m_inlets_verified[0];
}

float StateManager::zeroInletO2()
{
    return m_inlets[1];
}
float StateManager::verifyInletO2()
{
    return m_inlets_verified[1];
}

void StateManager::setZeroInletAir(float val)
{
    m_inlets[0] = val;
    emit settingChanged();
}
void StateManager::setVerifyInletAir(float val)
{
    m_inlets_verified[0] = val;
    emit settingChanged();
}

void StateManager::setZeroInletO2(float val)
{
    m_inlets[1] = val;
    emit settingChanged();
}
void StateManager::setVerifyInletO2(float val)
{
    m_inlets_verified[1] = val;
    emit settingChanged();
}

/* Getter and setter methods for PIP and SP sensor values. */
float StateManager::zeroPIP()
{
    return m_inlets[2];
}
float StateManager::verifyPIP()
{
    return m_inlets_verified[2];
}

float StateManager::zeroSP()
{
    return m_inlets[3];
}
float StateManager::verifySP()
{
    return m_inlets_verified[3];
}

void StateManager::setZeroPIP(float val)
{
    m_inlets[2] = val;
    emit settingChanged();
}
void StateManager::setVerifyPIP(float val){
    m_inlets_verified[2] = val;
    emit settingChanged();
}

void StateManager::setZeroSP(float val)
{
    m_inlets[3] = val;
    emit settingChanged();
}
void StateManager::setVerifySP(float val)
{
    m_inlets_verified[3] = val;
    emit settingChanged();
}

float StateManager::getZeroValue(unsigned char zero_id)
{
    if (zero_id == 3)
    {
        return m_inlets[0];
    }
    if (zero_id == 4)
    {
        return m_inlets[1];
    }
    if (zero_id == 0)
    {
        return m_inlets[2];
    }
    if (zero_id == 1)
    {
        return m_inlets[3];
    }
    return 0;
}

unsigned char StateManager::getSavedDP() const
{
    return m_saved_dp;
}

void StateManager::setSavedDP(unsigned char val)
{
    m_saved_dp = val;
}

unsigned char StateManager::getPresetComplete() const
{
    return m_preset_complete;
}

void StateManager::setPresetComplete(unsigned char val)
{
    m_preset_complete = val;
    emit settingChanged();
}

unsigned char StateManager::getDisplayWarnings() const
{
    return m_display_warnings;
}

void StateManager::setDisplayWarnings(unsigned char val)
{
    m_display_warnings = val;
    emit settingChanged();
}

unsigned char StateManager::getPresetCreateActive() const
{
    return m_preset_create_active;
}

void StateManager::setPresetCreateActive(unsigned char val)
{
    m_preset_create_active = val;
    emit settingChanged();
}

unsigned char StateManager::getSPLineState() const
{
    return m_sp_lines_state;
}

void StateManager::setSPLineState(unsigned char val)
{
    m_sp_lines_state = val;
    emit spLineSignal();
}

unsigned char StateManager::getEtco2ButtonState() const
{
    return m_etco2_button_state;
}

void StateManager::setEtco2ButtonState(unsigned char val)
{
    //Ensures that same state won't be set multiple times in a row.
    if ((val == 1) != (m_etco2_button_state == 0))
    {
        return;
    }
    m_etco2_button_state = val;
    emit etChanged();
}

void StateManager::setTotalFiles(int count)
{
    m_file_count = count;
    emit saveDataChanged();
}

int StateManager::getTotalFiles() const
{
    return m_file_count;
}
void StateManager::setSaveDataProgress(int count)
{
    m_file_progress = count;
    emit saveDataChanged();
}

void StateManager::incrementSaveDataProgress()
{
    m_file_progress = m_file_progress + 1;
    emit saveDataChanged();
}

int StateManager::getSaveDataProgress() const
{
    return m_file_progress;
}

void StateManager::forceManualOff()
{
    emit forceManualOffSignal();
}

void StateManager::updateServiceNotificationVector(const QVector<float> &notification)
{
    if (notification.size() == NUM_SERVICE_NOTIFICATIONS)
    {
        QVector<double> temp;
        temp.reserve(notification.size());

        std::transform(notification.begin(), notification.end(), std::back_inserter(temp), [](float value) -> double
        {
            return static_cast<double>(value);
        });

        service_notification_vector = std::move(temp);

        emit notificationVectorChanged();
    }
}

QVector<double> StateManager::getServiceNotificationVector()
{
    return service_notification_vector;
}

void StateManager::adjustOxygen()
{
    bool state_measured = true;
    const int min_o2 = 22;

    if (o2Setting() <= min_o2)
    {
        state_measured = notification_vector.at(2) <= min_o2;
    }
    else
    {
        state_measured = o2Setting() - 2 < notification_vector.at(2) && notification_vector.at(2) < o2Setting() + 2;
    }

    if (state_measured)
    {
        if (m_oxygen_adjusting == 0)
        {
            m_oxygen_adjusting = 1;
            emit oxygenAdjustmentSignal(1);
        }
    }
    else if (!state_measured)
    {
        if (m_oxygen_adjusting == 1)
        {
            m_oxygen_adjusting = 0;
            emit oxygenAdjustmentSignal(0);
        }
    }
}

void StateManager::settingsCompleteTriggered()
{
    emit settingsComplete();
}
