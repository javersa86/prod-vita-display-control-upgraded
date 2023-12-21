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
    m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", tColumns.data(),2);

    if (!QFileInfo::exists(QString::fromStdString("/media/NVENT_FILES/calibration")))
    {
        QDir().mkdir(QString::fromStdString("/media/NVENT_FILES/calibration"));
    }

    m_pipCsvManager = CSVManager(PIP_FILE, (zeroColumns).data(), 2);
    m_spCsvManager = CSVManager(SP_FILE, (zeroColumns).data(), 2);
    m_airCsvManager = CSVManager(INLET_AIR_FILE, (zeroColumns).data(), 2);
    m_o2CsvManager = CSVManager(INLET_O2_FILE, (zeroColumns).data(), 2);

    m_verifiedPipCsvManager = CSVManager(PIP_VERIFY_FILE, (zeroColumns).data(), 2);
    m_verifiedSpCsvManager = CSVManager(SP_VERIFY_FILE, (zeroColumns).data(), 2);
    m_verifiedInletAirCsvManager = CSVManager(INLET_AIR_VERIFY_FILE, (zeroColumns).data(), 2);
    m_verifiedInletO2CsvManager = CSVManager(INLET_O2_VERIFY_FILE, (zeroColumns).data(), 2);

    m_pip_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_sp_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_air_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_o2_timestamps = QVector<QString>(MAX_ZERO_VALS);

    m_verified_pip_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_verified_sp_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_verified_air_timestamps = QVector<QString>(MAX_ZERO_VALS);
    m_verified_o2_timestamps = QVector<QString>(MAX_ZERO_VALS);

    m_pipVals = QVector<float>(MAX_ZERO_VALS);
    m_spVals = QVector<float>(MAX_ZERO_VALS);
    m_airVals = QVector<float>(MAX_ZERO_VALS);
    m_o2Vals = QVector<float>(MAX_ZERO_VALS);

    m_verifiedPipVals = QVector<float>(MAX_ZERO_VALS);
    m_verifiedSpVals = QVector<float>(MAX_ZERO_VALS);
    m_verifiedAirVals = QVector<float>(MAX_ZERO_VALS);
    m_verifiedO2Vals = QVector<float>(MAX_ZERO_VALS);

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

    emit zeroChanged();
}

void ZeroManager::deleteOldestPipVal()
{
    m_pipCsvManager.deleteRecord(0);
    updateZeroVals();
    qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Delete Oldest PIP Value.";
}

void ZeroManager::updatePipVals()
{
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numPipVals = m_pipCsvManager.getNumEntries();

    if (m_numPipVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_vals.csv");
        m_pipCsvManager = CSVManager(PIP_FILE, (zeroColumns).data(), 2);
        m_numPipVals = m_pipCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "PIP Values reset do to corruption.";
    }

    int index = 0;
    for(; index < m_numPipVals; index++)
    {
        std::vector<std::string> tmp = m_pipCsvManager.readRecord(index);
        if (tmp.size() != 2)
        {
            m_pip_timestamps[index] = QString::fromStdString("");
            m_pipVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_pip_timestamps[index] = QString::fromStdString(tmp[0]);
            m_pipVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_pip_timestamps[index] = QString::fromStdString("");
            m_pipVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_pip_timestamps[index] = QString::fromStdString("");
        m_pipVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numSpVals = m_spCsvManager.getNumEntries();

    if (m_numSpVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_vals.csv");
        m_spCsvManager = CSVManager(SP_FILE, (zeroColumns).data(), 2);
        m_numSpVals = m_spCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "SP Values reset do to corruption.";
    }

    int index = 0;
    for(; index< m_numSpVals; index++)
    {
        std::vector<std::string> tmp = m_spCsvManager.readRecord(index);

        //Length of row must be 4
        if (tmp.size() != 2)
        {
            m_sp_timestamps[index] = QString::fromStdString("");
            m_spVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1])))
        {
            m_sp_timestamps[index] = QString::fromStdString(tmp[0]);
            m_spVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_sp_timestamps[index] = QString::fromStdString("");
            m_spVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_sp_timestamps[index] = QString::fromStdString("");
        m_spVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numAirVals = m_airCsvManager.getNumEntries();

    if (m_numAirVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/inlet_air_vals.csv");
        m_airCsvManager = CSVManager(INLET_AIR_FILE, (zeroColumns).data(), 2);
        m_numAirVals = m_airCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet Air Values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numAirVals; index++)
    {
        std::vector<std::string> tmp = m_airCsvManager.readRecord(index);
        if (tmp.size() != 4)
        {
            m_air_timestamps[index] = QString::fromStdString("");
            m_airVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1])))
        {
            m_air_timestamps[index] = QString::fromStdString(tmp[0]);
            m_pipVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_air_timestamps[index] = QString::fromStdString("");
            m_airVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_air_timestamps[index] = QString::fromStdString("");
        m_airVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numO2Vals = m_o2CsvManager.getNumEntries();

    if (m_numO2Vals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/inlet_o2_vals.csv");
        m_o2CsvManager = CSVManager(INLET_O2_FILE, (zeroColumns).data(), 2);
        m_numO2Vals = m_o2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet O2 values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numO2Vals; index++)
    {
        std::vector<std::string> tmp = m_o2CsvManager.readRecord(index);
        if(tmp.size() != 2)
        {
            m_o2_timestamps[index] = QString::fromStdString("");
            m_o2Vals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_o2_timestamps[index] = QString::fromStdString(tmp[0]);
            m_o2Vals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_o2_timestamps[index] = QString::fromStdString("");
            m_o2Vals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_o2_timestamps[index] = QString::fromStdString("");
        m_o2Vals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedPipVals = m_verifiedPipCsvManager.getNumEntries();

    if (m_numVerifiedPipVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_verify.csv");
        m_verifiedPipCsvManager = CSVManager(PIP_VERIFY_FILE, (zeroColumns).data(), 2);
        m_numVerifiedPipVals = m_verifiedPipCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified PIP values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numVerifiedPipVals; index++)
    {
        std::vector<std::string> tmp = m_verifiedPipCsvManager.readRecord(index);
        if(tmp.size() != 2)
        {
            m_verified_pip_timestamps[index] = QString::fromStdString("");
            m_verifiedPipVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_pip_timestamps[index] = QString::fromStdString(tmp[0]);
            m_verifiedPipVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_pip_timestamps[index] = QString::fromStdString("");
            m_verifiedPipVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_verified_pip_timestamps[index] = QString::fromStdString("");
        m_verifiedPipVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedSpVals = m_verifiedSpCsvManager.getNumEntries();

    if (m_numVerifiedSpVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_verify.csv");
        m_verifiedSpCsvManager = CSVManager(SP_VERIFY_FILE, (zeroColumns).data(), 2);
        m_numVerifiedSpVals = m_verifiedSpCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified SP values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numVerifiedSpVals; index++)
    {
        std::vector<std::string> tmp = m_verifiedSpCsvManager.readRecord(index);
        if(tmp.size() != 2)
        {
            m_verified_sp_timestamps[index] = QString::fromStdString("");
            m_verifiedSpVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_sp_timestamps[index] = QString::fromStdString(tmp[0]);
            m_verifiedSpVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_sp_timestamps[index] = QString::fromStdString("");
            m_verifiedSpVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_verified_sp_timestamps[index] = QString::fromStdString("");
        m_verifiedSpVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedAirVals = m_verifiedInletAirCsvManager.getNumEntries();

    if (m_numVerifiedAirVals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/sp_verify.csv");
        m_verifiedInletAirCsvManager = CSVManager(INLET_AIR_VERIFY_FILE, (zeroColumns).data(), 2);
        m_numVerifiedAirVals = m_verifiedInletAirCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified Air values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numVerifiedAirVals; index++)
    {
        std::vector<std::string> tmp = m_verifiedInletAirCsvManager.readRecord(index);
        if(tmp.size() != 2)
        {
            m_verified_air_timestamps[index] = QString::fromStdString("");
            m_verifiedAirVals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_air_timestamps[index] = QString::fromStdString(tmp[0]);
            m_verifiedAirVals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_air_timestamps[index] = QString::fromStdString("");
            m_verifiedAirVals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_verified_air_timestamps[index] = QString::fromStdString("");
        m_verifiedAirVals[index] = -1;
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
    QRegExp regularExpression(QString::fromStdString(R"(-?\d+(?:\.\d+)?)"));

    m_numVerifiedO2Vals = m_verifiedInletO2CsvManager.getNumEntries();

    if (m_numVerifiedO2Vals > MAX_ZERO_VALS)
    {
        system("rm /media/NVENT_FILES/calibration/pip_verify.csv");
        m_verifiedInletO2CsvManager = CSVManager(INLET_O2_VERIFY_FILE, (zeroColumns).data(), 2);
        m_numVerifiedO2Vals = m_verifiedInletO2CsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified O2 values reset do to corruption.";
    }

    int index = 0;
    for (; index < m_numVerifiedO2Vals; index++)
    {
        std::vector<std::string> tmp = m_verifiedInletO2CsvManager.readRecord(index);
        if(tmp.size() != 2)
        {
            m_verified_o2_timestamps[index] = QString::fromStdString("");
            m_verifiedO2Vals[index] = -1;
            break;
        }
        if (regularExpression.exactMatch(QString::fromStdString(tmp[1]))) {
            m_verified_o2_timestamps[index] = QString::fromStdString(tmp[0]);
            m_verifiedO2Vals[index] = QString::fromStdString(tmp[1]).toFloat();
        }
        else {
            m_verified_o2_timestamps[index] = QString::fromStdString("");
            m_verifiedO2Vals[index] = -1;
        }
    }

    for(; index < MAX_ZERO_VALS; index++)
    {
        m_verified_o2_timestamps[index] = QString::fromStdString("");
        m_verifiedO2Vals[index] = -1;
    }
}

void ZeroManager::addZeroValue(int sensor_id, float value)
{
    if (sensor_id == 0)
    {
        //Deletes oldest PIP value if at MAX_ZERO_VALS entry limit.
        if (m_numPipVals >= MAX_ZERO_VALS)
        {
            deleteOldestPipVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_pipCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "PIP Value: " + QString::number(value);
    }
    else if (sensor_id == 1)
    {
        //Deletes oldest SP value if at MAX_ZERO_VALS entry limit.
        if (m_numSpVals >= MAX_ZERO_VALS)
        {
            deleteOldestSpVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_spCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "SP Value: " + QString::number(value);
    }
    else if (sensor_id == 3)
    {
        //Deletes oldest Inlet Air value if at MAX_ZERO_VALS entry limit.
        if (m_numAirVals >= MAX_ZERO_VALS)
        {
            deleteOldestInletAirVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_airCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet Air Value: " + QString::number(value);
    }
    else if (sensor_id == 4)
    {
        //Deletes oldest Inlet O2 value if at MAX_ZERO_VALS entry limit.
        if (m_numO2Vals >= MAX_ZERO_VALS)
        {
            deleteOldestInletO2Val();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_o2CsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Inlet O2 Value: " + QString::number(value);
    }
    updateZeroVals();
}

void ZeroManager::addVerifiedValue(int sensor_id, float value)
{
    if (sensor_id == 0)
    {
        //Deletes oldest PIP value if at MAX_ZERO_VALS entry limit.
        if (m_numVerifiedPipVals >= MAX_ZERO_VALS)
        {
            deleteOldestVerifiedPipVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedPipCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified PIP Value: " + QString::number(value);
    }
    else if (sensor_id == 1)
    {
        //Deletes oldest SP value if at MAX_ZERO_VALS entry limit.
        if (m_numVerifiedSpVals >= MAX_ZERO_VALS)
        {
            deleteOldestVerifiedSpVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedSpCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified SP Value: " + QString::number(value);
    }
    else if (sensor_id == 3)
    {
        //Deletes oldest Inlet Air value if at MAX_ZERO_VALS entry limit.
        if (m_numVerifiedAirVals >= MAX_ZERO_VALS)
        {
            deleteOldestVerifiedInletAirVal();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedInletAirCsvManager.createRecord(vector.data());
        qInfo() << "NVENT" << "," << "PRESSURE SENSOR CALIBRATION" << "," << "Verified Inlet Air Value: " + QString::number(value);
    }
    else if (sensor_id == 4)
    {
        //Deletes oldest Inlet O2 value if at MAX_ZERO_VALS entry limit.
        if (m_numVerifiedO2Vals >= MAX_ZERO_VALS)
        {
            deleteOldestVerifiedInletO2Val();
        }

        std::string timeStamp = m_timeCsvManager.readRecord(0).at(1) + " - " + m_timeCsvManager.readRecord(1).at(1);
        std::vector<std::string> vector = {timeStamp, std::to_string(value)};

        m_verifiedInletO2CsvManager.createRecord(vector.data());
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
