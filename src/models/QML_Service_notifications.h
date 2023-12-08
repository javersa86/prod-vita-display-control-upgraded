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
            INLET_AIR_AVG = 4,
            INLET_AIR_INST = 5,
            INLET_O2_AVG = 6,
            INLET_O2_INST = 7,
            CAL_VAL = 8
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
