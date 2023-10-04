#pragma once

#include <QObject>
#include <QtTest/QtTest>

#include "src/warnings/warning_manager.h"

#define MAX_FILE_SIZE_KB 1000
#define MAX_NUM_FILES 5

class LoggingTests : public QObject
{
    Q_OBJECT
public:
    explicit LoggingTests(QObject *parent = nullptr);


private slots:
    void init();
    void deleteOldestFile();
    void createNewFile();
    void fileExceedsMaxSize();
    void maxNumFiles();

    void createRecord();
    void readRecord();
    void editRecord();
    void deleteRecord();

private:
    QVector<int> m_fake_warning_1;
};
