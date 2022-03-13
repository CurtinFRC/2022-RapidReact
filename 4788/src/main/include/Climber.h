#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

enum class ClimberState {
  kStowed,
  kDeployed
};

class Climber : public wml::StrategySystem, public wml::loops::LoopSystem {
 public:
  Climber(RobotMap::ClimberSystem &climberSystem, SmartControllerGroup &contGroup);

  void updateClimber(double dt);
  void disabledClimber();
  void setState(ClimberState _climberState);

  void Update(double dt) override;

 private:
  bool ClimberToggle = false;

  ClimberState _state{ ClimberState::kStowed };
  RobotMap::ClimberSystem &_climberSystem;
  wml::controllers::SmartControllerGroup &_contGroup;
};