#pragma once
#include <map>
#include <string>

/**
 * @addtogroup subsystemsModels
 * @{
 */

/**
 * @file subsystems.h
 * @brief The enumerations and constants for subsystems.
 */

/**
 * @brief Number of subsystems.
 */
constexpr int NUM_SUBSYSTEMS = 7;

/**
 * @brief The enumerations for Subsystem IDs.
 */
enum class SubsystemIDs
{
    PRIMARY_VENTILATION = 0,
    SECONDARY_VENTILATION = 1,
    AUXILIARY_FLOW = 2,
    OXYGEN_CONTROL = 3,
    PRIMARY_HUMIDIFICATION = 4,
    SECONDARY_HUMIDIFICATION = 5,
    AUXILIARY_HUMIDITY = 6

};

/** @} */
