#ifndef sensors
#define sensors

/**
 * @addtogroup measuredModels
 * @{
 */

/**
 * @file sensors.h
 * @brief The enumeration and constant values for measured and sensor values.
 */

/**
 * @brief Number of calibrated procedures.
 */
constexpr int NUM_OBP_SENSORS = 5;

/**
 * @brief Number of measurements on the system.
 */
constexpr int NUM_MEASURED_SENSORS = 40;

/**
 * @brief Number of sensors tracked.
 */
constexpr int NUM_ZERO_SENSORS = 3;

/**
 * @brief Number of DPR Calibration states.
 */
constexpr int NUM_HIGH_LOW_SENSORS = 2;

#include <QObject>
#include <QtQml/QQmlEngine>

//Used for zeroing on board pressure sensors
/**
 * @brief The enumerations for sensor values.
 */
enum class OBPSIDs
{
    ZERO_PIP = 0,
    ZERO_STACKING_PRESSURE_1 = 1,
    ZERO_STACKING_PRESSURE_2= 2,
    ZERO_INLET_AIR = 3,
    ZERO_INLET_O2 = 4
};

//Used for getting measurements. Especially the water sensor measurements to see if there is water sensed in the system and getting O2 cal vals
/**
 * @brief The enumeration for measurements.
 * @details The water sensor measurements are especially used to see if there is water sensed in the system.
 *          The O2 Calibration values are especially used as well.
 */
enum class MeasuredIDs
{
    DRIVING_PRESSURE_1 = 0,
    DRIVING_PRESSURE_2 = 1,
    RATE_1 = 2,
    RATE_2 = 3,
    INSPIRATORY_TIME_1 = 4,
    INSPIRATORY_TIME_2 = 5,
    STACKING_PRESSURE_1 = 6,
    STACKING_PRESSURE_2 = 7,
    OXYGEN = 8,
    PIP = 9,
    AUX = 10,
    HUM_1 = 11,
    HUM_2 = 12,
    HUM_AUX = 13,
    HEATER_TEMP = 14,
    AVG_FLOW_1 = 15,
    AVG_FLOW_2 = 16,
    WATER_SENSOR_1 = 17,
    WATER_SENSOR_2 = 18,
    WATER_SENSOR_AUX = 19,
    TV_1 = 20,
    TV_2 = 21,
    MAP = 22,
    INLET_AIR_PRESSURE = 23,
    INLET_O2_PRESSURE = 24,
    PIP_ZERO_VAL = 25,
    STACKING_PRESSURE_ZERO_VAL_1 = 26,
    STACKING_PRESSURE_ZERO_VAL_2 = 27,
    INLET_AIR_ZERO_VAL = 28,
    INLET_O2_ZERO_VAL = 29,
    O2_LOWER_CAL_VAL = 30,
    O2_UPPER_CAL_VAL = 31,
    O2_LOWER_BOUND = 32,
    O2_UPPER_BOUND = 33,
    REAL_CAL_VAL = 34,
    REAL_DPR_VAL = 35,
    SP_AVG = 36,
    SP_INST = 37,
    PIP_AVG = 38,
    PIP_INST = 39
};

//Used to connect the above enums with the QML
/**
 * @brief The SensorIDs class
 */
class SensorIDs : public QObject
{
    /**
     * @addtogroup measuredModels
     * @{
     */

    Q_OBJECT
    public:
        /**
         * @brief Empty Constructor
         * @param parent
         */
        SensorIDs(QObject *parent=nullptr) : QObject(parent){}

        /**
         * @brief The enumerations for sensor values on QML files.
         */
        enum OBPS
        {
            ZERO_PIP = (int)OBPSIDs::ZERO_PIP,
            ZERO_STACKING_PRESSURE_1 = (int)OBPSIDs::ZERO_STACKING_PRESSURE_1,
            ZERO_STACKING_PRESSURE_2= (int)OBPSIDs::ZERO_STACKING_PRESSURE_2,
            ZERO_INLET_AIR = (int)OBPSIDs::ZERO_INLET_AIR,
            ZERO_INLET_O2 = (int)OBPSIDs::ZERO_INLET_O2

        };

        /**
         * @brief The enumerations for measurements on QML files.
         */
        enum Measured
        {
            DRIVING_PRESSURE_1 = (int)MeasuredIDs::DRIVING_PRESSURE_1,
            DRIVING_PRESSURE_2 = (int)MeasuredIDs::DRIVING_PRESSURE_2,
            RATE_1 = (int)MeasuredIDs::RATE_1,
            RATE_2 = (int)MeasuredIDs::RATE_2,
            INSPIRATORY_TIME_1 = (int)MeasuredIDs::INSPIRATORY_TIME_1,
            INSPIRATORY_TIME_2 = (int)MeasuredIDs::INSPIRATORY_TIME_2,
            STACKING_PRESSURE_1 = (int)MeasuredIDs::STACKING_PRESSURE_1,
            STACKING_PRESSURE_2 = (int)MeasuredIDs::STACKING_PRESSURE_2,
            OXYGEN = (int)MeasuredIDs::OXYGEN,
            PIP = (int)MeasuredIDs::DRIVING_PRESSURE_1,
            AUX = (int)MeasuredIDs::AUX,
            HUM_1 = (int)MeasuredIDs::HUM_1,
            HUM_2 = (int)MeasuredIDs::HUM_2,
            HUM_AUX = (int)MeasuredIDs::HUM_AUX,
            HEATER_TEMP = (int)MeasuredIDs::HEATER_TEMP,
            AVG_FLOW_1 = (int)MeasuredIDs::AVG_FLOW_1,
            AVG_FLOW_2 = (int)MeasuredIDs::AVG_FLOW_2,
            WATER_SENSOR_1 = (int)MeasuredIDs::WATER_SENSOR_1,
            WATER_SENSOR_2 = (int)MeasuredIDs::WATER_SENSOR_2,
            WATER_SENSOR_AUX = (int)MeasuredIDs::WATER_SENSOR_AUX,
            TV_1 = (int)MeasuredIDs::TV_1,
            TV_2 = (int)MeasuredIDs::TV_2,
            MAP = (int)MeasuredIDs::MAP,
            INLET_AIR_PRESSURE = (int)MeasuredIDs::INLET_AIR_PRESSURE,
            INLET_O2_PRESSURE = (int)MeasuredIDs::INLET_O2_PRESSURE,
            PIP_ZERO_VAL = (int)MeasuredIDs::PIP_ZERO_VAL,
            STACKING_PRESSURE_ZERO_VAL_1 = (int)MeasuredIDs::STACKING_PRESSURE_ZERO_VAL_1,
            STACKING_PRESSURE_ZERO_VAL_2 = (int)MeasuredIDs::STACKING_PRESSURE_ZERO_VAL_2,
            INLET_AIR_ZERO_VAL = (int)MeasuredIDs::INLET_AIR_ZERO_VAL,
            INLET_O2_ZERO_VAL = (int)MeasuredIDs::INLET_O2_PRESSURE,
            O2_LOWER_CAL_VAL = (int)MeasuredIDs::O2_LOWER_CAL_VAL,
            O2_UPPER_CAL_VAL = (int)MeasuredIDs::O2_UPPER_CAL_VAL,
            O2_LOWER_BOUND = (int)MeasuredIDs::O2_LOWER_BOUND,
            O2_UPPER_BOUND = (int)MeasuredIDs::O2_UPPER_BOUND,
            REAL_CAL_VAL = (int)MeasuredIDs::REAL_CAL_VAL,
            REAL_DPR_VAL = (int)MeasuredIDs::REAL_DPR_VAL,
            SP_AVG = (int)MeasuredIDs::SP_AVG,
            SP_INST = (int)MeasuredIDs::SP_INST,
            PIP_AVG = (int)MeasuredIDs::PIP_AVG,
            PIP_INST = (int)MeasuredIDs::PIP_INST

        };

        Q_ENUM(OBPS)
        Q_ENUM(Measured)

        /**
         * @brief Declares QML variables for measurements.
         */
        static void declareQML()
        {
            qmlRegisterType<SensorIDs>("SensorID", 1, 0, "SensorID");
        }
        /** @} */

};

/** @} */

#endif
