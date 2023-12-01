#pragma once

#include <QString>
#include <QDebug>
//#include <QtSerialPort/QSerialPort>

#include <stdio.h> // standard input / output functions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <iostream>
#include <cstring>
#include <sstream>

#include "message.h"

using namespace std;

/**
 * @addtogroup serialModule
 * @{
 */

/**
 * @brief Constant value for buffer size for transmitted messages.
 */
#define TX_BUFFER_SIZE 512

/**
 * @brief Constant value for buffer size for received messages.
 */
#define RX_BUFFER_SIZE 512

/**
 * @file serial.h
 * @brief The Header file for the serial.cpp file with info.
 */

/**
 * @file serial.cpp
 * @brief The Comm Object is the UART Serial Port between the Display Controller and the System Controller.
 */

/**
 * @brief The Comm class
 */
class Comm
{
    /**
     * @addtogroup serialModule
     * @{
     */

    private:
        QString _portname = QString();
        int _baudrate = 0;
        int fileDescriptor; // file description for the serial port

        unsigned char tx_buf[TX_BUFFER_SIZE] = {0};
        int tx_index = 0;
        unsigned char rx_buf[RX_BUFFER_SIZE] = {0};
        int rx_index = 0;
        int reading_cursor = 0;


    public:
        /**
         * @brief Default Constructor.
         */
        Comm() = default;

        /**
         * @brief   Opens the specified port and reads the file description.
         * @details Returns 1 if opening the serial port failed and 0 if opening the serial port succeeded.
         * @return  int
         */
        int openPort();

        /**
         * @brief   Configures the port settings to the specified baudrate, parity, stop bits, and data bits.
         * @details After reading the existing settings and handling errors, it constructs the tty settings structure to raise the following port settings:
         *          - Clears parity bit, disabling parity (most common).
         *          - Clears stop field, only one stop bit used in communication (most common).
         *          - Clear all bits that set the data size.
         *          - 8 bits per byte (most common).
         *          - Disable RTS/CTS hardware flow control (most common).
         *          - Turn on READ & ignore ctrl lines (CLOCAL = 1).
         *          - Disable echo.
         *          - Disable erasure.
         *          - Disable new-line echo.
         *          - Disable interpretation of INTR, QUI and SUSP.
         *          - Turn off s/w flow ctrl.
         *          - Disable any special handling of received bytes.
         *          - Prevent special interpretation of output bytes (e.g. newline chars).
         *          - Prevent conversion of newline to carriage return/line feed.
         *          - Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
         * @note   After saving the tty settings, checks for more errors.
         * @return int
         */
        int configurePort() const;

        /**
         * @brief Sets the serial communication port's portname.
         * @param portname
         */
        void setPortname(const QString &portname);
        /**
         * @brief  Gets the serial communication port's portname.
         * @return QString
         */
        QString getPortname() const;

        /**
         * @brief Sets the serial communication port's baudrate.
         * @param baudrate
         */
        void setBaudrate(int);
        /**
         * @brief  Gets the serial communication port's baudrate.
         * @return int
         */
        int getBaudrate() const;

        /**
         * @brief   Writes and empties the TX buffer into the serial port.
         * @details The TX buffer is an array of bytes to be sent to the System Controller and then emptied.
         *          It is not a circular queue and if one or more messages overflows the TX buffer, then those messages are skipped.
         */
        void writeToMCU();
        /**
         * @brief   Stores a byte into the TX buffer.
         * @details The buffer is a pointer to the command to queue into the TX buffer.
         *
         * @param byte
         */
        void addTX(unsigned char);

        /**
         * @brief   Writes single message from message queue into the serial port.
         * @details The message object returns a TX buffer, an array of bytes to be sent the System Controller.
         *
         * @param message
         */
        void writeTxMessageToMCU(Message message) const;

        /**
         * @brief   Reads and stores the available amount of bytes into the RX buffer.
         * @details The RX buffer is an array of bytes sent from the system controller.
         *
         * @return int
         */
        int readIncoming();

        /**
         * @brief  Gets the next byte from the RX buffer
         * @return unsigned char
         */
        unsigned char getRxByte();

        /**
         * @brief   Checks if the next byte is available for reading on the RX buffer.
         * @details Returns 0 if no more new bytes can be read or 1 if a new byte is available.
         * @return  unsigned char
         */
        unsigned char nextByteAvailable(void);

        /**
         * @brief Closes the serial port.
         */
        void closeSerial() const;
        /** @} */
};

/** @} */
