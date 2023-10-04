#include "log_manager.h"
#include <QDebug>

#include <vector>
#include <string>

/**
 * @author Sarah, modifications by Joseph Aversa
 * @name log_manager
 * @date 03/11/2022
 *
 * The log system is a program that will record events taken place by the device.
 * Events include setting value request, mode switches, warning triggers, etc.
 * Program will record events on comma seperated variable log files.
 * The log event files will record all log events of the device.
 * The warnings files will record only the warnings that were triggered.
 *
 * Log event files are stored onto log events folder.
 * Warnings files are stored onto warnings folder.
 */

std::vector<std::string> m_columnTitles;
bool m_logInitiated;
QString m_currentEventFile;
QString m_currentEventFileWarnings;
CSVManager m_csvManager;
CSVManager m_csvManager_Warnings;
QVector<QString> m_activeFiles;
QVector<QString> m_activeWarningFiles;
CSVManager m_csvManager_Time;
bool m_service_state;

void serviceState(bool state)
{
    m_service_state = state;
}

bool directoryExists(QString path) {
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isDir()) {
        return true;
    } else {
        return false;
    }
}

bool deleteOldestEventFile()
{
    int index = -1;
    qint64 currentTimeLength = 0;
    QString path = QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER);
    //Will only loop through files if directory exists.
    if(QDir(path).exists())
    {
        //For loop will calculate the value of time for the oldest log file.
        for(int i = 0; i < m_activeFiles.size(); i++)
        {
            //If file is not an active log file, it will be deleted.
            QFileInfo file(m_activeFiles.at(i));
            if(file.exists())
            {
                //Extracts how old file is from file name.
                QString fileName = file.fileName();
                fileName = fileName.mid(5,19);
                QDateTime fileDT = QDateTime::fromString(fileName,"dd-MM-yyyy_HH_mm_ss");
                QDateTime now = QDateTime::currentDateTime();

                qint64 tempTime = fileDT.secsTo(now);

                //If age value is greater than the last calculated value, age value changes.
                if (tempTime >= currentTimeLength)
                {
                    index = i;
                    currentTimeLength = tempTime;
                }
            }
            else
            {
                m_activeFiles.remove(i);
                i--;
            }
        }
        //Removes log event file if older than 2 weeks (2 weeks = 1209600 seconds).
        if (index != -1 && currentTimeLength > 1209600)
        {
            QFile toRemove(m_activeFiles.at(index));
            toRemove.remove();
            m_activeFiles.remove(index);
            //Removes warnings file if older than 3 months (3 months == 7890000 seconds).
            if (m_activeWarningFiles.size() > 0 && currentTimeLength > 7890000)
            {
                QFile toRemove1(m_activeWarningFiles.at(index));
                toRemove1.remove();
                m_activeWarningFiles.remove(index);
            }
            return true;
        }
        else return false;
    }
    else return false;
}

void deleteOldestServiceLogs()
{
    QString path = QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER);
    //Will only loop through files if directory exists.
    if(QDir(path).exists())
    {
        //For loop will calculate the value of time for the oldest log file.
        for(int i = 0; i < m_activeFiles.size(); i++)
        {
            //If file is not an active log file, it will be deleted.
            QFileInfo file(m_activeFiles.at(i));
            if(file.exists())
            {
                //Extracts how old file is from file name.
                QString fileName = file.fileName();
                fileName = fileName.mid(6,22);
                QDateTime fileDT = QDateTime::fromString(fileName,"MM-dd-yyyy.hh.mm.ss_AP");
                QDateTime now = QDateTime::currentDateTime().addSecs(-5 * 3600);

                qint64 tempTime = fileDT.secsTo(now);

                if (tempTime > 1209600)
                {
                    QFile toRemove(m_activeFiles.at(i));
                    toRemove.remove();
                    m_activeFiles.remove(i);
                    i--;
                }
            }
            else
            {
                m_activeFiles.remove(i);
                i--;
            }
        }
    }
}

void deleteOldestWarningLogs()
{
    QString path = QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(WARNINGS_FOLDER);
    //Will only loop through files if directory exists.
    if(QDir(path).exists())
    {
        //For loop will calculate the value of time for the oldest log file.
        for(int i = 0; i < m_activeWarningFiles.size(); i++)
        {
            //If file is not an active log file, it will be deleted.
            QFileInfo file(m_activeWarningFiles.at(i));
            if(file.exists())
            {
                //Extracts how old file is from file name.
                QString fileName = file.fileName();
                fileName = fileName.mid(6,22);
                QDateTime fileDT = QDateTime::fromString(fileName,"MM-dd-yyyy.hh.mm.ss_AP");
                QDateTime now = QDateTime::currentDateTime().addSecs(-5 * 3600);

                qint64 tempTime = fileDT.secsTo(now);

                if (tempTime > 7890000)
                {
                    QFile toRemove(m_activeWarningFiles.at(i));
                    toRemove.remove();
                    m_activeWarningFiles.remove(i);
                    i--;
                }
            }
            else
            {
                m_activeWarningFiles.remove(i);
                i--;
            }
        }
    }
}

void generateNewEventFile()
{
    //Gets current date and time.
    QString tmpName = QString::fromStdString(m_csvManager_Time.readRecord(0).at(1));
    QString myCurrentDateTime = QDateTime::fromString(tmpName,"MM/dd/yyyy hh:mm:ss AP").toString("_MM-dd-yyyy_hh.mm.ss_AP");
    //Gets name of log events file.
    QString fileName = QString(ROOT_FOLDER) + QString(EVENT_FOLDER) +  QString(EVENT_FILE_ROOT) + myCurrentDateTime;
    //Gets name of warnings file.
    QString fileName1 = QString(ROOT_FOLDER) + QString(WARNINGS_FOLDER) +  QString(EVENT_FILE_ROOT) + myCurrentDateTime;

    //Checks if log events file exists, if so, creates another file with an incremented name.
    QFileInfo checkFile(fileName + QString(CSV));
    int v = 1;
    while(checkFile.exists())
    {
        fileName = QString(ROOT_FOLDER) + QString(EVENT_FOLDER) +  QString(EVENT_FILE_ROOT) + myCurrentDateTime +
                "-" + QString::number(v);
        v++;
        checkFile = QFileInfo(fileName+ QString(CSV));
    }

    //Checks if warnings file exists, if so, creates another file with an incremented name.
    QFileInfo checkFile1(fileName1 + QString(CSV));
    v = 1;
    while(checkFile1.exists())
    {
        fileName1 = QString(ROOT_FOLDER) + QString(WARNINGS_FOLDER) +  QString(EVENT_FILE_ROOT) + myCurrentDateTime +
                   "-" + QString::number(v);
        v++;
        checkFile1 = QFileInfo(fileName1+ QString(CSV));
    }

    //Creates the log event and warnings files that will be currently appended to and saved as active.
    m_csvManager.create((fileName+ QString(CSV)).toStdString(), &m_columnTitles[0]);
    m_csvManager_Warnings.create((fileName1+ QString(CSV)).toStdString(), &m_columnTitles[0]);

    m_currentEventFile = fileName + QString(CSV);
    m_currentEventFileWarnings = fileName1 + QString(CSV);

    m_activeFiles.append(m_currentEventFile);
    m_activeWarningFiles.append(m_currentEventFileWarnings);
}

bool findCurrentEventFile()
{
    QDirIterator iterator(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER), QDir::Files);
    QDirIterator iterator1(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(WARNINGS_FOLDER), QDir::Files);
    //If method is called without any active log files, it will generate a new one.
    if (m_activeFiles.size() == 0)
    {
        generateNewEventFile();
        return true;
    }

    m_currentEventFile = m_activeFiles.at(m_activeFiles.size() -1);
    m_currentEventFileWarnings = m_activeWarningFiles.at(m_activeWarningFiles.size() -1);
    return true;
}

float fileSize(QString fileAbsolutePath)
{
    QFileInfo file(fileAbsolutePath);
    float result = (float)file.size() / (1e3);
    return result;
}

void initLogger()
{
    //Initiate the (empty) list of file names
    m_activeFiles = QVector<QString>();
    m_activeWarningFiles = QVector<QString>();
    bool success = true;

    //Log system is initialized only when root folder exists.
    //If the root directory does not exist, return and do not initiate logger
    if (!directoryExists(QString::fromStdString(ROOT_FOLDER)))
    {
        m_logInitiated = false;
        qDebug() << "NVENT" << "," << "No directory exists for logs.";
        return;
    }
    //If the logs/ folder exists, but NV_Vita_events does not, create the logs/NV_Vita_events/ folder
    if (!directoryExists(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER)))
    {
        success = QDir().mkdir(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER)) && success;

    }
    //If the logs/ folder exists, but NV_Vita_warnings does not, create the logs/NV_Vita_warnings/ folder
    if (!directoryExists(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(WARNINGS_FOLDER)))
    {
        success = QDir().mkdir(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(WARNINGS_FOLDER)) && success;

    }

    //Loop through files in NV_Vita_events/ and add the file names to the list of active files
    QDirIterator iterator(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(iterator.hasNext())
    {
        QFileInfo file(iterator.next());
        if(file.fileName() != "." && file.fileName() != "..")
            m_activeFiles.append(file.filePath());
    }

    //Loop through files in NV_Vita_warnings/ and add the file names to the list of active files
    QDirIterator iterator1(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(WARNINGS_FOLDER));
    while(iterator1.hasNext())
    {
        QFileInfo file(iterator1.next());
        if(file.fileName() != "." && file.fileName() != "..")
            m_activeWarningFiles.append(file.filePath());
    }
    m_logInitiated = success;
}

void startLogs()
{
    if (!m_logInitiated) return;

    //Tracks curent date, time, and time zone from time file.
    std::vector<std::string> tColumns = {"TYPE", "TIME"};
    m_csvManager_Time = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(TIME_FILE), &tColumns[0],2);

    //The logs file is a CSV file. These are the columns. A time stamp, the kind of log (Mode Request, Setting Request, Confirmation, Warning, etc.)
    m_columnTitles = {TIMESTAMP_COLUMN,TYPE_COLUMN,EVENT_COLUMN};

    //These are the CSV files for the log
    m_csvManager = CSVManager("/media/NVENT_FILES/" + m_currentEventFile.toStdString(),&m_columnTitles[0],3);
    m_csvManager_Warnings = CSVManager("/media/NVENT_FILES/" + m_currentEventFile.toStdString(),&m_columnTitles[0],3);

    //When the device powers on, the oldest log files will be deleted; log events by 2 weeks and warnings by 3 months.
    deleteOldestServiceLogs();
    deleteOldestWarningLogs();
    //Generates new log files.
    generateNewEventFile();

    m_service_state = false;
}

QString getLogDateTime()
{
    return QString::fromStdString(m_csvManager_Time.readRecord(0).at(1)) + " - " + QString::fromStdString(m_csvManager_Time.readRecord(1).at(1));
}

void logEvent(QString msg)
{
    //Creates a list of column values by seperating ','.
    QStringList messageList = msg.split(",");
    QString event, type;
    //FORMAT: NVENT,TYPE,EVENT
    //The first "NVENT" tells us that the log is created by our application
    //type is the type of log (Mode Request, Setting Request, Confirmation, Warning, etc.)
    //Event exactly what happened. IE what settings were set, what mode was toggled to which state, which warning was raised or lowered....
    if(messageList.size() == 3)
    {
        type = messageList.at(1);
        event = messageList.at(2);
    }

    //If the log has been initiated, and the first entry in the msg list is NVENT, add the event to the current event file
    if(m_logInitiated && messageList.at(0).contains("NVENT"))
    {
        if (type == " SERVICE " && event == " Service Events Activated.")
        {
            serviceState(true);
        }
        else if (type == " SERVICE " && event == " Service Events Deactivated.")
        {
            serviceState(false);
            type = type + "(SERVICE) ";
        }

        findCurrentEventFile();

        QString timeStamp = getLogDateTime();
        if (m_service_state) type = type + "(SERVICE) ";

        std::vector<std::string> vector = {timeStamp.toStdString(), type.toStdString(), event.toStdString()};
        m_csvManager.createRecord(&vector[0]);

        //Will only record onto warnings file if type reads " WARNING ".
        if (type == " WARNING " || type == " WARNING (SERVICE) "){
            m_csvManager_Warnings.createRecord(&vector[0]);
        }
    }
}

void log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    //If debug methods are called, but log system is never initialized.
    if (!m_logInitiated)
    {
        initLogger();
    }
    if(!m_logInitiated)
    {
        return;
    }
    switch (type)
    {
        case QtDebugMsg:
        {
            //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            fprintf(stderr, "%s \n", localMsg.constData());
            break;
        }
        case QtInfoMsg:
        {
            logEvent(localMsg.constData());
            break;
        }
        case QtWarningMsg:
        {
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        }
        case QtCriticalMsg:
        {
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        }
        case QtFatalMsg:
        {
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        }
    }
}


