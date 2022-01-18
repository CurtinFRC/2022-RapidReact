#include "Drivebase.h"

using namespace wml;
using namespace wml::controllers;

Drivebase::Drivebase(RobotMap::DrivebaseSystem &drivebaseSystem, SmartControllerGroup &contGroup) : _drivebaseSystem(drivebaseSystem), _contGroup(contGroup) {
  drivebaseSystem.drivetrain.Set(0, 0); // Set the drivebase to 0 power as default
}

void Drivebase::teleopOnUpdate(double dt) {
  int dbLeftSpeed = 0, dbRightSpeed = 0;
  
  if(fabs(_contGroup.Get(ControlMap::drivebaseL) >= ControlMap::XboxDeadzone)) {
    dbLeftSpeed = _contGroup.Get(ControlMap::drivebaseL);
  }

  if(fabs(_contGroup.Get(ControlMap::drivebaseR)) >= ControlMap::XboxDeadzone) {
    dbRightSpeed = _contGroup.Get(ControlMap::drivebaseR);
  }

  _drivebaseSystem.drivetrain.Set(dbLeftSpeed, dbRightSpeed);
}

void Drivebase::autoOnUpdate(double dt) {

}

void Drivebase::testOnUpdate(double dt) {

}