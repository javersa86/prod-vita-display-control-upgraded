//Modules for all logging managers.

/**
 * @ingroup loggerModule
 * @defgroup csvManagerModule CSV Manager
 * @brief Documentation for how CSV Files stored on the Display Controller are read and written.
 * @{
 * @details
 *
 * \section csvManagerModule CSV Manager
 *
 * The CSV Manager is the most important component to all data managers on the display controller, for it acts as a tool to read and write the rows and columns of CSV files (Comma-Separated Value). The CSV Manager can also update rows of CSV files, delete rows, and return the number of entries representing each row.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup logManagerModule Log Manager
 * @brief Documentation for how Service Logs are written and saved on the Display Controller.
 * @{
 * @details
 *
 * \section logManagerModule Log Manager
 *
 * The Log Manager is tasked with writing all the service logs and warning logs on the system. Events on the service logs include settings requests, mode switches, warnings triggered, and other events. For whenever the NVENT-VITA display software starts up, two CSV files are created and stored onto the display controller's internal directory. One for writing all activities on the display, while another is specifically for when warnings are triggered. Each CSV filename will have the date and time of its creation. An incremented number will be added at the end of the filename for duplicates. Each service log entries will consists of the following:
 * - <b>TIMESTAMP:</b> The date and time for when the event occurred.
 * - <b>TYPE:</b> Which type and location for what activity is occuring. The label "(SERVICE)" will be written for activities involving the Service Menu.
 * - <b>EVENT:</b> A description for what is occurring on the device.
 *
 * The writing of all service log entries are triggered from qInfo statements in the backend source code. For the other managers, if CSV corruption occurs, the occurrence is logged to the Log Manager and a new CSV file is created. <b>IMPORTANT: Service log files are deleted after 2 weeks and warning logs are deleted after 3 months.</b>
 *
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup brightnessManagerModule Brightness Manager
 * @brief Documentation for managing brightness on the Display Controller.
 * @{
 * @details
 *
 * \section brightnessManagerModule Brightness Manager
 *
 * Connects with the display controller's internal systems to update the brightness of the display controller screen. Brightness is adjusted via the knob controller.
 *
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup contactManagerModule Contact Manager
 * @brief Documentation for managing all contacts stored on the Display Controller.
 * @{
 * @details
 *
 * \section contactManagerModule Contact Manager
 *
 * Updates and saves contact information for the servicing company (Susquehanna Micro) and the Sales Company (Lantern Medical) on to two CSV Files. Contact Information include the following:
 * - The Company Name
 * - Street Address
 * - City
 * - State
 * - Postal Code
 * - Email
 * - Phone Number
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup dprManagerModule DPR Manager
 * @brief Documentation for how Driving Pressure Regulator Calibration values are stored on the Display Controller.
 * @{
 * @details
 *
 * \section dprManagerModule DPR Manager
 *
 * Logs the dates and times of the lowest and highest Driving Pressure Regulator Calibration values (technically the same measurement types) onto a CSV file. The manager will store up to 5 entries and will delete the oldest entry when adding a new one. Updates the Log Manager for when new entries are added, and if entries are deleted.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup maintenanceManagerModule Maintenance Manager
 * @brief Documentation for how Service Dates are stored on the Display Controller.
 * @{
 * @details
 *
 * \section maintenanceManagerModule Maintenance Manager
 *
 * Updates and saves dates for the last service appointment and the next service appointment onto a CSV file. Updates the Log Manager for when dates are updated.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup o2CalManagerModule O2 Calibration Manager
 * @brief Documentation for how O<sub>2</sub> Calibration values are stored on the Display Controller.
 * @{
 * @details
 *
 * \section o2CalManagerModule O2 Calibration Manager
 *
 * Logs the dates and times of the lowest and highest O<sub>2</sub> Calibration Values and Voltages onto a CSV file. The manager will save up to 5 entries and will delete the oldest entry when adding a new one. Updates Log Manager for when entries are added or deleted. The manager is also tasked with running the timer for the Warning Banner's O<sub>2</sub> Calibration 1 minute progress time and is triggered when related warnings are active..
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup partManagerModule Part Manager
 * @brief Documentation for managing Component Data stored on the Display Controller.
 * @{
 * @details
 *
 * \section partManagerModule Part Manager
 *
 * Manages and updates the data for all 23 parts that can be replaced on the device. The parts included:
 * - Oxygen Sensor
 * - 25 Micron Filter (Air Inlet Filter)
 * - 25 Micron Filter (Oxygen Inlet Filter)
 * - Water Injector (Jet Line)
 * - Water Injector (Auxiliary Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (Jet Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (Auxiliary Line)
 * - \htmlonly Humidity \endhtmlonly Sensor (PCB)
 * - Jet Line Water Pump
 * - Auxiliary Line Water Pump
 * - Internal Tubing Sets
 * - Water Tubing Sets
 * - Mechanical Pressure Regulator (Air)
 * - Mechanical Pressure Regulator (O<sub>2</sub>)
 * - Proportional Valve (Air)
 * - Proportional Valve (O<sub>2</sub>)
 * - Proportional Valve (Auxiliary)
 * - Flow Sensor (Jet Line)
 * - Flow Sensor (Auxiliary Line)
 * - Calibration Valve
 * - Driving Pressure Regulator
 * - Heater Cartridge
 * - Jet Valve
 *
 * The manager will update different CSV files. One for saving the part's name, serial number (if available), and installation/replacement date. Another CSV file tracks each parts' hours operating, the total number of hours and minutes for how long the part is running on the device. The last CSV files track each parts' hours of ventilation, the total number of hours and minutes for when the system is ventilating with each part. Both time CSV files are updated from managers internal timers that increment each second. The ventilation timer will only run when the system is ventilating. All parts installed will be logged to the Log Manager.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup passcodeManagerModule Passcode Manager
 * @brief Documentation for managing Passcodes stored on the Display Controller.
 * @{
 * @details
 *
 * \section passcodeManagerModule Passcode Manager
 *
 * Updates and saves the 4 digit passcode used for creating, editing, and deleting presets, and passcode used for entering the service menu. While the main user will be able to update the preset passcode, the service technician can only update the service passcode and forcefully update the preset passcode. Updates the Log Manager for when passcodes are entered correctly, entered incorrectly, or changed.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup presetManagerModule Preset Manager
 * @brief Documentation for managing Presets on the Display Controller.
 * @{
 * @details
 *
 * \section presetManagerModule Preset Manager
 *
 * The preset manager is tasked with creating, editing, and deleting up to 12 presets onto a CSV file.
 * Each preset will include the following pneumatic settings to adjust: Driving Pressure, \htmlonly Rate\endhtmlonly, Inspiratory Time, Stacking Pressure, Oxygen Concentration,
 * Peak Inspiratory Pressure, Auxiliary Flow, and \htmlonly Humidity \endhtmlonly.
 *
 * The preset manager also creates edits and deletes the names for each preset on another CSV file. A name will be helpful in distinguishing the different presets for medical experts and are updated alongside presets.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup timeManagerModule Time Manager
 * @brief Documentation for managing Date, Time, and Time Zone for the digital clock on the Display Controller.
 * @{
 * @details
 *
 * \section timeManagerModule Time Manager
 *
 * The time manager runs timer to update the digital clock on the about and maintenance pages, and updates the following stored on a CSV files:
 * - <b>Date Time:</b> the date and time stored in milliseconds
 * - <b>Time Zone:</b> the time zone text display alongside digital clock
 * - <b>Internal Time:</b> the internal date and time that is never changed and is utilized for all user updates for time
 * - <b>Daylight Savings Time:</b> the state for when time zone should be in Daylight Savings Time or Standard Time
 *
 * All updates are logged to the Log Manager.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup versionManagerModule Version Manager
 * @brief Documentation for managing the HMI Controller version number and NVENT's serial number stored on the Display Controller.
 * @{
 * @details
 *
 * \section versionManagerModule Version Manager
 *
 * Manages and saves the version number for the HMI Controller and the NVENT-VITA serial number on the CSV file. Entries are logged to the Log Manager on startup.
 * @}
 */

/**
 * @ingroup loggerModule
 * @defgroup zeroManagerModule Zero Manager
 * @brief Documentation for how the Sensor Calibration values are stored on the Display Controller.
 * @{
 * @details
 *
 * \section zeroManagerModule Zero Manager
 *
 * Manages and saves the sensor calibration data, including zeroing and verification values, and time stamps on CSV files. Each file will save up to 5 entries, and deletes the oldest one if new value is added.
 *
 * Sensor Calibration Procedures include the following:
 * - <b>Stacking Pressure</b>
 * - <b>Peak Inspiratory Pressure</b>
 * - <b>Inlet Air</b>
 * - <b>Inlet O<sub>2</sub></b>
 * @}
 */
