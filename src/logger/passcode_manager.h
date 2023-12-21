#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QCryptographicHash>

/**
 * @addtogroup passcodeManagerModule
 * @{
 */

/**
 * @file passcode_manager.h
 * @brief Header for passcode_manager.cpp with info
 */

/**
 * @file passcode_manager.cpp
 * @brief Manages passcodes used on device.
 */

/**
 * @brief Name of CSV file that stores passcodes.
 */
constexpr const char* PASSCODE_FILE = "passcodes.csv";

/**
 * @brief The PasscodeManager class
 */
class PasscodeManager : public QObject
{
    /**
     * @addtogroup passcodeManagerModule
     * @{
     */

    Q_OBJECT

    //Signals current values for passcodes to qml files.

    /**
     * @brief servicePasscode
     */
    Q_PROPERTY(QString servicePasscode READ getServicePasscode NOTIFY passcodeChanged)
    /**
     * @brief presetPasscode
     */
    Q_PROPERTY(QString presetPasscode READ getPresetPasscode NOTIFY passcodeChanged)

    Q_PROPERTY(QString servicePasscode READ getServicePasscode WRITE editServicePasscode NOTIFY passcodeChanged)
    Q_PROPERTY(QString presetPasscode READ getPresetPasscode WRITE editPresetPasscode NOTIFY passcodeChanged)

    /**
     * @brief changedValue
     */
    Q_PROPERTY(int changedValue READ getChangedValue NOTIFY passcodeChanged)

    /**
     * @brief presetPasscodeManual
     */
    Q_PROPERTY(QString presetPasscodeManual READ getPresetPasscodeManual NOTIFY passcodeChanged)
    Q_PROPERTY(QString presetPasscodeManual READ getPresetPasscodeManual WRITE editPresetPasscodeManual NOTIFY passcodeChanged)

    public:
        /**
         * @brief Constructor method.
         * @details The service page and the presets page require passcodes to make significant changes to the device.
         *          Program will allow access to passcodes from QML files.
         *          Passwords are stored onto a .csv file.
         *          The user will have the ability to change passcodes through the service page and settings page.
         * @param parent
         */
        PasscodeManager(QObject *parent = nullptr);

        /**
         * @brief Gets service passcode.
         * @return QString
         */
        QString getServicePasscode();

        /**
         * @brief Gets preset passcode.
         * @return QString
         */
        QString getPresetPasscode();
        /**
         * @brief Gets signal change value.
         * @details Signal change value is used to signal the QML file if passcode was changed and why.
         *          If signal equals 0, passcode was changed.
         *          If signal equals 1, passcode was not changed because user enter old passcode.
         *          If signal equals 2, passcode was not changed because new passcode length was not 6 digits.
         * @return QString
         */
        int getChangedValue() const;

        /**
         * @brief Gets preset passcode when preset was changed on service page
         * @return QString
         */
        QString getPresetPasscodeManual();

    public slots:
        /**
         * @brief Changes service page passcode.
         * @details The system will not change new passcode if old one was entered.
         *          Passcode is required to be 4 digits.
         *          Records new passcode onto .csv file.
         *          Records log entry for passcode change.
         * @param newPasscode
         * @callergraph
         */
        void editServicePasscode(const QString &newPasscode);
        /**
         * @brief Changes preset page passcode.
         * @details The system will not change new passcode if old one was entered.
         *          Passcode is required to be 4 digits.
         *          Records new passcode onto .csv file.
         *          Records log entry for passcode change.
         * @param newPasscode
         * @callergraph
         */
        void editPresetPasscode(const QString &newPasscode);
        /**
         * @brief Changes preset page passcode.
         * @details Called when technician is requested to change passcode throught the service page.
         *          Will change passcode even if new passcode is the original old passcode.
         *          Passcode is required to be 4 digits.
         *          Records new passcode onto .csv file.
         *          Records log entry for passcode change.
         * @param newPasscode
         * @callergraph
         */
        void editPresetPasscodeManual(const QString &newPasscode);

    signals:
        /**
         * @brief Signal for when passcode changes.
         * @callgraph
         */
        void passcodeChanged();

    private:

        /**
         * @brief Retrieves current passcodes onto .csv file.
         * @details Stores the current variables for service page and preset page passcodes.
         *          Updates whenever device powers on or whenever passcodes are changed by the user.
         *          If newly created passcode file has no rows for preset passcode and service passcode,
         *          system will store variables with default passcode values.
         *          Also, it will record default passcodes onto .csv file.
         */
        void updatePasscode();
        QString encryptPasscode(QString);
        QString decriptPasscode(QString);

        CSVManager m_passcodeCsvManager;
        QString m_service_passcode;
        QString m_preset_passcode;
        int m_signal_change_value = 0;
        /** @} */

};

/** @} */
