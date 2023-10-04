#pragma once

#include <QThread>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>

#include <queue>
#include <QDebug>
#include <unordered_set>

#include <stdio.h>
#include <string.h>

#include "message.h"

/**
 * @addtogroup messageQueueModule
 * @{
 */

/**
 * @file message_queue.cpp
 * @brief The header file for message_queue.cpp with info.
 */

/**
 * @file message_queue.h
 * @brief The Message Queue stores TX Message that need to sent to the system controller.
 * @note The Queue is thread safe.
 */

/**
 * @brief The MessageQueue class
 */
class MessageQueue
{
    /**
     * @addtogroup messageQueueModule
     * @{
     */

    public:
        /**
         * @brief Empty Constructor.
         */
        MessageQueue() {}

        /**
         * @brief Pushes the message to the queue.
         * @note If the message already exists and has the safe CRC, it will not be pushed.
         * @param message
         */
        void push(Message message);

        /**
         * @brief Pops and returns a message from the queue.
         * @note If the queue is empty, an empty message will be returned instead.
         * @return Message
         */
        Message pop();

        /**
         * @brief Returns true or false if queue is empty.
         * @return bool
         */
        bool empty() const;

        /**
         * @brief Returns size of queue.
         * @return int
         */
        int size() const;

        /**
         * @brief Locks mutex of QThread.
         */
        void lock();

        /**
         * @brief Pauses QThread.
         */
        void wait();

        /**
         * @brief Wakes QThread.
         */
        void wake();

    private:
        /**
         * @brief Used to lock the queue from the API Thread.
         */
        mutable QMutex m_mutex;
        /**
         * @brief Stores messages.
         */
        QQueue<Message> m_queue;
        /**
         * @brief Stores CRC characters to ensure that the safe message wont be stored.
         */
        std::unordered_set<unsigned char> m_crc_set;

        QWaitCondition m_dataAvailable;
        /** @} */
};

/** @} */


