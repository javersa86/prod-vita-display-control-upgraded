#pragma once

#include <QObject>

/**
 * @addtogroup gpioMainModule
 * @{
 */

/**
 * @file gpio.h
 * @brief The header file for gpio.cpp with info.
 */

/**
 * @file gpio.cpp
 * @brief Represents a pin connected to the microcontroller.
 * @note General Purpose Input/Output
 */

/**
 * @brief The GPIO class
 */
class GPIO : public QObject{

    /**
     * @addtogroup gpioMainModule
     * @{
     */

    Q_OBJECT

    private:
        bool _isOut;

        int	_ioFd;

        uint _currentValue;
        uint _pinNumber;

        /**
         * @brief Used to export the pin. If not exported, we cannot interact with the pin
         * @return int
         */
        int	exportPin();

        /**
         * @brief Used to set the file direction of the pin. If out, direction will be out. Otherwise, direction will be in.
         * @param out
         * @return int
         */
        int	setDirection(bool out);

    public:

        /**
         * @brief GPIO pin contructor. Exports the pin with number pinNumber, in direction isOut with edge.
         * @param pinNumber
         * @param edge
         * @param isOut
         * @param parent
         */
        explicit GPIO(uint pinNumber, char* edge, bool isOut = true, QObject *parent = 0);
        /**
         * @brief GPIO destructor. Closes the pin
         */
        ~GPIO();

        /**
         * @brief Gets the current value of a pin
         * @return
         */
        unsigned char getValue();

        /**
         * @brief Used to open file descriptor of pin so that we may read it.
         */
        void openFd();

        /**
        * @brief Sets the edge of pin. Rising, Falling, or both.
        * @param edge
        * @return int
        */
        int setEdge(char *edge);

        //int setValue(uint value);
        /**
         * @brief watch
         */
        void watch();
        /**
         * @brief run
         * @return
         */
        int run();

        /**
         * @brief Gets the file descriptor for the pin
         * @return int
         */
        int getFD();

    signals:
        /**
         * @brief Signal for when pin changes.
         * @callgraph
         */
        void pinChange(unsigned char);

    public slots:
        /** @} */
};

/** @} */

