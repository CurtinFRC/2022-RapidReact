#pragma once

#include "RobotMap.h";
#include "controllers/Controllers.h";

using Controllers = wml::controllers::SmartControllerGroup;

enum class IntakeStates{
  STOWED = 0,
  DEPLOYED
};

class Intake {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);
  void teleopOnUpdate (double dt);
  void autoOnUpdate (double dt);
  void testOnUpdate (double dt);
 private:
  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;

  double power;
  IntakeStates _intakeState{IntakeStates::STOWED};
};