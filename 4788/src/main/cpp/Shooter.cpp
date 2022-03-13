#include "Shooter.h"
#include <iostream>
#include "frc/RobotController.h"

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup), _filterPos(wml::control::LinearFilter::MovingAverage(20)), _filterVel((wml::control::LinearFilter::MovingAverage(20))) {

}

void Shooter::setManual(double voltage) {
  _flyWheelVoltage = voltage;
  _state = ShooterState::kManual;
}

void Shooter::setPID(double goal, double dt) {
  if (_state != ShooterState::kPID) {
    _flyWheelVoltage = 0;
    _sum = 0;
    _previousError = 0;
    _iterations = 0;
  }
  _state = ShooterState::kPID;
  _angularVelocityGoal = goal;
}

void Shooter::updateShooter(double dt) {
  auto shooterInst = nt::NetworkTableInstance::GetDefault();
  auto shooterSystem = shooterInst.GetTable("shooterSystem");

  nt::NetworkTableInstance::GetDefault().GetTable("shooterSystem")->GetEntry("State").SetString(shooter_state_to_string(_state));

  switch (_state) {
  case ShooterState::kManual:
    break;

  case ShooterState::kIdle:
    _flyWheelVoltage = 0;
    break;

  case ShooterState::kPID:
    _flyWheelVoltage = calculatePID(_angularVelocityGoal, dt);
    break;

  case ShooterState::kRaw:
    manualOutput = -_rawPower;
  break;

  default:
    _state = ShooterState::kIdle;
    std::cout << "in default case, somthing is wrong" << std::endl;
    break;
  }

  if (_state != ShooterState::kRaw) {
    double angularVel = -_shooterSystem.shooterGearbox.encoder->GetEncoderAngularVelocity();
    auto &motor = _shooterSystem.shooterGearbox.motor;
    double Vmax = ControlMap::ShooterGains::IMax * motor.R() + motor.kw() * angularVel;
    double Vmin = -(ControlMap::ShooterGains::IMax) * motor.R() + motor.kw() * angularVel;
    manualOutput = std::min(_flyWheelVoltage, Vmax);
  }

  nt::NetworkTableInstance::GetDefault().GetTable("shooter gains")->GetEntry("Vout").SetDouble(manualOutput);
  nt::NetworkTableInstance::GetDefault().GetTable("shooter gains")->GetEntry("isDone").SetBoolean(isDone());

  _shooterSystem.shooterGearbox.transmission->SetVoltage(manualOutput);
}


void Shooter::Update(double dt) {
  updateShooter(dt);
}


double Shooter::calculatePID(double angularVelocity, double dt) {
  double input = -(_shooterSystem.shooterGearbox.encoder->GetEncoderAngularVelocity());
  double error = angularVelocity - input;
  double derror = (error - _previousError) / dt;
  _sum += error * dt;

  auto &motor = _shooterSystem.shooterGearbox.motor;
  double output = ControlMap::ShooterGains::kp * error + ControlMap::ShooterGains::ki * _sum + (ControlMap::ShooterGains::kd) * derror +  motor.kw() * angularVelocity;

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("shooter gains");

  _avgPos = _filterPos.Get(error);
  _avgVel = _filterVel.Get(derror);

  table->GetEntry("input").SetDouble(input);
  table->GetEntry("output").SetDouble(output);
  table->GetEntry("goal").SetDouble(angularVelocity);
  table->GetEntry("error").SetDouble(error);

  table->GetEntry("P").SetDouble(ControlMap::ShooterGains::kp * error);
  table->GetEntry("I").SetDouble(ControlMap::ShooterGains::ki * _sum);
  table->GetEntry("D").SetDouble(ControlMap::ShooterGains::kd * derror);

  table->GetEntry("avg_pos").SetDouble(_avgPos);
  table->GetEntry("avg_vel").SetDouble(_avgVel);

  _previousError = error;
  _iterations ++;
  return output;
}

void Shooter::SetIsDoneThreshold(double threshAvgPos, double threshAvgVel) {
  _threshAvgPos = threshAvgPos;
  _threshAvgVel = threshAvgVel;
}

bool Shooter::isDone() {
  return _state == ShooterState::kPID && _iterations > 20 && std::abs(_avgPos) < _threshAvgPos && std::abs(_avgVel) < _threshAvgVel;
}


void Shooter::GetOut(double dt, double power) {
  _state = ShooterState::kRaw;
  _rawPower = power;
}

ShooterState Shooter::getShooterState() {
  return _state;
}