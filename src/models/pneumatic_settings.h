#pragma once
#include <QObject>
#include <QString>
#include "settings.h"

/**
 * @addtogroup settingsModels
 * @{
 */

/**
 * @file pneumatic_settings.h
 * @brief The header for pneumatic_settings.cpp with info.
 */

/**
 * @file pneumatic_settings.cpp
 * @brief The parent class for all pneumatics setting subclasses.
 * @details Each pneumatic setting will have unique variables to each other:
 *          - minimum value
 *          - maximum value
 *          - unit
 *          - title
 *          - setting_id
 *          - step
 *          - minimumOn
 *          - help text
 *          - warning threshold
 */

/**
 * @brief The PneumaticSettings class
 */
class PneumaticSettings : public QObject
{
    /**
     * @addtogroup settingsModels
     * @{
     */

    Q_OBJECT

    /**
     * @brief min
     */
    Q_PROPERTY(int min READ min NOTIFY minSignal)
    /**
     * @brief max
     */
    Q_PROPERTY(int max READ max NOTIFY maxSignal)
    /**
     * @brief unit
     */
    Q_PROPERTY(QString unit READ unit NOTIFY unitSignal)
    /**
     * @brief title
     */
    Q_PROPERTY(QString title READ title NOTIFY titleSignal)
    /**
     * @brief id
     */
    Q_PROPERTY(int id READ id NOTIFY idSignal)
    /**
     * @brief step
     */
    Q_PROPERTY(int step READ step NOTIFY stepSignal)
    /**
     * @brief minimumOn
     */
    Q_PROPERTY(int minimumOn READ minOn NOTIFY minOnSignal)
    /**
     * @brief help
     */
    Q_PROPERTY(QString help READ help NOTIFY helpSignal)
    /**
     * @brief warningThreshold
     */
    Q_PROPERTY(int warningThreshold READ warningThreshold NOTIFY warningThresholdSignal)

    public:

        /**
         * @brief Default constructor. Should never be called.
         */
        PneumaticSettings() = default;

        /**
         * @brief Constructor to build a Pneumatic Setting with a "minimum on" parameter.
         * @note  The minOn parameter is only used for humidity. 0 is off and minimum on is 30.
         * @param setting_id
         * @param unit
         * @param title
         * @param help
         * @param min
         * @param max
         * @param step
         * @param minOn
         * @param warningThreshold
         * @param parent
         */
        PneumaticSettings(int setting_id, const QString &unit, const QString &title, const QString &help,
                          int min, int max, int step, int minOn, int warningThreshold, QObject *parent = nullptr);

        /**
         * @brief Constructor to build a Pneumatic Setting without a "minimum on" setting.
         * @param id -> id of the setting according to the API
         * @param unit -> unit of the setting
         * @param title -> title of the setting. id, Peak Insp. Pressure
         * @param help -> Help text to give the operator information about the setting
         * @param min -> Min value of the setting in unit
         * @param max -> max value of the setting in unit
         * @param step -> Value to increase or decrease by when using the dial
         * @param warningThreshold -> the value past which the system will raise a confirmation popup when the user tries to set the setting that high
         * @param parent -> required for qObjects. Usually a null pointer.
         */
        PneumaticSettings(int setting_id, const QString &unit, const QString &title, const QString &help,
                          int min, int max, int step, int warningThreshold, QObject *parent = nullptr);

        /**
         * @brief Getter for setting unit.
         * @return QString
         */
        QString unit() const;
        /**
         * @brief Getter for setting title.
         * @return QString
         */
        QString title() const;
        /**
         * @brief Getter for setting help information.
         * @return QString
         */
        QString help() const;
        /**
         * @brief Getter for setting min.
         * @return int
         */
        int min() const;
        /**
         * @brief Getter for setting max.
         * @return int
         */
        int max() const;
        /**
         * @brief Getter for setting step.
         * @return int
         */
        int step() const;
        /**
         * @brief Getter for setting id.
         * @return int
         */
        int id() const;
        /**
         * @brief Getter for setting minimum on, the value when minimum is set.
         * @return int
         */
        int minOn() const;
        /**
         * @brief Getter for setting warning threshold.
         * @return int
         */
        int warningThreshold() const;

    signals:
        /**
         * @brief minSignal
         * @callgraph
         */
        void minSignal();
        /**
         * @brief maxSignal
         * @callgraph
         */
        void maxSignal();
        /**
         * @brief unitSignal
         * @callgraph
         */
        void unitSignal();
        /**
         * @brief stepSignal
         * @callgraph
         */
        void stepSignal();
        /**
         * @brief titleSignal
         * @callgraph
         */
        void titleSignal();
        /**
         * @brief idSignal
         * @callgraph
         */
        void idSignal();
        /**
         * @brief minOnSignal
         * @callgraph
         */
        void minOnSignal();
        /**
         * @brief helpSignal
         * @callgraph
         */
        void helpSignal();
        /**
         * @brief warningThresholdSignal
         * @callgraph
         */
        void warningThresholdSignal();

    private:
        int m_id{-1};
        QString m_unit;
        QString m_title;
        int m_min{-1};
        int m_max{-1};
        int m_step{1};
        int m_minOn{m_min};
        int m_warningThreshold = 1;
        QString m_help;
        /** @} */

};

/** @} */

/**
 * @addtogroup settingsModels
 * @{
 */

/**
 * @brief The Driving Pressure class
 */
class DrivingPressure : public PneumaticSettings
{
public:
    /**
     * @brief Constructor for Driving Pressure.
     * @note  You can pass in the id, the title, and the help information and this will need to be done for double jet settings, but for now just id is required.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit DrivingPressure(int setting_id, const QString &title = QStringLiteral("Driving Pressure"),
        const QString &help = QStringLiteral("Driving Pressure indicates the desired pressure to be supplied from the NVENT Vita. This applied pressure increases or decreases respiratory flow causing an effect on TV/MV (i.e. ventilation). The Driving Pressure may be adjusted by the user to achieve better lung recruitment and compensate for lung compliance."));
};

/**
 * @brief The Rate class
 */
class Rate : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Rate.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit Rate(int setting_id, const QString &title = QStringLiteral("Rate"),
        const QString &help = QStringLiteral("The Respiratory Rate setting, measured in Breaths Per Minute (BPM), adjusts the rate at which breaths are supplied to the patient."));
};

/**
 * @brief The InspiratoryTime class
 */
class InspiratoryTime : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Inspiratory Time.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit InspiratoryTime(int setting_id, const QString &title = QStringLiteral("Inspiratory Time"),
                             const QString &help = QStringLiteral("The Inspiratory Time is the percentage of time during the breath cycle in which critical gases are delivered to the patient."));
};

/**
 * @brief The StackingPressure class
 */
class StackingPressure : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Stacking Pressure.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit StackingPressure(int setting_id, const QString &title = QStringLiteral("Stacking Pressure"),
                              const QString &help = QStringLiteral("Stacking Pressure (SP) refers to the residual pressure in the airway as measured through the Blue Jet Line approximately 1 ms prior to each inspiratory phase beginning. This is similar to End Expiratory Pressure (EEP) (i.e. closed system ventilation) in critical care ventilators.<br><br>The VITA  will graphically display the measured Stacking Pressure on the main screen with a blue trace. The Blue graph lines can be hidden for the the Stacking Pressure from within settings. The set limit for SP is represented on the graph with a blue dashed line.<br><br>The operator can set the Stacking Pressure threshold from 1-100 cmH<sub>2</sub>O. The measured value must fall below the set threshold on each breath cycle, indicating that there is adequate egress to the flow of air exiting the patient (i.e. no stacking of breaths). Otherwise, the NVENT Vita immediately alerts the operator and restricts ventilation until the measured Stacking Pressure value drops to 30% of the set Stacking Pressure threshold."));
};

/**
 * @brief The O2 class
 */
class O2 : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for O2.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit O2(int setting_id, const QString &title = QStringLiteral("Oxygen"),
                const QString &help = QStringLiteral("The NVENT Vita is able to proportionally control the concentration of oxygen being delivered to the patient based on desired operator settings.  The NVENT VITA performs an automatic O2 calibration of the oxygen sensor 3 minutes after powering the device on. An automatic secondary O2 calibration will be performed 10 mins after the device is powered on to ensure proper operation. Calibration can also be performed by the user manually, or it will occur automatically once every 24 hours the unit is powered on. The oxygen concentration can be set in 1% increments from  21% to 100%. The Oxygen setpoint will be delivered on both the Jet Line and the Auxiliary Line."));
};

/**
 * @brief The PIP class
 */
class PIP : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for PIP.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit PIP(int setting_id, const QString &title = QStringLiteral("Peak Insp. Pressure"),
                 const QString &help = QStringLiteral("The Peak Inspiratory Pressure (PIP) measures continuously and is the highest pressure measured during the respiratory cycle and is an indication of both the resistance of the airways and the compliance of the patient. This pressure is measured on the Red PIP Line.<br><br>The VITA measures the PIP regularly and graphically displays the waveform measured on the main screen with a Red trace. The set limit for PIP is represented on the graph with a red dashed line.<br><br>The operator can set the PIP threshold from 0-100 cmH<sub>2</sub>O. If the measured PIP value meets the set threshold at any point during a breath cycle, the operator is immediately alerted and the Vita restricts ventilation until the measured PIP value drops to 30% of the set Peak Inspiratory Pressure threshold."));
};

/**
 * @brief The AuxFlow class
 */
class AuxFlow : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for AuxFlow.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit AuxFlow(int setting_id, const QString &title = QStringLiteral("Auxiliary Flow"),
                     const QString &help = QStringLiteral("The NVENT Vita includes an auxiliary flow line used for supplemental gas flow where continuous flow is needed. The flow from the AUX port is delivered at the same O<sub>2</sub>% as the Jet 1. This line can also be supplied with humidity.<br>**Note: This line does not have pressure monitoring capabilities.**"));
};

/**
 * @brief The Humidity class
 */
class Humidity : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Humidity.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit Humidity(int setting_id, const QString &title = QStringLiteral("Humidity"),
                      const QString &help = QStringLiteral("Humidity on the Jet Line or Auxiliary can be controlled in a unified or separated mode by the operator. Humidity should be used whenever jetting time exceeds 30 minutes of continuous use, it is always advantageous to use humidity although not mandatory for shorter procedures. The use of humidity reduces the risk of drying of the tracheal mucosa, it also helps to prevent compliance issues caused by drying of the lungs.  The use of humidity also aids in airway surgery to prevent the tissues from becoming sticky for the surgeon."));
};

/**
 * @brief The ETCO2Rate class
 */
class ETCO2Rate : public PneumaticSettings
{
public:

    /**
     * @brief Constructior for Rate used during ETCO2 procedure.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit ETCO2Rate(int setting_id, const QString &title = QStringLiteral("ETCO<sub>2</sub> Rate"),
                       const QString &help = QStringLiteral("End-tidal CO<sub>2</sub> (ETCO<sub>2</sub>) mode is used when users need to perform an ETCO<sub>2</sub> measurement using an external ETCO<sub>2</sub> monitor. When enabled, the system changes the respiratory rate, inspiratory time, and driving pressure to user-set values which are more representative of natural ventilation. This enables the ability to acquire a more accurate ETCO<sub>2</sub> measurement using an external capnograph."));
};

/**
 * @brief The ETCO2IT class
 */
class ETCO2IT : public PneumaticSettings
{
public:

    /**
     * @brief Constructior for IT used during ETCO2 procedure.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit ETCO2IT(int setting_id, const QString &title = QStringLiteral("ETCO<sub>2</sub> Inspiratory Time"),
                     const QString &help = QStringLiteral("End-tidal CO<sub>2</sub> (ETCO<sub>2</sub>) mode is used when users need to perform an ETCO<sub>2</sub> measurement using an external ETCO<sub>2</sub> monitor. When enabled, the system changes the respiratory rate, inspiratory time, and driving pressure to user-set values which are more representative of natural ventilation. This enables the ability to acquire a more accurate ETCO<sub>2</sub> measurement using an external capnograph."));
};

/**
 * @brief The ETCO2Breaths class
 */
class ETCO2Breaths : public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Number of breaths used during ETCO2.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit ETCO2Breaths(int setting_id, const QString &title = QStringLiteral("ETCO<sub>2</sub> Number of Breaths"),
                          const QString &help = QStringLiteral("End-tidal CO<sub>2</sub> (ETCO<sub>2</sub>) mode is used when users need to perform an ETCO<sub>2</sub> measurement using an external ETCO<sub>2</sub> monitor. When enabled, the system changes the respiratory rate, inspiratory time, and driving pressure to user-set values which are more representative of natural ventilation. This enables the ability to acquire a more accurate ETCO<sub>2</sub> measurement using an external capnograph."));
};

/**
 * @brief The ETCO2DP class
 */
class ETCO2DP : public PneumaticSettings
{
public:

    /**
     * @brief Constructior for DP used during ETCO2 procedure.
     * @note  Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit ETCO2DP(int setting_id, const QString &title = QStringLiteral("ETCO<sub>2</sub> Driving Pressure"),
                     const QString &help = QStringLiteral("End-tidal CO<sub>2</sub> (ETCO<sub>2</sub>) mode is used when users need to perform an ETCO<sub>2</sub> measurement using an external ETCO<sub>2</sub> monitor. When enabled, the system changes the respiratory rate, inspiratory time, and driving pressure to user-set values which are more representative of natural ventilation. This enables the ability to acquire a more accurate ETCO<sub>2</sub> measurement using an external capnograph."));
};

/**
 * @brief The LaserO2 class
 */
class LaserO2: public PneumaticSettings
{
public:

    /**
     * @brief Constructor for LaserO2.
     * @note  Upper O2 threshold while laser-safe mode is active. Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit LaserO2(int setting_id, const QString &title = QStringLiteral("Limted O<sub>2</sub>"),
                     const QString &help = QStringLiteral("Limited O<sub>2</sub> Mode should be activated before any procedure involving a risk of ignition to help prevent airway fires. Limited O<sub>2</sub> Mode restricts the oxygen concentration to a lower user-set limit, to not exceed 40% O<sub>2</sub>."));
};

/**
 * @brief The Volume class
 */
class Volume: public PneumaticSettings
{
public:

    /**
     * @brief Constructor for Volume.
     * @note  Volume of auditory alarm. Only id is required to pass in.
     * @param setting_id
     * @param title
     * @param help
     */
    explicit Volume(int setting_id, const QString &title = QStringLiteral("Volume"),
                       const QString &help = QStringLiteral("The sound icon will create an additional audible warning when an alarm is active."));
};

/** @} */
