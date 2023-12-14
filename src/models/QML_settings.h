#pragma once
#include <QObject>
#include <QtQml/QQmlEngine>

/**
 * @addtogroup settingsModels
 * @{
 */

/**
 * @file QML_settings.h
 * @brief Exposes setting threshold Indexes to the QML.
 */

//This file is used to expose setting threshold Indexes to the QML
/**
 * @brief The SettingIndex class
 */
class SettingIndex : public QObject
{
    /**
     * @addtogroup settingsModels
     * @{
     */

    Q_OBJECT
    public:
        /**
         * @brief Empty Constructor
         * @param parent
         */
        SettingIndex(QObject *parent = nullptr) : QObject(parent){}

        /**
         * @brief The Index Enumerations for Setting Updates on QML files.
         */
        enum Index
        {
            DRIVING_PRESSURE_1 = 0,
            DRIVING_PRESSURE_2 = 1,
            RATE_1 = 2,
            RATE_2 = 3,
            INSPIRATORY_TIME_1 = 4,
            INSPIRATORY_TIME_2 = 5,
            STACKING_PRESSURE_1 = 6,
            STACKING_PRESSURE_2 = 7,
            O2 = 8,
            PIP = 9,
            AUX_FLOW = 10,
            HUM_1 = 11,
            HUM_2 = 12,
            HUM_AUX = 13
            };
        Q_ENUM(Index)

        /**
         * @brief Declare QML variables for Settings.
         */
        static void declareQML()
        {
            qmlRegisterType<SettingIndex>("SettingIndex", 1, 0, "Index");
        }
        /** @} */

};

/** @} */
