#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

enum class TeleopClimber {kStationary = 0, kZeroing, kManual, kMoving};


enum class ClimberStates {
  STOWED,
  DEPLOYED,
  DISABLED
};

class Climber {
 public:
  Climber(RobotMap::ClimberSystem &climberSystem, SmartControllerGroup &contGroup);

  void teleopOnUpdate(double dt);
  void autoOnUpdate(double dt);
  void testOnUpdate(double dt);
  void disabled(double dt);

  void setState(ClimberStates state);

 private:
  void _update(double dt);
  void _toggle();

  ClimberStates _climberState{ ClimberStates::STOWED };
  RobotMap::ClimberSystem &_climberSystem;
  wml::controllers::SmartControllerGroup &_contGroup;
};
