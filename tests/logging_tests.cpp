#include "logging_tests.h"
#include "src/logger/log_manager.h"
#include "src/logger/preset_manager.h"
#include <QDir>

LoggingTests::LoggingTests(QObject *parent)
    :QObject(parent)
{
}

void LoggingTests::init()
{
    QDir dir = QDir::currentPath();
    dir.mkdir("logs");
    initLogger();
}

void LoggingTests::deleteOldestFile()
{
    generateNewEventFile();
    QDir events("logs/events");
    generateNewEventFile();
    int num = events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count();
    QVERIFY(num > 0);
    deleteOldestEventFile();
    QVERIFY(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == num-1);
}

void LoggingTests::createNewFile()
{

    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }
    int num = events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count();
    QVERIFY(num == 0);
    generateNewEventFile();
    num = events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count();
    QVERIFY(num == 1);
}

void LoggingTests::fileExceedsMaxSize()
{
    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }
    generateNewEventFile();
    QFileInfo file(m_currentEventFile);
    QString firstFile = m_currentEventFile;
    QString timeStamp = QDateTime::currentDateTime().toString("dd/MM/yyyy-hh:mm:ss");
    float size = fileSize(firstFile) + .1;
    while(size < MAX_FILE_SIZE_KB)
    {
        logEvent(QString("NVENT,TYPE,EVENT"));
        size = fileSize(firstFile) - ((float)QString("NVENT,TYPE,EVENT").size()) / 1000 - .001;
    }
    logEvent(QString("NVENT,TYPE,EVENT"));
    logEvent(QString("NVENT,TYPE,EVENT"));
    logEvent(QString("NVENT,TYPE,EVENT"));
    logEvent(QString("NVENT,TYPE,EVENT"));
    QVERIFY(QFileInfo(file).filePath() != QString(m_currentEventFile));

}

void LoggingTests::maxNumFiles()
{
    QDir events("logs/events");
    for(int i = 0; i <= MAX_NUM_FILES + 1; i++)
    {
        generateNewEventFile();
        if (i > 100)
        {
            break;
        }
    }
    int num = events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count();
    QVERIFY(num == MAX_NUM_FILES);
}

void LoggingTests::createRecord()
{
    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }

    generateNewEventFile();
    QString type = "type 1";
    QString event = "event 1";
    logEvent("NVENT," + type + "," + event);
    QFile file(m_currentEventFile);
    file.open(QFile::ReadOnly);
    QTextStream in (&file);
    QString line;
    bool appended = false;
    while (!in.atEnd()){
        line = in.readLine();
        appended = appended | (line.contains(type) && line.contains(event));
    };
    QVERIFY(appended);
}

void LoggingTests::readRecord()
{
    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }

    generateNewEventFile();
    std::vector<std::string> buffer = {"one", "two", "three"};
    std::vector<std::string> buffer_copy;
    m_csvManager.createRecord(&buffer[0]);
    buffer_copy = m_csvManager.readRecord(0);
    QVERIFY(buffer == buffer_copy);
    buffer_copy = m_csvManager.readRecord(1);
    QVERIFY(buffer_copy.size() == 0);
}

void::LoggingTests::editRecord()
{
    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }

    generateNewEventFile();
    std::vector<std::string> buffer = {"one", "two", "three"};
    std::vector<std::string> buffer_copy;


    m_csvManager.updateRecord(1, &buffer[0]);
    buffer_copy = m_csvManager.readRecord(1);
    QVERIFY(buffer_copy.size() == 0);


    m_csvManager.createRecord(&buffer[0]);
    m_csvManager.createRecord(&buffer[0]);

    buffer = {"apple", "banana", "pear"};

    m_csvManager.updateRecord(1, &buffer[0]);
    buffer_copy = m_csvManager.readRecord(1);

    auto pair = std::mismatch(buffer.begin(), buffer.end(), buffer_copy.begin());
    QVERIFY(pair.first == buffer.end() && pair.second == buffer_copy.end());

}

void LoggingTests::deleteRecord()
{
    QDir events(QString::fromStdString(ROOT_FOLDER) + QString::fromStdString(EVENT_FOLDER));
    while(events.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() > 0)
    {
        deleteOldestEventFile();
    }

    generateNewEventFile();
    std::vector<std::string> buffer_copy;


    //add {one, two, three to file}
    std::vector<std::string> buffer = {"one", "two", "three"};
    m_csvManager.createRecord(&buffer[0]);

    //add {peach, banana,pear to file}
    buffer = {"peach", "banana", "pear"};
    m_csvManager.createRecord(&buffer[0]);

    //verify index zero does not match the most recent insertion
    buffer_copy = m_csvManager.readRecord(0);
    auto pair = std::mismatch(buffer.begin(), buffer.end(), buffer_copy.begin());
    QVERIFY(pair.first != buffer.end() || pair.second != buffer_copy.end());

    //delete record at index 0
    m_csvManager.deleteRecord(0);
    QVERIFY(buffer_copy.size() > 0);

    //verify index zero does match most recent insertion
    buffer_copy = m_csvManager.readRecord(0);
    pair = std::mismatch(buffer.begin(), buffer.end(), buffer_copy.begin());
    QVERIFY(pair.first == buffer.end() && pair.second == buffer_copy.end());

}

QTEST_MAIN(LoggingTests)
