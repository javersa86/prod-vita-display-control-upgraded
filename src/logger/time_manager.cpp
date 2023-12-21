#include "time_manager.h"

/**
 * @author Joseph Aversa
 * @name time_manager
 * @date 05/19/2022
 *
 * Program allows technician to change current date, time, and time zone.
 * Values are saved on .csv file.
 */

TimeManager::TimeManager(QObject *parent) :
    QObject(parent), m_increment_time(new QTimer(this))
{
    std::vector<std::string> tColumns = {"TYPE             ", "TIME"};
    m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(TIME_FILE), tColumns.data(), 2);

    updateTime();

    //Backend timer the increments the current date and time per second.
    m_increment_time->setInterval(TIMER_INTERVAL_ONE_SECOND);
    m_increment_time->setSingleShot(false);
    connect(m_increment_time, &QTimer::timeout, this, &TimeManager::setTime);
    m_increment_time->start();
}

void TimeManager::updateTime()
{
    if (m_timeCsvManager.getNumEntries() == 0)
    {
        system("rm /run/media/mmcblk0p2/home/ubuntu/time.csv");
        std::vector<std::string> tColumns = {"TYPE             ", "TIME"};
        m_timeCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(TIME_FILE), tColumns.data(), 2);

        m_time_zone = QString::fromStdString("EDT");
        m_current_date_time = QDateTime::currentDateTime().addSecs(timeZoneValues.at(m_time_zone) * MINUTE_TO_MILLISECECONDS);
        m_internal = QDateTime::currentDateTime().addSecs(timeZoneValues.at(m_time_zone) * MINUTE_TO_MILLISECECONDS);

        m_temp_date = m_current_date_time.date();
        m_temp_time = m_current_date_time.time();
        getTimeZoneDifference(m_time_zone,m_time_zone);

        m_daylight_savings_state = 1;

        std::vector<std::string> vector1 = {DATE_TIME, m_current_date_time.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()};
        std::vector<std::string> vector2 = {TIME_ZONE, m_time_zone.toStdString()};
        std::vector<std::string> vector3 = {INTERNAL, m_internal.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()};
        std::vector<std::string> vector4 = {DAYLIGHT_SAVINGS, std::to_string(m_daylight_savings_state)};

        m_timeCsvManager.createRecord(vector1.data());
        m_timeCsvManager.createRecord(vector2.data());
        m_timeCsvManager.createRecord(vector3.data());
        m_timeCsvManager.createRecord(vector4.data());

        emit timeChanged();
        return;
    }
    std::vector<std::string> date_time_row = m_timeCsvManager.readRecord(0);
    std::vector<std::string> time_zone_row = m_timeCsvManager.readRecord(1);
    std::vector<std::string> internal_row = m_timeCsvManager.readRecord(2);
    std::vector<std::string> daylight_row = m_timeCsvManager.readRecord(3);

    if (time_zone_row.size() == 2)
    {
        m_time_zone = QString::fromStdString(time_zone_row.at(1));
    }
    else
    {
        m_time_zone = QString::fromStdString("EST");
    }

    if (date_time_row.size() == 2 && internal_row.size() == 2)
    {
        m_current_date_time = QDateTime::fromString(
                    QString::fromStdString(date_time_row.at(1)),
                    QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"))
                .addMSecs(getTimeDifference(QString::fromStdString(internal_row.at(1))));
    }
    else
    {
        m_current_date_time = QDateTime::currentDateTime().addSecs(timeZoneValues.at(m_time_zone) * MINUTE_TO_MILLISECECONDS);
    }
    m_internal = QDateTime::currentDateTime().addSecs(timeZoneValues.at(m_time_zone) * MINUTE_TO_MILLISECECONDS);

    m_daylight_savings_state = QString::fromStdString(daylight_row.at(1)).toInt();

    m_temp_date = m_current_date_time.date();
    m_temp_time = m_current_date_time.time();
    getTimeZoneDifference(m_time_zone,m_time_zone);

    std::vector<std::string> vector1 = {DATE_TIME, m_current_date_time.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()};
    m_timeCsvManager.updateRecord(0,vector1.data());
    std::vector<std::string> vector2 = {TIME_ZONE, m_time_zone.toStdString()};
    m_timeCsvManager.updateRecord(1,vector2.data());
    std::vector<std::string> vector3 = {INTERNAL, m_internal.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()};
    m_timeCsvManager.updateRecord(2,vector3.data());
    std::vector<std::string> vector4 = {DAYLIGHT_SAVINGS, std::to_string(m_daylight_savings_state)};
    m_timeCsvManager.updateRecord(3,vector4.data());

    emit timeChanged();
}

QString TimeManager::getCurrentDateTime()
{
    return m_current_date_time.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")) + " - " + m_time_zone;
}

void TimeManager::setCurrentDate(const QString &temp)
{
    m_temp_date = QDate::fromString(temp, QString::fromStdString("MM/dd/yyyy"));
    m_date_state = 1;
    qInfo() << "NVENT"
            << ","
            << "TIME"
            << ","
            << "Updated current date to " +
               m_temp_date.toString(QString::fromStdString("MM/dd/yyyy")) +
               ".";
}

void TimeManager::setCurrentTime(const QString &hours, const QString &minutes, const QString &shift)
{
    QString temp = hours + ":" + minutes + ":" + QString::number(m_current_date_time.time().second()) + " " + shift;
    m_temp_time = QTime::fromString(temp, QString::fromStdString("hh:mm:ss AP"));
    m_time_state = 1;
    qInfo() << "NVENT"
            << ","
            << "TIME"
            << ","
            << "Updated current time to " +
               m_temp_time.toString(QString::fromStdString("hh:mm:ss AP")) +
               ".";
}

void TimeManager::setTimeZone(const QString &temp)
{
    getTimeZoneDifference(m_time_zone,temp);
    m_time_zone = temp;
    std::vector<std::string> vector = {TIME_ZONE,m_time_zone.toStdString()};
    m_timeCsvManager.updateRecord(1,vector.data());
    m_time_zone_state = 1;

    qInfo() << "NVENT" << "," << "TIME" << "," << "Updated time zone to " + m_time_zone + ".";
}

void TimeManager::setTime()
{
    //When user updates date, it will be saved at next increment.
    if (m_date_state == 1)
    {
        m_current_date_time.setDate(m_temp_date);
        m_date_state = 0;
    }
    //When user updates time, it will be saved at next increment.
    if (m_time_state == 1)
    {
        m_current_date_time.setTime(m_temp_time);
        m_time_state = 0;
    }
    if (m_time_zone_state == 1)
    {
        m_current_date_time = m_current_date_time.addSecs(m_temp_time_zone * MINUTE_TO_MILLISECECONDS);
        m_internal = m_internal.addSecs(m_temp_time_zone * MINUTE_TO_MILLISECECONDS);
        m_time_zone_state = 0;
    }
    m_current_date_time = m_current_date_time.addSecs(1);
    m_internal = m_internal.addSecs(1);

    std::vector<std::string> vector = {
        DATE_TIME,
        m_current_date_time.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()
    };
    m_timeCsvManager.updateRecord(0,vector.data());

    std::vector<std::string> vector1 = {
        INTERNAL,
        m_internal.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")).toStdString()
    };
    m_timeCsvManager.updateRecord(2,vector1.data());

    emit timeChanged();
}

qint64 TimeManager::getTimeDifference(const QString &temp)
{
    return QDateTime::fromString(
                temp,
                QString::fromStdString("MM/dd/yyyy hh:mm:ss AP")
                ).msecsTo(QDateTime::currentDateTime().addSecs(timeZoneValues.at(m_time_zone) * MINUTE_TO_MILLISECECONDS));
}

void TimeManager::getTimeZoneDifference(const QString &oldZone, const QString &newZone){
    m_temp_time_zone = -1 * (timeZoneValues.at(oldZone) - timeZoneValues.at(newZone));
}

unsigned char TimeManager::getDaylightSavings() const
{
    return m_daylight_savings_state;
}

void TimeManager::updateDaylightSavings()
{
    m_daylight_savings_state = static_cast<unsigned char>(m_daylight_savings_state == 0);
    std::vector<std::string> vector4 = {DAYLIGHT_SAVINGS, std::to_string(m_daylight_savings_state)};
    m_timeCsvManager.updateRecord(3, vector4.data());
    emit daylightChanged();

    if (m_daylight_savings_state == 1)
    {
        auto iterator = std::find(standardTimeZones.begin(),
                                  standardTimeZones.end(),
                                  m_time_zone.toStdString());
        if (iterator != standardTimeZones.end())
        {
            setTimeZone(
                        QString::fromStdString(
                            daylightSavingsTimeZones.at(
                                std::distance(
                                    standardTimeZones.begin(),
                                    iterator
                                    )
                                )
                            )
                        );
        }
    }
    else
    {
        auto iterator = std::find(daylightSavingsTimeZones.begin(),
                            daylightSavingsTimeZones.end(),
                            m_time_zone.toStdString());
        if (iterator != daylightSavingsTimeZones.end())
        {
            setTimeZone(
                        QString::fromStdString(
                            standardTimeZones.at(
                                std::distance(
                                    daylightSavingsTimeZones.begin(),
                                    iterator
                                    )
                                )
                            )
                        );
        }
    }
}

void TimeManager::updateDalyightSavingsForced(unsigned char value)
{
    m_daylight_savings_state = value;
    std::vector<std::string> vector4 = {DAYLIGHT_SAVINGS, std::to_string(m_daylight_savings_state)};
    m_timeCsvManager.updateRecord(3,vector4.data());
    emit daylightChanged();
}
