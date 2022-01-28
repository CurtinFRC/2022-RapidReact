#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Shooter {
 public: 
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);
  void teleopOnUpdate(double dt);

 private:
  wml::controllers::SmartControllerGroup &_contGroup;
  RobotMap::ShooterSystem &_shooterSystem;
};