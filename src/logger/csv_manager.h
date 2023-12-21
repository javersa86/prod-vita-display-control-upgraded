#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include <QDebug>

/**
 * @addtogroup csvManagerModule
 * @{
 */

/**
 * @brief Number of O<sub>2</sub> Columns for O<sub>2</sub> Calibration Manager.
 */
constexpr int NUM_O2_COLS = 7;

/**
 * @brief Constant value for number of columns on DPR Managers csv file.
 */
constexpr int MAX_O2_VALS = 5;

/**
 * @file csv_manager.h
 * @brief Header file for csv_manager.cpp with info.
 */

/**
 * @file csv_manager.cpp
 * @brief Object used for log managers to read and write CSV files.
 */

/**
 * @brief The CSVManager class
 */
class CSVManager
{
    /**
     * @addtogroup csvManagerModule
     * @{
     */

    public:
        /**
         * @brief Empty Constructor.
         */
        CSVManager() = default;

        /**
         * @brief Contructor for the csv manager. The CSV manager manages CSV's CRUD entries and ensure the max number of entries is not exceeded.
         * @param filePath
         * @param buffer
         * @param numArgs
         */
        CSVManager(std::string filePath, std::string *buffer, int numArgs);

        /**
         * @brief Reads the row by index and returns array with data.
         * @details Opens the existing file, reads the data from the file as a String Vector,
         *          reads an entire row and stores it in a string variable 'line'.
         * @note Skips the first n rows (including title column).
         * @param row
         * @return <std::vector<std::string>
         */
        std::vector<std::string> readRecord(int row);

        /**
         * @brief Updates the record on row by index from buffer.
         * @details Traverses the file and adds the entries before row to the placeholder file.
         *          A new entry is entered and throws away old entry.
         *          Adds to the rest of the entries to the placeholder file.
         *          Renames the updated file with the existing file name.
         * @note Skips the first n rows (including title column).
         * @param row
         * @param buffer
         */
        void updateRecord(int row, std::string *buffer);

        /**
         * @brief Deletes the record with index.
         * @details Traverse the file and adds the first n entries to the placeholder file.
         *          Skips the entry at index and adds the rest of the entries to the placeholder file.
         *          Renaming the updated file with the existing file name.
         * @note Skips the first n rows (including title column).
         * @param row
         */
        void deleteRecord(int row);

        /**
         * @brief Creates a record from pointer to an std::string parameter.
         * @param buffer
         */
        void createRecord(std::string *buffer);

        /**
         * @brief Creates the csv file.
         * @param filePath
         * @param buffer
         */
        void create(std::string filePath, std::string *buffer);

        /**
         * @brief Gets the number of entries in the CSV file.
         * @return int
         */
        int getNumEntries();

    private:

        /**
         * @brief Gets whether or not the csv file exists.
         * @param filePath
         * @return bool
         */
        static bool exists(std::string &filePath);

        std::string m_filePath;
        std::string m_currDir;
        int m_numArgs = 0;
        /** @} */
};

/** @} */
