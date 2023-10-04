#include "dpr_manager.h"
#include "csv_manager.h"

DPRManager::DPRManager(QObject * parent) :
    QObject(parent)
{
    //Retrive Time Stamp from time manager CSV file
    std::vector<std::string> tColumns = {"TYPE", "TIME"};
    m_timeManager = CSVManager("/run/media/mmcblk0p2/home/ubuntu/time.csv", &tColumns[0],2);

    m_dprCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(DPR_FILE),&dprColumns[0], 2);
    m_timeStamps = QVector<QString>( MAX_O2_VALS );
    m_dprVals = QVector<int>( MAX_O2_VALS );
    updateDPRVals();
}

void DPRManager::updateDPRVals()
{
    QRegExp re("\\d*");

    m_numDPRVals = m_dprCsvManager.getNumEntries();

    //Reset if DPR file is corrupted.
    if (m_numDPRVals > MAX_O2_VALS)
    {
        system("rm /media/NVENT_FILES/dpr_vals.csv");
        m_dprCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(DPR_FILE),&dprColumns[0], 2);
        m_numDPRVals = m_dprCsvManager.getNumEntries();
        qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "DPR Calibration Manager reset do to corruption.";
    }
    int i = 0;
    for(; i< m_numDPRVals; i++)
    {
        std::vector<std::string> tmp =  m_dprCsvManager.readRecord(i);
        m_timeStamps[i] = "";
        m_dprVals[i] = -1;
        //The length of the row must be 4
        if (tmp.size() != 2)
        {
            m_timeStamps[i] = "";
            m_dprVals[i] = -1;
        }
        else {
            for (int j = 0; j < 2; j++)
            {
                if(j == 0)
                {
                    m_timeStamps[i] = QString::fromStdString(tmp[j]);
                }
                else if(j == 1){
                    if (re.exactMatch(QString::fromStdString(tmp[j])))
                    {
                        m_dprVals[i] = QString::fromStdString(tmp[j]).toInt();
                    }
                    //If value is not a digit
                    else
                    {
                        m_dprVals[i] = -1;
                    }
                }
            }
        }
    }

    for(;i < MAX_O2_VALS; i++)
    {
        m_timeStamps[i] = "";
        m_dprVals[i] = -1;
    }

    emit dprValsChanged();
}

void DPRManager::addDPRVal(int value)
{
    while(m_numDPRVals >= 5)
    {
        deleteOldestDPRVal();
    }

    std::string timeStamp = m_timeManager.readRecord(0).at(1) + " - " + m_timeManager.readRecord(1).at(1);
    std::vector<std::string> tmp = {timeStamp,std::to_string(value)};

    m_dprCsvManager.createRecord(&tmp[0]);
    updateDPRVals();

    qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Confirm Calibration for Driving Pressure Regulator Calibration: " + QString::number(value);
}

void DPRManager::deleteOldestDPRVal()
{
    m_dprCsvManager.deleteRecord(0);
    updateDPRVals();

    qInfo() << "NVENT" << "," << "PRESSURE REGULATOR CALIBRATION" << "," << "Delete Oldest Calibration value.";
}

int DPRManager::getDPRCalVal()
{
    if( m_numDPRVals )
    {
        return m_dprVals[m_numDPRVals - 1];
    }
    else return -1;
}
