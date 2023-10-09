#include "warnings.h"

Warning::Warning()
{

}

Warning::Warning(const int id, const QVector<QString> troubleshooting_steps, const QString title, const int warning_class, const QString desc, const unsigned char clearingBehavior, QString color, QString clearText)
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

PatientWarning::PatientWarning(const int &id, const QString &title, const QVector<QString> &troubleshooting_steps, unsigned char clearingBehavior, QString color)
    :Warning(id, troubleshooting_steps, title, 0, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

SystemWarning::SystemWarning(const int &id, const QString &title, const QVector<QString> &troubleshooting_steps, unsigned char clearingBehavior, QString color)
    :Warning(id, troubleshooting_steps, title, 1, QStringLiteral("Alert!"), clearingBehavior, color)
{
}

Notice::Notice(const int &id, const QString &title, const QVector<QString> &troubleshooting_steps, unsigned char clearingBehavior, QString color)
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

void Warning::setClearText(QString text)
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

StackingPressureHigh::StackingPressureHigh(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPHigh::PIPHigh(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPDisconnected::PIPDisconnected(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoWaterJet::NoWaterJet(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText("PRIME");
}

NoWaterAux::NoWaterAux(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText("PRIME");
}

NoWaterPrime::NoWaterPrime(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    PatientWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{
    setClearText("PRIME");
}

JetSwitchError::JetSwitchError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

StackingPressureSensorDefective::StackingPressureSensorDefective(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureSensorDefectiveDouble::StackingPressureSensorDefectiveDouble(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

StackingPressureDisconnected::StackingPressureDisconnected(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

InappropriateOxygenSensor::InappropriateOxygenSensor(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxSwitchError::AuxSwitchError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxProportionalValveError::AuxProportionalValveError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxFlowSensorError::AuxFlowSensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveError::AirProportionalValveError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirProportionalValveErrorNoLaser::AirProportionalValveErrorNoLaser(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2ProportionalValveError::O2ProportionalValveError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorError::AirInletPressureSensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AirInletPressureSensorErrorNoLaser::AirInletPressureSensorErrorNoLaser(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2InletPressureSensorError::O2InletPressureSensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupply::LowAirSupply(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowAirSupplyNoLaser::LowAirSupplyNoLaser(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LowOxygenSupply::LowOxygenSupply(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

SpeakerDefect::SpeakerDefect(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

HeaterFailure::HeaterFailure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

TemperatureMeasuringError::TemperatureMeasuringError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetFlowSensorError::JetFlowSensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetHumiditySensorError::JetHumiditySensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxHumiditySensorError::AuxHumiditySensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

RTCError::RTCError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ExhaustFanError::ExhaustFanError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DrivingPressureRegulatorError::DrivingPressureRegulatorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

PIPSensorError::PIPSensorError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

FiO2Failure::FiO2Failure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

O2CalFailure::O2CalFailure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

NoComm::NoComm(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterPumpError::AuxWaterPumpError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterPumpError::JetWaterPumpError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

DehumidificationFailed::DehumidificationFailed(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

FlashError::FlashError(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BreathTimingFailure::BreathTimingFailure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

JetWaterSensorFailure::JetWaterSensorFailure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AuxWaterSensorFailure::AuxWaterSensorFailure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

AmbientTempSensorDefect::AmbientTempSensorDefect(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    SystemWarning(id, title, troubleshooting_steps, CLEAR_AFTER_RESOLVED)
{

}

LaserOK::LaserOK(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY, QStringLiteral("#6FCC68"))
{

}

LaserPrepping::LaserPrepping(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticAirPressure::LowStaticAirPressure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

LowStaticO2Pressure::LowStaticO2Pressure(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

InternalTempHigh::InternalTempHigh(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ManualModePIPMonitoringRecommended::ManualModePIPMonitoringRecommended(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PIPMonitoringRecommended::PIPMonitoringRecommended(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

ETCO2Active::ETCO2Active(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

ServiceDue::ServiceDue(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

BatteryReplacement::BatteryReplacement(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

HeaterHumidiferOff::HeaterHumidiferOff(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidificationDeactivated::HumidificationDeactivated(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

JetHumidificationOff::JetHumidificationOff(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxHumidificationOff::AuxHumidificationOff(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

AuxFlowDeactivated::AuxFlowDeactivated(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

DistilledWater::DistilledWater(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

PumpsPriming::PumpsPriming(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

HumidityReminder::HumidityReminder(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_ON_DEMAND)
{

}

O2CalInProgress::O2CalInProgress(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}

O2CalInProgressNoLaser::O2CalInProgressNoLaser(const int &id, const QVector<QString> &troubleshooting_steps, const QString &title) :
    Notice(id, title, troubleshooting_steps, CLEAR_AUTONOMOUSLY)
{

}




