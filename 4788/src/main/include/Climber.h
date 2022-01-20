#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

enum class TeleopClimber {kStationary = 0, kZeroing, kManual, kMoving};

class Climber {
 public:
  Climber(RobotMap::ClimberSystem &climberSystem, SmartControllerGroup &contGroup);

  
  void teleopOnUpdate(double dt);
  void autoOnUpdate(double dt);
  void testOnUpdate(double dt);

 private:
  bool ClimberToggle = false;
  RobotMap::ClimberSystem &_climberSystem;
  wml::controllers::SmartControllerGroup &_contGroup;


};