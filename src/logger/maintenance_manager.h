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
 * @addtogroup maintenanceManagerModule
 * @{
 */

/**
 * @brief Name of csv file for maintenance manager.
 */
#define MAINTENANCE_FILE "maintenance.csv"

/**
 * @brief Name of row for last service date.
 */
#define LAST_DATE "LAST SERVICE DATE"

/**
 * @brief Name of row for next service date.
 */
#define NEXT_DATE "NEXT SERVICE DATE"

/**
 * @file maintenance_manager.h
 * @brief Header for maintenance_manager.cpp with info.
 */

/**
 * @file maintenance_manager.cpp
 * @brief Manages the dates for servicing.
 */

/**
 * @brief The MaintenanceManager class
 */
class MaintenanceManager : public QObject
{
    /**
     * @addtogroup maintenanceManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief lastServiceDate
     */
    Q_PROPERTY(QString lastServiceDate READ getLastServiceDate WRITE setLastServiceDate NOTIFY dateChanged)
    /**
     * @brief nextServiceDate
     */
    Q_PROPERTY(QString nextServiceDate READ getNextServiceDate WRITE setNextServiceDate NOTIFY dateChanged)

    /**
     * @brief lastTodayDate
     */
    Q_PROPERTY(QString lastTodayDate READ updateLastTodayDate NOTIFY dateChanged);
    /**
     * @brief nextTwelveMonthDate
     */
    Q_PROPERTY(QString nextTwelveMonthDate READ updateNextTwelveMonthDate NOTIFY dateChanged);

    public:
        /**
         * @brief Constructor Method.
         * @param parent
         */
        MaintenanceManager(QObject *parent = nullptr);

        /**
         * @brief Gets last service date.
         * @return QString
         */
        QString getLastServiceDate();
        /**
         * @brief Gets next service date.
         * @return QString
         */
        QString getNextServiceDate();

        /**
         * @brief Gets today's date.
         * @return QString
         */
        QString updateLastTodayDate();
        /**
         * @brief Sets next service date as the date 12 months from the last service date and returns new date.
         * @note New date must also be the first of the month.
         *
         * @return QString
         */
        QString updateNextTwelveMonthDate();

    private:
        CSVManager m_maintenanceCsvManager;
        QString m_last_date;
        QString m_next_date;

        CSVManager m_timeCsvManager;
        QTimer *m_timer;

        unsigned char m_alarm_state = 0;
        int m_timer_count = 0;

        /**
         * @brief Retrieves current dates onto .csv file and stores the current variables for last service date and next service date.
         * @note Updates whenever devices powers on or whenever dates change.
         */
        void updateServiceDates();

        /**
         * @brief Reads from time manager to update Service Due Warning.
         */
        void raiseAlarm();

    public slots:
        /**
         * @brief Sets last service date.
         * @param newDate
         * @callergraph
         */
        void setLastServiceDate(QString);
        /**
         * @brief Sets next service date.
         * @param newDate
         * @callergraph
         */
        void setNextServiceDate(QString);

        void isValid(QString, QString, QString);

        void startTimer();

    signals:

        /**
         * @brief Signal for when service dates change.
         * @callgraph
         */
        void dateChanged();

        void validation(bool value);

        void alarmSignal(unsigned char);
        /** @} */

};

/** @} */
