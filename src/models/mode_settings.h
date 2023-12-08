#pragma once

#include <QString>
/*
 * This is a class to model mode settings. Mode Settings include laser o2, ECTO2 inspiratory time, and ETCO2 rate.
 *
 */

/**
 * @addtogroup opModeModels
 * @{
 */

/**
 * @file mode_settings.h
 * @brief Header to mode_settings.cpp with info.
 */

/**
 * @file mode_settings.cpp
 * @brief This is a class to model mode settings. Mode Settings include laser o2, ECTO2 inspiratory time, and ETCO2 rate.
 */

/**
 * @brief The ModeSetting class
 */
class ModeSetting
{
    /**
     * @addtogroup opModeModels
     * @{
     */
    public:
    
        /**
         * @brief Empty Constructor
         */
        ModeSetting() = default;
    
        /**
         * @brief Constructor method for mode with min/max value and increments.
         * @param id
         * @param min
         * @param max
         * @param step
         */
        ModeSetting(int mode_id, int min, int max, int step);
    
        /**
         * @brief Sets mode value.
         * @param value
         */
        void value(int value);
    
        /**
         * @brief Gets mode value.
         * @return int
         */
        int value() const;
    
        /**
         * @brief Gets mode id.
         * @return int
         */
        int id() const;
    
        /**
         * @brief Gets mode increment change limit.
         * @return int
         */
        int step() const;
    
        /**
         * @brief Gets min limit for mode.
         * @return int
         */
        int min() const;
    
        /**
         * @brief Gets max limit for mode.
         * @return int
         */
        int max() const;
    
    private:
        int m_value = -1;
        int m_id = -1;
        int m_min = -1;
        int m_max = -1;
        int m_step = -1;
        /** @} */
};

/** @} */

