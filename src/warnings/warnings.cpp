#include "warnings.h"


Warning::Warning(
        const int warning_id,
        const QVector<QString> &troubleshooting_steps,
        const QString &title,
        const int warning_class,
        const QString &desc,
        const unsigned char
        clearingBehavior,
        const QString &color,
        const QString &clearText)
    :
      m_id(warning_id),
      m_title(QString(title)),
      m_warning_class(warning_class),
      m_desc(QString(desc)),
      m_troubleshooting_steps(troubleshooting_steps),
      m_clearingBehavior(clearingBehavior),
      m_color(QString(color)),
      m_clear(QString(clearText))
{
}

PatientWarning::PatientWarning(
        int warning_id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(warning_id, troubleshooting_steps, title, 0, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

SystemWarning::SystemWarning(
        int warning_id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(warning_id, troubleshooting_steps, title, 1, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

Notice::Notice(
        int warning_id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(warning_id, troubleshooting_steps, title, 2, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

auto Warning::id() const -> int
{
    return m_id;
}

auto Warning::title() const -> QString
{
    return m_title;
}

auto Warning::warningClass() const -> int
{
    return m_warning_class;
}

auto Warning::description() const -> QString
{
    return m_desc;
}

auto Warning::clearText() const -> QString
{
    return m_clear;
}

void Warning::setClearText(const QString &text)
{
    m_clear = text;
}

auto Warning::troubleshootingSteps() const -> QVector<QString>
{
    return m_troubleshooting_steps;
}

auto Warning::clearingBehavior() const -> unsigned char
{
    return m_clearingBehavior;
}

auto Warning::color() const -> QString
{
    return m_color;
}

/*~Following are all of the specific warnings. All fields are filled except the ID, meaning to instantiate them, one must only call the constructor and pass the ID~*/

StackingPressureHigh::StackingPressureHigh(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPHigh::PIPHigh(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPDisconnected::PIPDisconnected(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoWaterJet::NoWaterJet(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

NoWaterAux::NoWaterAux(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

NoWaterPrime::NoWaterPrime(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

JetSwitchError::JetSwitchError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

StackingPressureSensorDefective::StackingPressureSensorDefective(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureSensorDefectiveDouble::StackingPressureSensorDefectiveDouble(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureDisconnected::StackingPressureDisconnected(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

InappropriateOxygenSensor::InappropriateOxygenSensor(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxSwitchError::AuxSwitchError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxProportionalValveError::AuxProportionalValveError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxFlowSensorError::AuxFlowSensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveError::AirProportionalValveError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveErrorNoLaser::AirProportionalValveErrorNoLaser(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2ProportionalValveError::O2ProportionalValveError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorError::AirInletPressureSensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorErrorNoLaser::AirInletPressureSensorErrorNoLaser(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2InletPressureSensorError::O2InletPressureSensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupply::LowAirSupply(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupplyNoLaser::LowAirSupplyNoLaser(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowOxygenSupply::LowOxygenSupply(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

SpeakerDefect::SpeakerDefect(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

HeaterFailure::HeaterFailure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

TemperatureMeasuringError::TemperatureMeasuringError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetFlowSensorError::JetFlowSensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetHumiditySensorError::JetHumiditySensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxHumiditySensorError::AuxHumiditySensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

RTCError::RTCError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ExhaustFanError::ExhaustFanError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DrivingPressureRegulatorError::DrivingPressureRegulatorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPSensorError::PIPSensorError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

FiO2Failure::FiO2Failure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2CalFailure::O2CalFailure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoComm::NoComm(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterPumpError::AuxWaterPumpError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterPumpError::JetWaterPumpError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DehumidificationFailed::DehumidificationFailed(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

FlashError::FlashError(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BreathTimingFailure::BreathTimingFailure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterSensorFailure::JetWaterSensorFailure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterSensorFailure::AuxWaterSensorFailure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AmbientTempSensorDefect::AmbientTempSensorDefect(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

InternalTempHigh::InternalTempHigh(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(warning_id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LaserOK::LaserOK(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY, QStringLiteral("#6FCC68"))
{

}

LaserPrepping::LaserPrepping(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticAirPressure::LowStaticAirPressure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticO2Pressure::LowStaticO2Pressure(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ManualModePIPMonitoringRecommended::ManualModePIPMonitoringRecommended(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PIPMonitoringRecommended::PIPMonitoringRecommended(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ETCO2Active::ETCO2Active(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ServiceDue::ServiceDue(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BatteryReplacement::BatteryReplacement(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

HeaterHumidiferOff::HeaterHumidiferOff(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidificationDeactivated::HumidificationDeactivated(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

JetHumidificationOff::JetHumidificationOff(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxHumidificationOff::AuxHumidificationOff(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxFlowDeactivated::AuxFlowDeactivated(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

DistilledWater::DistilledWater(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PumpsPriming::PumpsPriming(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidityReminder::HumidityReminder(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

O2CalInProgress::O2CalInProgress(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

O2CalInProgressNoLaser::O2CalInProgressNoLaser(int warning_id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(warning_id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}




