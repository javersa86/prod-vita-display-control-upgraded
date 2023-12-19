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

/** @} */
