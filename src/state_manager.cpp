#include <QtDebug>

#include "state_manager.h"
#include "../nventConfig.h"

StateManager::StateManager(QObject *parent)
    : QObject(parent)
{
}

auto StateManager::getSystemSoftwareVersion() -> QString
{
    return m_systemVersion;
}

void StateManager::setSystemVersion(const QString &version)
{
    m_systemVersion = version;
}

auto StateManager::getDisplaySoftwareVersion() -> QString
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

auto StateManager::startupFlag() const -> int
{
    return m_startup_flag;
}

/*----Power Down--------------------------------------------*/

void StateManager::setPowerdownFlag(int flag)
{
    m_powerdown_flag = flag;
    emit powerdownFlagChanged();
}

auto StateManager::powerdownFlag() const -> int
{
    return m_powerdown_flag;
}

void StateManager::setVentilating(unsigned char state)
{
    m_ventilating = state;
    emit ventilatingChanged();
}

auto StateManager::ventilating() const -> unsigned char
{
    return m_ventilating;
}

/*---Humidity Separation------------------------------------*/

void StateManager::setSeparateHumidity(unsigned char value)
{
    m_humiditySeparated = value;
    emit separateHumidityChanged();
}

auto StateManager::separatedHumidity() const -> unsigned char
{
    return m_humiditySeparated;
}

/*---Notifications------------------------------------------*/

void StateManager::updateNotificationVector(const QVector<float> &notification)
{
    if (notification.size() == NUM_SETTINGS_NOTIFICATIONS + NUM_CALCULATIONS_NOTIFICATIONS + 1)
    {
        QVector<double> temp(notification.size());
        const float *_data = notification.constData();
        double *notifications_data = temp.data();

        for (int i = 0; i < notification.size(); ++i)
        {
            notifications_data[i] = _data[i];
        }

        notification_vector = std::move(temp);

        emit notificationVectorChanged();
        adjustOxygen();
    }
}

auto StateManager::getNotificationVector() -> QVector<double>
{
    return notification_vector;
}

/*---Sensor Measurements____________________________________*/

auto StateManager::sensorMeasurements() -> QVector<int>
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
auto StateManager::laserMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::LASER_MODE];
}
auto StateManager::manualMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::MANUAL_MODE];
}

auto StateManager::pipMonitoringMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::PIP_MONITORING_MODE];
}

auto StateManager::demoMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::DEMO_MODE];
}

auto StateManager::screenLockMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::SCREEN_LOCK_MODE];
}

auto StateManager::doubleJetMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::DOUBLE_JET_MODE];
}

auto StateManager::etCO2Mode() -> unsigned char
{
    return m_modes[(int)ModeIDs::ETCO2_MODE];
}

auto StateManager::dehumidifyMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::DEHUMIDIFY_MODE];
}

auto StateManager::humidityPrimingResetAvailable() -> unsigned char
{
    return m_modes[(int)ModeIDs::HUMIDITY_PRIMING_RESET_AVAILABLE];
}

auto StateManager::o2CalMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::O2_CALIBRATION_MODE];
}

auto StateManager::alarmSounding() -> unsigned char
{
    return m_modes[(int)ModeIDs::ALARM_SOUNDING];
}

auto StateManager::listeningToKnob() -> unsigned char
{
    return m_modes[(int)ModeIDs::LISTENING_KNOB];
}

auto StateManager::soundIcon() -> unsigned char
{
    return m_modes[(int)ModeIDs::SOUND_ICON];
}

auto StateManager::calMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::CALIBRATION_MODE];
}

auto StateManager::screenLockTouchedMode() -> unsigned char
{
    return m_modes[(int)ModeIDs::SCREEN_LOCK_TOUCHED_MODE];
}

auto StateManager::getModeEnabled(unsigned char modeID) -> unsigned char
{
    return m_modes[modeID];
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

auto StateManager::o2CalSuccess() -> unsigned char
{
    return m_modes_success[(int)ModeIDs::O2_CALIBRATION_MODE];
}

auto StateManager::dehumidifySuccess() -> unsigned char
{
    return m_modes_success[(int)ModeIDs::DEHUMIDIFY_MODE];
}

auto StateManager::etco2Success() -> unsigned char
{
    return m_modes_success[(int)ModeIDs::ETCO2_MODE];
}

auto StateManager::limitedO2Success() -> unsigned char
{
    return m_modes_success[(int)ModeIDs::LASER_MODE];
}

/*---Subsystems---------------------------------------------*/

//GETTERS (used by QML for Q_PROPERTIES)

auto StateManager::primaryVentilationState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::PRIMARY_VENTILATION];
}

auto StateManager::secondaryVentilationState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::SECONDARY_VENTILATION];
}

auto StateManager::auxiliaryFlowState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::AUXILIARY_FLOW];
}

auto StateManager::oxygenControlState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::OXYGEN_CONTROL];
}

auto StateManager::primaryHumidificationState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::PRIMARY_HUMIDIFICATION];
}

auto StateManager::secondaryHumidificationState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::SECONDARY_HUMIDIFICATION];
}

auto StateManager::auxiliaryHumidificationState() -> unsigned char
{
    return m_subsystems[(int)SubsystemIDs::AUXILIARY_HUMIDITY];
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
auto StateManager::dp1Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::DRIVING_PRESSURE_1];
}

auto StateManager::dp2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::DRIVING_PRESSURE_2];
}

auto StateManager::rate1Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::RATE_1];
}

auto StateManager::rate2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::RATE_2];
}

auto StateManager::it1Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::INSPIRATORY_TIME_1];
}

auto StateManager::it2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::INSPIRATORY_TIME_2];
}

auto StateManager::sp1Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::STACKING_PRESSURE_1];
}

auto StateManager::sp2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::STACKING_PRESSURE_2];
}

auto StateManager::o2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::O2];
}

auto StateManager::pipSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::PIP];
}
auto StateManager::auxSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::AUX_FLOW];
}

auto StateManager::hum1Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::HUM_1];
}

auto StateManager::hum2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::HUM_2];
}

auto StateManager::humauxSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::HUM_AUX];
}

auto StateManager::etco2RateSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::ETCO2_RATE];
}

auto StateManager::etco2ITSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::ETCO2_IT];
}

auto StateManager::etco2NumBreathsSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::ETCO2_NUM_BREATHS];
}

auto StateManager::etco2DPSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::ETCO2_DP];
}

auto StateManager::laserO2Setting() -> unsigned char
{
    return m_settings[(int)SettingIds::LASER_O2];
}

auto StateManager::volumeSetting() -> unsigned char
{
    return m_settings[(int)SettingIds::VOLUME];
}

auto StateManager::getSettingValue(unsigned char setting_id) -> unsigned char
{
    if(setting_id < NUM_SETTINGS)
    {
        return m_settings[setting_id];
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

auto StateManager::getSetO2Val() const -> unsigned char
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

auto StateManager::getIPAddress() -> QString
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

auto StateManager::currentDPR() const -> int
{
    return m_currentDPR;
}

void StateManager::setDPR(int val)
{
    m_currentDPR = val;
    emit dprChanged();
}

/* Getter and setter methods for inlet air and o2 */
auto StateManager::zeroInletAir() -> float
{
    return m_inlets[0];
}
auto StateManager::verifyInletAir() -> float
{
    return m_inlets_verified[0];
}

auto StateManager::zeroInletO2() -> float
{
    return m_inlets[1];
}
auto StateManager::verifyInletO2() -> float
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
auto StateManager::zeroPIP() -> float
{
    return m_inlets[2];
}
auto StateManager::verifyPIP() -> float
{
    return m_inlets_verified[2];
}

auto StateManager::zeroSP() -> float
{
    return m_inlets[3];
}
auto StateManager::verifySP() -> float
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

auto StateManager::getZeroValue(unsigned char zero_id) -> float
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

auto StateManager::getSavedDP() const -> unsigned char
{
    return m_saved_dp;
}

void StateManager::setSavedDP(unsigned char val)
{
    m_saved_dp = val;
}

auto StateManager::getPresetComplete() const -> unsigned char
{
    return m_preset_complete;
}

void StateManager::setPresetComplete(unsigned char val)
{
    m_preset_complete = val;
    emit settingChanged();
}

auto StateManager::getDisplayWarnings() const -> unsigned char
{
    return m_display_warnings;
}

void StateManager::setDisplayWarnings(unsigned char val)
{
    m_display_warnings = val;
    emit settingChanged();
}

auto StateManager::getPresetCreateActive() const -> unsigned char
{
    return m_preset_create_active;
}

void StateManager::setPresetCreateActive(unsigned char val)
{
    m_preset_create_active = val;
    emit settingChanged();
}

auto StateManager::getSPLineState() const -> unsigned char
{
    return m_sp_lines_state;
}

void StateManager::setSPLineState(unsigned char val)
{
    m_sp_lines_state = val;
    emit spLineSignal();
}

auto StateManager::getEtco2ButtonState() const -> unsigned char
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

auto StateManager::getTotalFiles() const -> int
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

auto StateManager::getSaveDataProgress() const -> int
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
        QVector<double> temp(notification.size());
        const float *_data = notification.constData();
        double *notifications_data = temp.data();

        for (int i = 0; i < notification.size(); i++)
        {
            notifications_data[i] = _data[i];
        }

        service_notification_vector = std::move(temp);

        emit notificationVectorChanged();
    }
}

auto StateManager::getServiceNotificationVector() -> QVector<double>
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
