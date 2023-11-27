#include "warnings.h"

Warning::Warning()
{

}

Warning::Warning(
        const int id,
        const QVector<QString> &troubleshooting_steps,
        const QString &title,
        const int warning_class,
        const QString &desc,
        const unsigned char
        clearingBehavior,
        const QString &color,
        const QString &clearText)
    :
      m_id(id),
      m_title(title),
      m_warning_class(warning_class),
      m_desc(desc),
      m_troubleshooting_steps(troubleshooting_steps),
      m_clearingBehavior(clearingBehavior),
      m_color(color),
      m_clear(clearText)
{
}

PatientWarning::PatientWarning(
        int id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(id, troubleshooting_steps, title, 0, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

SystemWarning::SystemWarning(
        int id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(id, troubleshooting_steps, title, 1, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

Notice::Notice(
        int id,
        const QString &title,
        const QVector<QString> &troubleshooting_steps,
        unsigned char clearingBehavior,
        const QString &color)
    :Warning(id, troubleshooting_steps, title, 2, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

int Warning::id() const
{
    return m_id;
}

QString Warning::title() const
{
    return m_title;
}

int Warning::warningClass() const
{
    return m_warning_class;
}

QString Warning::description() const
{
    return m_desc;
}

QString Warning::clearText() const
{
    return m_clear;
}

void Warning::setClearText(const QString &text)
{
    m_clear = text;
}

QVector<QString> Warning::troubleshootingSteps() const
{
    return m_troubleshooting_steps;
}

unsigned char Warning::clearingBehavior() const
{
    return m_clearingBehavior;
}

QString Warning::color() const
{
    return m_color;
}

/*~Following are all of the specific warnings. All fields are filled except the ID, meaning to instantiate them, one must only call the constructor and pass the ID~*/

StackingPressureHigh::StackingPressureHigh(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPHigh::PIPHigh(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPDisconnected::PIPDisconnected(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoWaterJet::NoWaterJet(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

NoWaterAux::NoWaterAux(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

NoWaterPrime::NoWaterPrime(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText(QStringLiteral("PRIME"));
}

JetSwitchError::JetSwitchError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

StackingPressureSensorDefective::StackingPressureSensorDefective(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureSensorDefectiveDouble::StackingPressureSensorDefectiveDouble(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureDisconnected::StackingPressureDisconnected(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

InappropriateOxygenSensor::InappropriateOxygenSensor(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxSwitchError::AuxSwitchError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxProportionalValveError::AuxProportionalValveError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxFlowSensorError::AuxFlowSensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveError::AirProportionalValveError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveErrorNoLaser::AirProportionalValveErrorNoLaser(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2ProportionalValveError::O2ProportionalValveError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorError::AirInletPressureSensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorErrorNoLaser::AirInletPressureSensorErrorNoLaser(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2InletPressureSensorError::O2InletPressureSensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupply::LowAirSupply(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupplyNoLaser::LowAirSupplyNoLaser(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowOxygenSupply::LowOxygenSupply(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

SpeakerDefect::SpeakerDefect(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

HeaterFailure::HeaterFailure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

TemperatureMeasuringError::TemperatureMeasuringError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetFlowSensorError::JetFlowSensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetHumiditySensorError::JetHumiditySensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxHumiditySensorError::AuxHumiditySensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

RTCError::RTCError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ExhaustFanError::ExhaustFanError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DrivingPressureRegulatorError::DrivingPressureRegulatorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPSensorError::PIPSensorError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

FiO2Failure::FiO2Failure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2CalFailure::O2CalFailure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoComm::NoComm(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterPumpError::AuxWaterPumpError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterPumpError::JetWaterPumpError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DehumidificationFailed::DehumidificationFailed(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

FlashError::FlashError(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BreathTimingFailure::BreathTimingFailure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterSensorFailure::JetWaterSensorFailure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterSensorFailure::AuxWaterSensorFailure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AmbientTempSensorDefect::AmbientTempSensorDefect(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

InternalTempHigh::InternalTempHigh(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LaserOK::LaserOK(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY, QStringLiteral("#6FCC68"))
{

}

LaserPrepping::LaserPrepping(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticAirPressure::LowStaticAirPressure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticO2Pressure::LowStaticO2Pressure(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ManualModePIPMonitoringRecommended::ManualModePIPMonitoringRecommended(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PIPMonitoringRecommended::PIPMonitoringRecommended(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ETCO2Active::ETCO2Active(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ServiceDue::ServiceDue(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BatteryReplacement::BatteryReplacement(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

HeaterHumidiferOff::HeaterHumidiferOff(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidificationDeactivated::HumidificationDeactivated(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

JetHumidificationOff::JetHumidificationOff(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxHumidificationOff::AuxHumidificationOff(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxFlowDeactivated::AuxFlowDeactivated(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

DistilledWater::DistilledWater(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PumpsPriming::PumpsPriming(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidityReminder::HumidityReminder(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

O2CalInProgress::O2CalInProgress(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

O2CalInProgressNoLaser::O2CalInProgressNoLaser(int id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}




