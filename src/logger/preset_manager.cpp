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
    m_presetCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PRESET_FILE),columns.data(), NUM_PNEUMATIC_SETTINGS);
    m_presets = QVector<QVector<int>>( MAX_PRESETS );

    std::vector<std::string> columns1 = {"Preset"};
    m_presetNameCsvManager = CSVManager("/media/NVENT_FILES/preset_names.csv", columns1.data(), 1);
    m_preset_names = QVector<QString>( MAX_PRESETS );

    updatePresets();
}

int PresetManager::getNumPresets()
{
     return m_presetCsvManager.getNumEntries();
}

QVector<int> PresetManager::getPreset1()
{
    return m_presets.at(PRESET_INDEX_1);
}

QVector<int> PresetManager::getPreset2()
{
    return m_presets.at(PRESET_INDEX_2);
}

QVector<int> PresetManager::getPreset3()
{
    return m_presets.at(PRESET_INDEX_3);
}

QVector<int> PresetManager::getPreset4()
{
    return m_presets.at(PRESET_INDEX_4);
}

QVector<int> PresetManager::getPreset5()
{
    return m_presets.at(PRESET_INDEX_5);
}

QVector<int> PresetManager::getPreset6()
{
    return m_presets.at(PRESET_INDEX_6);
}

QVector<int> PresetManager::getPreset7()
{
    return m_presets.at(PRESET_INDEX_7);
}

QVector<int> PresetManager::getPreset8()
{
    return m_presets.at(PRESET_INDEX_8);
}

QVector<int> PresetManager::getPreset9()
{
    return m_presets.at(PRESET_INDEX_9);
}

QVector<int> PresetManager::getPreset10()
{
    return m_presets.at(PRESET_INDEX_10);
}

QVector<int> PresetManager::getPreset11()
{
    return m_presets.at(PRESET_INDEX_11);
}

QVector<int> PresetManager::getPreset12()
{
    return m_presets.at(PRESET_INDEX_12);
}

void PresetManager::createPreset(const QVector<int> &preset)
{
    std::vector<std::string> tmp(NUM_PNEUMATIC_SETTINGS);

    if(m_numPresets < MAX_PRESETS)
    {
        for(int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
        {
            if(i < preset.size())
            {
                tmp[i] = std::to_string(preset.at(i));
            }
        }

        m_presetCsvManager.createRecord(tmp.data());
        updatePresets();
    }
}

void PresetManager::deletePreset(int preset_id)
{
    m_presetCsvManager.deleteRecord(preset_id);
    m_presetNameCsvManager.deleteRecord(preset_id);
    updatePresets();

}
void PresetManager::updatePreset(int preset_id, const QVector<int> &preset)
{
    std::vector<std::string> tmp(NUM_PNEUMATIC_SETTINGS);

    for(int i = 0; i < NUM_PNEUMATIC_SETTINGS; i++)
    {
        if(i < preset.size())
        {
            tmp[i] = std::to_string(preset.at(i));
        }
    }

    if(preset_id > getNumPresets() && preset_id < MAX_PRESETS)
    {
        m_presetCsvManager.createRecord(tmp.data());
        return;
    }

    m_presetCsvManager.updateRecord(preset_id, tmp.data());

    updatePresets();
}


void PresetManager::updatePresets()
{
    m_numPresets = getNumPresets();

    if (m_numPresets > MAX_PRESETS)
    {
        system("rm /media/NVENT_FILES/presets.csv");
        system("rm /media/NVENT_FILES/preset_names.csv");
        std::vector<std::string> columns(NUM_PNEUMATIC_SETTINGS);
        for(int i = 0; i< NUM_PNEUMATIC_SETTINGS; i++)
        {
            columns[i] = settingNameMap.at(i);
        }
        m_presetCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(PRESET_FILE), columns.data(), NUM_PNEUMATIC_SETTINGS);
        m_numPresets = getNumPresets();

        std::vector<std::string> columns1 = {"Preset"};
        m_presetNameCsvManager = CSVManager("/media/NVENT_FILES/preset_names.csv", columns1.data(), 1);

        qInfo() << "NVENT" << "," << "PRESETS" << "," << "Preset Manager reset do to corruption.";
    }

    int index = 0;
    for(; index < m_numPresets; index++)
    {
        m_presets[index].resize(NUM_PNEUMATIC_SETTINGS);
        std::vector<std::string> tmp =  m_presetCsvManager.readRecord(index);
        QRegExp regularExpression(QString::fromStdString("\\d*"));
        //Length of the row must be 14
        if (tmp.size() != NUM_PNEUMATIC_SETTINGS)
        {
            m_presets[index] = QVector<int>(NUM_PNEUMATIC_SETTINGS).fill(0);
        }
        else
        {
            for (int j = 0; j < NUM_PNEUMATIC_SETTINGS; j++)
            {
                if(j < (int) tmp.size() && regularExpression.exactMatch(QString::fromStdString(tmp[j])))
                {
                    m_presets[index][j] = QString::fromStdString(tmp[j]).toInt();
                }
                //Value must be a digit
                else
                {
                    m_presets[index][j] = 0;
                }
            }
        }
        m_preset_names[index] = QString::fromStdString(m_presetNameCsvManager.readRecord(index).at(0));

    }

    for(;index < MAX_PRESETS; index++)
    {
        m_presets[index] = QVector<int>(NUM_PNEUMATIC_SETTINGS).fill(0);
        m_preset_names[index] = "Preset " + QString::number(index + 1);
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

void PresetManager::setPresetName(const QString &name)
{
    m_preset_name = name;
    emit presetNameChanged();
}

void PresetManager::deletePresetName()
{
    m_preset_name = QString::fromStdString("");
    emit presetNameChanged();
}

void PresetManager::addPresetName(const QString &input)
{
    if (m_preset_name.size() < PRESET_NAME_LENGTH)
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
        m_presetNameCsvManager.createRecord(vector.data());
        return;
    }
    m_presetNameCsvManager.updateRecord(m_preset_name_index, vector.data());

    updatePresets();
}

void PresetManager::updateKeyboardState(unsigned char preset_id)
{
    if (m_keyboard_state == 0 && all_caps_state == 0 && preset_id == 1)
    {
        all_caps_state = 1;
        emit presetAllCapChanged();
        emit presetKeyboardStateChanged();
        return;
    }

    if (m_keyboard_state == 0 && all_caps_state == 1 && preset_id == 1)
    {
        m_keyboard_state = preset_id;
        all_caps_state = 0;
        emit presetAllCapChanged();
        emit presetKeyboardStateChanged();
        return;
    }

    m_keyboard_state = preset_id;
    all_caps_state = 0;

    emit presetAllCapChanged();
    emit presetKeyboardStateChanged();
}

unsigned char PresetManager::getKeyboardState() const
{
    return m_keyboard_state;
}

unsigned char PresetManager::getAllCapState() const
{
    return all_caps_state;
}

void PresetManager::resetKeyboard()
{
    m_keyboard_state = 0;
    all_caps_state = 0;
}
