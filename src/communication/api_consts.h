#pragma once

#include "../models/modes.h"
#include "../models/sensors.h"
#include "../models/settings.h"
#include "../models/subsystems.h"

/**
 * @addtogroup apiModule
 * @{
 */

/**
 * @brief Constant for number of warnings in system.
 */
constexpr int NUM_WARNINGS = 72;

/**
 * @brief Constant for number of bytes used for warnings in notification vector.
 */
constexpr int NUM_WARNINGS_BYTES = 9;

/**
 * @brief Constant for number of bytes used for pneumatic setting values in notification vector.
 */
constexpr int NUM_SETTINGS_NOTIFICATIONS = 5;

/**
 * @brief Constant for number of bytes used for measured values in notification vector.
 */
constexpr int NUM_CALCULATIONS_NOTIFICATIONS = 3;

/**
 * @brief Constant for number of bytes used service calibration values.
 */
constexpr int NUM_SERVICE_NOTIFICATIONS = 5;

/**
 * @file api_consts.h
 * @brief The header file for enumerations used for API Messaging.
 */

/**
 * @brief Op Codes for transmitted messages.
 * @details Here is a detailed list of Op Codes:
 *          - Power On Received: 0
 *          - Get Settings Request: 1
 *          - Enable Notifications Request: 2
 *          - Get Op Modes Request: 3
 *          - Get Subsystem State Request: 4
 *          - Get System Version Request: 5
 *          - Set Settings Request: 6
 *          - Get Measured Request: 7
 *          - Clear Warning Request: 8
 *          - Enable Op Mode Request: 9
 *          - Enable Op Mode Response: 10
 *          - Notification Received: 11
 *          - Subsystem Status Received: 12
 *          - Ventilation Status Received: 13
 *          - HMI Button Pushed Received: 14
 *          - Shutdown Received: 15
 *          - Shutdown Confirmed and Cancelled: 16
 *          - Enable DPR Calibration Request: 17
 *          - Set DPR Calibration Value Request: 18
 *          - Confirm DPR Calibration Request: 19
 *          - Enable Pressure Sensor Zero Request: 20
 *          - Service Notification Received: 21
 *          - Service Calibration Response: 22
 */
enum class txOpCodes
{
    DISPLAY_POWER_ON_RECEIVED = 0,
    DISPLAY_GET_SETTINGS_REQUEST = 1,
    DISPLAY_ENABLE_NOTIFICATIONS_REQUEST = 2,
    DISPLAY_GET_OP_MODES_REQUEST = 3,
    DISPLAY_GET_SUBSYSTEM_STATE_REQUEST = 4,
    DISPLAY_GET_SYSTEM_VERSION_REQUEST = 5,

    DISPLAY_SET_SETTINGS_REQUEST = 6,
    DISPLAY_GET_MEASURED_REQUEST = 7,
    DISPLAY_CLEAR_WARNING_REQUEST = 8,

    DISPLAY_ENABLE_OP_MODE_REQUEST = 9,
    DISPLAY_ENABLE_OP_MODE_RESPONSE = 10,

    DISPLAY_NOTIFICATION_RECEIVED = 11,
    DISPLAY_SUBSYSTEM_STATUS_RECEIVED = 12,
    DISPLAY_VENTILATION_STATUS_RECEIVED = 13,
    DISPLAY_HMI_BUTTON_PUSHED_RECEIVED = 14,

    DISPLAY_SHUTDOWN_RECEIVED = 15,
    DISPLAY_SHUTDOWN_CONFIRM_SEND = 16,

    DISPLAY_ENABLE_DPR_CAL_REQUEST = 17, // Useless
    DISPLAY_SET_DPR_CAL_VAL_REQUEST = 18,
    DISPLAY_CONFIRM_DPR_CAL_REQUEST = 19, // Useless
    DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST = 20,

    DISPLAY_SERVICE_NOTIFICATION_RECEIVED = 21,
    DISPLAY_SERVICE_CALIBRATION_RESPONSE = 22
};

/**
 * @brief Buffer lengths for transmitted messages.
 * @details Here is a detailed list of Op Code lengths (excluding start byte and crc):
 *          - Power On Received: 1
 *          - Get Settings Request: 1
 *          - Enable Notifications Request: 2
 *          - Get Op Modes Request: 1
 *          - Get Subsystem State Request: 1
 *          - Get System Version Request: 1
 *          - Set Settings Request: 81
 *          - Get Measured Request: 2
 *          - Clear Warning Request: 2
 *          - Enable Op Mode Request: 4
 *          - Enable Op Mode Response: 3
 *          - Notification Received: 1
 *          - Subsystem Status Received: 1
 *          - Ventilation Status Received: 1
 *          - HMI Button Pushed Received: 2
 *          - Shutdown Received: 1
 *          - Shutdown Confirmed and Cancelled: 2
 *          - Enable DPR Calibration Request: 2
 *          - Set DPR Calibration Value Request: 2
 *          - Confirm DPR Calibration Request: 1
 *          - Enable Pressure Sensor Zero Request: 2
 *          - Service Notification Received: 1
 *          - Service Calibration Response: 33
 */
enum class txLengths
{
    DISPLAY_POWER_ON_RECEIVED = 1,

    DISPLAY_GET_SETTINGS_REQUEST = 1,
    DISPLAY_ENABLE_NOTIFICATIONS_REQUEST = 2,
    DISPLAY_GET_OP_MODES_REQUEST = 1,
    DISPLAY_GET_SUBSYSTEM_STATE_REQUEST = 1,
    DISPLAY_GET_SYSTEM_VERSION_REQUEST = 1,

    DISPLAY_SET_SETTINGS_REQUEST = 1 + NUM_SETTINGS *4,
    DISPLAY_GET_MEASURED_REQUEST = 2,
    DISPLAY_CLEAR_WARNING_REQUEST = 2,

    DISPLAY_ENABLE_OP_MODE_REQUEST = 4,
    DISPLAY_ENABLE_OP_MODE_RESPONSE = 3 * 1,

    DISPLAY_NOTIFICATION_RECEIVED = 1,
    DISPLAY_SUBSYSTEM_STATUS_RECEIVED = 1,
    DISPLAY_VENTILATION_STATUS_RECEIVED = 1,
    DISPLAY_HMI_BUTTON_PUSHED_RECEIVED = 2,

    DISPLAY_SHUTDOWN_RECEIVED = 1,
    DISPLAY_SHUTDOWN_CONFIRM_SEND = 2,

    DISPLAY_ENABLE_DPR_CAL_REQUEST = 2,
    DISPLAY_SET_DPR_CAL_VAL_REQUEST = 2,
    DISPLAY_CONFIRM_DPR_CAL_REQUEST = 1,
    DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST = 6 * 1,

    DISPLAY_SERVICE_NOTIFICATION_RECEIVED = 1,
    DISPLAY_SERVICE_CALIBRATION_RESPONSE = 1 + 8 * 4,
};

/**
 * @brief Op Codes for received messages.
 * @details Here is a detailed list of Op Codes:
 *          - Power On Send: 100
 *          - Get Settings Response: 101
 *          - Enable Notifications Response: 102
 *          - Get Op Modes Response: 103
 *          - Get Subsystem State Response: 104
 *          - Get System Version Response: 105
 *          - Set Settings Response: 106
 *          - Get Measured Response: 107
 *          - Clear Warning Response: 108
 *          - Enable Op Mode Response: 109
 *          - Enable Op Mode Request: 110
 *          - Notification Update: 111
 *          - Subsystem Status Update: 112
 *          - Ventilation Status Update: 113
 *          - HMI Button Pushed Update: 114
 *          - Shutdown Request: 115
 *          - Shutdown Confirm Received: 116
 *          - Enable DPR Calibration Response: 117
 *          - Set DPR Calibration Value Response: 118
 *          - Confirm DPR Calibration Response: 119
 *          - Enable Pressure Sensor Zero Response: 120
 *          - Service Notification Update: 121
 *          - Service Calibration Request: 122
 */
enum class rxOpCodes
{
    SYSTEM_POWER_ON_SEND = 100,

    SYSTEM_GET_SETTINGS_RESPONSE = 101,
    SYSTEM_ENABLE_NOTIFICATIONS_RESPONSE = 102,
    SYSTEM_GET_OP_MODES_RESPONSE = 103,
    SYSTEM_GET_SUBSYSTEM_STATE_RESPONSE = 104,
    SYSTEM_GET_SYSTEM_VERSION_RESPONSE = 105,

    SYSTEM_SET_SETTINGS_RESPONSE = 106,
    SYSTEM_GET_MEASURED_RESPONSE = 107,
    SYSTEM_CLEAR_WARNING_RESPONSE = 108,

    SYSTEM_ENABLE_OP_MODE_RESPONSE = 109,
    SYSTEM_ENABLE_OP_MODE_REQUEST = 110,

    SYSTEM_NOTIFICATION_UPDATE = 111,
    SYSTEM_SUBSYSTEM_STATUS_UPDATE = 112,
    SYSTEM_VENTILATION_STATUS_UPDATE = 113,
    SYSTEM_HMI_BUTTON_PUSHED_UPDATE = 114,

    SYSTEM_SHUTDOWN_REQUEST = 115,
    SYSTEM_SHUTDOWN_CONFIRM_RECEIVED = 116,

    SYSTEM_ENABLE_DPR_CAL_RESPONSE = 117,
    SYSTEM_SET_DPR_CAL_VAL_RESPONSE = 118,
    SYSTEM_CONFIRM_DPR_CAL_RESPONSE = 119,
    SYSTEM_ENABLE_PRESSURE_SENSOR_ZERO_RESPONSE = 120,

    SYSTEM_SERVICE_NOTIFICATION_UPDATE = 121,
    SYSTEM_SERVICE_CALIBRATION_REQUEST = 122
};

/**
 * @brief Buffer lengths for received messages.
 * @details Here is a detailed list of Op Code lengths (excluding start byte and crc):
 *          - Power On Send: 1
 *          - Get Settings Response: 81
 *          - Enable Notifications Response: 1
 *          - Get Op Modes Response: 16
 *          - Get Subsystem State Response: 8
 *          - Get System Version Response: 4
 *          - Set Settings Response: 1
 *          - Get Measured Response: 6
 *          - Clear Warning Response: 1
 *          - Enable Op Mode Response: 3
 *          - Enable Op Mode Request: 4
 *          - Notification Update: 47
 *          - Subsystem Status Update: 8
 *          - Ventilation Status Update: 2
 *          - HMI Button Pushed Update: 2
 *          - Shutdown Request: 1
 *          - Shutdown Confirm Received: 2
 *          - Enable DPR Calibration Response: 1
 *          - Set DPR Calibration Value Response: 1
 *          - Confirm DPR Calibration Response: 1
 *          - Enable Pressure Sensor Zero Response: 3
 *          - Service Notification Update: 21
 *          - Service Calibration Request: 1
 */
enum class rxLengths
{
    SYSTEM_POWER_ON_SEND = 1,

    SYSTEM_GET_SETTINGS_RESPONSE = 1 + NUM_SETTINGS *4,
    SYSTEM_ENABLE_NOTIFICATIONS_RESPONSE = 1,
    SYSTEM_GET_OP_MODES_RESPONSE = 1+NUM_MODES,
    SYSTEM_GET_SUBSYSTEM_STATE_RESPONSE = 1 + NUM_SUBSYSTEMS,
    SYSTEM_GET_SYSTEM_VERSION_RESPONSE = 4,

    SYSTEM_SET_SETTINGS_RESPONSE = 1,
    SYSTEM_GET_MEASURED_RESPONSE = 1 + 1 + 1 * 4,
    SYSTEM_CLEAR_WARNING_RESPONSE = 1,

    SYSTEM_ENABLE_OP_MODE_RESPONSE = 3 * 1,
    SYSTEM_ENABLE_OP_MODE_REQUEST = 4,

    SYSTEM_NOTIFICATION_UPDATE = 1+NUM_SETTINGS_NOTIFICATIONS*4 + NUM_CALCULATIONS_NOTIFICATIONS*4 + NUM_WARNINGS_BYTES + 1,
    SYSTEM_SUBSYSTEM_STATUS_UPDATE = 1 + NUM_SUBSYSTEMS,
    SYSTEM_VENTILATION_STATUS_UPDATE = 2,
    SYSTEM_HMI_BUTTON_PUSHED_UPDATE = 2,

    SYSTEM_SHUTDOWN_REQUEST = 1,
    SYSTEM_SHUTDOWN_CONFIRM_RECEIVED = 2,

    SYSTEM_ENABLE_DPR_CAL_RESPONSE = 1,
    SYSTEM_SET_DPR_CAL_VAL_RESPONSE = 1,
    SYSTEM_CONFIRM_DPR_CAL_RESPONSE = 1,
    SYSTEM_ENABLE_PRESSURE_SENSOR_ZERO_RESPONSE = 3 * 1,

    SYSTEM_SERVICE_NOTIFICATION_UPDATE = 1 + NUM_SERVICE_NOTIFICATIONS*4,
    SYSTEM_SERVICE_CALIBRATION_REQUEST = 1
};
/** @} */
