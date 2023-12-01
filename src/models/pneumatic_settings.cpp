/**
 * Update by Joseph Aversa
 * Added help descriptions for etCO2 settings, laser_o2, and volume.
 * Strings will be displayed when user touch help icons on associated settings pages.
 */
#include "pneumatic_settings.h"

PneumaticSettings::PneumaticSettings(
        int setting_id,
        const QString &unit,
        const QString &title,
        const QString &help,
        int min, int max,
        int step,
        int warningThreshold,
        QObject *parent
        )
    : m_id(setting_id)
    , m_unit(QString(unit))
    , m_title(QString(title))
    , m_min(min)
    , m_max(max)
    , m_step(step)
    , m_minOn(min)
    , m_warningThreshold(warningThreshold)
    , m_help(QString(help))

{
}

PneumaticSettings::PneumaticSettings(
        int setting_id,
        const QString &unit,
        const QString &title,
        const QString &help,
        int min,
        int max,
        int step,
        int minOn,
        int warningThreshold,
        QObject *parent
        )
    : m_id(setting_id)
    , m_unit(QString(unit))
    , m_title(QString(title))
    , m_min(min)
    , m_max(max)
    , m_step(step)
    , m_minOn(minOn)
    , m_warningThreshold(warningThreshold)
    , m_help(QString(help))
{
}

auto PneumaticSettings::unit() const -> QString
{
    return m_unit;
}

auto PneumaticSettings::title() const -> QString
{
    return m_title;
}

auto PneumaticSettings::min() const -> int
{
    return m_min;
}

auto PneumaticSettings::max() const -> int
{
    return m_max;
}

auto PneumaticSettings::step() const -> int
{
    return m_step;
}

auto PneumaticSettings::id() const -> int
{
    return m_id;
}

/**
 * @brief PneumaticSettings::minOn getter for setting minimum on
 * @return Get value when minimum is set
 */
auto PneumaticSettings::minOn() const -> int
{
    return m_minOn;
}

auto PneumaticSettings::warningThreshold() const -> int
{
    return m_warningThreshold;
}

auto PneumaticSettings::help() const -> QString
{
    return m_help;
}

DrivingPressure::DrivingPressure(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("PSI"), title, help,
                        (int)SettingMin::DRIVING_PRESSURE, (int)SettingMax::DRIVING_PRESSURE, (int)SettingIncrement::DRIVING_PRESSURE, (int)SettingWarningThreshold::DRIVING_PRESSURE)
{
}

Rate::Rate(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("BPM"), title, help,
                        (int)SettingMin::RATE, (int)SettingMax::RATE, (int)SettingIncrement::RATE, (int)SettingWarningThreshold::RATE)
{
}

InspiratoryTime::InspiratoryTime(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("%"), title, help,
                       (int)SettingMin::INSPIRATORY_TIME, (int)SettingMax::INSPIRATORY_TIME, (int)SettingIncrement::INSPIRATORY_TIME, (int)SettingWarningThreshold::INSPIRATORY_TIME)
{
}

StackingPressure::StackingPressure(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("cmH<sub>2</sub>O"), title, help,
                       (int)SettingMin::STACKING_PRESSURE, (int)SettingMax::STACKING_PRESSURE, (int)SettingIncrement::STACKING_PRESSURE, (int)SettingWarningThreshold::STACKING_PRESSURE)
{
}

O2::O2(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("%"),title, help,
                       (int)SettingMin::O2, (int)SettingMax::O2, (int)SettingIncrement::O2, (int)SettingWarningThreshold::O2)
{
}

PIP::PIP(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("cmH<sub>2</sub>O"), title, help,
                       (int)SettingMin::PIP, (int)SettingMax::PIP, (int)SettingIncrement::PIP, (int)SettingWarningThreshold::PIP)
{
}

AuxFlow::AuxFlow(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("lpm"),title, help,
                       (int)SettingMin::AUX_FLOW, (int)SettingMax::AUX_FLOW, (int)SettingIncrement::AUX_FLOW, (int)SettingMinimumOn::AUX_FLOW, (int)SettingWarningThreshold::AUX_FLOW)
{
}

Humidity::Humidity(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("level"), title, help,
                       (int)SettingMin::HUM, (int)SettingMax::HUM, (int)SettingIncrement::HUM, (int)SettingMinimumOn::HUM, (int)SettingWarningThreshold::HUM)
{
}

ETCO2Breaths::ETCO2Breaths(int setting_id, const QString &title, const QString &help)
    : PneumaticSettings(setting_id, QStringLiteral("Breaths"), title, help,
                       (int)SettingMin::ETCO2_NUM_BREATHS, (int)SettingMax::ETCO2_NUM_BREATHS, (int)SettingIncrement::ETCO2_NUM_BREATHS, (int)SettingWarningThreshold::ETCO2_NUM_BREATHS)
{
}

ETCO2IT::ETCO2IT(int setting_id, const QString &title, const QString &help)
    :PneumaticSettings(setting_id, QStringLiteral("%"), title, help,
                       (int)SettingMin::ETCO2_IT, (int)SettingMax::ETCO2_IT, (int)SettingIncrement::ETCO2_IT, (int)SettingWarningThreshold::ETCO2_IT)
{
}

ETCO2Rate::ETCO2Rate(int setting_id, const QString &title, const QString &help)
    :PneumaticSettings(setting_id, QStringLiteral("BPM"), title, help,
                       (int)SettingMin::ETCO2_RATE, (int)SettingMax::ETCO2_RATE, (int)SettingIncrement::ETCO2_RATE, (int)SettingWarningThreshold::ETCO2_RATE)
{
}

ETCO2DP::ETCO2DP(int setting_id, const QString &title, const QString &help)
    :PneumaticSettings(setting_id, QStringLiteral("PSI"), title, help,
                       (int)SettingMin::ETCO2_RATE, (int)SettingMax::ETCO2_DP, (int)SettingIncrement::ETCO2_DP, (int)SettingWarningThreshold::ETCO2_DP)
{
}

LaserO2::LaserO2(int setting_id, const QString &title, const QString &help)
    :PneumaticSettings(setting_id, QStringLiteral("%"), title, help,
                       (int)SettingMin::LASER_O2, (int)SettingMax::LASER_O2, (int)SettingIncrement::LASER_O2, (int)SettingWarningThreshold::LASER_O2)
{
}

Volume::Volume(int setting_id, const QString &title, const QString &help)
    :PneumaticSettings(setting_id, QStringLiteral("%"), title, help,
                       (int)SettingMin::VOLUME, (int)SettingMax::VOLUME, (int)SettingIncrement::VOLUME, (int)SettingWarningThreshold::VOLUME)
{
}


