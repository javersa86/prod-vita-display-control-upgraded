#include "warning_manager.h"
#include <QDebug>

WarningManager::WarningManager(QVector<unsigned char> *clearable_warnings, QObject *parent)
    : QObject(parent)
{
    m_active_warnings = QVector<int>(NUM_WARNINGS);
    m_inactive_by_occurance = QVector<int>();
    m_autoclearing_warnings = QVector<int>(NUM_WARNINGS);
    m_notices = QVector<int>(NUM_WARNINGS - BEGIN_NOTICE_INDEX);
    m_top_warning = NO_WARNINGS;
    m_num_active_warnings_flag = NO_WARNINGS;

    m_currentStateValues = QVector<int>();
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
            clearable.replace(i, (unsigned char) (m_warnings[i].clearingBehavior() == CLEAR_AUTONOMOUSLY || m_warnings[i].clearingBehavior() == CLEAR_ON_DEMAND));
        }
        setAutoClearingWarnings(&clearable);
    }

    m_disconnectTimer = new QTimer(this);
    connect(m_disconnectTimer,&QTimer::timeout,this,&WarningManager::raiseDisconnectWarning);
    m_disconnectTimer->start(3000);
}

void WarningManager::raiseDisconnectWarning()
{
    if (m_service_state) return;

    QVector<unsigned char> warningCopy = QVector<unsigned char>(NUM_WARNINGS);
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        warningCopy.replace(i, m_active_warnings.at(i));
    }
    warningCopy.replace(NO_COMMUNICATION, 1);
    setActiveWarnings(&warningCopy);
}

void WarningManager::setActiveWarnings(QVector<unsigned char> *warnings )
{
    unsigned char changed = 0;
    if (warnings->length() == NUM_WARNINGS)
    {
        for (int i = 0; i < BEGIN_NOTICE_INDEX; i++)
        {
            unsigned char temp = m_active_warnings.at(i);
            unsigned char temp1= warnings->at(i);
            if(m_active_warnings.at(i) != warnings->at(i))
            {
                changed = 1;
                //Writes down single and double jet values.
                QString msg = "";
                for (int j = 0; j< NUM_PNEUMATIC_SETTINGS; j ++)
                {
                    msg += QString::fromStdString(settingNameMap.at(j)) + ": ";
                    msg += QString::number(m_currentStateValues.at(j)) + "; ";
                }
                qInfo() << "NVENT " << "," << "WARNING" << "," << m_warnings[i].title().remove( + ",") << (warnings->at(i) ? "ACTIVE" : "INACTIVE") << msg;

                //if warning was raised and isn't yet in the by occurrance list
                if(warnings->at(i) && !m_inactive_by_occurance.contains(i))
                    m_inactive_by_occurance.append(i);

                //if warning was lowered
                if(!warnings->at(i))
                {
                    //if warning autoclears, remove it from occurance list
                    if(m_autoclearing_warnings.at(i))
                    {
                        m_inactive_by_occurance.removeAll(i);
                    }
                }
                //update active warnings
                m_active_warnings.replace(i, warnings->at(i));

                //Signals to qml if SP High is raised and shows blue lines.
                if (i == 1 && m_active_warnings.at(i))
                {
                    emit spWarning();
                }
            }
        }

        for (int i = BEGIN_NOTICE_INDEX; i< NUM_WARNINGS; i++)
        {
            if(m_notices.at(i - BEGIN_NOTICE_INDEX) != warnings->at(i))
            {
                changed = 1;
                //Writes down single and double jet values.
                QString msg = "";
                for (int j = 0; j< NUM_PNEUMATIC_SETTINGS; j ++)
                {
                    msg += QString::fromStdString(settingNameMap.at(j)) + ": ";
                    msg += QString::number(m_currentStateValues.at(j)) + "; ";
                }
                qInfo() << "NVENT " << "," << "WARNING" << "," << m_warnings[i].title().remove( + ",") << (warnings->at(i) ? "ACTIVE" : "INACTIVE") << msg;

                m_notices.replace(i - BEGIN_NOTICE_INDEX,warnings->at(i));
            }

            //Checks if O2 Calibration Progress warnings are active.
            setCalibrationProgress(i - BEGIN_NOTICE_INDEX);
        }
        if(changed)
        {
            emit warningChanged();
            int num = getNumActiveWarnings();
            num++;
        }
    }
}

void WarningManager::setCalibrationProgress(int o2_index)
{

    if (o2_index == 19)
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
    if (o2_index == 20)
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
    if (m_notices.at(0)) return 0;
    else if (m_notices.at(1)) return 1;
    else if (m_notices.at(19)) return 1;
    else return 2;
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

void WarningManager::clearWarning(unsigned char id)
{
    if(id < BEGIN_NOTICE_INDEX)
    {
        if(!(m_active_warnings.at(id)))
        {
            m_inactive_by_occurance.removeAll(id);
            emit warningChanged();
        }
    }
}

bool WarningManager::activeWarnings()
{
    for (int i = 0; i < NUM_WARNINGS; i++)
    {
        if(m_active_warnings.at(i))
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
        if(m_notices.at(i))
        {
            return true;
        }
    }
    return false;
}

bool WarningManager::getWarningActive(unsigned char i)
{
    if (i < NUM_WARNINGS)
    {
        if(i < BEGIN_NOTICE_INDEX)
            return (bool) m_active_warnings[i];
        else
            return (bool) m_notices[i - BEGIN_NOTICE_INDEX];
    }
    return false;
}

int WarningManager::getWarningBehavior(unsigned char i)
{
    if(i < NUM_WARNINGS)
    {
        return m_warnings[i].clearingBehavior();
    }
    else return 0;
}

int WarningManager::getNumActiveWarnings()
{
    int num_warnings = 0;
    for(int i = 0; i < BEGIN_NOTICE_INDEX; i++)
    {
        if(m_active_warnings.at(i))
            num_warnings ++;
        else if (m_inactive_by_occurance.contains(i))
            num_warnings ++;
    }
    for(int i = BEGIN_NOTICE_INDEX; i < NUM_WARNINGS; i++)
    {
        if (m_notices.at(i - BEGIN_NOTICE_INDEX))
            num_warnings ++;
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
            if (m_active_warnings.at(i))
            {
                warnings.append(i);
            }
        }
    }
    for(int i = 0; i < m_inactive_by_occurance.size(); i++)
    {
        if (!m_active_warnings.at(m_inactive_by_occurance.at(i)))
        {
            warnings.append(m_inactive_by_occurance.at(i));
        }
    }
    for (int i = BEGIN_NOTICE_INDEX; i < NUM_WARNINGS; i ++)
    {
        if (m_notices.at(i - BEGIN_NOTICE_INDEX))
        {
            warnings.append(i);
        }
    }
    return warnings;
}

void WarningManager::updateWarnings(QVector<unsigned char> *warnings)
{
    m_disconnectTimer->stop();
    m_disconnectTimer->start(3000);
    warnings->replace(NO_COMMUNICATION, 0);
    setActiveWarnings(warnings);
}

QString WarningManager::getWarningTitle(unsigned char i)
{
    if (i < NUM_WARNINGS)  return m_warnings[i].title();
    else return QString();
}

QString WarningManager::getWarningDesc(unsigned char i)
{
    if (i < NUM_WARNINGS) return m_warnings[i].description();
    else return QString();
}

QString WarningManager::getWarningClearText(unsigned char i)
{
    if (i < NUM_WARNINGS) return m_warnings[i].clearText();
    return QString();
}

QVector<QString> WarningManager::getWarningInformation(unsigned char i)
{
    if (i < NUM_WARNINGS) return m_warnings[i].troubleshootingSteps();
    else return QVector<QString>();
}

int WarningManager::getWarningClass(unsigned char i)
{
    if (i < NUM_WARNINGS) return m_warnings[i].warningClass();
    else return NO_WARNINGS;
}

QString WarningManager::getWarningColor(unsigned char i)
{
    if (i < NUM_WARNINGS) return m_warnings[i].color();
    else return QString("");
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

void WarningManager::setStateValue(int id, int value)
{
    if (id < NUM_PNEUMATIC_SETTINGS)
    {
        m_currentStateValues[id] = value;
    }
}

void WarningManager::pauseDisconnection(unsigned char value)
{
    m_service_state = value;
}
