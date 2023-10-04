#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QTimer>

/**
 * @addtogroup partManagerModule
 * @{
 */

/**
 * @file part_manager.h
 * @brief Header for part_manager.cpp with info.
 */

/**
 * @file part_manager.cpp
 * @brief Manages all of the components that need to be replaced on the device.
 */

/**
 * @brief Number of columns of CSV file for part manager.
 */
#define PART_DATA 3

/**
 * @brief Number of parts and rows for part manager.
 */
#define NUMBER_OF_PARTS 23

/**
 * @brief Name of csv file for part information.
 */
#define PART_FILE "components.csv"

/**
 * @brief Name of csv file for each parts hours of operation.
 */
#define PART_OPERATING_FILE "components_operating.csv"

/**
 * @brief Name of csv file for each parts hours of ventilation.
 */
#define PART_VENTILATING_FILE "components_ventilating.csv"

/**
 * @brief Constant strings for column names.
 */
const std::map<int, std::string> partNameMap = {
    {0, "Part"},
    {1, "Serial Number"},
    {2, "DateTime"}
};

/**
 * @brief Constant strings for part names.
 */
const std::map<int, std::string> componentNameMap = {
    {0, "Oxygen Sensor"},
    {1, "25 Micron filter (Air Inlet Filter)"},
    {2, "25 Micron filter (Oxygen Inlet Filter)"},
    {3, "Water Injector (Jet)"},
    {4, "Water Injector (AUX)"},
    {5, "Humidity Sensor (Jet)"},
    {6, "Humidity Sensor (AUX)"},
    {7, "Humidity Sensor (PCB)"},
    {8, "Jet Water Pump"},
    {9, "Aux Water Pump"},
    {10,"Internal Tubing Sets"},
    {11,"Water Tubing Sets"},
    {12,"Mechanical Pressure Regulator (Air)"},
    {13,"Mechanical Pressure Regulator (O2)"},
    {14,"Proportional Valve (Air)"},
    {15,"Proportional Valve (O2)"},
    {16,"Proportional Valve (AUX)"},
    {17,"Flow Sensor (Jet)"},
    {18,"Flow Sensor (AUX)"},
    {19,"Calibration Valve"},
    {20,"Driving Pressure Regulator"},
    {21,"Heater Cartridge"},
    {22,"Jet Valve"}
};

/**
 * @brief The PartManager class
 */
class PartManager : public QObject
{
    /**
     * @addtogroup partManagerModule
     * @{
     */

    Q_OBJECT

    //QML signal for get method for specific part's name.
    /**
     * @brief partName
     */
    Q_PROPERTY(QString partName READ getPartName NOTIFY partChanged)
    //QML signal for get method for specific part's serial number.
    /**
     * @brief partNumber
     */
    Q_PROPERTY(QString partNumber READ getPartNumber NOTIFY partChanged)
    //QML signal for get method for specific part's installation date.
    /**
     * @brief partDateTime
     */
    Q_PROPERTY(QString partDateTime READ getPartDateTime NOTIFY partChanged)
    //QML signal for get method for specific part's hours of operation.
    /**
     * @brief hoursOperating
     */
    Q_PROPERTY(int hoursOperating READ getHoursOperating NOTIFY partOpChanged)
    //QML signal for get method for specific part's hours of ventilation.
    /**
     * @brief hoursVentilating
     */
    Q_PROPERTY(int hoursVentilating READ getHoursVentilating NOTIFY partVentChanged)
    //QML signal for get and set methods for index of updated part.
    /**
     * @brief listIndex
     */
    Q_PROPERTY(int listIndex READ getIndex WRITE setIndex NOTIFY partChanged)
    //QML signal for get method for user input serial number.
    /**
     * @brief serialNumber
     */
    Q_PROPERTY(QString serialNumber READ getSerialNumber NOTIFY serialChanged)
    //QML signal for get and set methods for index where part serial number and date is updated.
    /**
     * @brief partIndex
     */
    Q_PROPERTY(unsigned char partIndex READ getPartIndex WRITE setPartIndex NOTIFY partChanged)

    private:
        CSVManager m_partCsvManager;
        CSVManager m_hoursOperatingCsvManager;
        CSVManager m_hoursVentilatingCsvManager;

        QString m_partName;
        QString m_partNumber;
        QString m_partDateTime;

        int m_hoursOperating;
        int m_hoursVentilating;

        int m_row_index;

        unsigned char m_reset_op = 0;
        unsigned char m_reset_vent = 0;

        unsigned char m_ventilation_state = 0;

        int m_temp_row_index = -1;
        QString m_temp_name = "";
        QString m_temp_serial_number = "";
        QString m_temp_date = "";
        unsigned char m_temp_oper_index = -1;
        unsigned char m_temp_vent_index = -1;

        unsigned char m_part_index = -1;


        //Increments hours operating and ventilating per second.
        QTimer *m_hours_operating_timer;
        QTimer *m_hours_ventilating_timer;


        /**
         * @brief Updates signal values for part name, serial number and installation date.
         * @details Retrieves component from row on .csv file.
         *          Stores the current values for current component.
         *          Updates current component whenever device powers on,
         *          whenever current component is changed by the user,
         *          or when different component is selected.
         *          Component data will reset due to CSV file corruption.
         */
        void updatePart();

        /**
         * @brief Creates components when device powers on for the first time or if data is corrupted.
         * @note Creates default data for parts when starting new device.
         */
        void createComponents();

        /**
         * @brief Updates signal values for hours operating.
         * @details Retrieve component hours of operation row on .csv file.
         *          Stores the current value for current component.
         *          Component data will reset due to CSV file corruption.
         */
        void updateHoursOperating();
        /**
         * @brief Updates signal values for hours ventilating.
         * @details Retrieve component hours of ventilation row on .csv file.
         *          Stores the current value for current component.
         *          Component data will reset due to CSV file corruption.
         */
        void updateHoursVentilating();

        /**
         * @brief Starts component hours of operations when device powers on for the first time or restarts if data is corrupted.
         * @note Creates default data for hours when starting new device.
         */
        void createHoursOperating();
        /**
         * @brief Starts component hours of ventilations when device powers on for the first time or restarts if data is corrupted.
         * @note Creates default data for hours when starting new device.
         */
        void createHoursVentilating();

        /**
         * @brief Increments each part hours of operation by a second.
         */
        void incrementHoursOperating();
        /**
         * @brief Increments each part hours of ventilation by a second. Only increments while device is ventilating.
         */
        void incrementHoursVentilating();

    public:
        /**
         * @brief Constructor method for program allows the user to change info for each component.
         * @param parent
         */
        PartManager(QObject *parent = nullptr);

        /**
         * @brief Gets current name for component.
         * @return QString
         */
        QString getPartName();
        /**
         * @brief Gets current part number for component.
         * @return QString
         */
        QString getPartNumber();
        /**
         * @brief Gets current part installation date for component.
         * @return QString
         */
        QString getPartDateTime();

        /**
         * @brief Gets hours operating for part.
         * @return int
         */
        int getHoursOperating();
        /**
         * @brief Gets hours ventilating for part.
         * @return int
         */
        int getHoursVentilating();

        /**
         * @brief Gets index of current row.
         * @return int
         */
        int getIndex();

        /**
         * @brief Gets user generated serial number.
         * @return QString
         */
        QString getSerialNumber();

        /**
         * @brief Gets index of part that was replaced.
         * @return unsigned char
         */
        unsigned char getPartIndex();

    public slots:
        /**
         * @brief Updates variable for when ventilation is active or inactive.
         * @param val
         * @callergraph
         */
        void setVentilationState(unsigned char);

        /**
         * @brief Updates current index for row on .csv file.
         * @param index
         * @callergraph
         */
        void setIndex(int);

        /**
         * @brief Sets index of part that needs to be replaced.
         * @param index
         * @callergraph
         */
        void setTempIndex(int);
        /**
         * @brief Sets name of part that needs to be replaced.
         * @param name
         * @callergraph
         */
        void setTempName(QString);
        /**
         * @brief Added digit to end of user generated serial number.
         * @param input
         * @callergraph
         */
        void addDigit(QString);
        /**
         * @brief Removes end digit to user generated serial number.
         * @callergraph
         */
        void removeDigit();
        /**
         * @brief Sets user generated serial number.
         * @param number
         * @callergraph
         */
        void setTempSerial(QString);
        /**
         * @brief Sets installation date for part that needs to be replaced.
         * @param date
         * @callergraph
         */
        void setTempDate(QString);

        /**
         * @brief Sets serial number, installation date, hours operating, and hours ventilating for replacement part.
         * @callergraph
         */
        void setNewPart(QString);

        /**
         * @brief Sets index of part that was replaced.
         * @param index
         * @callergraph
         */
        void setPartIndex(unsigned char);

    signals:
        /**
         * @brief Signal for updating part information.
         * @callgraph
         */
        void partChanged();
        /**
         * @brief Signal for resetting part hours of operation.
         * @callgraph
         */
        void partOpChanged();
        /**
         * @brief Signal for resetting part hours of ventilation.
         * @callgraph
         */
        void partVentChanged();
        /**
         * @brief Signal for updating part serial number.
         * @callgraph
         */
        void serialChanged();
        /** @} */
};

/** @} */

