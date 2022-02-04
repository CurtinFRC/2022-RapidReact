#include "Intake.h"
#include <iostream>
#include "ControlMap.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) { }

void Intake::teleopOnUpdate (double dt){
  // double intakeCont = fabs(_contGroup.GetController(1).Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::intake) : 0;
  double intakeCont = fabs(_contGroup.Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::intake) : 0;
  _intakeSystem.intake.Set(-intakeCont); //invert the intake motor
}