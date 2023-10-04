#pragma once

#include <string>
#include <map>

/**
 * @addtogroup settingsModels
 * @{
 */

/**
 * @file settings.h
 * @brief The enumerations for all parts of each setting.
 */

/**
 * @brief Number of settings.
 */
#define NUM_SETTINGS 20

/**
 * @brief Number of pneumatic settings.
 */
#define NUM_PNEUMATIC_SETTINGS 14

/**
 * @brief The enumerations for Setting IDs.
 */
enum class SettingIds
{
    DRIVING_PRESSURE_1 = 0,
    DRIVING_PRESSURE_2 = 1,
    RATE_1 = 2,
    RATE_2 = 3,
    INSPIRATORY_TIME_1 = 4,
    INSPIRATORY_TIME_2 = 5,
    STACKING_PRESSURE_1 = 6,
    STACKING_PRESSURE_2 = 7,
    O2 = 8,
    PIP = 9,
    AUX_FLOW = 10,
    HUM_1 = 11,
    HUM_2 = 12,
    HUM_AUX = 13,
    ETCO2_DP = 14,
    ETCO2_RATE = 15,
    ETCO2_IT = 16,
    ETCO2_NUM_BREATHS = 17,
    LASER_O2 = 18,
    VOLUME = 19
};

/**
 * @brief The enumerations for the minimum values of each setting.
 */
enum class SettingMin
{
    DRIVING_PRESSURE = 5,
    RATE = 5,
    INSPIRATORY_TIME = 20,
    STACKING_PRESSURE = 1,
    O2 = 21,
    PIP = 1,
    AUX_FLOW = 0,
    HUM = 0,
    ETCO2_RATE = 5,
    ETCO2_IT = 20,
    ETCO2_NUM_BREATHS = 1,
    ETCO2_DP = 5,
    LASER_O2 = 21,
    VOLUME = 20
};

/**
 * @brief The enumerations for the maximum values of each setting.
 */
enum class SettingMax
{
    DRIVING_PRESSURE = 50,
    RATE = 150,
    INSPIRATORY_TIME = 70,
    STACKING_PRESSURE = 100,
    O2 = 100,
    PIP = 100,
    AUX_FLOW = 65,
    HUM = 4, //100,
    ETCO2_RATE = 30,
    ETCO2_IT = 70,
    ETCO2_NUM_BREATHS = 10,
    ETCO2_DP = 50,
    LASER_O2 = 40,
    VOLUME = 100
};

/**
 * @brief The enumerations for increments of each setting.
 */
enum class SettingIncrement
{
    DRIVING_PRESSURE = 1,
    RATE = 5,
    INSPIRATORY_TIME = 5,
    STACKING_PRESSURE = 1,
    O2 = 1,
    PIP = 1,
    AUX_FLOW = 1,
    HUM = 1, //10,
    ETCO2_RATE = 1,
    ETCO2_IT = 5,
    ETCO2_NUM_BREATHS = 1,
    ETCO2_DP = 1,
    LASER_O2 = 1,
    VOLUME = 10
};

/**
 * @brief The enumerations for minOn of each setting (mostly used for humidity settings).
 */
enum class SettingMinimumOn
{
    DRIVING_PRESSURE = 5,
    RATE = 5,
    INSPIRATORY_TIME = 20,
    STACKING_PRESSURE = 1,
    O2 = 21,
    PIP = 1,
    AUX_FLOW = 3,
    HUM = 0, //30,
    ETCO2_RATE = 5,
    ETCO2_IT = 20,
    ETCO2_NUM_BREATHS = 1,
    ETCO2_DP = 5,
    LASER_O2 = 21,
    VOLUME = 20
};

/**
 * @brief The enumerations for warning thresholds of each setting.
 */
enum class SettingWarningThreshold
{
    DRIVING_PRESSURE = (int)SettingMax::DRIVING_PRESSURE + 1,
    RATE = (int)SettingMax::RATE + 1,
    INSPIRATORY_TIME = 60,
    STACKING_PRESSURE = 41, //60
    O2 = (int)SettingMax::O2 + 1,
    PIP = 41, //60
    AUX_FLOW = (int)SettingMax::AUX_FLOW + 1,
    HUM = (int)SettingMax::HUM + 1,
    ETCO2_RATE = (int)SettingMax::ETCO2_RATE + 1,
    ETCO2_IT = (int)SettingMax::ETCO2_IT + 1,
    ETCO2_NUM_BREATHS = (int)SettingMax::ETCO2_NUM_BREATHS + 1,
    ETCO2_DP = (int)SettingMax::ETCO2_DP + 1,
    LASER_O2 = (int)SettingMax::LASER_O2 + 1,
    VOLUME = (int)SettingMax::VOLUME + 1
};

/**
 * @brief The constant strings for setting names.
 */
const std::map<int, std::string> settingNameMap = {
    {(int)SettingIds::DRIVING_PRESSURE_1 , "Driving Pressure 1"},
    {(int)SettingIds::DRIVING_PRESSURE_2 , "Driving Pressure 2"},
    {(int)SettingIds::RATE_1 , "Rate 1"},
    {(int)SettingIds::RATE_2 , "Rate 2"},
    {(int)SettingIds::INSPIRATORY_TIME_1 , "Inspiratory Time 1"},
    {(int)SettingIds::INSPIRATORY_TIME_2 , "Inspiratory Time 2"},
    {(int)SettingIds::STACKING_PRESSURE_1 , "Stacking Pressure 1"},
    {(int)SettingIds::STACKING_PRESSURE_2 , "Stacking Pressure 2"},
    {(int)SettingIds::O2 , "Oxygen"},
    {(int)SettingIds::PIP , "PIP"},
    {(int)SettingIds::AUX_FLOW , "Auxiliary Flow"},
    {(int)SettingIds::HUM_1 , "Humidity 1"},
    {(int)SettingIds::HUM_2 , "Humidity 2"},
    {(int)SettingIds::HUM_AUX , "Humidity Auxiliary"},
    {(int)SettingIds::ETCO2_RATE , "End-tidal CO2 Rate"},
    {(int)SettingIds::ETCO2_IT , "End-tidal CO2 Inspiratory Time"},
    {(int)SettingIds::ETCO2_NUM_BREATHS , "End-tidal CO2 Num Breaths"},
    {(int)SettingIds::ETCO2_DP , "End-tidal CO2 Driving Pressure"},
    {(int)SettingIds::LASER_O2 , "Laser-safe O2"},
    {(int)SettingIds::VOLUME , "Volume"}
};

/** @} */

