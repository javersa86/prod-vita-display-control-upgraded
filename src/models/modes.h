#pragma once
#include <map>
#include <string>

/**
 * @addtogroup opModeModels
 * @{
 */

/**
 * @file modes.h
 * @brief Enumarations and Constants for Mode IDs and Names.
 */

/**
 * @brief Number of modes on the system.
 */
#define NUM_MODES 15

/**
 * @brief Enumerations for Mode IDs.
 */
enum class ModeIDs
{
    LASER_MODE = 0,
    DOUBLE_JET_MODE = 1,
    MANUAL_MODE = 2,
    SCREEN_LOCK_MODE = 3,
    DEMO_MODE = 4,
    PIP_MONITORING_MODE = 5,
    ETCO2_MODE = 6,
    DEHUMIDIFY_MODE = 7,
    O2_CALIBRATION_MODE = 8,
    ALARM_SOUNDING = 9,
    HUMIDITY_PRIMING_RESET_AVAILABLE = 10,
    LISTENING_KNOB = 11,
    SOUND_ICON = 12,
    CALIBRATION_MODE = 13,
    SCREEN_LOCK_TOUCHED_MODE = 14
};

/**
 * @brief Constants for Mode Names.
 */
const std::map<int,std::string> modeNameMap = {
        {(int)ModeIDs::LASER_MODE , "Laser-safe O2"},
        {(int)ModeIDs::DOUBLE_JET_MODE , "Double Jet"},
        {(int)ModeIDs::MANUAL_MODE , "Manual"},
        {(int)ModeIDs::SCREEN_LOCK_MODE , "Screen Lock"},
        {(int)ModeIDs::DEMO_MODE , "Demo"},
        {(int)ModeIDs::PIP_MONITORING_MODE , "PIP Monitoring"},
        {(int)ModeIDs::ETCO2_MODE , "ETCO2"},
        {(int)ModeIDs::DEHUMIDIFY_MODE , "Dehumidify"},
        {(int)ModeIDs::O2_CALIBRATION_MODE , "O2 Calibration"},
        {(int)ModeIDs::ALARM_SOUNDING , "Alarm Sounding"},
        {(int)ModeIDs::HUMIDITY_PRIMING_RESET_AVAILABLE, "Humidity Priming Reset Available"},
        {(int)ModeIDs::LISTENING_KNOB, "DC is listening to the knob"},
        {(int)ModeIDs::SOUND_ICON, "Sound Icon Activated"},
        {(int)ModeIDs::CALIBRATION_MODE, "Calibration is active."},
        {(int)ModeIDs::SCREEN_LOCK_TOUCHED_MODE, "Screen Lock Touched."}
};

/** @} */
