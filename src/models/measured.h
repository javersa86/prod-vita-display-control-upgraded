#pragma once

/**
 * @addtogroup measuredModels
 * @{
 */

/**
 * @file measured.h
 * @brief List of IDs for Measured Values (obsolete).
 */

/**
 * @brief Number of measurements.
 */
constexpr int NUM_MEASURED_REQUESTS = 36;

/**
 * @brief The enumerations for Measured IDs.
 */
enum MeasuredRequests
{
    DRIVING_PRESSURE_1 = 0,
    DRIVING_PRESSURE_2 = 1,
    FREQUENCY_1 = 2,
    FREQUENCY_2 = 3,
    INSPIRATORY_TIME_1 = 4,
    INSPIRATORY_TIME_2 = 5,
    STACKING_PRESSURE_1 = 6,
    STACKING_PRESSURE_2 = 7,
    OXYGEN = 8,
    PIP = 9,
    AUX_FLOW = 10,
    HUMIDITY_1 = 11,
    HUMIDITY_2 = 12,
    HUMIDITY_AUX = 13,
    HEATER_TEMP = 14,
    AVG_FLOW_JET_1 = 15,
    AVG_FLOW_JET_2 = 16,
    WATER_SENSOR_JET_1 = 17,
    WATER_SENSOR_JET_2 = 18,
    WATER_SENSOR_JET_AUX = 19,
    TIDAL_VOLUME_JET_1 = 20,
    TIDAL_VOLUME_JET_2 = 21,
    MAP = 22,
    INLET_AIR_PRESSURE = 23,
    INLET_O2_PRESSURE = 24,
    PIP_ZERO_VALUE = 25,
    JET_1_STACKING_ZERO_VALUE = 26,
    JET_2_STACKING_ZERO_VALUE = 27,
    INLET_AIR_ZERO_VALUE = 28,
    INLET_O2_ZERO_VALUE = 29,
    O2_LOW_CAL_VALUE = 30,
    O2_HIGH_CAL_VAL = 31,
    O2_LOWER_BOUND = 32,
    O2_UPPER_BOUND = 33,
    REAL_CAL_VAL = 34,
    REAL_DPR_VAL = 35,
    SP_AVG = 36,
    SP_INST = 37,
    PIP_AVG = 38,
    PIP_INST = 39
};

/** @} */
