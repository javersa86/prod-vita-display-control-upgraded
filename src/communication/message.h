#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <QString>
#include <QVector>

/**
 * @addtogroup messageModule
 * @{
 */

/**
 * @brief Constant value for buffer size for message sent to api.
 */
#define INPUT_BUFFER_SIZE 512

/**
 * @brief Constant character that appears at the beginning of all messages.
 */
#define START_CHAR 255

/**
 * @file message.h
 * @brief The Header file for the message.cpp file with info.
 */

/**
 * @file message.cpp
 * @brief The Message Object stores a TX Buffer that will be sent.
 */

/**
 * @brief The Message class
 */
class Message
{
    /**
     * @addtogroup messageModule
     * @{
     */

    public:
        /**
         * @brief Empty Constructor
         */
        Message() = default;

        /**
         * @brief Contructs the unsigned char array representing the TX Message.
         * @note  All messages will have the start character, message variables, and the CRC charater at the end.
         * @param data
         * @param crc
         * @param tx_size
         */
        Message(const unsigned char* data, unsigned char crc, int tx_size);

        /**
         * @brief Gets the CRC character of the message.
         * @return unsigned char
         */
        unsigned char getCRC() const;

        /**
         * @brief Gets the unsigned char array representing the TX Buffer of the message.
         * @return unsigned char *
         */
        unsigned char * getMessage();

        /**
         * @brief Gets the size of the TX Buffer.
         * @return int
         */
        int getSize() const;

        /**
         * @brief Returns a string representation of the TX Buffer.
         * @return QString
         */
        QString toString();

    private:
        QVector<unsigned char> m_message = QVector<unsigned char>(INPUT_BUFFER_SIZE, 0); //[INPUT_BUFFER_SIZE] = {0};
        unsigned char m_crc = 0;
        int m_tx_size = 0;
        /** @} */
};

/** @} */

