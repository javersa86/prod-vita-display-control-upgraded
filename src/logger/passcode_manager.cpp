/**
 * @author Joseph Aversa
 * @name passcode_manager
 * @date 03/17/2022
 *
 * The service page and the presets page require passcodes to make significant changes to the device.
 * Program will allow access to passcodes from QML files.
 * Passwords are stored onto a .csv file.
 * The user will have the ability to change passcodes through the service page and settings page.
 */

#include "passcode_manager.h"
#include "csv_manager.h"

PasscodeManager::PasscodeManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> pcColumns(2);
    pcColumns[0] = "ROOT";
    pcColumns[1] = "PASSCODE";

    //Creates new passcode csv files if one wasn't created already.
    m_passcodeCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PASSCODE_FILE), &pcColumns[0],2);

    updatePasscode();
}

void PasscodeManager::updatePasscode()
{
    if (m_passcodeCsvManager.getNumEntries() > 2)
    {
        system("rm /media/NVENT_FILES/passcodes.csv");
        std::vector<std::string> pcColumns(2);
        pcColumns[0] = "ROOT";
        pcColumns[1] = "PASSCODE";
        m_passcodeCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PASSCODE_FILE), &pcColumns[0],2);
        
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Pass Code Manager reset do to corruption.";
    }
    //If newly created passcode file has no rows for preset passcode and service passcode,
    //system will store variables with default passcode values.
    //Also, it will record default passcodes onto .csv file.
    if (m_passcodeCsvManager.getNumEntries() == 0)
    {
        m_service_passcode = "0000";
        m_preset_passcode = "0000";

        std::vector<std::string> vector1 = {"SERVICE",m_service_passcode.toStdString()};
        std::vector<std::string> vector2 = {"PRESET",m_preset_passcode.toStdString()};

        m_passcodeCsvManager.createRecord(&vector1[0]);
        m_passcodeCsvManager.createRecord(&vector2[0]);

        emit passcodeChanged();

        return;
    }
    std::vector<std::string> service_row = m_passcodeCsvManager.readRecord(0);
    std::vector<std::string> preset_row = m_passcodeCsvManager.readRecord(1);

    QRegExp re("\\d{4}$");
    if (service_row.size() == 2 && re.exactMatch(QString::fromStdString(service_row.at(1))))
    {
        m_service_passcode = QString::fromStdString(service_row.at(1));
    }
    else
    {
        m_service_passcode = "0000";
        std::vector<std::string> vector1 = {"SERVICE",m_service_passcode.toStdString()};
        m_passcodeCsvManager.updateRecord(0,&vector1[0]);
    }
    if (preset_row.size() == 2  && re.exactMatch(QString::fromStdString(preset_row.at(1))))
    {
        m_preset_passcode = QString::fromStdString(preset_row.at(1));
    }
    else
    {
        m_preset_passcode = "0000";
        std::vector<std::string> vector2 = {"PRESET",m_preset_passcode.toStdString()};
        m_passcodeCsvManager.updateRecord(1,&vector2[0]);
    }

    emit passcodeChanged();
}

void PasscodeManager::editServicePasscode(QString newPasscode)
{
    //System will not change new passcode if old one was entered.
    if (newPasscode == m_service_passcode)
    {
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Previous passcode was entered.";
        m_signal_change_value = 1;
        return;
    }
    //Passcode is required to be 4 digits.
    else if (newPasscode.size() < 4 || 4 < newPasscode.size())
    {
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Passcode length is incorrect.";
        m_signal_change_value = 2;
        return;
    }
    //Records new passcode onto .csv file.
    std::vector<std::string> service_row = {"SERVICE",newPasscode.toStdString()};
    m_passcodeCsvManager.updateRecord(0, &service_row[0]);
    m_signal_change_value = 0;

    //Records log entry for passcode change.
    qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Service passcode has changed.";

    updatePasscode();
}

void PasscodeManager::editPresetPasscode(QString newPasscode)
{
    //System will not change new passcode if old one was entered.
    if (newPasscode == m_preset_passcode)
    {
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Previous passcode was entered.";
        m_signal_change_value = 1;
        return;
    }
    //Passcode is required to be 4 digits.
    else if (newPasscode.size() < 4 || 4 < newPasscode.size())
    {
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Passcode length is incorrect.";
        m_signal_change_value = 2;
        return;
    }
    //Records new passcode onto .csv file.
    std::vector<std::string> preset_row = {"PRESET",newPasscode.toStdString()};
    m_passcodeCsvManager.updateRecord(1, &preset_row[0]);
    m_signal_change_value = 0;

    //Records log entry for passcode change.
    qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Preset passcode has changed.";
    updatePasscode();
}

void PasscodeManager::editPresetPasscodeManual(QString newPasscode)
{
    //Passcode still needs to be 4 digits.
    if (newPasscode.size() < 4 || 4 < newPasscode.size())
    {
        qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Passcode length is incorrect.";
        m_signal_change_value = 2;
        return;
    }
    //Records new passcode onto .csv file.
    std::vector<std::string> preset_row = {"PRESET",newPasscode.toStdString()};
    m_passcodeCsvManager.updateRecord(1, &preset_row[0]);
    m_signal_change_value = 0;

    //Records log entry for passcode change.
    qInfo() << "NVENT" << "," << "PASSCODE" << "," << "Preset passcode has changed forcefully by technician.";
    updatePasscode();
}

QString PasscodeManager::getServicePasscode()
{
    return m_service_passcode;
}

QString PasscodeManager::getPresetPasscode()
{
    return m_preset_passcode;
}

int PasscodeManager::getChangedValue()
{
    return m_signal_change_value;
}

QString PasscodeManager::getPresetPasscodeManual()
{
    return m_preset_passcode;
}
