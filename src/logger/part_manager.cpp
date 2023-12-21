#include "part_manager.h"
#include "csv_manager.h"

PartManager::PartManager(QObject *parent) :
    QObject(parent), m_hours_operating_timer(new QTimer(this)), m_hours_ventilating_timer(new QTimer(this))
{
    //Constructs CSV file and variables for part names, serial numbers, and date installations.
    std::vector<std::string> columns(PART_DATA);
    for(int i = 0; i < PART_DATA; i++)
    {
        columns[i] = partNameMap.at(i);
    }
    m_partCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PART_FILE), columns.data(), PART_DATA);
    updatePart();

    //Constructs CSV file and variables for hours of operations.
    std::vector<std::string> columns1 = {"Part", "Hours Operating"};
    m_hoursOperatingCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(PART_OPERATING_FILE), columns1.data(), 2);
    updateHoursOperating();

    //Constructs CSV file and variables for hours of ventilation.
    std::vector<std::string> columns2 = {"Part", "Hours Ventilating"};
    m_hoursVentilatingCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(PART_VENTILATING_FILE), columns2.data(), 2);
    updateHoursVentilating();

    constexpr int INTERVAL_ONE_SECOND = 1000;

    //Timer that increments the hours of operation for parts per second.
    m_hours_operating_timer->setInterval(INTERVAL_ONE_SECOND);
    m_hours_operating_timer->setSingleShot(false);
    connect(m_hours_operating_timer, &QTimer::timeout, this, &PartManager::incrementHoursOperating);
    m_hours_operating_timer->start();

    //Timer that increments the hours of ventilation for parts per second.
    m_hours_ventilating_timer->setInterval(INTERVAL_ONE_SECOND);
    m_hours_ventilating_timer->setSingleShot(false);
    connect(m_hours_ventilating_timer, &QTimer::timeout, this, &PartManager::incrementHoursVentilating);
    m_hours_ventilating_timer->start();
}

void PartManager::updatePart()
{
    if (m_partCsvManager.getNumEntries() != NUMBER_OF_PARTS)
    {
        if (m_partCsvManager.getNumEntries() == 0)
        {
            createComponents();
        }
        else
        {
            system("rm /media/NVENT_FILES/components.csv");
            std::vector<std::string> columns(PART_DATA);
            for(int i = 0; i < PART_DATA; i++)
            {
                columns[i] = partNameMap.at(i);
            }
            m_partCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PART_FILE), columns.data(), PART_DATA);
            createComponents();
            qInfo() << "NVENT" << "," << "COMPONENTS" << "," << "Components Manager reset do to corruption.";
        }
    }
    std::vector<std::string> row = m_partCsvManager.readRecord(m_row_index);
    if (row.empty())
    {
        m_partName = QString::fromStdString("");
        m_partNumber = QString::fromStdString("");
        m_partDateTime = QString::fromStdString("");
        emit partChanged();
        return;
    }
    m_partName = QString::fromStdString(row.at(0));
    m_partNumber = QString::fromStdString(row.at(1));
    m_partDateTime = QString::fromStdString(row.at(2));
    emit partChanged();
}

void PartManager::createComponents()
{
    QDateTime temp = QDateTime::currentDateTime();
    for (int i = 0; i < NUMBER_OF_PARTS; i++)
    {
        std::vector<std::string> vector = {
            componentNameMap.at(i),
            "N/A",
            temp.toString(QString::fromStdString("MM/dd/yyyy hh:mm:ss")).toStdString()
        };
        m_partCsvManager.createRecord(vector.data());
    }
}

void PartManager::updateHoursOperating()
{
    if (m_hoursOperatingCsvManager.getNumEntries() != NUMBER_OF_PARTS)
    {
        if (m_hoursOperatingCsvManager.getNumEntries() == 0)
        {
            createHoursOperating();
        }
        else
        {
            system("rm /run/media/mmcblk0p2/home/ubuntu/components_operating.csv");
            std::vector<std::string> columns1 = {"Part", "Hours Operating"};
            m_hoursOperatingCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(PART_OPERATING_FILE), columns1.data(), 2);
            
            qInfo() << "NVENT" << "," << "COMPONENTS" << "," << "Components Manager Hours Operating reset do to corruption.";
        }
    }

    std::vector<std::string> row = m_hoursOperatingCsvManager.readRecord(m_row_index);

    if (row.empty())
    {
        m_hoursOperating = -1;
        emit partOpChanged();
        return;
    }
    m_hoursOperating = stoi(row.at(1));
    emit partOpChanged();
}

void PartManager::createHoursOperating()
{
    for (int i = 0; i < NUMBER_OF_PARTS; i++)
    {
        std::vector<std::string> vector = {componentNameMap.at(i), "0"};
        m_hoursOperatingCsvManager.createRecord(vector.data());
    }
}

void PartManager::incrementHoursOperating()
{
    for (int i = 0; i < NUMBER_OF_PARTS; i++)
    {
        std::vector<std::string> vector;
        if (i == m_temp_oper_index && m_reset_op == 1)
        {
            vector = {m_hoursOperatingCsvManager.readRecord(i).at(0),"0"};
            m_reset_op = 0;
            m_temp_oper_index = -1;
        }
        else
        {
            std::vector<std::string> row = m_hoursOperatingCsvManager.readRecord(i);
            int operating_count = std::stoi(row.at(1));
            vector = {row.at(0), std::to_string(operating_count + 1)};
        }
        m_hoursOperatingCsvManager.updateRecord(i, vector.data());
    }
    updateHoursOperating();
}

void PartManager::updateHoursVentilating()
{
    if (m_hoursVentilatingCsvManager.getNumEntries() != NUMBER_OF_PARTS)
    {
        if (m_hoursVentilatingCsvManager.getNumEntries() == 0)
        {
            createHoursVentilating();
        }
        else
        {
            system("rm /run/media/mmcblk0p2/home/ubuntu/components_ventilating.csv");
            std::vector<std::string> columns2 = {"Part", "Hours Ventilating"};
            m_hoursVentilatingCsvManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/" + std::string(PART_VENTILATING_FILE), columns2.data(), 2);
            
            qInfo() << "NVENT" << "," << "COMPONENTS" << "," << "Components Manager Hours Ventilating reset do to corruption.";
        }
    }

    std::vector<std::string> row = m_hoursVentilatingCsvManager.readRecord(m_row_index);

    if (row.empty())
    {
        m_hoursVentilating = -1;
        emit partVentChanged();
        return;
    }
    m_hoursVentilating = stoi(row.at(1));
    emit partVentChanged();
}

void PartManager::createHoursVentilating()
{
    for (int i = 0; i < NUMBER_OF_PARTS; i++)
    {
        std::vector<std::string> vector = {componentNameMap.at(i), "0"};
        m_hoursVentilatingCsvManager.createRecord(vector.data());
    }
}

void PartManager::incrementHoursVentilating()
{
    if (m_ventilation_state == 1)
    {
        for (int i = 0; i < NUMBER_OF_PARTS; i++)
        {
            std::vector<std::string> vector;
            if (i == m_temp_vent_index && m_reset_vent == 1)
            {
                vector = {m_hoursVentilatingCsvManager.readRecord(i).at(0),"0"};
                m_reset_vent = 0;
                m_temp_vent_index = -1;
            }
            else
            {
                std::vector<std::string> row = m_hoursVentilatingCsvManager.readRecord(i);
                int ventilating_count = std::stoi(row.at(1));
                vector = {row.at(0), std::to_string(ventilating_count + 1)};
            }
            m_hoursVentilatingCsvManager.updateRecord(i, vector.data());
        }
        updateHoursVentilating();
    }
}

void PartManager::setIndex(int index)
{
    m_row_index = index;
    updatePart();
    updateHoursOperating();
    updateHoursVentilating();
}

void PartManager::setVentilationState(unsigned char val)
{
    m_ventilation_state = val;
}

QString PartManager::getPartName()
{
    return m_partName;
}

QString PartManager::getPartNumber()
{
    return m_partNumber;
}

QString PartManager::getPartDateTime()
{
    return m_partDateTime;
}

int PartManager::getHoursOperating() const
{
    return m_hoursOperating;
}

int PartManager::getHoursVentilating() const
{
    return m_hoursVentilating;
}

int PartManager::getIndex() const
{
    return m_row_index;
}

void PartManager::setTempIndex(int index)
{
    m_temp_row_index = index;
}

void PartManager::setTempName(const QString &name)
{
    m_temp_name = name;
}

void PartManager::addDigit(const QString &input)
{
    m_temp_serial_number = m_temp_serial_number + input;
    emit serialChanged();
}

void PartManager::removeDigit()
{
    if (m_temp_serial_number.size() > 0)
    {
        m_temp_serial_number = m_temp_serial_number.left(m_temp_serial_number.size() - 1);
        emit serialChanged();
    }
}

void PartManager::setTempSerial(const QString &number)
{
    m_temp_serial_number = number;
}

QString PartManager::getSerialNumber()
{
    //If part number length is greater than 20, will return substring of serial number at length of 20.
    if (m_temp_serial_number.size() > PART_NUMBER_SIZE)
    {
        return m_temp_serial_number.mid(m_temp_serial_number.size() - PART_NUMBER_SIZE, PART_NUMBER_SIZE);
    }
    return m_temp_serial_number;
}

void PartManager::setTempDate(const QString &date)
{
    m_temp_date = date;
}

void PartManager::setNewPart(const QString &newTime)
{
    m_temp_date = m_temp_date +
            " " +
            QDateTime::fromString(
                newTime,
                QString::fromStdString("MM/dd/yyyy hh:mm:ss AP"))
            .toString(QString::fromStdString("hh:mm:ss AP"));

    //Updates serial number and installation date.
    std::vector<std::string> vector = {
        m_temp_name.toStdString(),
        m_temp_serial_number.toStdString(),
        m_temp_date.toStdString()
    };
    m_partCsvManager.updateRecord(m_temp_row_index, vector.data());
    updatePart();

    //Updates hours of operation by tracking index in hours timer.
    m_temp_oper_index = m_temp_row_index;
    m_reset_op = 1;

    //Updates hours of ventilation while ventilating by tracking index in hours timer.
    if (m_ventilation_state == 1)
    {
        m_temp_vent_index = m_temp_row_index;
        m_reset_vent = 1;
    }
    //Updates hours of ventilation while not ventilating.
    else
    {
        std::vector<std::string> vector1 = {m_temp_name.toStdString(),std::to_string(0)};
        m_hoursVentilatingCsvManager.updateRecord(m_temp_row_index, vector1.data());
        updateHoursVentilating();
    }

    //Updates index for part that was replaced.
    m_part_index = m_temp_row_index;

    qInfo() << "NVENT"
            << ","
            << "COMPONENTS"
            << ","
            << m_temp_name +
               " installed on " +
               m_temp_date +
               " with the following serial number: " +
               m_temp_serial_number +
               ".";

    m_temp_row_index = -1;
    m_temp_name = QString::fromStdString("");
    m_temp_serial_number = QString::fromStdString("");
    m_temp_date = QString::fromStdString("");
    emit serialChanged();
}

void PartManager::setPartIndex(char index)
{
    m_part_index = index;
}

char PartManager::getPartIndex() const
{
    return m_part_index;
}

