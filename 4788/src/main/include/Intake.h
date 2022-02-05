#pragma once

#include "RobotMap.h"
#include "controllers/Controllers.h"

using Controllers = wml::controllers::SmartControllerGroup;


class Intake {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);
  void teleopOnUpdate (double dt);

 private:
  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;
};