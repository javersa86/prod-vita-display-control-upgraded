#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <iomanip>
#include <sstream>

/**
 * @addtogroup dprManagerModule
 * @{
 */

/**
 * @brief CSV file name for DPR Calibration Manager.
 */
#define DPR_FILE "dpr_vals.csv"

/**
 * @brief Constant value for number of columns on DPR Managers csv file.
 */
#define MAX_O2_VALS 5

/**
 * @file dpr_manager.h
 * @brief Header for dpr_manager.cpp with info.
 */

/**
 * @file dpr_manager.cpp
 * @brief Manages and saves the Driving Pressure Regulator values for calibration.
 */

/**
 * @brief The DPRManager class
 */
class DPRManager : public QObject
{
    /**
     * @addtogroup dprManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief DPRCalVal
     */
    Q_PROPERTY(int DPRCalVal READ getDPRCalVal NOTIFY dprValsChanged)

    private:
        CSVManager m_dprCsvManager;
        QVector<QString> m_timeStamps;
        QVector<int> m_dprVals;
        int m_numDPRVals;

        CSVManager m_timeManager;

        std::vector<std::string> dprColumns = {
            "TIME STAMP",
            " DPR VALUE"
        };

        /**
         * @brief Deletes the oldest CSV entry. Assumes the oldest entry is the first.
         */
        void deleteOldestDPRVal();

        /**
         * @brief Reads the CSV file and updatse the values saved in memory accordingly
         */
        void updateDPRVals();

    public:
        /**
         * @brief Constructor for the Calibration Manager.
         * @details The DPR values are saved in CSV files with a maximum of 5 entries.
         *          The columns in the DPR CSV file are DPR Val, Month, Day, and Year.
         *
         * @note There are a maximum of 5 entries at any point and retrievees Time Stampe from Time Manager.
         * @param parent
         */
        DPRManager(QObject *parent = nullptr);

    public slots:
        /**
         * @brief Adds an entry to the DPR Val CSV file.
         * @param value
         * @callergraph
         */
        void addDPRVal(int);

        /**
         * @brief Gets the last DPR value.
         * @return int
         * @callergraph
         */
        int getDPRCalVal();

    signals:
        /**
         * @brief Signal for when DPR Calibration information is updated.
         * @callgraph
         */
        void dprValsChanged();
        /** @} */
};

/** @} */
