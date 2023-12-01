#pragma once

#include <iostream>
#include <libusb-1.0/libusb.h>
#include <iterator>
#include <map>

/**
 * @addtogroup devicesModule
 * @{
 */

/**
 * @file devices.h
 * @brief The Header file for the devices.cpp file with info.
 */

/**
 * @file devices.cpp
 * @brief Tracks the number of devices mounted to the display controller via USB.
 */

/**
 * @brief The devices class
 */
class devices
{
    /**
     * @addtogroup devicesModule
     * @{
     */
    public:
        /**
         * @brief Default Constructor.
         */
        devices() = default;
        //Devices connected at the time of collection.

        /**
         * @brief Gets the number of USB devices connected to the NVENT-Vita.
         * @note Devices should be connected at the time of collection.
         * @return size_t
         */
        static size_t deviceCount();
        /** @} */

};

/** @} */

