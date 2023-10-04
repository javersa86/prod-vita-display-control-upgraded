#include "maintenance_manager.h"

MaintenanceManager::MaintenanceManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> tColumns = {"TYPE", "DATES"};
    m_maintenanceCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(MAINTENANCE_FILE), &tColumns[0], 2);

    updateServiceDates();
}

void MaintenanceManager::updateServiceDates()
{
    if (m_maintenanceCsvManager.getNumEntries() == 0)
    {
        QDate temp0 = QDate::currentDate();
        QDate temp1 = temp0.addMonths(12);

        m_last_date = temp0.toString("MM/dd/yyyy");
        m_next_date = temp1.toString("MM/dd/yyyy");

        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};

        m_maintenanceCsvManager.createRecord(&vector1[0]);
        m_maintenanceCsvManager.createRecord(&vector2[0]);

        emit dateChanged();

        return;
    }

    std::vector<std::string> last_service_row = m_maintenanceCsvManager.readRecord(0);
    std::vector<std::string> next_service_row = m_maintenanceCsvManager.readRecord(1);

    if (last_service_row.size() == 2)
    {
        m_last_date = QString::fromStdString(last_service_row.at(1));
    }
    else {
        m_last_date = QDate::currentDate().toString("MM/dd/yyyy");
        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(0,&vector1[0]);
    }
    if (next_service_row.size() == 2)
    {
        m_next_date = QString::fromStdString(next_service_row.at(1));
    }
    else {
        m_next_date = QDate::currentDate().addMonths(12).toString("MM/dd/yyyy");
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(1,&vector2[0]);
    }

    emit dateChanged();
}

QString MaintenanceManager::getLastServiceDate()
{
    return m_last_date;
}

QString MaintenanceManager::getNextServiceDate()
{
    return m_next_date;
}

QString MaintenanceManager::updateLastTodayDate()
{
    return QDate::currentDate().toString("MM/dd/yyyy");
}

QString MaintenanceManager::updateNextTwelveMonthDate()
{
    QDate temp0 = QDate::fromString(m_last_date,"MM/dd/yyyy");
    QDate temp1 = temp0.addMonths(12);
    return temp1.toString("MM") + "/01/" + temp1.toString("yyyy");
}

void MaintenanceManager::setLastServiceDate(QString newDate)
{
    std::vector<std::string> vector = {LAST_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(0,&vector[0]);

    qInfo() << "NVENT" << "," << "MAINTENANCE" << "," << "Updated last service date from " + m_last_date + " to " + newDate + ".";
    updateServiceDates();
}

void MaintenanceManager::setNextServiceDate(QString newDate)
{
    std::vector<std::string> vector = {NEXT_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(1,&vector[0]);

    qInfo() << "NVENT" << "," << "MAINTENANCE" << "," << "Updated next service date from " + m_next_date + " to " + newDate + ".";
    updateServiceDates();
}

void MaintenanceManager::isValid(QString month, QString day, QString year)
{

    emit validation(QDate::fromString(month + "/" + day + "/" + year, "MM/dd/yyyy").isValid());
}
