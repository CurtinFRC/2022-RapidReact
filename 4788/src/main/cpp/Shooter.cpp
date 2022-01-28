#include "Shooter.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {}

void Shooter::teleopOnUpdate(double dt) {
  // double shooterSpeed = fabs(_contGroup.GetController(1).Get(ControlMap::ShooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::ShooterManualSpin) : 0;
  double shooterSpeed = fabs(_contGroup.Get(ControlMap::ShooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::ShooterManualSpin) : 0;

  shooterSpeed *= ControlMap::shooterMaxSpeed;

  // if (_contGroup.GetController(1).Get(ControlMap::ShooterSlow)) {
  //   ControlMap::shooterMaxSpeed = 0.25;
  // }
  // if (_contGroup.GetController(1).Get(ControlMap::ShooterMid)) {
  //   ControlMap::shooterMaxSpeed = 0.5;
  // }
  // if (_contGroup.GetController(1).Get(ControlMap::ShooterSpeedChange)) {
  //   ControlMap::shooterMaxSpeed = 0.75;
  // }
  // if (_contGroup.GetController(1).Get(ControlMap::ShooterHighSpeed)) {
  //   ControlMap::shooterMaxSpeed = 1;
  // }

  if (_contGroup.Get(ControlMap::ShooterSlow)) {
    ControlMap::shooterMaxSpeed = 0.25;
  }
  if (_contGroup.Get(ControlMap::ShooterMid)) {
    ControlMap::shooterMaxSpeed = 0.5;
  }
  if (_contGroup.Get(ControlMap::ShooterSpeedChange)) {
    ControlMap::shooterMaxSpeed = 0.75;
  }
  if (_contGroup.Get(ControlMap::ShooterHighSpeed)) {
    ControlMap::shooterMaxSpeed = 1;
  }

  std::cout << ControlMap::shooterMaxSpeed << std::endl;

  _shooterSystem.leftFlyWheelMotor.Set(shooterSpeed);
  _shooterSystem.rightFlyWheelMotor.Set(shooterSpeed);
  _shooterSystem.centerFlyWheelMotor.Set(shooterSpeed);

  // double indexSpeed = fabs(_contGroup.GetController(1).Get(ControlMap::IndexSpin)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::IndexSpin) : 0;
  double indexSpeed = fabs(_contGroup.Get(ControlMap::IndexSpin)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::IndexSpin) : 0;
  _shooterSystem.indexWheel.Set(indexSpeed);
}

//GET PEOPLE ASSEMBLING 