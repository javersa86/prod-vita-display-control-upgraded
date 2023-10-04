#pragma once

#include <QObject>
#include "gpio.h"

/**
 * @addtogroup switchModule
 * @{
 */

/**
 * @file switch.h
 * @brief The header file for switch.cpp with info.
 */

/**
 * @file switch.cpp
 * @brief The button meant to be pushed down on the knob.
 */

/**
 * @brief The Switch class
 */
class Switch : public QObject
{
    /**
     * @addtogroup switchModule
     * @{
     */

    Q_OBJECT
    public:

        /**
         * @brief Constructor to set up the button in the rotary knob.
         * @note  Switch includes path to thee switch pin value file.
         * @param pin_path
         */
        Switch();

    private:
        uint m_state;
        unsigned char m_ignore = 0;

    signals:

        /**
         * @brief Signal for when button is pushed.
         * @callgraph
         */
        void push(); //param in/out

    public:

        /**
         * @brief Slot to listen for button pushes. Only emits a signal on the release of the button.
         * @param value
         */
        void onPinChange(unsigned char);

        /**
         * @brief Updates states of the switch.
         * @param value
         */
        void setState(unsigned char);
        /** @} */
};

/** @} */
