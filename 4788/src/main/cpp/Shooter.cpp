#include "Shooter.h"
#include <iostream>
#include "frc/RobotController.h"

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {}

void Shooter::setManual(double voltage) {
  setFlyWheelVoltage = voltage;
  _state = ShooterState::kManual;
}

void Shooter::setIndex(double power) {
  setIndexVoltage = power;
}

void Shooter::setPID(double goal, double dt) {
  _state = ShooterState::kPID;
  angularVelocityGoal = goal;
}

void Shooter::updateShooter(double dt) {
  double pidSetPower = calculatePID(angularVelocityGoal, dt);


  switch (_state) {
  case ShooterState::kManual:
    _shooterSystem.shooterGearbox.transmission->SetVoltage(setFlyWheelVoltage * 12);

    _shooterSystem.indexWheel.Set(setIndexVoltage);

    break;

  case ShooterState::kIdle:

    _shooterSystem.indexWheel.Set(setIndexVoltage);
    _shooterSystem.shooterGearbox.transmission->SetVoltage(0);

    break;

  case ShooterState::kPID:
    _shooterSystem.indexWheel.Set(setIndexVoltage);

    _shooterSystem.shooterGearbox.transmission->SetVoltage(pidSetPower * 12);
    std::cout << "shooter speed" << _shooterSystem.rightFlyWheelMotor.GetEncoderAngularVelocity() << std::endl; 
    break;

  default:
    std::cout << "in default case, somthing is wrong" << std::endl;
    break;
  }
}

void Shooter::update(double dt) {
  updateShooter(dt);
}


double sum = 0;
double previousError = 0;
double Shooter::calculatePID(double angularVelocity, double dt) {
  std::cout << "goal: " << angularVelocityGoal << std::endl;
  double input = (_shooterSystem.leftFlyWheelMotor.GetEncoderAngularVelocity());
  std::cout << "angular velocity" << input << std::endl;
  double error = angularVelocityGoal - input;
  double derror = (error - previousError) / dt;
  sum += error * dt;

  double output = ControlMap::kp * error + ControlMap::ki * sum + (ControlMap::kd) * derror;
  std::cout << "P Value: " << ControlMap::kp << std::endl;

  auto &motor = _shooterSystem.shooterGearbox.motor;
  double Vmax = ControlMap::IMax * motor.R() + motor.kw() * input;
  double Vmin = -(ControlMap::IMax) * motor.R() + motor.kw() * input;

  output = std::min(std::max(output, Vmin), Vmax);

  previousError = error;

  std::cout << "error: " << error << std::endl;
  std::cout << "Output: " << output*12 << std::endl;
  // std::cout << "DT: " << dt << std::endl;
  return output;
}
