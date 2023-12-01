#include "o2_cal_manager.h"
#include "csv_manager.h"

O2CalManager::O2CalManager(QObject *parent) :
    QObject(parent), m_calibration_progress_timer(new QTimer(this))
{
    //Retrive Time Stamp from time manager CSV file
    std::vector<std::string> tColumns = {"TYPE", "TIME"};
    m_timeManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", tColumns.data(), 2);

    m_o2CsvManager = CSVManager("/media/NVENT_FILES/" + std::string(O2_CAL_FILE),(o2Columns).data(), MAX_O2_VALS);
    m_timeStamps = QVector<QString>(MAX_O2_VALS);
    m_o2Vals = QVector<QVector<int>>( MAX_O2_VALS );
    m_volts = QVector<QVector<QString>>( MAX_O2_VALS );
    updateO2Vals();

    constexpr int INTERVAL_ONE_SECOND = 1000;

    m_calibration_progress_timer->setInterval(INTERVAL_ONE_SECOND);
    m_calibration_progress_timer->setSingleShot(false);
    connect(m_calibration_progress_timer, &QTimer::timeout, this, &O2CalManager::incrementCalibrationProgress);

}

void O2CalManager::updateO2Vals()
{
    int index = 0;
    m_numO2Vals = m_o2CsvManager.getNumEntries();

    //Reset if o2 Cal file is corrupted.
    if (m_numO2Vals > MAX_O2_VALS)
    {
        system("rm /media/NVENT_FILES/o2_cal_vals.csv");
        m_o2CsvManager = CSVManager("/media/NVENT_FILES/" + std::string(O2_CAL_FILE),(o2Columns).data(), MAX_O2_VALS);
        m_numO2Vals = m_o2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "O2 Calibration Manager reset do to corruption.";
    }

    for(; index < m_numO2Vals; index++)
    {
        constructO2CalVals(index);
    }

    for(; index < MAX_O2_VALS; index++)
    {
        m_timeStamps[index] = QString::fromStdString("");
        m_o2Vals[index] = QVector<int>(2).fill(-1);
        m_volts[index] = QVector<QString>(2).fill(QString::fromStdString("-1"));
    }

    emit o2ValsChanged();
}

void O2CalManager::constructO2CalVals(int index)
{
    std::vector<std::string> tmp =  m_o2CsvManager.readRecord(index);
    m_timeStamps[index] = QString::fromStdString("");
    m_o2Vals[index].resize(2);
    m_volts[index].resize(2);

    //The length of the row must be 7
    if (tmp.size() != MAX_O2_VALS)
    {
        m_timeStamps[index] = QString::fromStdString("");
        m_o2Vals[index] = QVector<int>(2).fill(-1);
        m_volts[index] = QVector<QString>(2).fill(QString::fromStdString("-1"));
    }
    else
    {
        for (int j = 0; j < MAX_O2_VALS; j++)
        {
            constructO2CalValRows(tmp, index, j);
        }
    }

}

void O2CalManager::constructO2CalValRows(std::vector<std::string> tmp, int index_i, int index_j)
{
    QRegExp regularExpresion(QString::fromStdString("\\d*"));
    QRegExp regularExpresion1(QString::fromStdString("[+-]?([0-9]*[.])?[0-9]+"));

    if (index_j == 0)
    {
        m_timeStamps[index_i] = QString::fromStdString(tmp[index_j]);
    }
    else if (index_j == 1)
    {
        if (regularExpresion.exactMatch(QString::fromStdString(tmp[index_j])))
        {
            m_o2Vals[index_i][0] = QString::fromStdString(tmp[index_j]).toInt();
        }
        //If value is not an int
        else
        {
            m_o2Vals[index_i][0] = -1;
        }
    }
    else if (index_j == 2)
    {
        if (regularExpresion.exactMatch(QString::fromStdString(tmp[index_j])))
        {
            m_o2Vals[index_i][1] = QString::fromStdString(tmp[index_j]).toInt();
        }
        //If value is not an int
        else
        {
            m_o2Vals[index_i][1] = -1;
        }
    }
    else if (index_j == 3)
    {
        if (regularExpresion1.exactMatch(QString::fromStdString(tmp[index_j])))
        {
            m_volts[index_i][0] = QString::fromStdString(tmp[index_j]);
        }
        //If value is not a float
        else
        {
            m_volts[index_i][0] = QString::fromStdString("-1");
        }
    }
    else if (index_j == 4)
    {
        if (regularExpresion1.exactMatch(QString::fromStdString(tmp[index_j])))
        {
            m_volts[index_i][1] = QString::fromStdString(tmp[index_j]);
        }
        //If value is not a float
        else
        {
            m_volts[index_i][1] = QString::fromStdString("-1");
        }
    }
}

auto O2CalManager::getNumO2CalVals() const -> int
{
    return m_numO2Vals;
}

void O2CalManager::addO2CalVals(int low, int high, float lowVolt, float highVolt)
{
    while(m_numO2Vals >= MAX_O2_VALS)
    {
        deleteOldestO2CalVal();
    }

    std::string timeStamp = m_timeManager.readRecord(0).at(1) +
            " " +
            m_timeManager.readRecord(1).at(1);

    std::stringstream stream1;
    stream1 << std::fixed << std::setprecision(3) << lowVolt;
    std::string strLine1 = stream1.str();

    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(3) << highVolt;
    std::string strLine2 = stream2.str();

    std::vector<std::string> tmp = {
        timeStamp,
        std::to_string(low),
        std::to_string(high),
        strLine1,
        strLine2
    };

    m_o2CsvManager.createRecord(tmp.data());
    updateO2Vals();

    qInfo() << "NVENT"
            << ","
            << "O2 CALIBRATION"
            << ","
            << "Save O2 Calibration values: Low Calibration " +
               QString::number(low) + "; High Calibration " +
               QString::number(high) + "; Low Voltage " +
               QString::number(lowVolt) +
               "; High Voltage " +
               QString::number(highVolt);
}

void O2CalManager::deleteOldestO2CalVal()
{
    m_o2CsvManager.deleteRecord(0);
    updateO2Vals();

    qInfo() << "NVENT" << "," << "O2 CALIBRATION" << "," << "Delete Oldest Calibration values.";
}

auto O2CalManager::getMostRecentTimeStamp() -> QString
{
    if (!m_timeStamps.isEmpty() && m_numO2Vals > 0)
    {
        return m_timeStamps.at(m_numO2Vals - 1);
    }
    return QString::fromStdString("");
}

auto O2CalManager::getLastTimeStamp() -> QString
{
    if (m_numO2Vals >= 2)
    {
        return m_timeStamps.at(m_numO2Vals - 2);
    }
    if (m_numO2Vals == 1)
    {
        return m_timeStamps.at(0);
    }
    return QString::fromStdString("");
}

auto O2CalManager::getMostRecentO2CalVal() -> QVector<int>
{
    if (m_numO2Vals > 0)
    {
        return m_o2Vals.at(m_numO2Vals - 1);
    }
    return QVector<int>(2);
}

auto O2CalManager::getMostRecentVoltVal() -> QVector<QString>
{
    if (m_numO2Vals > 0)
    {
        return m_volts.at(m_numO2Vals - 1);
    }
    return QVector<QString>(2);
}

auto O2CalManager::getLastVoltVal() -> QVector<QString>
{
    if (m_numO2Vals >= 2)
    {
        return m_volts.at(m_numO2Vals - 2);
    }
    if (m_numO2Vals == 1)
    {
        return m_volts.at(0);
    }
    return QVector<QString>(2);
}

void O2CalManager::calibrationState()
{
    if (m_calibration_progress_timer->isActive())
    {
        return;
    }
    m_calibration_text = QString::fromStdString("01:00");
    m_calibration_seconds = DEFAULT_SECONDS;

    emit calibrationProgressSignal();

    m_calibration_progress_timer->start();
}

void O2CalManager::incrementCalibrationProgress()
{
    int seconds = m_calibration_seconds;
    int minutes = seconds / DEFAULT_SECONDS;
    m_calibration_text = prependZero(int(minutes % DEFAULT_SECONDS)) + ":" + prependZero(int(seconds % DEFAULT_SECONDS));
    m_calibration_seconds = m_calibration_seconds - 1;

    emit calibrationProgressSignal();

    if (m_calibration_seconds == -1)
    {
        m_calibration_progress_timer->stop();
        m_calibration_text = QString::fromStdString("01:00");
    }
}

auto O2CalManager::prependZero(int value) -> QString
{
    const int UNDER_TEN = 10;
    if (value < UNDER_TEN)
    {
        return "0" + QString::number(value);
    }
    return QString::number(value);
}

auto O2CalManager::getCalibrationProgressTime() -> QString
{
    return m_calibration_text;
}

void O2CalManager::resetCalibration()
{
    m_calibration_progress_timer->stop();
    m_calibration_text = QString::fromStdString("01:00");
    m_calibration_seconds = DEFAULT_SECONDS;
}
