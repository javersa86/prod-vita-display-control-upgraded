#pragma once

#include <QObject>
#include <fcntl.h>
#include <cstdio>
#include <syslog.h>
#include <unistd.h>
#include <poll.h>
#include <QDebug>

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
 * @brief MAX Buffer size for pin update.
 */
constexpr int ENCODER_MAX_BUF = 64;

/**
 * @brief Constant string for file path for gpio.
 */
constexpr const char* SYSFS_GPIO_DIR = "/sys/class/gpio";

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

        bool _is_out = true;

        int	_ioFd = -1;

        uint _currentValue = 2;
        uint _pinNumber;

        /**
         * @brief Used to export the pin. If not exported, we cannot interact with the pin
         * @return int
         */
        int	exportPin() const;

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
        explicit GPIO(uint pinNumber, char* edge, bool isOut, QObject *parent = nullptr);
        /**
         * @brief GPIO destructor. Closes the pin
         */
        ~GPIO() override;

        GPIO(const GPIO&) = delete;
        GPIO& operator=(const GPIO&) = delete; // Delete the copy assignment operator
        GPIO(GPIO&&) = delete; // Delete the move constructor
        GPIO& operator=(GPIO&&) = delete; // Delete the move assignment operator

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
        int setEdge(char *edge) const;

        //int setValue(uint value);
        /**
         * @brief watch
         */
        void watch();

        /**
         * @brief Gets the file descriptor for the pin
         * @return int
         */
        int getFD() const;

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

