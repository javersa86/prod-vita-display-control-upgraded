#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QByteArray>
#include <QLocale>
#include <QTimer>

/**
 * @addtogroup versionManagerModule
 * @{
 */

/**
 * @file version_manager.h
 * @brief Header for version_manager.cpp with info.
 */

/**
 * @file version_manager.cpp
 * @brief Manages the system version numbers on the device.
 */

/**
 * @brief Name of csv file that stores system controller version number.
 */
#define VERSION_FILE "versions.csv"

/**
 * @brief Name of row for HMI version number.
 */
#define HMI "HMI"

/**
 * @brief Name of row for serial number.
 */
#define SERIAL_NUMBER "SERIAL NUMBER"

/**
 * @brief The VersionManager class
 */
class VersionManager: public QObject
{
    /**
     * @addtogroup versionManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief hmiVersion
     */
    Q_PROPERTY(QString hmiVersion READ getHmiVersion NOTIFY versionChanged)
    /**
     * @brief serialNumber
     */
    Q_PROPERTY(QString serialNumber READ getSerialNumber NOTIFY versionChanged)

    private:
        CSVManager m_versionCsvManager;

        QString m_hmiVersion;
        QString m_serialNumber;

        /**
         * @brief   Retrieves current HMI Version and Serial Number from .csv file.
         * @details Stores current values onto vectors. Updates whenever device powers on or whenever info changes.
         */
        void updateVersions();

    public:

        /**
         * @brief Constructor Method.
         * @param parent
         */
        VersionManager(QObject *parent = nullptr);

        /**
         * @brief Gets HMI Version.
         * @return QString
         */
        QString getHmiVersion();

        /**
         * @brief Gets Serial Number.
         * @return QString
         */
        QString getSerialNumber();

    public slots:
        /**
         * @brief Logs HMI Version and Serial Number to service logs.
         * @callergraph
         */
        void logVersions();

        /**
         * @brief Manually updates the text for the Serial Number.
         * @param serial
         */
        void updateSerialNumber(QString serial);
        /**
         * @brief Confirm and saves updated to CSV file for the Serial Number.
         */
        void confirmSerialNumber();

        /**
         * @brief Add digit to the Serial Number.
         * @param input
         */
        void addDigit(QString input);
        /**
         * @brief Remove digit from the Serial Number.
         */
        void removeDigit();

    signals:

        /**
         * @brief Signal for when HMI Version and Serial Number is updated.
         * @callgraph
         */
        void versionChanged();
        /** @} */
};

/** @} */
