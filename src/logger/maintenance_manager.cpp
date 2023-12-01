#include "maintenance_manager.h"

MaintenanceManager::MaintenanceManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> timeColumns = {"TYPE", "TIME"};
    m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", timeColumns.data(),2);

    std::vector<std::string> tColumns = {"TYPE", "DATES"};
    m_maintenanceCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(MAINTENANCE_FILE), tColumns.data(), 2);

    updateServiceDates();
}

void MaintenanceManager::updateServiceDates()
{
    if (m_maintenanceCsvManager.getNumEntries() == 0 || m_maintenanceCsvManager.getNumEntries() > 2)
    {
        system("rm /run/media/mmcblk0p2/home/ubuntu/maintenance.csv");

        std::vector<std::string> tColumns = {"TYPE", "DATES"};
        m_maintenanceCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(MAINTENANCE_FILE), tColumns.data(), 2);

        std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
        QString date_time_string = QString::fromStdString(date_time_row.at(1));
        QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

        QDate temp0 = dateTimeStamp.date();
        QDate temp1 = temp0.addMonths(TWELVE_MONTHS);

        m_last_date = temp0.toString(QString::fromStdString("MM/dd/yyyy"));
        m_next_date = temp1.toString(QString::fromStdString("MM/dd/yyyy"));

        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};

        m_maintenanceCsvManager.createRecord(vector1.data());
        m_maintenanceCsvManager.createRecord(vector2.data());

        emit dateChanged();

        return;
    }

    std::vector<std::string> last_service_row = m_maintenanceCsvManager.readRecord(0);
    std::vector<std::string> next_service_row = m_maintenanceCsvManager.readRecord(1);

    std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
    QString date_time_string = QString::fromStdString(date_time_row.at(1));
    QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

    if (last_service_row.size() == 2)
    {
        m_last_date = QString::fromStdString(last_service_row.at(1));
    }
    else
    {
        m_last_date = dateTimeStamp.date().toString(QString::fromStdString("MM/dd/yyyy"));
        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(0,vector1.data());
    }

    if (next_service_row.size() == 2)
    {
        m_next_date = QString::fromStdString(next_service_row.at(1));
    }
    else
    {
        m_next_date = dateTimeStamp.date().addMonths(TWELVE_MONTHS).toString(QString::fromStdString("MM/dd/yyyy"));
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(1, vector2.data());
    }

    emit dateChanged();
}

auto MaintenanceManager::getLastServiceDate() -> QString
{
    return m_last_date;
}

auto MaintenanceManager::getNextServiceDate() -> QString
{
    return m_next_date;
}

auto MaintenanceManager::updateLastTodayDate() -> QString
{
    std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
    QString date_time_string = QString::fromStdString(date_time_row.at(1));
    QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

    return dateTimeStamp.date().toString(QString::fromStdString("MM/dd/yyyy"));
}

auto MaintenanceManager::updateNextTwelveMonthDate() -> QString
{
    QDate temp0 = QDate::fromString(m_last_date,QString::fromStdString("MM/dd/yyyy"));
    QDate temp1 = temp0.addMonths(TWELVE_MONTHS);
    return temp1.toString(QString::fromStdString("MM")) +
            QString::fromStdString("/01/") +
            temp1.toString(QString::fromStdString("yyyy"));
}

void MaintenanceManager::setLastServiceDate(const QString &newDate)
{
    std::vector<std::string> vector = {LAST_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(0,vector.data());

    qInfo() << "NVENT"
            << ","
            << "MAINTENANCE"
            << ","
            << "Updated last service date from " +
               m_last_date +
               " to " +
               newDate +
               ".";

    updateServiceDates();
}

void MaintenanceManager::setNextServiceDate(const QString &newDate)
{
    std::vector<std::string> vector = {NEXT_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(1,vector.data());

    qInfo() << "NVENT"
            << ","
            << "MAINTENANCE"
            << ","
            << "Updated next service date from " +
               m_next_date +
               " to " +
               newDate +
               ".";

    updateServiceDates();

    raiseAlarm();
}

void MaintenanceManager::isValid(const QString &month, const QString &day, const QString &year)
{

    emit validation(
                QDate::fromString(
                    month +
                    QString::fromStdString("/") +
                    day +
                    QString::fromStdString("/") +
                    year,
                    QString::fromStdString("MM/dd/yyyy")
                    )
                .isValid());
}

void MaintenanceManager::raiseAlarm()
{
    std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
    QString date_time_string = QString::fromStdString(date_time_row.at(1));
    QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

    QDate dateStamp = dateTimeStamp.date();
    QDate next_data = QDate::fromString(m_next_date, QString::fromStdString("MM/dd/yyyy"));

    qint64 tmp = dateStamp.daysTo(next_data);

    if (tmp <= 0)
    {
        if (m_alarm_state == 0)
        {
            m_alarm_state = 1;
            emit alarmSignal(m_alarm_state);
        }
    }
    else if (tmp > 0)
    {
        if (m_alarm_state == 1)
        {
            m_alarm_state = 0;
            emit alarmSignal(m_alarm_state);
        }
    }
}

void MaintenanceManager::startTimer()
{
    raiseAlarm();
}
