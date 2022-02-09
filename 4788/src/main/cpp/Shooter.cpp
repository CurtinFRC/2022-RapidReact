#include "Shooter.h"
#include <iostream>
#include "frc/RobotController.h"

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {
  ControlMap::shooterPID = false;
}

void Shooter::setFlywheel(double power) {
  _teleopShooter = TeleopShooter::kManual;
  setFlyWheelPower = power;
}

void Shooter::setIndex(double power) {
  setIndexPower = power;
}

void Shooter::setAuto(double goal, double dt) {
  pidShooterSpeed = speed(flyWheelGoal, dt);
  _teleopShooter = TeleopShooter::kAuto;
  flyWheelGoal = goal;
  //call the PID loop
}

void Shooter::updateShooter(double dt) {

  switch (_teleopShooter) {
  case TeleopShooter::kManual:
    _shooterSystem.shooterGearbox.transmission->SetVoltage(setFlyWheelPower * 12);

    _shooterSystem.indexWheel.Set(setIndexPower);
    std::cout << "index speed" << setIndexPower << std::endl;


    break;

  case TeleopShooter::kIdle:

    _shooterSystem.indexWheel.Set(setIndexPower);


    break;

  case TeleopShooter::kTesting:

  

    break;

  case TeleopShooter::kAuto:
    _shooterSystem.indexWheel.Set(setIndexPower);

    _shooterSystem.shooterGearbox.transmission->SetVoltage(pidShooterSpeed);
    std::cout << "shooter speed" << _shooterSystem.rightFlyWheelMotor.GetEncoderAngularVelocity() << std::endl; 
    break;

  default:
    break;
  }
}

void Shooter::update(double dt) {
  updateShooter(dt);
}


double sum = 0;
double previousError = 0;
double previousOutput = 0;
double Shooter::speed(double goal, double dt) {
  std::cout << "goal: " << goal << std::endl;
  double input = (_shooterSystem.leftFlyWheelMotor.GetEncoderAngularVelocity());
  std::cout << "angular velocity" << input << std::endl;
  // std::cout << "radians per second" << input << std::endl;
  double error = goal - input;
  double derror = (error - previousError) / dt;
  sum += error * dt;

  double output = ControlMap::kp * error + ControlMap::ki * sum + (ControlMap::kd) * derror;
  std::cout << "P Value: " << ControlMap::kp << std::endl;

  auto &motor = _shooterSystem.shooterGearbox.motor;
  double Vmax = ControlMap::IMax * motor.R() + motor.kw() * input;
  double Vmin = -(ControlMap::IMax) * motor.R() + motor.kw() * input;

  output = std::min(std::max(output, Vmin), Vmax);

  previousError = error;
  previousOutput = output;

  std::cout << "error: " << error << std::endl;
  std::cout << "Output: " << output*12 << std::endl;
  // std::cout << "DT: " << dt << std::endl;
  return output;
}