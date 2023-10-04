#include "o2_cal_manager.h"
#include "csv_manager.h"

O2CalManager::O2CalManager(QObject *parent) :
    QObject(parent)
{
    //Retrive Time Stamp from time manager CSV file
    std::vector<std::string> tColumns = {"TYPE", "TIME"};
    m_timeManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", &tColumns[0],2);

    m_o2CsvManager = CSVManager("/media/NVENT_FILES/" + std::string(O2_CAL_FILE),&o2Columns[0], 5);
    m_timeStamps = QVector<QString>(MAX_O2_VALS);
    m_o2Vals = QVector<QVector<int>>( MAX_O2_VALS );
    m_volts = QVector<QVector<QString>>( MAX_O2_VALS );
    updateO2Vals();

    m_calibration_progress_timer = new QTimer(this);
    m_calibration_progress_timer->setInterval(1000);
    m_calibration_progress_timer->setSingleShot(false);
    connect(m_calibration_progress_timer, &QTimer::timeout, this, &O2CalManager::incrementCalibrationProgress);

}

void O2CalManager::updateO2Vals()
{
    QRegExp re("\\d*");
    QRegExp re1("[+-]?([0-9]*[.])?[0-9]+");

    m_numO2Vals = m_o2CsvManager.getNumEntries();

    //Reset if o2 Cal file is corrupted.
    if (m_numO2Vals > MAX_O2_VALS)
    {
        system("rm /media/NVENT_FILES/o2_cal_vals.csv");
        m_o2CsvManager = CSVManager("/media/NVENT_FILES/" + std::string(O2_CAL_FILE),&o2Columns[0], 5);
        m_numO2Vals = m_o2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "O2 Calibration Manager reset do to corruption.";
    }

    int i = 0;
    for(; i< m_numO2Vals; i++)
    {
        std::vector<std::string> tmp =  m_o2CsvManager.readRecord(i);
        m_timeStamps[i] = "";
        m_o2Vals[i].resize(2);
        m_volts[i].resize(2);
        //The length of the row must be 7
        if (tmp.size() != 5)
        {
            m_timeStamps[i] = "";
            m_o2Vals[i] = QVector<int>(2).fill(-1);
            m_volts[i] = QVector<QString>(2).fill("-1");
        }
        else
        {
            for (int j = 0; j < 5; j++)
            {
                if (j == 0)
                {
                    m_timeStamps[i] = QString::fromStdString(tmp[j]);
                }
                else if (j == 1)
                {
                    if (re.exactMatch(QString::fromStdString(tmp[j])))
                    {
                        m_o2Vals[i][0] = QString::fromStdString(tmp[j]).toInt();
                    }
                    //If value is not an int
                    else
                    {
                        m_o2Vals[i][0] = -1;
                    }
                }
                else if (j == 2)
                {
                    if (re.exactMatch(QString::fromStdString(tmp[j])))
                    {
                        m_o2Vals[i][1] = QString::fromStdString(tmp[j]).toInt();
                    }
                    //If value is not an int
                    else
                    {
                        m_o2Vals[i][1] = -1;
                    }
                }
                else if (j == 3)
                {
                    if (re1.exactMatch(QString::fromStdString(tmp[j])))
                    {
                        m_volts[i][0] = QString::fromStdString(tmp[j]);
                    }
                    //If value is not a float
                    else
                    {
                        m_volts[i][0] = "-1";
                    }
                }
                else if (j == 4)
                {
                    if (re1.exactMatch(QString::fromStdString(tmp[j])))
                    {
                        m_volts[i][1] = QString::fromStdString(tmp[j]);
                    }
                    //If value is not a float
                    else
                    {
                        m_volts[i][1] = "-1";
                    }
                }
            }
        }
    }

    for(;i < MAX_O2_VALS; i++)
    {
        m_timeStamps[i] = "";
        m_o2Vals[i] = QVector<int>(2).fill(-1);
        m_volts[i] = QVector<QString>(2).fill("-1");
    }

    emit o2ValsChanged();
}

int O2CalManager::getNumO2CalVals()
{
    return m_numO2Vals;
}

void O2CalManager::addO2CalVals(int low, int high, float lowVolt, float highVolt)
{
    while(m_numO2Vals >= 5)
    {
        deleteOldestO2CalVal();
    }

    std::string timeStamp = m_timeManager.readRecord(0).at(1) + " " + m_timeManager.readRecord(1).at(1);

    std::stringstream stream1;
    stream1 << std::fixed << std::setprecision(3) << lowVolt;
    std::string s1 = stream1.str();

    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(3) << highVolt;
    std::string s2 = stream2.str();
    std::vector<std::string> tmp = {timeStamp, std::to_string(low), std::to_string(high), s1, s2};

    m_o2CsvManager.createRecord(&tmp[0]);
    updateO2Vals();

    qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "Save O2 Calibration values: Low Calibration " + QString::number(low) + "; High Calibration " + QString::number(high) + "; Low Voltage " + QString::number(lowVolt) + "; High Voltage " + QString::number(highVolt);
}

void O2CalManager::deleteOldestO2CalVal()
{
    m_o2CsvManager.deleteRecord(0);
    updateO2Vals();

    qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "Delete Oldest Calibration values.";
}

QString O2CalManager::getMostRecentTimeStamp()
{
    if (m_numO2Vals)
    {
        return m_timeStamps[m_numO2Vals - 1];
    }
    else return "";
}

QString O2CalManager::getLastTimeStamp()
{
    if (m_numO2Vals >= 2)
    {
        return m_timeStamps[m_numO2Vals - 2];
    }
    else if (m_numO2Vals == 1)
    {
        return m_timeStamps[0];
    }
    else return "";
}

QVector<int> O2CalManager::getMostRecentO2CalVal()
{
    if (m_numO2Vals )
    {
        return m_o2Vals[m_numO2Vals - 1];
    }
    else return QVector<int>(2);
}

QVector<QString> O2CalManager::getMostRecentVoltVal()
{
    if (m_numO2Vals )
    {
        return m_volts[m_numO2Vals - 1];
    }
    else return QVector<QString>(2);
}

QVector<QString> O2CalManager::getLastVoltVal()
{
    if (m_numO2Vals >= 2)
    {
        return m_volts[m_numO2Vals - 2];
    }
    else if (m_numO2Vals == 1)
    {
        return m_volts[0];
    }
    else return QVector<QString>(2);
}

void O2CalManager::calibrationState()
{
    if (m_calibration_progress_timer->isActive())
    {
        return;
    }
    m_calibration_text = "01:00";
    m_calibration_seconds = 60;
    emit calibrationProgressSignal();
    m_calibration_progress_timer->start();
}

void O2CalManager::incrementCalibrationProgress()
{
    int seconds = m_calibration_seconds;
    int minutes = seconds / 60;
    m_calibration_text = prependZero(int(minutes % 60)) + ":" + prependZero(int(seconds % 60));
    m_calibration_seconds = m_calibration_seconds - 1;
    emit calibrationProgressSignal();

    if (m_calibration_seconds == -1)
    {
        m_calibration_progress_timer->stop();
        m_calibration_text = "01:00";
    }
}

QString O2CalManager::prependZero(int value)
{
    if (value < 10)
    {
        return "0" + QString::number(value);
    }
    else return QString::number(value);
}

QString O2CalManager::getCalibrationProgressTime()
{
    return m_calibration_text;
}

void O2CalManager::resetCalibration()
{
    m_calibration_progress_timer->stop();
    m_calibration_text = "01:00";
    m_calibration_seconds = 60;
}
