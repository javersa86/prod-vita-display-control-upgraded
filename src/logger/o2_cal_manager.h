#pragma once
#include "csv_manager.h"
#include <iomanip>
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QTimer>
#include <sstream>
#include <time.h>

/**
 * @addtogroup o2CalManagerModule
 * @{
 */

/**
 * @file o2_cal_manager.h
 * @brief Header for o2_cal_manager.cpp with info.
 */

/**
 * @file o2_cal_manager.cpp
 * @brief Manages the O2 Calibration values for O<sub>2</sub> Calibration.
 */

/**
 * @brief Name of title for O<sub>2</sub> Calibration Manager csv file.
 */
#define O2_CAL_FILE "o2_cal_vals.csv"

/**
 * @brief Number of O<sub>2</sub> Columns for O<sub>2</sub> Calibration Manager.
 */
#define MAX_O2_VALS 5

/**
 * @brief The O2CalManager class
 */
class O2CalManager : public QObject
{
    /**
     * @addtogroup o2CalManagerModule
     * @{
     */
     
     Q_OBJECT

    /**
     * @brief mostRecentTimeStamp
     */
    Q_PROPERTY(QString mostRecentTimeStamp READ getMostRecentTimeStamp NOTIFY o2ValsChanged)
    
    /**
     * @brief lastTimeStamp
     */
    Q_PROPERTY(QString lastTimeStamp READ getLastTimeStamp NOTIFY o2ValsChanged)

    /**
     * @brief mostRecentVoltVal
     */
    Q_PROPERTY(QVector<QString> mostRecentVoltVal READ getMostRecentVoltVal NOTIFY o2ValsChanged)
    /**
     * @brief lastVoltVal
     */
    Q_PROPERTY(QVector<QString> lastVoltVal READ getLastVoltVal NOTIFY o2ValsChanged)

    /**
     * @brief numO2CalVals
     */
    Q_PROPERTY(int numO2CalVals READ getNumO2CalVals NOTIFY o2ValsChanged)

    /**
     * @brief calibraitonProgressTime
     */
    Q_PROPERTY(QString calibrationProgressTime READ getCalibrationProgressTime NOTIFY calibrationProgressSignal)

    private:
        /**
         * @brief  Deletes the oldest CSV entry. Assumes the oldest entry is the first entry.
         */
        void deleteOldestO2CalVal();
        /**
         * @brief Read the CSV file and update the values saved in memory accordingly.
         */
        void updateO2Vals();
        /**
         * @brief Updates progress timer for calibration.
         */
        void incrementCalibrationProgress();

        void constructO2CalVals(int index);
        void constructO2CalValRows(std::vector<std::string> tmp, int index_i, int index_j);

        /**
         * @brief Updates text for minutes and seconds.
         * @param value
         * @return QString
         */
        static QString prependZero(int value);

        CSVManager m_o2CsvManager;
        QVector<QString> m_timeStamps;
        QVector<QVector<int>> m_o2Vals;
        QVector<QVector<QString>> m_volts;
        int m_numO2Vals;

        CSVManager m_timeManager;

        std::vector<std::string> o2Columns = {
            "TIME STAMP",
            " LOWEST VALUE",
            " HIGHEST VALUE",
            " LOWEST VOLTAGE",
            " HIGHEST VOLTAGE"
        };

        QString m_calibration_text = "01:00";
        int m_calibration_seconds = 60;
        QTimer *m_calibration_progress_timer;

        const int DEFAULT_SECONDS = 60;

    public:
        /**
         * @brief Constructor for the Calibration Manager
         * @details The O2 Calibration values are saved in CSV files with a maximum of 5 entries.
         *          The columns in the O2 Cal CSV file are Low Value, High Value, Low Volt, High Volt, Month, Day, and Year.
         * @note There are a maximum of 5 entries at any point.
         * @param parent
         */
        O2CalManager(QObject *parent = nullptr);

        /**
         * @brief Gets time for calibration progress.
         * @return QString
         */
        QString getCalibrationProgressTime();


    public slots:
        /**
         * @brief Adds an entry to the O2 Cal Vals CSV file.
         * @param low
         * @param high
         * @param lowVolt
         * @param highVolt
         * @callergraph
         */
        void addO2CalVals(int, int, float, float);

        /**
         * @brief Gets the most recent time stamp.
         * @return QString
         * @callergraph
         */
        QString getMostRecentTimeStamp();
        
        /**
         * @brief Gets the last time stamp.
         * @return QString
         * @callergraph
         */
        QString getLastTimeStamp();

        /**
         * @brief Gets the most recent o2 calibration value. Assumes the most recent entry is the last entry
         * @return QVector<QString>
         * @callergraph
         */
        QVector<int> getMostRecentO2CalVal();

        /**
         * @brief Gets the most recent o2 volt. Assumes the most recent entry is the last entry
         * @return QVector<QString>
         * @callergraph
         */
        QVector<QString> getMostRecentVoltVal();

        /**
         * @brief Gets the last o2 volt. Assumes the last entry is the second to last entry
         * @return QVector<QString>
         * @callergraph
         */
        QVector<QString> getLastVoltVal();

        /**
         * @brief Gets the number of o2 calibration entries. Relies on the CSVManager method.
         * @return int
         * @callergraph
         */
        int getNumO2CalVals() const;

        /**
         * @brief Starts the calibration timer, and won't restart timer if warning is triggered again.
         * @callergraph
         */
        void calibrationState();

        /**
         * @brief Reset Calibration timer after manual trigger.
         * @callergraph
         */
        void resetCalibration();

    signals:
        /**
         * @brief Signal for when O2 calibration data is updated.
         * @callgraph
         */
        void o2ValsChanged();
        /**
         * @brief Signal for calibration time.
         * @callgraph
         */
        void calibrationProgressSignal();
        /** @} */
};

/** @} */
