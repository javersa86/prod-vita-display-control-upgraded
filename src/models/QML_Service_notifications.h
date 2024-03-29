#pragma once
#include <QObject>
#include <QtQml/QQmlEngine>

/**
 * @addtogroup serviceNotificationModels
 * @{
 */

/**
 * @file QML_Service_notifications.h
 * @brief Exposes Service Notifications Indexes to the QML.
 */

//This file is used to expose Notification Indexes to the QML
/**
 * @brief The ServiceNotificationIndex class
 */
class ServiceNotificationIndex : public QObject
{

    /**
     * @addtogroup serviceNotificationModels
     * @{
     */

    Q_OBJECT
    public:
        /**
         * @brief
         * @param parent
         */
        ServiceNotificationIndex(QObject *parent=nullptr) : QObject(parent){};

        enum Index
        {
            SP_AVG = 0,
            SP_INST = 1,
            PIP_AVG = 2,
            PIP_INST = 3,
            CAL_VAL = 4
        };
        Q_ENUM(Index);

        /**
         * @brief Declare QML variables for Service Notifications.
         */
        static void declareQML()
        {
            qmlRegisterType<ServiceNotificationIndex>("ServiceNotificationIndex",1,0,"Index");
        }
        /** @} */
};

/** @} */
