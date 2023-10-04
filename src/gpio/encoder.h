#pragma once

#include <QObject>
#include "gpio.h"

/**
 * @addtogroup encoderModule
 * @{
 */

/**
 * @file encoder.h
 * @brief The header file for encoder.cpp with info.
 */

/**
 * @file encoder.cpp
 * @brief The encoder listens for changes on the A pin and the B pin and emits signals when the knob is turned.
 * @note Encapsulates the rotary knob behavior.
 */

/**
 * @brief The Encoder class
 */
class Encoder : public QObject
{
    /**
     * @addtogroup encoderModule
     * @{
     */

    Q_OBJECT
    public:

        /**
         * @brief   Constructor method for making a rotary encoder object.
         * @details For diffente paths: pin A and pin B
         *
         * @param[out] m_a_state
         * @param[out] m_b_state
         */
        Encoder();
    private:
        uint m_a_state;
        uint m_b_state;
        volatile int m_last_encoded;

        volatile int m_sum_0 = -1;
        volatile int m_sum_1 = -1;

        /**
         * @brief Updates m_last_state and emits a signal for +1 or -1 if the knob has been turned.
         */
        void updateEncoder();

    public:

        /**
         * @brief Slot for updating m_b_state when the b pin value changes. Calls updateEncoder.
         * @param value
         */
        void onPinAChange(unsigned char);

        /**
         * @brief Slot for updating m_b_state when the b pin value changes. Calls updateEncoder.
         * @param value
         */
        void onPinBChange(unsigned char);

        /**
         * @brief Updates m_a_state and m_b_state.
         * @param aState
         * @param bState
         */
        void setState(unsigned char, unsigned char);

    signals:
        /**
         * @brief Signal for when knob turns.
         * @param value
         * @callgraph
         */
        void encoderIncrement(unsigned char value);
    /** @} */

};

/** @} */
