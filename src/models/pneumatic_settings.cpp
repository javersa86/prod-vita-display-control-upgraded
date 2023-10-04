/**
 * Update by Joseph Aversa
 * Added help descriptions for etCO2 settings, laser_o2, and volume.
 * Strings will be displayed when user touch help icons on associated settings pages.
 */
#include "pneumatic_settings.h"
#include "settings.h"

PneumaticSettings::PneumaticSettings()
{
}

PneumaticSettings::PneumaticSettings(int id, const QString &unit, const QString &title, const QString &help,
                                     int min, int max, int step, int warningThreshold, QObject *parent)
    : m_id(id)
    , m_unit(unit)
    , m_title(title)
    , m_min(min)
    , m_max(max)
    , m_step(step)
    , m_minOn(min)
    , m_warningThreshold(warningThreshold)
    , m_help(help)

{
}

PneumaticSettings::PneumaticSettings(int id, const QString &unit, const QString &title, const QString &help,
                  int min, int max, int step, int minOn, int warningThreshold, QObject *parent)
    : m_id(id)
    , m_unit(unit)
    , m_title(title)
    , m_min(min)
    , m_max(max)
    , m_step(step)
    , m_minOn(minOn)
    , m_warningThreshold(warningThreshold)
    , m_help(help)
{
}

QString PneumaticSettings::unit() const
{
    return m_unit;
}

QString PneumaticSettings::title() const
{
    return m_title;
}

int PneumaticSettings::min() const
{
    return m_min;
}

int PneumaticSettings::max() const
{
    return m_max;
}

int PneumaticSettings::step() const
{
    return m_step;
}

int PneumaticSettings::id() const
{
    return m_id;
}

/**
 * @brief PneumaticSettings::minOn getter for setting minimum on
 * @return Get value when minimum is set
 */
int PneumaticSettings::minOn() const
{
    return m_minOn;
}

int PneumaticSettings::warningThreshold() const
{
    return m_warningThreshold;
}

QString PneumaticSettings::help() const
{
    return m_help;
}

DrivingPressure::DrivingPressure(int id, const QString &title, const QString &help)
    : PneumaticSettings(id, QStringLiteral("PSI"), title, help,
                        (int)SettingMin::DRIVING_PRESSURE, (int)SettingMax::DRIVING_PRESSURE, (int)SettingIncrement::DRIVING_PRESSURE, (int)SettingWarningThreshold::DRIVING_PRESSURE)
{
}

Rate::Rate(int id, const QString &title, const QString &help)
    : PneumaticSettings(id, QStringLiteral("BPM"), title, help,
                        (int)SettingMin::RATE, (int)SettingMax::RATE, (int)SettingIncrement::RATE, (int)SettingWarningThreshold::RATE)
{
}

InspiratoryTime::InspiratoryTime(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("%"), title, help,
                       (int)SettingMin::INSPIRATORY_TIME, (int)SettingMax::INSPIRATORY_TIME, (int)SettingIncrement::INSPIRATORY_TIME, (int)SettingWarningThreshold::INSPIRATORY_TIME)
{
}

StackingPressure::StackingPressure(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("cmH<sub>2</sub>O"), title, help,
                       (int)SettingMin::STACKING_PRESSURE, (int)SettingMax::STACKING_PRESSURE, (int)SettingIncrement::STACKING_PRESSURE, (int)SettingWarningThreshold::STACKING_PRESSURE)
{
}

O2::O2(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("%"),title, help,
                       (int)SettingMin::O2, (int)SettingMax::O2, (int)SettingIncrement::O2, (int)SettingWarningThreshold::O2)
{
}

PIP::PIP(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("cmH<sub>2</sub>O"), title, help,
                       (int)SettingMin::PIP, (int)SettingMax::PIP, (int)SettingIncrement::PIP, (int)SettingWarningThreshold::PIP)
{
}

AuxFlow::AuxFlow(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("lpm"),title, help,
                       (int)SettingMin::AUX_FLOW, (int)SettingMax::AUX_FLOW, (int)SettingIncrement::AUX_FLOW, (int)SettingMinimumOn::AUX_FLOW, (int)SettingWarningThreshold::AUX_FLOW)
{
}

Humidity::Humidity(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("level"), title, help,
                       (int)SettingMin::HUM, (int)SettingMax::HUM, (int)SettingIncrement::HUM, (int)SettingMinimumOn::HUM, (int)SettingWarningThreshold::HUM)
{
}

ETCO2Breaths::ETCO2Breaths(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("Breaths"), title, help,
                       (int)SettingMin::ETCO2_NUM_BREATHS, (int)SettingMax::ETCO2_NUM_BREATHS, (int)SettingIncrement::ETCO2_NUM_BREATHS, (int)SettingWarningThreshold::ETCO2_NUM_BREATHS)
{
}

ETCO2IT::ETCO2IT(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("%"), title, help,
                       (int)SettingMin::ETCO2_IT, (int)SettingMax::ETCO2_IT, (int)SettingIncrement::ETCO2_IT, (int)SettingWarningThreshold::ETCO2_IT)
{
}

ETCO2Rate::ETCO2Rate(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("BPM"), title, help,
                       (int)SettingMin::ETCO2_RATE, (int)SettingMax::ETCO2_RATE, (int)SettingIncrement::ETCO2_RATE, (int)SettingWarningThreshold::ETCO2_RATE)
{
}

ETCO2DP::ETCO2DP(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("PSI"), title, help,
                       (int)SettingMin::ETCO2_RATE, (int)SettingMax::ETCO2_DP, (int)SettingIncrement::ETCO2_DP, (int)SettingWarningThreshold::ETCO2_DP)
{
}

LaserO2::LaserO2(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("%"), title, help,
                       (int)SettingMin::LASER_O2, (int)SettingMax::LASER_O2, (int)SettingIncrement::LASER_O2, (int)SettingWarningThreshold::LASER_O2)
{
}

Volume::Volume(int id, const QString &title, const QString &help)
    :PneumaticSettings(id, QStringLiteral("%"), title, help,
                       (int)SettingMin::VOLUME, (int)SettingMax::VOLUME, (int)SettingIncrement::VOLUME, (int)SettingWarningThreshold::VOLUME)
{
}


