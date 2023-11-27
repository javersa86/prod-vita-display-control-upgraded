#pragma once
#include <QObject>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include <QDateTime>
#include <QTimeZone>
#include <stdio.h>
#include <unistd.h>

#include "csv_manager.h"
#include "time_manager.h"

/**
 * @addtogroup logManagerModule
 * @{
 */

/**
 * @brief Name and path for directory where all files are stored.
 */
#define ROOT_FOLDER "/media/NVENT_FILES/"  //change to folder on display not SD card

/**
 * @brief Name and path for directory where all service logs are stored.
 */
#define EVENT_FOLDER "NV_Vita_events/"

/**
 * @brief Beginning of each service log file title.
 */
#define EVENT_FILE_ROOT "event"

/**
 * @brief Name and path for directory where all warning logs are stored.
 */
#define WARNINGS_FOLDER "NV_Vita_warnings/"

/**
 * @brief Name of event column on service log.
 */
#define EVENT_COLUMN "EVENT"

/**
 * @brief File extension.
 */
#define CSV ".csv"

/**
 * @brief Time stamp of event column on service log.
 */
#define TIMESTAMP_COLUMN "TIME STAMP"

/**
 * @brief Type of event column on service log.
 */
#define TYPE_COLUMN "TYPE"

/**
 * @file log_manager.h
 * @authors Sarah, modifications by Joseph Aversa
 * @brief Header file for log_manager.cpp with info.
 * @date 03/11/2022
 */

/**
 * @file log_manager.cpp
 * @brief The log system is a program that will record events taken place by the device.
 * @details Events include setting value request, mode switches, warning triggers, etc.
 *          Program will record events on comma seperated variable log files.
 *          The log event files will record all log events of the device.
 *          The warnings files will record only the warnings that were triggered.
 *
 *          Log event files are stored onto log events folder.
 *          Warnings files are stored onto warnings folder.
 */

/**
 * @brief Sets the state used to add service label for entering events from service menu.
 */
void serviceState(bool);

/**
 * @brief Check that the logs directory exists, True if logs directory exists, False otherwise.
 * @param path
 * @return bool
 */
bool directoryExists(const QString &path);

/**
 * @brief Method loops through list of currently active log files and deletes the oldest.
 * @details If the oldest log event file is older than 2 weeks, the file will be deleted
 *          If the corresponding warnings file is older than 3 months, the file will be deleted
 *          Returns True if log file is deleted, False otherwise.
 *          Will only loop through files if directory exists.
 *          The for loop will calculate the value of time for the oldest log file.
 *          If file is not an active log file, it will be deleted.
 *          Extracts how old file is from file name.
 *          If age value is greater than the last calculated value, age value changes.
 *          Removes log event file if older than 2 weeks (2 weeks = 1209600 seconds).
 *          Removes warnings file if older than 3 months (3 months == 7890000 seconds).
 * @return bool
 */
bool deleteOldestEventFile();

/**
 * @brief Method loops through list of currently active log files and deletes service logs older than 2 weeks.
 * @details Will only loop through files if directory exists.
 *          For loop will calculate the value of time for the oldest log file.
 *          If file is not an active log file, it will be deleted.
 *          Extracts how old file is from file name.
 */
void deleteOldestServiceLogs();

/**
 * @brief Method loops through list of currently active warning log files and deletes service logs older than 3 months.
 * @details Will only loop through files if directory exists.
 *          For loop will calculate the value of time for the oldest log file.
 *          If file is not an active log file, it will be deleted.
 *          Extracts how old file is from file name.
 */
void deleteOldestWarningLogs();

/**
 * @brief Creates new log event and warnings files.
 * @details Gets current date and time, name of log events file, and name of warnings file.
 *          Checks if log events file exists. If so, creates another file with an incremented name.
 *          Checks if warnings file exists. If so, creates another file with an incremented name.
 *          Creates the log event and warnings files that will be currently appended to and saved as active.
 *          Naming Structures:
 *          - /event/NV_Vita_events/event_MM-dd-yyyy_hh.mm.ss_AP
 *          - /event/NV_Vita_warnings/event_MM-dd-yyyy_hh.mm.ss_AP
 */
void generateNewEventFile();

/**
 * @brief Returns success of finding current log event and warnings files.
 * @details Assume the last file in the files lists are the most recent event and warnings files.
 *          If method is called without any active log files, it will generate a new one.
 * @return bool
 */
bool findCurrentEventFile();

/**
 * @brief Get the size of a file in bytes and returns the float value for bytes.
 * @param fileAbsolutePath
 * @return float
 */
float fileSize(const QString &fileAbsolutePath);

/**
 * @brief Initiate the log manager and all required variables
 * @details The log system is a program that will record events taken place by the device.
 *          Events include setting value request, mode switches, warning triggers, etc.
 *          Program will record events on comma seperated variable log files.
 *          The log event files will record all log events of the device.
 *          The warnings files will record only the warnings that were triggered.
 *          Log event files are stored onto log events folder.
 *          Warnings files are stored onto warnings folder.
 *          The follow events take place in initiation:
 *
 *          - Initiates the (empty) lists of file names.
 *          - Log system is initialized only when root folder exists.
 *          - If the root directory does not exist, method returns void and logger is not initiated.
 *          - If the logs/ folder exists, but NV_Vita_events does not, create the logs/NV_Vita_events/ folder.
 *          - If the logs/ folder exists, but NV_Vita_warnings does not, create the logs/NV_Vita_warnings/ folder.
 *          - Logger loops through files in NV_Vita_events/ and add the file names to the list of active files.
 *          - Logger loops through files in NV_Vita_warnings/ and add the file names to the list of active files.
 *          - Once all events are completed, log initiation will be declared successful.
 *
 * @note If the root directory "/run/media/mmcblk0p2/home/ubuntu/" does not exist,
 *       the logger will not be initiated and no logs will be saved.
 */
void initLogger();

/**
 * @brief Constructs CSV Managers in Log Manager.
 * @details The logs file is a CSV file.
 *          These are the columns: the time stamp,
 *          the type of log (Mode Request, Setting Request, Confirmation, Warning, etc.),
 *          and the event that took place.
 *          CSV Managers include service log updates, warning log updates, and time information for time stamps (current date, time, and time zone).
 *          When the device powers on, the oldest log files will be deleted; log events by 2 weeks and warnings by 3 months.
 * @note Method is only executed after time manager is constructed.
 */
void startLogs();

/**
 * @brief Returns the current date and time written in the time.csv file.
 * @return QString
 */
QString getLogDateTime();

/**
 * @brief This is the method that replaces the original QDebug log statements.
 *        Only qInfo messages will be logged to the file and the rest should be printed to the console (QtDebug, QtWarning, QtCritical, and QtFatal).
 *
 * @param type
 * @param context
 * @param msg
 *
 * @note If debug methods are called, but log manager is never initialized, log manager will begin initiation.
 */
void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

/**
 * @brief Records log event onto log file.
 * @details Creates a list of column values by seperating ','.
 *          Format for service logs: NVENT, TYPE, and EVENT.
 *          The first "NVENT" tells us that the log is created by our application.
 *          Type is the of log (Mode Request, Setting Request, Confirmation, Warning, etc.).
 *          Event tells exactly what happens. If what settings were set, what mode was toggled to which state, which warning was raised or lowered...
 *          If the log has been initiated, and the first entry in the msg list is NVENT, add the event to the current event file.
 * @param event
 * @note Will only record onto warings file if type reads "WARNING".
 */
void logEvent(const QString &msg);
/**
 * @brief Vector that stores Titles for Service Log files.
 */
extern std::vector<std::string> m_columnTitles;
/**
 * @brief Variable used to declared when log manager is initiated.
 */
extern bool m_logInitiated;
/**
 * @brief String variable for the name of the CSV file that stores all service logs.
 */
extern QString m_currentEventFile;
/**
 * @brief String variable for the name of the CSV file that stores service logs associated with warning logs.
 */
extern QString m_currentEventFileWarnings;
/**
 * @brief CSV Manager used to update information on current service log file.
 */
extern CSVManager m_csvManager;
/**
 * @brief CSV Manager used to update information on current service log file associated with warning logs.
 */
extern CSVManager m_csvManager_Warnings;
/**
 * @brief Vector that tracks the titles of all service logs stored in the system.
 */
extern QVector<QString> m_activeFiles;
/**
 * @brief Vector that tracks the titles of all service logs stored in the system that only store warning logs.
 */
extern QVector<QString> m_activeWarningFiles;
/**
 * @brief CSV Manager used to update CSV file from Time Manager.
 */
extern CSVManager m_csvManager_Time;
/**
 * @brief Boolean variable used to log service events directly from the service menu.
 */
extern bool m_service_state;
/**
 * @brief String variable that stores the title of the currently active service log file.
 */
extern QString m_fileName;

/** @} */

