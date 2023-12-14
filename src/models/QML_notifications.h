#pragma once
#include <QObject>
#include <QtQml/QQmlEngine>

/**
 * @addtogroup notificationModels
 * @{
 */

/**
 * @file QML_notifications.h
 * @brief Exposes Notification Indexes to the QML.
 */

//This file is used to expose Notification Indexes to the QML
/**
 * @brief The NotificationIndex class
 */
class NotificationIndex : public QObject
{

    /**
     * @addtogroup notificationModels
     * @{
     */

    Q_OBJECT
    public:
        /**
         * @brief Empty Constructor
         * @param parent
         */
        NotificationIndex(QObject *parent = nullptr) : QObject(parent){}

        /**
         * @brief The Index Enumerations for Notification Updates on QML files.
         */
        enum Index
        {
            STACKING_PRESSURE_1 = 0,
            STACKING_PRESSURE_2 = 1,
            O2 = 2,
            PIP = 3,
            AUX = 4,
            TV_1 = 5,
            TV_2= 6,
            MAP = 7,
            ALARM_SILENCE_TIMER = 8
        };
        Q_ENUM(Index)

        /**
         * @brief Declare QML variables for Notifications.
         */
        static void declareQML()
        {
            qmlRegisterType<NotificationIndex>("NotificationIndex", 1, 0, "Index");
        }
        /** @} */

};

/** @} */
