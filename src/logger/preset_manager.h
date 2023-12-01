#pragma once

#include "csv_manager.h"
#include <QObject>
#include <QVector>

/**
 * @addtogroup presetManagerModule
 * @{
 */

/**
 * @file preset_manager.h
 * @brief Header for preset_manager.cpp with info.
 */

/**
 * @file preset_manager.cpp
 * @brief Manages preset data on device.
 */

/**
 * @brief Name of csv that stores presets.
 */
#define PRESET_FILE "presets.csv"

/**
 * @brief Name of number of presets stored on device.
 */
#define MAX_PRESETS 12

#define PRESET_NAME_LENGTH 20

/**
 * @brief The PresetManager class
 */
class PresetManager : public QObject
{
    /**
     * @addtogroup presetManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief numPresets
     */
    Q_PROPERTY(int numPresets READ getNumPresets NOTIFY presetsChanged)

    /**
     * @brief preset1
     */
    Q_PROPERTY(QVector<int> preset1  READ getPreset1  NOTIFY presetsChanged)
    /**
     * @brief preset2
     */
    Q_PROPERTY(QVector<int> preset2  READ getPreset2  NOTIFY presetsChanged)
    /**
     * @brief preset3
     */
    Q_PROPERTY(QVector<int> preset3  READ getPreset3  NOTIFY presetsChanged)
    /**
     * @brief preset4
     */
    Q_PROPERTY(QVector<int> preset4  READ getPreset4  NOTIFY presetsChanged)
    /**
     * @brief preset5
     */
    Q_PROPERTY(QVector<int> preset5  READ getPreset5  NOTIFY presetsChanged)
    /**
     * @brief preset6
     */
    Q_PROPERTY(QVector<int> preset6  READ getPreset6  NOTIFY presetsChanged)
    /**
     * @brief preset7
     */
    Q_PROPERTY(QVector<int> preset7  READ getPreset7  NOTIFY presetsChanged)
    /**
     * @brief preset8
     */
    Q_PROPERTY(QVector<int> preset8  READ getPreset8  NOTIFY presetsChanged)
    /**
     * @brief preset9
     */
    Q_PROPERTY(QVector<int> preset9  READ getPreset9  NOTIFY presetsChanged)
    /**
     * @brief preset10
     */
    Q_PROPERTY(QVector<int> preset10 READ getPreset10 NOTIFY presetsChanged)
    /**
     * @brief preset11
     */
    Q_PROPERTY(QVector<int> preset11 READ getPreset11 NOTIFY presetsChanged)
    /**
     * @brief preset12
     */
    Q_PROPERTY(QVector<int> preset12 READ getPreset12 NOTIFY presetsChanged)

    /**
     * @brief presetName
     */
    Q_PROPERTY(QString presetName READ getPresetName NOTIFY presetNameChanged)
    /**
     * @brief keyboardState
     */
    Q_PROPERTY(unsigned char keyboardState READ getKeyboardState NOTIFY presetKeyboardStateChanged)

    /**
     * @brief allCapState
     */
    Q_PROPERTY(unsigned char allCapState READ getAllCapState NOTIFY presetAllCapChanged)

    signals:

        /**
         * @brief Signal for when preset value is updated.
         * @callgraph
         */
        void presetsChanged();

        /**
         * @brief Signal for when preset name is updated.
         * @callgraph
         */
        void presetNameChanged();

        /**
         * @brief Signal for when keyboard state changed.
         * @callgraph
         */
        void presetKeyboardStateChanged();

        /**
         * @brief Signal for when keyboard is all caps.
         * @callgraph
         */
        void presetAllCapChanged();

    public:

        /**
         * @brief Constructor for the preset manager and preset name manager. The preset manager can CRUD presets.
         * @param parent
         */
        PresetManager(QObject *parent = nullptr);

        /**
         * @brief Gets the number of presets.
         * @return int
         */
        int getNumPresets();

        /**
         * @brief Gets the first preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset1();

        /**
         * @brief Gets the second preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset2();
        /**
         * @brief Gets the third preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset3();
        /**
         * @brief Gets the fourth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset4();
        /**
         * @brief Gets the fifth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset5();
        /**
         * @brief Gets the sixth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset6();
        /**
         * @brief Gets the seventh preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset7();
        /**
         * @brief Gets the eighth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset8();
        /**
         * @brief Gets the nineth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset9();
        /**
         * @brief Gets the tenth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset10();
        /**
         * @brief Gets the eleventh preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset11();
        /**
         * @brief Gets the twelveth preset in the list of presets.
         * @return QVector<int>
         */
        QVector<int> getPreset12();

        /**
         * @brief Gets the current edited preset name.
         * @return QString
         */
        QString getPresetName(); //must update index to get preset name

        /**
         * @brief Gets state of keyboard: uppercase, lowercase, numbers and symbols, and other symbols.
         * @return unsigned char
         */
        unsigned char getKeyboardState() const;

        /**
         * @brief Gets all caps state.
         * @return unsigned char
         */
        unsigned char getAllCapState() const;

    public slots:
        /**
         * @brief Deletes the preset with the given id.
         * @param id
         * @callergraph
         */
        void deletePreset(int id);

        /**
         * @brief Updates the preset with the given id.
         * @param id
         * @param preset
         * @callergraph
         */
        void updatePreset(int id, const QVector<int> &preset);

        /**
         * @brief Adds character at end of preset name.
         * @param input
         * @callergraph
         */
        void addPresetName(const QString &input);
        /**
         * @brief Removes last character from preset name.
         * @callergraph
         */
        void backspacePresetName();

        /**
         * @brief Deletes the current edited preset name.
         * @callergraph
         */
        void deletePresetName();
        /**
         * @brief Saves the current preset name to the preset name manager.
         * @callergraph
         */
        void enterPresetName();

        /**
         * @brief Sets the current edited preset name.
         * @param name
         * @callergraph
         */
        void setPresetName(const QString &name);

        /**
         * @brief   Updates the current state of the preset name change page.
         * @details When user presses the shift key once, all caps is set: state 0 will remain active.
         *          When user presses the shift key twice, all caps is disabled: state 1 is set.
         *          Different state ids include:
         *              - 0. Uppercase
         *              - 1. Lowercase
         *              - 2. Numbers and symbols
         *              - 3. Other symbols
         * @param id
         * @callergraph
         */
        void updateKeyboardState(unsigned char id);

        /**
         * @brief Updates the variable to edit the current preset name.
         * @param index
         * @callergraph
         */
        void updatePresetNameIndex(unsigned char);

        /**
         * @brief Defaults keyboard state and all caps state.
         * @callergraph
         */
        void resetKeyboard();

    private:
        CSVManager m_presetCsvManager;
        QVector<QVector<int>> m_presets;

        int m_numPresets;

        /**
         * @brief Updates presets and preset names saved in memory based on the presets and preset names in the CSV files.
         */
        void updatePresets();
        /**
         * @brief Creates a new preset if there are fewer than 6 presets.
         * @param preset
         */
        void createPreset(const QVector<int> &preset);

        CSVManager m_presetNameCsvManager;
        QVector<QString> m_preset_names;

        QString m_preset_name;

        unsigned char m_preset_name_index = 0;

        unsigned char m_keyboard_state = 0;

        unsigned char all_caps_state = 0;

        const int PRESET_INDEX_1 = 0;
        const int PRESET_INDEX_2 = 1;
        const int PRESET_INDEX_3 = 2;
        const int PRESET_INDEX_4 = 3;
        const int PRESET_INDEX_5 = 4;
        const int PRESET_INDEX_6 = 5;
        const int PRESET_INDEX_7 = 6;
        const int PRESET_INDEX_8 = 7;
        const int PRESET_INDEX_9 = 8;
        const int PRESET_INDEX_10 = 9;
        const int PRESET_INDEX_11 = 10;
        const int PRESET_INDEX_12 = 11;
        /** @} */
};

/** @} */
