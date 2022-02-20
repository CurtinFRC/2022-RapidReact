#include "Strategy/ClimberStrategy.h"
#include <iostream>

ClimberStrategy::ClimberStrategy(std::string name, Climber &climber, Controllers &contGroup) : Strategy(name), _climber(climber), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&climber);
}

void ClimberStrategy::OnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::climberActuate, wml::controllers::XboxController::ONRISE)) {
    if (_climberToggle) {
      _climberToggle = false;
    } else {
      _climberToggle = true;
    }
  }

  if (_climberToggle) {
    _climber.setState(ClimberState::kDeployed);
  } else {
    _climber.setState(ClimberState::kStowed);
  }
}

ClimberDisableStrategy::ClimberDisableStrategy(std::string name, Climber &climber) : Strategy(name), _climber(climber) {
  SetCanBeInterrupted(false);
  SetCanBeReused(true); //&QUESTION should this be false
  Requires(&climber);
}

void ClimberDisableStrategy::OnUpdate(double dt) {
  _climber.disabledClimber();
}

