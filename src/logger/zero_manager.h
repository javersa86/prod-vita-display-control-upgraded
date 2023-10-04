#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>

/**
 * @addtogroup zeroManagerModule
 * @{
 */

/**
 * @file zero_manager.h
 * @brief Header for zero_manager.cpp with info.
 */

/**
 * @file zero_manager.cpp
 * @brief Manages the data for sensor calibration.
 */

/**
 * @brief Name of csv file for storing PIP info.
 */
#define PIP_FILE "/media/NVENT_FILES/calibration/pip_vals.csv"

/**
 * @brief Name of csv file for storing SP info.
 */
#define SP_FILE "/media/NVENT_FILES/calibration/sp_vals.csv"

/**
 * @brief Name of csv file for storing Inlet Air info.
 */
#define INLET_AIR_FILE "/media/NVENT_FILES/calibration/inlet_air_vals.csv"

/**
 * @brief Name of csv file for storing Inlet O2 info.
 */
#define INLET_O2_FILE "/media/NVENT_FILES/calibration/inlet_o2_vals.csv"

/**
 * @brief Name of csv file for storing PIP Verification info.
 */
#define PIP_VERIFY_FILE "/media/NVENT_FILES/calibration/pip_verify.csv"

/**
 * @brief Name of csv file for storing SP Verification info.
 */
#define SP_VERIFY_FILE "/media/NVENT_FILES/calibration/sp_verify.csv"

/**
 * @brief Name of csv file for storing Inlet Air Verification info.
 */
#define INLET_AIR_VERIFY_FILE "/media/NVENT_FILES/calibration/inlet_air_verify.csv"

/**
 * @brief Name of csv file for storing Inlet O2 Verification info.
 */
#define INLET_O2_VERIFY_FILE "/media/NVENT_FILES/calibration/inlet_o2_verify.csv"

/**
 * @brief Number of columns on csv files.
 */
#define MAX_ZERO_VALS 5

/**
 * @brief The ZeroManager class
 */
class ZeroManager : public QObject
{
    /**
     * @addtogroup zeroManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief zeroPIP
     */
    Q_PROPERTY(float zeroPIP READ getZeroPIP NOTIFY zeroChanged);
    /**
     * @brief zeroSP
     */
    Q_PROPERTY(float zeroSP  READ getZeroSP  NOTIFY zeroChanged);
    /**
     * @brief inletAir
     */
    Q_PROPERTY(float inletAir READ getInletAir NOTIFY zeroChanged);
    /**
     * @brief inletO2
     */
    Q_PROPERTY(float inletO2 READ getInletO2 NOTIFY zeroChanged);

    /**
     * @brief verifiedZeroPIP
     */
    Q_PROPERTY(float verifiedZeroPIP READ getVerifiedZeroPIP NOTIFY zeroChanged);
    /**
     * @brief verifiedZeroSP
     */
    Q_PROPERTY(float verifiedZeroSP READ getVerifiedZeroSP NOTIFY zeroChanged);
    /**
     * @brief verifiedInletAir
     */
    Q_PROPERTY(float verifiedInletAir READ getVerifiedInletAir NOTIFY zeroChanged);
    /**
     * @brief verifiedInletO2
     */
    Q_PROPERTY(float verifiedInletO2 READ getVerifiedInletO2 NOTIFY zeroChanged);
    
    public:

        /**
         * @brief   Constructor method.
         * @details The PIP and SP Calibration values are saved in a CSV file with maximum 5 entries.
         *          The columns in the CSV folder are Value, Month, Day, and Year.
         *          There are a maximum of 5 zero calibration entries at any point.
         * @param   parent
         */
        ZeroManager(QObject *parent = nullptr);

        /**
         * @brief  Gets the most recent PIP zero calibration value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getZeroPIP();

        /**
         * @brief  Gets the most recent SP zero calibration value
         * @note   Assumes the most recent entry is the last entry
         * @return float
         */
        float getZeroSP();

        /**
         * @brief  Gets the most recent Inlet Air calibration value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getInletAir();

        /**
         * @brief  Gets the most recent Inlet O2 calibration value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getInletO2();

        /**
         * @brief  Gets the most recent Verification PIP value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getVerifiedZeroPIP();

        /**
         * @brief  Gets the most recent Verification SP value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getVerifiedZeroSP();

        /**
         * @brief  Gets the most recent Verification Inlet Air value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getVerifiedInletAir();

        /**
         * @brief  Gets the most recent Verification Inlet O2 value.
         * @note   Assumes the most recent entry is the last entry.
         * @return float
         */
        float getVerifiedInletO2();

        /**
         * @brief Column names for csv file for Zero Manager.
         */
        std::vector<std::string> zeroColumns = {
            "TIMESTAMP",
            "Value"
        };


    private:

        /**
         * @brief   Retrieves current values from .csv files.
         * @details Stores current values onto vectors.
         *          Updates whenever powers on or whenever values are changed by the user.
         */
        void updateZeroVals();
        /**
         * @brief Read the CSV file and update the PIP values saved in memory accordingly.
         */
        void updatePipVals();
        /**
         * @brief Read the CSV file and update the SP values saved in memory accordingly.
         */
        void updateSpVals();
        /**
         * @brief Read the CSV file and update the Inlet Air values saved in memory accordingly.
         */
        void updateInletAirVals();
        /**
         * @brief Read the CSV file and update the Inlet O2 values saved in memory accordingly.
         */
        void updateInletO2Vals();

        /**
         * @brief Read the CSV file and update the Verification PIP values saved in memory accordingly.
         */
        void updateVerifiedPipVals();
        /**
         * @brief Read the CSV file and update the Verification SP values saved in memory accordingly.
         */
        void updateVerifiedSpVals();
        /**
         * @brief Read the CSV file and update the Verification Inlet Air values saved in memory accordingly.
         */
        void updateVerifiedInletAir();
        /**
         * @brief Read the CSV file and update the Verification Inlet O2 values saved in memory accordingly.
         */
        void updateVerifiedInletO2();

        /**
         * @brief Deletes oldest pip value from file.
         */
        void deleteOldestPipVal();
        /**
         * @brief Deletes oldest sp value from file.
         */
        void deleteOldestSpVal();
        /**
         * @brief Deletes oldest inlet air value from file.
         */
        void deleteOldestInletAirVal();
        /**
         * @brief Deletes oldest inlet o2 value from file.
         */
        void deleteOldestInletO2Val();

        /**
         * @brief Deletes oldest verification pip value from file.
         */
        void deleteOldestVerifiedPipVal();
        /**
         * @brief Deletes oldest verification sp value from file.
         */
        void deleteOldestVerifiedSpVal();
        /**
         * @brief Deletes oldest verification inlet air value from file.
         */
        void deleteOldestVerifiedInletAirVal();
        /**
         * @brief Deletes oldest verification inlet o2 value from file.
         */
        void deleteOldestVerifiedInletO2Val();

    private:
        CSVManager m_timeCsvManager;
        
        CSVManager m_pipCsvManager;
        CSVManager m_spCsvManager;
        CSVManager m_airCsvManager;
        CSVManager m_o2CsvManager;

        CSVManager m_verifiedPipCsvManager;
        CSVManager m_verifiedSpCsvManager;
        CSVManager m_verifiedInletAirCsvManager;
        CSVManager m_verifiedInletO2CsvManager;

        QVector<QString> m_pip_timestamps;
        QVector<QString> m_sp_timestamps;
        QVector<QString> m_air_timestamps;
        QVector<QString> m_o2_timestamps;

        QVector<QString> m_verified_pip_timestamps;
        QVector<QString> m_verified_sp_timestamps;
        QVector<QString> m_verified_air_timestamps;
        QVector<QString> m_verified_o2_timestamps;
        
        QVector<float> m_pipVals;
        QVector<float> m_spVals;
        QVector<float> m_airVals;
        QVector<float> m_o2Vals;

        QVector<float> m_verifiedPipVals;
        QVector<float> m_verifiedSpVals;
        QVector<float> m_verifiedAirVals;
        QVector<float> m_verifiedO2Vals;
        
        int m_numPipVals;
        int m_numSpVals;
        int m_numAirVals;
        int m_numO2Vals;

        int m_numVerifiedPipVals;
        int m_numVerifiedSpVals;
        int m_numVerifiedAirVals;
        int m_numVerifiedO2Vals;

    public slots:
        /**
         * @brief Adds an entry to the Zero values associated CSV file.
         * @param id
         * @param value
         * @callergraph
         */
        void addZeroValue(int, float);
        
        /**
         * @brief Adds an entry to the Verification values associated CSV file.
         * @param id
         * @param value
         * @callergraph
         */
        void addVerifiedValue(int, float);

    signals:
        /**
         * @brief Signal for when zero manager is updated.
         * @callgraph
         */
        void zeroChanged();
        /** @} */
};

/** @} */
