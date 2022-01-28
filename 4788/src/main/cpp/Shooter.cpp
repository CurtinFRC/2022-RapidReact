#include "Shooter.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {}

void Shooter::teleopOnUpdate(double dt) {
  double shooterSpeed = fabs(_contGroup.GetController(1).Get(ControlMap::ShooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::ShooterManualSpin) : 0;

  _shooterSystem.leftFlyWheelMotor.Set(shooterSpeed);
  _shooterSystem.rightFlyWheelMotor.Set(shooterSpeed);
  _shooterSystem.centerFlyWheelMotor.Set(shooterSpeed);

  double indexSpeed = fabs(_contGroup.GetController(1).Get(ControlMap::IndexSpin)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::IndexSpin) : 0;
  _shooterSystem.indexWheel.Set(indexSpeed);
}