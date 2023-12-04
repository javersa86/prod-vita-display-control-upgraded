#ifndef QML_IDs
#define QML_IDs
#include <QObject>
#include "modes.h"
#include <QQmlEngine>

/**
 * @addtogroup opModeModels
 * @{
 */

/**
 * @file QML_IDS.h
 * @brief Exposes Mode IDs to the QML.
 */

//This file is used to expose Mode IDs to the QML
/**
 * @brief The IDs class
 */
class IDs : public QObject
{

    /**
     * @addtogroup opModeModels
     * @{
     */

    Q_OBJECT
    public:

        /**
         * @brief Empty Constructor
         * @param parent
         */
        IDs(QObject *parent=nullptr) : QObject(parent){}

        /**
         * @brief The enumerations for Mode IDs on QML files.
         */
        enum Modes
        {
            LASER_MODE = (int)ModeIDs::LASER_MODE,
            DOUBLE_JET_MODE = (int)ModeIDs::DOUBLE_JET_MODE,
            MANUAL_MODE = (int)ModeIDs::MANUAL_MODE,
            SCREEN_LOCK_MODE = (int)ModeIDs::SCREEN_LOCK_MODE,
            DEMO_MODE = (int)ModeIDs::DEMO_MODE,
            PIP_MONITORING_MODE = (int)ModeIDs::PIP_MONITORING_MODE,
            ETCO2_MODE = (int)ModeIDs::ETCO2_MODE,
            DEHUMIDIFY_MODE = (int)ModeIDs::DEHUMIDIFY_MODE,
            O2_CALIBRATION_MODE = (int)ModeIDs::O2_CALIBRATION_MODE,
            ALARM_SOUNDING = (int)ModeIDs::ALARM_SOUNDING,
            HUMIDITY_PRIMING_RESET_AVAILABLE = (int)ModeIDs::HUMIDITY_PRIMING_RESET_AVAILABLE,
            LISTENING_KNOB = (int)ModeIDs::LISTENING_KNOB,
            SOUND_ICON = (int)ModeIDs::SOUND_ICON,
            CALIBRATION_MODE = (int)ModeIDs::CALIBRATION_MODE,
            SCREEN_LOCK_TOUCHED_MODE = (int)ModeIDs::SCREEN_LOCK_TOUCHED_MODE

        };
        Q_ENUM(Modes)

        /**
         * @brief Declares QML variables for Mode IDs.
         */
        static void declareQML()
        {
            qmlRegisterType<IDs>("IDs", 1, 0, "ID");
        }

        /** @} */
};

/** @} */
#endif
