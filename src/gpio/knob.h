#pragma once

#include <QObject>
#include "gpio.h"
#include "switch.h"
#include "encoder.h"
#include <QThread>

/**
 * @addtogroup knobModule
 * @{
 */

/**
 * @file knob.h
 * @brief The header file for knob.cpp with info.
 */

/**
 * @file knob.cpp
 * @brief The controller for the encoder knob that translates rotational motion into digital signals.
 */

/**
 * @brief The Knob class
 */
class Knob : public QThread
{
    /**
     * @addtogroup knobModule
     * @{
     */

    Q_OBJECT
    public:

        /**
         * @brief Constructor to make a whole knob consisting of a rotary encoder and a button.
         * @details Paths include the following:
         *          - The path to pin a for the rotary encoder.
         *          - The path to pin b for the rotary encoder.
         *          - The path to the switch for the button.
         * @param pin_a
         * @param pin_b
         * @param pin_switch
         */
        Knob(uint, uint, uint);

        /**
         * @brief Loops to listen to the knob. Loops while m_running is true.
         */
        void run();

    private:
        Switch* button;
        Encoder* encoder;

        GPIO* m_pinA;
        GPIO* m_pinB;
        GPIO* m_pinButton;

    public slots:

        /**
         * @brief Listens to the knob if listening is enabled. Else, stops listening to the knob.
         * @param listen
         * @callergraph
         */
        void listen(unsigned char);

    private slots:

        /**
         * @brief   Emits a signal when the knob is turned.
         * @details Signal emitted include the following:
         *          - 1 when turned clockwise
         *          - 0 when turned counter clockwise
         * @param value
         * @callergraph
         */
        void onEncoderIncrement(unsigned char);

        /**
         * @brief Emits a signal when the button is pushed.
         * @callergraph
         */
        void onButtonPush();



    signals:
        /**
         * @brief Signal for increment or decrementing the knob value -> 1 = +1 and 0 = -1.
         * @param encoderVal
         * @callgraph
         */
        void encoderIncrement(int encoderVal); //increment or decrement the knob value -> 1 = +1; 0= -1
        /**
         * @brief Signal for when button is pushed.
         * @callgraph
         */
        void buttonPush();

    private:
        int m_encoderIncrement{0};
        bool m_running = false;

        /** @} */
};

/** @} */
