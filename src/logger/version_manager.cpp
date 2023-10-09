#include "version_manager.h"

VersionManager::VersionManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> tColumns = {"VERSION","NUMBER"};

    m_versionCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(VERSION_FILE), &tColumns[0], 2);
    updateVersions();
}

void VersionManager::updateVersions()
{
    if (m_versionCsvManager.getNumEntries() == 0)
    {
        m_hmiVersion = "v2.0.0";
        m_serialNumber = "LTN0001";

        std::vector<std::string> vector1 = {HMI,m_hmiVersion.toStdString()};
        std::vector<std::string> vector2 = {SERIAL_NUMBER,m_serialNumber.toStdString()};

        m_versionCsvManager.createRecord(&vector1[0]);
        m_versionCsvManager.createRecord(&vector2[0]);

        emit versionChanged();
        return;
    }

    m_hmiVersion = QString::fromStdString(m_versionCsvManager.readRecord(0).at(1));
    m_serialNumber = QString::fromStdString(m_versionCsvManager.readRecord(1).at(1));

    emit versionChanged();
}

QString VersionManager::getHmiVersion()
{
    return m_hmiVersion;
}

QString VersionManager::getSerialNumber()
{
    return m_serialNumber;
}

void VersionManager::logVersions()
{
    qInfo() << "NVENT" << "," << "HMI VERSION" << "," << m_hmiVersion;
    qInfo() << "NVENT" << "," << "SERIAL NUMBER" << "," << m_serialNumber;
}

void VersionManager::updateSerialNumber(QString serial)
{
    std::vector<std::string> vector2 = {SERIAL_NUMBER,serial.toStdString()};
    m_versionCsvManager.updateRecord(1,&vector2[0]);

    updateVersions();

}
