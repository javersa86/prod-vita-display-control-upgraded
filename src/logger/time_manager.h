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
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

/**
 * @addtogroup timeManagerModule
 * @{
 */

/**
 * @file time_manager.h
 * @brief Header for time_manager.cpp with info.
 */

/**
 * @file time_manager.cpp
 * @brief Manages the digital clock on the device.
 */

/**
 * @brief Name of csv file that stores digital clock information.
 */
#define TIME_FILE "time.csv"

/**
 * @brief Name of row for date and time displayed on screen.
 */
#define DATE_TIME "DATE & TIME      "

/**
 * @brief Name of row for time zone.
 */
#define TIME_ZONE "TIME ZONE        "

/**
 * @brief Name of row for date and time tracked within display controller.
 */
#define INTERNAL  "INTERNAL         "

/**
 * @brief Name of row for daylight savings.
 */
#define DAYLIGHT_SAVINGS  "DAYLIGHT SAVINGS "

/**
 * @brief Costant string and values for time zones.
 */
const std::map<QString,int> timeZoneValues = {
    {"EDT", -4},
    {"EST", -5},
    {"CDT", -5},
    {"CST", -6},
    {"MDT", -7},
    {"MST", -7},
    {"PDT", -7},
    {"PST", -8},
    {"AKDT",-8},
    {"AKST",-9},
    {"HADT",-9},
    {"HAST",-10}
};

/**
 * @brief Constant strings for daylight savings time zones.
 */
const std::vector<std::string> daylightSavingsTimeZones = {
    "EDT",
    "CDT",
    "MDT",
    "PDT",
    "AKDT",
    "HADT"
};

/**
 * @brief Constant strings for standard time zones.
 */
const std::vector<std::string> standardTimeZones = {
    "EST",
    "CST",
    "MST",
    "PST",
    "AKST",
    "HAST"
};

/**
 * @brief The TimeManager class
 */
class TimeManager : public QObject
{
    /**
     * @addtogroup timeManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief currentDateTime
     */
    Q_PROPERTY(QString currentDateTime READ getCurrentDateTime NOTIFY timeChanged)

    /**
     * @brief daylightSavings
     */
    Q_PROPERTY(unsigned char daylightSavings READ getDaylightSavings NOTIFY daylightChanged)

    public:
        /**
         * @brief   Constructor Method that updates all time componets at start and starts the timer for digital clock.
         * @param parent
         */
        TimeManager(QObject *parent = nullptr);

        /**
         * @brief Gets current date, time, and time zone.
         * @return QString
         */
        QString getCurrentDateTime();

    private:
        CSVManager m_timeCsvManager;

        QDateTime m_current_date_time;
        QString m_time_zone;
        QDateTime m_internal;

        QTimer *m_increment_time;

        QDate m_temp_date;
        QTime m_temp_time;
        int m_temp_time_zone;

        unsigned char m_date_state = 0;
        unsigned char m_time_state = 0;
        unsigned char m_time_zone_state = 0;

        unsigned char m_daylight_savings_state = 0;

        /**
         * @brief   Retrieves current date time, time zone, and internal clock's date and time onto .csv file.
         * @details  Stores current variables for changed date and time, time zone, and internal clock's date and time.
         *           Updates whenever devices powers on or when date/time changes.
         */
        void updateTime();

        /**
         * @brief Gets the time different between current date and time and internal date and time.
         * @return qint64
         */
        qint64 getTimeDifference(QString);

        /**
         * @brief Updates time when time zone is updated.
         */
        void getTimeZoneDifference(QString,QString);

    public slots:

        /**
         * @brief Sets the current date.
         * @param temp
         * @callergraph
         */
        void setCurrentDate(QString);

        /**
         * @brief Sets the current time.
         * @param hours
         * @param minutes
         * @param shift
         * @callergraph
         */
        void setCurrentTime(QString,QString,QString);

        /**
         * @brief Sets current time zone.
         * @param temp
         * @callergraph
         */
        void setTimeZone(QString);

        /**
         * @brief Increments the current date and time, and the internal date and time by 1 second.
         * @callergraph
         */
        void setTime();

        /**
         * @brief Gets the state of daylight savings.
         * @return unsigned char
         */
        unsigned char getDaylightSavings();

        /**
         * @brief Switches between daylight savings.
         * @callergraph
         */
        void updateDaylightSavings();

        /**
         * @brief Sets daylight savings.
         * @param value
         * @callergraph
         */
        void updateDalyightSavingsForced(unsigned char value);

    signals:

        /**
         * @brief Signal for when date and time is updated.
         * @callgraph
         */
        void timeChanged();

        /**
         * @brief Signal for when daylight savings is updated.
         * @callgraph
         */
        void daylightChanged();
        /** @} */
};

/** @} */
