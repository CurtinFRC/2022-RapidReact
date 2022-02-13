#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

enum class ClimberState {
  kStowed,
  kDeployed
};

class Climber {
 public:
  Climber(RobotMap::ClimberSystem &climberSystem, SmartControllerGroup &contGroup);

  void onDisable(double dt);
  void setState(double dt);
  void _toggleClimber();
  void setState(ClimberState state);

  void updateClimber(double dt);
  void _update(double dt);

 private:
  bool ClimberToggle = false;

  ClimberState _state{ ClimberState::kStowed };
  RobotMap::ClimberSystem &_climberSystem;
  wml::controllers::SmartControllerGroup &_contGroup;
};