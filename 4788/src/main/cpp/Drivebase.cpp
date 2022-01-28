#include "Drivebase.h"

using namespace wml;
using namespace wml::controllers;

DrivetrainManual::DrivetrainManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void DrivetrainManual::OnUpdate(double dt) {
  double leftPower = fabs(_contGroup.GetController(0).Get(ControlMap::drivebaseL)) > ControlMap::triggerDeadzone ? _contGroup.GetController(0).Get(ControlMap::drivebaseL) : 0;
  double rightPower = fabs(_contGroup.GetController(0).Get(ControlMap::drivebaseR)) > ControlMap::triggerDeadzone ? _contGroup.GetController(0).Get(ControlMap::drivebaseR) : 0;

  leftPower *= ControlMap::maxDrivetrainPower;
  rightPower *= ControlMap::maxDrivetrainPower;

  // std::cout << leftPower << std::endl;
  _drivetrain.Set(leftPower, rightPower);
}