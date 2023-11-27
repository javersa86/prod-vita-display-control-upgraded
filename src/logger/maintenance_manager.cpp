#include "maintenance_manager.h"

MaintenanceManager::MaintenanceManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> timeColumns = {"TYPE", "TIME"};
    m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", &timeColumns[0],2);

    std::vector<std::string> tColumns = {"TYPE", "DATES"};
    m_maintenanceCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(MAINTENANCE_FILE), &tColumns[0], 2);

    updateServiceDates();

//    m_timer = new QTimer(this);
//    m_timer->setInterval(1000);
//    m_timer->setSingleShot(false);
//    connect(m_timer, &QTimer::timeout, this, &MaintenanceManager::raiseAlarm);
}

void MaintenanceManager::updateServiceDates()
{
    if (m_maintenanceCsvManager.getNumEntries() == 0 || m_maintenanceCsvManager.getNumEntries() > 2)
    {
        system("rm /run/media/mmcblk0p2/home/ubuntu/maintenance.csv");

        std::vector<std::string> tColumns = {"TYPE", "DATES"};
        m_maintenanceCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(MAINTENANCE_FILE), &tColumns[0], 2);

        std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
        QString date_time_string = QString::fromStdString(date_time_row.at(1));
        QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

        QDate temp0 = dateTimeStamp.date();
        QDate temp1 = temp0.addMonths(12);

        m_last_date = temp0.toString(QString::fromStdString("MM/dd/yyyy"));
        m_next_date = temp1.toString(QString::fromStdString("MM/dd/yyyy"));

        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};

        m_maintenanceCsvManager.createRecord(&vector1[0]);
        m_maintenanceCsvManager.createRecord(&vector2[0]);

        Q_EMIT dateChanged();

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
    else {
        m_last_date = dateTimeStamp.date().toString(QString::fromStdString("MM/dd/yyyy"));
        std::vector<std::string> vector1 = {LAST_DATE,m_last_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(0,&vector1[0]);
    }
    if (next_service_row.size() == 2)
    {
        m_next_date = QString::fromStdString(next_service_row.at(1));
    }
    else {
        m_next_date = dateTimeStamp.date().addMonths(12).toString(QString::fromStdString("MM/dd/yyyy"));
        std::vector<std::string> vector2 = {NEXT_DATE,m_next_date.toStdString()};
        m_maintenanceCsvManager.updateRecord(1,&vector2[0]);
    }

    Q_EMIT dateChanged();
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
    std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
    QString date_time_string = QString::fromStdString(date_time_row.at(1));
    QDateTime dateTimeStamp = QDateTime::fromString(date_time_string, QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"));

    //QDate dateStamp = QDate::currentDate();
    return dateTimeStamp.date().toString(QString::fromStdString("MM/dd/yyyy"));
}

QString MaintenanceManager::updateNextTwelveMonthDate()
{
    QDate temp0 = QDate::fromString(m_last_date,QString::fromStdString("MM/dd/yyyy"));
    QDate temp1 = temp0.addMonths(12);
    return temp1.toString(QString::fromStdString("MM")) + QString::fromStdString("/01/") + temp1.toString(QString::fromStdString("yyyy"));
}

void MaintenanceManager::setLastServiceDate(const QString &newDate)
{
    std::vector<std::string> vector = {LAST_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(0,&vector[0]);

    qInfo() << "NVENT" << "," << "MAINTENANCE" << "," << "Updated last service date from " + m_last_date + " to " + newDate + ".";
    updateServiceDates();
}

void MaintenanceManager::setNextServiceDate(const QString &newDate)
{
    std::vector<std::string> vector = {NEXT_DATE,newDate.toStdString()};
    m_maintenanceCsvManager.updateRecord(1,&vector[0]);

    qInfo() << "NVENT" << "," << "MAINTENANCE" << "," << "Updated next service date from " + m_next_date + " to " + newDate + ".";
    updateServiceDates();

    //m_timer_count = 0;
    raiseAlarm();
}

void MaintenanceManager::isValid(const QString &month, const QString &day, const QString &year)
{

    Q_EMIT validation(
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

    //QDate dateStamp = QDate::currentDate();
    QDate dateStamp = dateTimeStamp.date();
    QDate next_data = QDate::fromString(m_next_date, QString::fromStdString("MM/dd/yyyy"));

    qint64 tmp = dateStamp.daysTo(next_data);

    if (tmp <= 0)
    {
        if (!m_alarm_state) {
            m_alarm_state = 1;
            Q_EMIT alarmSignal(m_alarm_state);
        }
    }
    else if (tmp > 0)
    {
        if (m_alarm_state) {
            m_alarm_state = 0;
            Q_EMIT alarmSignal(m_alarm_state);
        }
    }
}

void MaintenanceManager::startTimer()
{
    //m_timer->start();
    raiseAlarm();
}
