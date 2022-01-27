#include "Drivebase.h"

using namespace wml;
using namespace wml::controllers;

DrivebaseManual::DrivebaseManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void DrivebaseManual::OnUpdate(double dt) {
  if(fabs(_contGroup.GetController(1).Get(ControlMap::drivebaseL) >= ControlMap::xboxDeadzone)) {
    _leftPower = _contGroup.GetController(1).Get(ControlMap::drivebaseL);
    std::cout << "Left drive" << std::endl;
  }

  if(fabs(_contGroup.GetController(1).Get(ControlMap::drivebaseR)) >= ControlMap::xboxDeadzone) {
    _rightPower = _contGroup.GetController(1).Get(ControlMap::drivebaseR);
    std::cout << "right drive" << std::endl;
  }

  _leftPower *= 0.5;
  _rightPower *= 0.5;

  _drivetrain.Set(_leftPower, _rightPower);
}