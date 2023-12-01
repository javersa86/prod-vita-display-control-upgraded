#pragma once

/**
 * @addtogroup hmiModels
 * @{
 */

/**
 * @file hmi_buttons.h
 * @brief The HMI Buttons.
 */

/**
 * @brief Number of buttons tracked.
 */
constexpr int NUM_BUTTONS = 3;

/**
 * @brief The Enumerations for HMI Buttons.
 */
enum HMIButtons
{
    POWER = 0,
    START_STOP = 1,
    ALARM_MUTE = 2,
    DIAL_PUSH = 3
};

/** @} */
