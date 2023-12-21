#include "warning_manager.h"
#include <QDebug>

WarningManager::WarningManager(QVector<unsigned char> *clearable_warnings, QObject *parent)
    : QObject(parent), m_disconnectTimer(new QTimer(this))
{
    initStateValues();

    if(clearable_warnings != nullptr)
    {
        setAutoClearingWarnings(clearable_warnings);
    }
    else
    {
        QVector<unsigned char> clearable = QVector<unsigned char>(NUM_WARNINGS);
        for(int i = 0; i< NUM_WARNINGS; i++)
        {
            clearable.replace(
                        i,
                        (unsigned char) (m_warnings.at(i).clearingBehavior() == CLEAR_AUTONOMOUSLY || m_warnings.at(i).clearingBehavior() == CLEAR_ON_DEMAND)
                        );
        }
        setAutoClearingWarnings(&clearable);
    }

    connect(m_disconnectTimer,&QTimer::timeout,this,&WarningManager::raiseDisconnectWarning);
    m_disconnectTimer->start(INTERVAL_THREE_SECONDS);
}

void WarningManager::raiseDisconnectWarning()
{
    if (m_service_state == 1)
    {
        return;
    }

    QVector<unsigned char> warningCopy = QVector<unsigned char>(NUM_WARNINGS);
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        warningCopy.replace(i, m_active_warnings.at(i));
    }
    warningCopy.replace(NO_COMMUNICATION, 1);
    setActiveWarnings(&warningCopy);
}

void WarningManager::setActiveWarnings(QVector<unsigned char> *warnings)
{
    unsigned char changed = 0;
    if (warnings->length() == NUM_WARNINGS)
    {
        changed = setActiveAlarms(changed, warnings);
        changed = setActiveNotices(changed, warnings);

        //Updates service due.
        if (m_notices.at(SERVICE_NOTICE_ID) != m_service_due_state)
        {
            changed = 1;
            m_notices.replace(SERVICE_NOTICE_ID, m_service_due_state);
        }

        if(changed == 1)
        {
            emit warningChanged();

            int num = getNumActiveWarnings();
            num++;
        }
    }
}

unsigned char WarningManager::setActiveAlarms(unsigned char changed, QVector<unsigned char> *warnings)
{
    for (int i = 0; i < BEGIN_NOTICE_INDEX; i++)
    {
        if(m_active_warnings.at(i) != warnings->at(i))
        {
            changed = 1;
            //Writes down single and double jet values.
            QString msg = QString::fromStdString("");
            for (int j = 0; j< NUM_PNEUMATIC_SETTINGS; j ++)
            {
                msg += QString::fromStdString(settingNameMap.at(j)) + ": ";
                msg += QString::number(m_currentStateValues.at(j)) + "; ";
            }
            qInfo() << "NVENT "
                    << ","
                    << "WARNING"
                    << ","
                    << m_warnings.at(i).title().replace(
                           QString::fromStdString(","),
                           QString::fromStdString("")
                           )
                    << (warnings->at(i) == 1 ? "ACTIVE" : "INACTIVE")
                    << msg;

            //if warning was raised and isn't yet in the by occurrance list
            if ((warnings->at(i) == 1) && m_inactive_by_occurance.contains(i))
            {
                m_inactive_by_occurance.append(i);
            }

            //if warning was lowered
            if(warnings->at(i) == 0)
            {
                //if warning autoclears, remove it from occurance list
                if(m_autoclearing_warnings.at(i) == 1)
                {
                    m_inactive_by_occurance.removeAll(i);
                }
            }
            //update active warnings
            m_active_warnings.replace(i, warnings->at(i));

            //Signals to qml if SP High is raised and shows blue lines.
            if (i == 1 && m_active_warnings.at(i) == 1)
            {
                emit spWarning();
            }
        }
    }
    return changed;
}
unsigned char WarningManager::setActiveNotices(unsigned char changed, QVector<unsigned char> *warnings)
{
    for (int i = BEGIN_NOTICE_INDEX; i< NUM_WARNINGS; i++)
    {
        if (i == SERVICE_ID && m_service_due_state == 1)
        {
            continue;
        }

        if(m_notices.at(i - BEGIN_NOTICE_INDEX) != warnings->at(i))
        {
            changed = 1;
            //Writes down single and double jet values.
            QString msg = QString::fromStdString("");
            for (int j = 0; j< NUM_PNEUMATIC_SETTINGS; j ++)
            {
                msg += QString::fromStdString(settingNameMap.at(j)) + ": ";
                msg += QString::number(m_currentStateValues.at(j)) + "; ";
            }
            qInfo() << "NVENT "
                    << ","
                    << "WARNING"
                    << ","
                    << m_warnings.at(i).title().replace(
                           QString::fromStdString(","),
                           QString::fromStdString("")
                           )
                    << (warnings->at(i) == 1 ? "ACTIVE" : "INACTIVE")
                    << msg;

            m_notices.replace(i - BEGIN_NOTICE_INDEX,warnings->at(i));
        }
        //Checks if O2 Calibration Progress warnings are active.
        setCalibrationProgress(i - BEGIN_NOTICE_INDEX);
    }
    return changed;
}

void WarningManager::setCalibrationProgress(int o2_index)
{
    if (o2_index == CALIBRATION_ID)
    {
        if (m_notices.at(o2_index) == 1 && m_o2_calibration_flag == 0)
        {
            emit o2CalibrationSignal();
            m_o2_calibration_flag = 1;
        }
        else if (m_notices.at(o2_index) == 0 && m_o2_calibration_flag == 1)
        {
            m_o2_calibration_flag = 0;
        }
    }
    if (o2_index == CALIBRATION_LIMITED_ID)
    {
        if (m_notices.at(o2_index) == 1 && m_o2_laser_in_progress_calibration_flag == 0)
        {
            emit o2CalibrationSignal();
            m_o2_laser_in_progress_calibration_flag = 1;
        }
        else if (m_notices.at(o2_index) == 0 && m_o2_laser_in_progress_calibration_flag == 1)
        {
            m_o2_laser_in_progress_calibration_flag = 0;
        }
    }
}

int WarningManager::getLaserWarning()
{
    if (m_notices.at(0) == 1)
    {
        return 0;
    }
    if (m_notices.at(1) == 1 || m_notices.at(CALIBRATION_ID) == 1)
    {
        return 1;
    }
    return 2;
}

void WarningManager::setAutoClearingWarnings(QVector<unsigned char> *clearable_warnings)
{
    if (clearable_warnings->length() == NUM_WARNINGS)
    {
        for (int i = 0; i < NUM_WARNINGS; i++)
        {
            m_autoclearing_warnings.replace(i,clearable_warnings->at(i));
        }
    }
}

void WarningManager::clearWarning(unsigned char clear_id)
{
    if(clear_id < BEGIN_NOTICE_INDEX)
    {
        if(m_active_warnings.at(clear_id) == 0)
        {
            m_inactive_by_occurance.removeAll(clear_id);
            emit warningChanged();
        }
    }
}

bool WarningManager::activeWarnings()
{
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if(m_active_warnings.at(i) == 1)
        {
            return true;
        }
    }
    return false;
}

bool WarningManager::notices()
{
    for (int i = 0; i < NUM_WARNINGS - BEGIN_NOTICE_INDEX; i++)
    {
        if(m_notices.at(i) == 1)
        {
            return true;
        }
    }
    return false;
}

bool WarningManager::getWarningActive(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        if(warning_id < BEGIN_NOTICE_INDEX)
        {
            return (bool) m_active_warnings.at(warning_id);
        }
        return (bool) m_notices.at(warning_id - BEGIN_NOTICE_INDEX);
    }
    return false;
}

int WarningManager::getWarningBehavior(unsigned char warning_id)
{
    if(warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).clearingBehavior();
    }
    return 0;
}

int WarningManager::getNumActiveWarnings()
{
    int num_warnings = 0;
    for(int i = 0; i < BEGIN_NOTICE_INDEX; i++)
    {
        if(m_active_warnings.at(i) == 1 || m_inactive_by_occurance.contains(i))
        {
            num_warnings ++;
        }
    }
    for(int i = BEGIN_NOTICE_INDEX; i < NUM_WARNINGS; i++)
    {
        if (m_notices.at(i - BEGIN_NOTICE_INDEX) == 1)
        {
            num_warnings ++;
        }
    }
    return num_warnings;
}

QVector<int> WarningManager::getWarningBanners()
{
    QVector<int> warnings = QVector<int>();
    if(activeWarnings())
    {
        for (int i = 0; i < BEGIN_NOTICE_INDEX; i++)
        {
            if (m_active_warnings.at(i) == 1)
            {
                warnings.append(i);
            }
        }
    }
    int total_inactive = m_inactive_by_occurance.size();

    for(int i = 0; i < total_inactive; i++)
    {
        if (m_active_warnings.at(m_inactive_by_occurance.at(i)) == 0)
        {
            warnings.append(m_inactive_by_occurance.at(i));
        }
    }
    for (int i = BEGIN_NOTICE_INDEX; i < NUM_WARNINGS; i ++)
    {
        if (m_notices.at(i - BEGIN_NOTICE_INDEX) == 1)
        {
            warnings.append(i);
        }
    }
    return warnings;
}

void WarningManager::updateWarnings(QVector<unsigned char> *warnings)
{
    constexpr int INTERVAL_THREE_SECONDS = 3000;

    m_disconnectTimer->stop();
    m_disconnectTimer->start(INTERVAL_THREE_SECONDS);
    warnings->replace(NO_COMMUNICATION, 0);
    setActiveWarnings(warnings);
}

QString WarningManager::getWarningTitle(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).title();
    }
    return {};
}

QString WarningManager::getWarningDesc(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).description();
    }
    return {};
}

QString WarningManager::getWarningClearText(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).clearText();
    }
    return {};
}

QVector<QString> WarningManager::getWarningInformation(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).troubleshootingSteps();
    }
    return {};
}

int WarningManager::getWarningClass(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).warningClass();
    }
    return NO_WARNINGS;
}

QString WarningManager::getWarningColor(unsigned char warning_id)
{
    if (warning_id < NUM_WARNINGS)
    {
        return m_warnings.at(warning_id).color();
    }
    return QString::fromStdString("");
}

void WarningManager::initStateValues()
{
    for (int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
    {
        m_currentStateValues.append(0);
    }
}

void WarningManager::setStateValues(QVector<int> temp)
{
    for (int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
    {
        m_currentStateValues[i] = temp[i];
    }
}

void WarningManager::setStateValue(int warning_id, int value)
{
    if (warning_id < NUM_PNEUMATIC_SETTINGS)
    {
        m_currentStateValues[warning_id] = value;
    }
}

void WarningManager::pauseDisconnection(unsigned char value)
{
    m_service_state = value;
}

void WarningManager::updateServiceAlarm(unsigned char state)
{
    m_service_due_state = state;
}
