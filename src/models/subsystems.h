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
#define NUM_SUBSYSTEMS 7

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

/**
 * @brief The contant values for Subsystem names.
 */
const std::map<int,std::string> subsystemNameMap = {
        {(int)SubsystemIDs::PRIMARY_VENTILATION , "Primary Ventilation"},
        {(int)SubsystemIDs::SECONDARY_VENTILATION , "Secondary Ventilation"},
        {(int)SubsystemIDs::AUXILIARY_FLOW , "Auxiliary Flow"},
        {(int)SubsystemIDs::OXYGEN_CONTROL , "Oxygen Control"},
        {(int)SubsystemIDs::PRIMARY_HUMIDIFICATION , "Primary Humidification"},
        {(int)SubsystemIDs::SECONDARY_HUMIDIFICATION , "Secondary Humidification"},
        {(int)SubsystemIDs::AUXILIARY_HUMIDITY , "Auxiliary Humidity"}
};

/** @} */
