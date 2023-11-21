#include "preset_manager.h"
#include "log_manager.h"
#include "../models/settings.h"
#include <QtDebug>

PresetManager::PresetManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> columns(NUM_PNEUMATIC_SETTINGS);
    for(int i = 0; i< NUM_PNEUMATIC_SETTINGS; i++)
    {
        columns[i] = settingNameMap.at(i);
    }
    m_presetCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PRESET_FILE),&columns[0], NUM_PNEUMATIC_SETTINGS);
    m_presets = QVector<QVector<int>>( MAX_PRESETS );

    std::vector<std::string> columns1 = {"Preset"};
    m_presetNameCsvManager = CSVManager("/media/NVENT_FILES/preset_names.csv", &columns1[0], 1);
    m_preset_names = QVector<QString>( MAX_PRESETS );

    updatePresets();
}

int PresetManager::getNumPresets()
{
     return m_presetCsvManager.getNumEntries();
}

QVector<int> PresetManager::getPreset1()
{
    return m_presets[0];
}

QVector<int> PresetManager::getPreset2()
{
    return m_presets[1];
}

QVector<int> PresetManager::getPreset3()
{
    return m_presets[2];
}

QVector<int> PresetManager::getPreset4()
{
    return m_presets[3];
}

QVector<int> PresetManager::getPreset5()
{
    return m_presets[4];
}

QVector<int> PresetManager::getPreset6()
{
    return m_presets[5];
}

QVector<int> PresetManager::getPreset7()
{
    return m_presets[6];
}

QVector<int> PresetManager::getPreset8()
{
    return m_presets[7];
}

QVector<int> PresetManager::getPreset9()
{
    return m_presets[8];
}

QVector<int> PresetManager::getPreset10()
{
    return m_presets[9];
}


QVector<int> PresetManager::getPreset11()
{
    return m_presets[10];
}

QVector<int> PresetManager::getPreset12()
{
    return m_presets[11];
}

void PresetManager::createPreset(QVector<int> preset)
{
    std::vector<std::string> tmp(NUM_PNEUMATIC_SETTINGS);

    if(m_numPresets < 12)
    {
        for(int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
        {
            if(i < preset.size())
                tmp[i] = std::to_string(preset.at(i));
        }

        m_presetCsvManager.createRecord(&tmp[0]);
        updatePresets();
    }
}

void PresetManager::deletePreset(int id)
{
    m_presetCsvManager.deleteRecord(id);
    m_presetNameCsvManager.deleteRecord(id);
    updatePresets();

}
void PresetManager::updatePreset(int id, QVector<int> preset)
{
    std::vector<std::string> tmp(NUM_PNEUMATIC_SETTINGS);

    for(int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
    {
        if(i < preset.size())
            tmp[i] = std::to_string(preset.at(i));
    }

    if(id > getNumPresets() && id < MAX_PRESETS)
    {
        m_presetCsvManager.createRecord(&tmp[0]);
        return;
    }

    m_presetCsvManager.updateRecord(id, &tmp[0]);

    updatePresets();
}


void PresetManager::updatePresets()
{
    m_numPresets = getNumPresets();

    if (m_numPresets > 12)
    {
        system("rm /media/NVENT_FILES/presets.csv");
        system("rm /media/NVENT_FILES/preset_names.csv");
        std::vector<std::string> columns(NUM_PNEUMATIC_SETTINGS);
        for(int i = 0; i< NUM_PNEUMATIC_SETTINGS; i++)
        {
            columns[i] = settingNameMap.at(i);
        }
        m_presetCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PRESET_FILE),&columns[0], NUM_PNEUMATIC_SETTINGS);
        m_numPresets = getNumPresets();

        std::vector<std::string> columns1 = {"Preset"};
        m_presetNameCsvManager = CSVManager("/media/NVENT_FILES/preset_names.csv", &columns1[0], 1);

        qInfo() << "NVENT" << "," << "PRESETS" << "," << "Preset Manager reset do to corruption.";
    }

    int i = 0;
    for(; i< m_numPresets; i++)
    {
        m_presets[i].resize(NUM_PNEUMATIC_SETTINGS);
        std::vector<std::string> tmp =  m_presetCsvManager.readRecord(i);
        QRegExp re("\\d*");
        //Length of the row must be 14
        if (tmp.size() != NUM_PNEUMATIC_SETTINGS)
        {
            m_presets[i] = QVector<int>(NUM_PNEUMATIC_SETTINGS).fill(0);
        }
        else
        {
            for (int j = 0; j < NUM_PNEUMATIC_SETTINGS; j++)
            {
                if(j < (int) tmp.size() && re.exactMatch(QString::fromStdString(tmp[j])))
                    m_presets[i][j] = QString::fromStdString(tmp[j]).toInt();
                //Value must be a digit
                else
                    m_presets[i][j] = 0;
            }
        }
        m_preset_names[i] = QString::fromStdString(m_presetNameCsvManager.readRecord(i).at(0));

    }

    for(;i < MAX_PRESETS; i++)
    {
        m_presets[i] = QVector<int>(NUM_PNEUMATIC_SETTINGS).fill(0);
        m_preset_names[i] = "Preset " + QString::number(i + 1);
    }

    m_preset_name = m_preset_names[m_preset_name_index];

    emit presetsChanged();

}

void PresetManager::updatePresetNameIndex(unsigned char index)
{
    m_preset_name_index = index;
    m_preset_name = m_preset_names[m_preset_name_index];
}

QString PresetManager::getPresetName()
{
    return m_preset_name;
}

void PresetManager::setPresetName(QString name)
{
    m_preset_name = name;
    emit presetNameChanged();
}

void PresetManager::deletePresetName()
{
    m_preset_name = "";
    emit presetNameChanged();
}

void PresetManager::addPresetName(QString input)
{
    if (m_preset_name.size() < 20)
    {
        //updates keyboard state back to 1 if state was originally at 0
        if (m_keyboard_state == 0 && all_caps_state == 0)
        {
            all_caps_state = 2;
            updateKeyboardState(1);
        }
        m_preset_name = m_preset_name + input;
        emit presetNameChanged();
    }
}

void PresetManager::backspacePresetName()
{
    if (m_preset_name.size() > 0)
    {
        m_preset_name = m_preset_name.left(m_preset_name.size() - 1);
        emit presetNameChanged();
    }
}

void PresetManager::enterPresetName()
{
    std::vector<std::string> vector = {m_preset_name.toStdString()};
    if (m_preset_name_index + 1 > m_presetNameCsvManager.getNumEntries() && m_preset_name_index + 1 < MAX_PRESETS)
    {
        m_presetNameCsvManager.createRecord(&vector[0]);
        return;
    }
    m_presetNameCsvManager.updateRecord(m_preset_name_index, &vector[0]);

    updatePresets();
}

void PresetManager::updateKeyboardState(unsigned char id)
{
    if (m_keyboard_state == 0 && all_caps_state == 0 && id == 1)
    {
        all_caps_state = 1;
    }
    else if (m_keyboard_state == 0 && all_caps_state == 1 && id == 1)
    {
        m_keyboard_state = id;
        all_caps_state = 0;
    }
    else {
        m_keyboard_state = id;
        all_caps_state = 0;
    }
    emit presetAllCapChanged();
    emit presetKeyboardStateChanged();
}

unsigned char PresetManager::getKeyboardState()
{
    return m_keyboard_state;
}

unsigned char PresetManager::getAllCapState()
{
    return all_caps_state;
}

void PresetManager::resetKeyboard()
{
    m_keyboard_state = 0;
    all_caps_state = 0;
}
