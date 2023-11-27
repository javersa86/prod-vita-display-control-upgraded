#include "zero_manager.h"

/**
 * @author Joseph Aversa
 * @name zero_manager
 * @date 05/31/2022
 *
 * When the PIP and SP sensors are zeroed, the display asks the service technician to apply pressure
 * to those sensors to verify that the sensor zeroing was effective.
 * The display controller should save the value measured when the technician selects the "confirm" button.
 * This value should be viewable from the service menu.
 */

ZeroManager::ZeroManager(QObject *parent) :
    QObject(parent)
{
    //Retrive Time Stamp from time manager CSV file
    std::vector<std::string> tColumns = {"TYPE", "TIME"};
    m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", &tColumns[0],2);

    if (!QFileInfo::exists(QString::fromStdString("/media/NVENT_FILES/calibration")))
    {
        QDir().mkdir(QString::fromStdString("/media/NVENT_FILES/calibration"));
    }

    m_pipCsvManager = CSVManager(PIP_FILE, &zeroColumns[0], 2);
    m_spCsvManager = CSVManager(SP_FILE, &zeroColumns[0], 2);
    m_airCsvManager = CSVManager(INLET_AIR_FILE, &zeroColumns[0], 2);
    m_o2CsvManager = CSVManager(INLET_O2_FILE, &zeroColumns[0], 2);

    m_verifiedPipCsvManager = CSVManager(PIP_VERIFY_FILE, &zeroColumns[0], 2);
    m_verifiedSpCsvManager = CSVManager(SP_VERIFY_FILE, &zeroColumns[0], 2);
    m_verifiedInletAirCsvManager = CSVManager(INLET_AIR_VERIFY_FILE, &zeroColumns[0], 2);
    m_verifiedInletO2CsvManager = CSVManager(INLET_O2_VERIFY_FILE, &zeroColumns[0], 2);

    m_pip_timestamps = QVector<QString>(5);
    m_sp_timestamps = QVector<QString>(5);
    m_air_timestamps = QVector<QString>(5);
    m_o2_timestamps = QVector<QString>(5);

    m_verified_pip_timestamps = QVector<QString>(5);
    m_verified_sp_timestamps = QVector<QString>(5);
    m_verified_air_timestamps = QVector<QString>(5);
    m_verified_o2_timestamps = QVector<QString>(5);

    m_pipVals = QVector<float>(5);
    m_spVals = QVector<float>(5);
    m_airVals = QVector<float>(5);
    m_o2Vals = QVector<float>(5);

    m_verifiedPipVals = QVector<float>(5);
    m_verifiedSpVals = QVector<float>(5);
    m_verifiedAirVals = QVector<float>(5);
    m_verifiedO2Vals = QVector<float>(5);

    updateZeroVals();
}

void ZeroManager::updateZeroVals()
{
    updatePipVals();
    updateSpVals();
    updateInletAirVals();
    updateInletO2Vals();

    updateVerifiedPipVals();
    updateVerifiedSpVals();
    updateVerifiedInletAir();
    updateVerifiedInletO2();

    Q_EMIT zeroChanged();
}

void ZeroManager::deleteOldestPipVal()
{
    m_pipCsvManager.deleteRecord(0);
    updateZeroVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest PIP Value.";
}

void ZeroManager::updatePipVals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numPipVals = m_pipCsvManager.getNumEntries();

    if (m_numPipVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_vals.csv");
        m_pipCsvManager = CSVManager(PIP_FILE, &zeroColumns[0], 2);
        m_numPipVals = m_pipCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "PIP Values reset do to corruption.";
    }

    int i = 0;
    for(; i< m_numPipVals; i++)
    {
        std::vector<std::string> tmp = m_pipCsvManager.readRecord(i);
        if (tmp.size() != 2)
        {
            m_pip_timestamps[i] = QString::fromStdString("");
            m_pipVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_pip_timestamps[i] = QString::fromStdString(tmp[0]);
            m_pipVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_pip_timestamps[i] = QString::fromStdString("");
            m_pipVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_pip_timestamps[i] = QString::fromStdString("");
        m_pipVals[i] = -1;
    }
}

void ZeroManager::deleteOldestSpVal()
{
    m_spCsvManager.deleteRecord(0);
    updateZeroVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest SP Value.";
}

void ZeroManager::updateSpVals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numSpVals = m_spCsvManager.getNumEntries();

    if (m_numSpVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_vals.csv");
        m_spCsvManager = CSVManager(SP_FILE, &zeroColumns[0], 2);
        m_numSpVals = m_spCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "SP Values reset do to corruption.";
    }

    int i = 0;
    for(; i< m_numSpVals; i++)
    {
        std::vector<std::string> tmp = m_spCsvManager.readRecord(i);

        //Length of row must be 4
        if (tmp.size() != 2)
        {
            m_sp_timestamps[i] = QString::fromStdString("");
            m_spVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_sp_timestamps[i] = QString::fromStdString(tmp[0]);
            m_spVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_sp_timestamps[i] = QString::fromStdString("");
            m_spVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_sp_timestamps[i] = QString::fromStdString("");
        m_spVals[i] = -1;
    }
}

void ZeroManager::deleteOldestInletAirVal()
{
    m_airCsvManager.deleteRecord(0);
    updateZeroVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Inlet Air Value.";
}

void ZeroManager::updateInletAirVals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numAirVals = m_airCsvManager.getNumEntries();

    if (m_numAirVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/inlet_air_vals.csv");
        m_airCsvManager = CSVManager(INLET_AIR_FILE, &zeroColumns[0], 2);
        m_numAirVals = m_airCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet Air Values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numAirVals; i++)
    {
        std::vector<std::string> tmp = m_airCsvManager.readRecord(i);
        if (tmp.size() != 4)
        {
            m_air_timestamps[i] = QString::fromStdString("");
            m_airVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1])))
        {
            m_air_timestamps[i] = QString::fromStdString(tmp[0]);
            m_pipVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_air_timestamps[i] = QString::fromStdString("");
            m_airVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_air_timestamps[i] = QString::fromStdString("");
        m_airVals[i] = -1;
    }
}

void ZeroManager::deleteOldestInletO2Val()
{
    m_o2CsvManager.deleteRecord(0);
    updateZeroVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Inlet O2 Value.";
}

void ZeroManager::updateInletO2Vals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numO2Vals = m_o2CsvManager.getNumEntries();

    if (m_numO2Vals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/inlet_o2_vals.csv");
        m_o2CsvManager = CSVManager(INLET_O2_FILE, &zeroColumns[0], 2);
        m_numO2Vals = m_o2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet O2 values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numO2Vals; i++)
    {
        std::vector<std::string> tmp = m_o2CsvManager.readRecord(i);
        if(tmp.size() != 2)
        {
            m_o2_timestamps[i] = QString::fromStdString("");
            m_o2Vals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_o2_timestamps[i] = QString::fromStdString(tmp[0]);
            m_o2Vals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_o2_timestamps[i] = QString::fromStdString("");
            m_o2Vals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_o2_timestamps[i] = QString::fromStdString("");
        m_o2Vals[i] = -1;
    }
}

void ZeroManager::deleteOldestVerifiedPipVal()
{
    m_verifiedPipCsvManager.deleteRecord(0);
    updateVerifiedPipVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Verified PIP Value.";
}

void ZeroManager::updateVerifiedPipVals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedPipVals = m_verifiedPipCsvManager.getNumEntries();

    if (m_numVerifiedPipVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_verify.csv");
        m_verifiedPipCsvManager = CSVManager(PIP_VERIFY_FILE, &zeroColumns[0], 2);
        m_numVerifiedPipVals = m_verifiedPipCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified PIP values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numVerifiedPipVals; i++)
    {
        std::vector<std::string> tmp = m_verifiedPipCsvManager.readRecord(i);
        if(tmp.size() != 2)
        {
            m_verified_pip_timestamps[i] = QString::fromStdString("");
            m_verifiedPipVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_pip_timestamps[i] = QString::fromStdString(tmp[0]);
            m_verifiedPipVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_pip_timestamps[i] = QString::fromStdString("");
            m_verifiedPipVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_verified_pip_timestamps[i] = QString::fromStdString("");
        m_verifiedPipVals[i] = -1;
    }
}

void ZeroManager::deleteOldestVerifiedSpVal()
{
    m_verifiedSpCsvManager.deleteRecord(0);
    updateVerifiedSpVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Verified SP Value.";
}

void ZeroManager::updateVerifiedSpVals()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedSpVals = m_verifiedSpCsvManager.getNumEntries();

    if (m_numVerifiedSpVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_verify.csv");
        m_verifiedSpCsvManager = CSVManager(SP_VERIFY_FILE, &zeroColumns[0], 2);
        m_numVerifiedSpVals = m_verifiedSpCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified SP values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numVerifiedSpVals; i++)
    {
        std::vector<std::string> tmp = m_verifiedSpCsvManager.readRecord(i);
        if(tmp.size() != 2)
        {
            m_verified_sp_timestamps[i] = QString::fromStdString("");
            m_verifiedSpVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_sp_timestamps[i] = QString::fromStdString(tmp[0]);
            m_verifiedSpVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_sp_timestamps[i] = QString::fromStdString("");
            m_verifiedSpVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_verified_sp_timestamps[i] = QString::fromStdString("");
        m_verifiedSpVals[i] = -1;
    }
}

void ZeroManager::deleteOldestVerifiedInletAirVal()
{
    m_verifiedInletAirCsvManager.deleteRecord(0);
    updateVerifiedInletAir();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Verified Air Value.";
}

void ZeroManager::updateVerifiedInletAir()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedAirVals = m_verifiedInletAirCsvManager.getNumEntries();

    if (m_numVerifiedAirVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_verify.csv");
        m_verifiedInletAirCsvManager = CSVManager(INLET_AIR_VERIFY_FILE, &zeroColumns[0], 2);
        m_numVerifiedAirVals = m_verifiedInletAirCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified Air values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numVerifiedAirVals; i++)
    {
        std::vector<std::string> tmp = m_verifiedInletAirCsvManager.readRecord(i);
        if(tmp.size() != 2)
        {
            m_verified_air_timestamps[i] = QString::fromStdString("");
            m_verifiedAirVals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_air_timestamps[i] = QString::fromStdString(tmp[0]);
            m_verifiedAirVals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_air_timestamps[i] = QString::fromStdString("");
            m_verifiedAirVals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_verified_air_timestamps[i] = QString::fromStdString("");
        m_verifiedAirVals[i] = -1;
    }
}

void ZeroManager::deleteOldestVerifiedInletO2Val()
{
    m_verifiedInletO2CsvManager.deleteRecord(0);
    updateVerifiedInletAir();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest Verified O2 Value.";
}

void ZeroManager::updateVerifiedInletO2()
{
    QRegExp re(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedO2Vals = m_verifiedInletO2CsvManager.getNumEntries();

    if (m_numVerifiedO2Vals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_verify.csv");
        m_verifiedInletO2CsvManager = CSVManager(INLET_O2_VERIFY_FILE, &zeroColumns[0], 2);
        m_numVerifiedO2Vals = m_verifiedInletO2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified O2 values reset do to corruption.";
    }

    int i = 0;
    for (; i < m_numVerifiedO2Vals; i++)
    {
        std::vector<std::string> tmp = m_verifiedInletO2CsvManager.readRecord(i);
        if(tmp.size() != 2)
        {
            m_verified_o2_timestamps[i] = QString::fromStdString("");
            m_verifiedO2Vals[i] = -1;
        }
        else if (re.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_o2_timestamps[i] = QString::fromStdString(tmp[0]);
            m_verifiedO2Vals[i] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_o2_timestamps[i] = QString::fromStdString("");
            m_verifiedO2Vals[i] = -1;
        }
    }

    for(; i < MAX_ZERO_VALS; i++)
    {
        m_verified_o2_timestamps[i] = QString::fromStdString("");
        m_verifiedO2Vals[i] = -1;
    }
}

void ZeroManager::addZeroValue(int id, float value)
{
    if (id == 0)
    {
        //Deletes oldest PIP value if at 5 entry limit.
        if (m_numPipVals >= 5)
        {
            deleteOldestPipVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_pipCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "PIP Value: " + QString::number(value);
    }
    else if (id == 1)
    {
        //Deletes oldest SP value if at 5 entry limit.
        if (m_numSpVals >= 5)
        {
            deleteOldestSpVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_spCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "SP Value: " + QString::number(value);
    }
    else if (id == 3)
    {
        //Deletes oldest Inlet Air value if at 5 entry limit.
        if (m_numAirVals >= 5)
        {
            deleteOldestInletAirVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_airCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet Air Value: " + QString::number(value);
    }
    else if (id == 4)
    {
        //Deletes oldest Inlet O2 value if at 5 entry limit.
        if (m_numO2Vals >= 5)
        {
            deleteOldestInletO2Val();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_o2CsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet O2 Value: " + QString::number(value);
    }
    updateZeroVals();
}

void ZeroManager::addVerifiedValue(int id, float value)
{
    if (id == 0)
    {
        //Deletes oldest PIP value if at 5 entry limit.
        if (m_numVerifiedPipVals >= 5)
        {
            deleteOldestVerifiedPipVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedPipCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified PIP Value: " + QString::number(value);
    }
    else if (id == 1)
    {
        //Deletes oldest SP value if at 5 entry limit.
        if (m_numVerifiedSpVals >= 5)
        {
            deleteOldestVerifiedSpVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedSpCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified SP Value: " + QString::number(value);
    }
    else if (id == 3)
    {
        //Deletes oldest Inlet Air value if at 5 entry limit.
        if (m_numVerifiedAirVals >= 5)
        {
            deleteOldestVerifiedInletAirVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedInletAirCsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified Inlet Air Value: " + QString::number(value);
    }
    else if (id == 4)
    {
        //Deletes oldest Inlet O2 value if at 5 entry limit.
        if (m_numVerifiedO2Vals >= 5)
        {
            deleteOldestVerifiedInletO2Val();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedInletO2CsvManager.createRecord(&vector[0]);
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified Inlet O2 Value: " + QString::number(value);
    }
    updateZeroVals();

}

float ZeroManager::getZeroPIP()
{
    if (m_numPipVals > 0)
    {
        return m_pipVals.at(m_numPipVals - 1);
    }
    return -1;
}

float ZeroManager::getZeroSP()
{
    if (m_numSpVals > 0)
    {
        return m_spVals.at(m_numSpVals - 1);
    }
    return -1;
}

float ZeroManager::getInletAir()
{
    if (m_numAirVals > 0)
    {
        return m_airVals.at(m_numAirVals - 1);
    }
    return -1;
}

float ZeroManager::getInletO2()
{
    if (m_numO2Vals > 0)
    {
        return m_o2Vals.at(m_numO2Vals - 1);
    }
    return -1;
}

float ZeroManager::getVerifiedZeroPIP()
{
    if (m_numVerifiedPipVals > 0)
    {
        return m_verifiedPipVals.at(m_numVerifiedPipVals - 1);
    }
    return -1;
}

float ZeroManager::getVerifiedZeroSP()
{
    if (m_numVerifiedSpVals > 0)
    {
        return m_verifiedSpVals.at(m_numVerifiedSpVals - 1);
    }
    return -1;
}

float ZeroManager::getVerifiedInletAir()
{
    if (m_numVerifiedAirVals > 0)
    {
        return m_verifiedAirVals.at(m_numVerifiedAirVals - 1);
    }
    return -1;
}

float ZeroManager::getVerifiedInletO2()
{
    if (m_numVerifiedO2Vals > 0)
    {
        return m_verifiedO2Vals.at(m_numVerifiedO2Vals - 1);
    }
    return -1;
}
