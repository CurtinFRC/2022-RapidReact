#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {
  // _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  // std::cout << "set climber to false" << std::endl;
}

void Climber::_update(double dt) {
  switch(_state) {
    case ClimberState::kStowed:
      _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
    break;

    case ClimberState::kDeployed:
      _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    break;

    default: 
      std::cout << "Climber default state something is wrong" << std::endl;
    break;
  }

  _climberSystem.climberSolenoid.Update(dt);

}

void Climber::_toggleClimber() {
  _state == ClimberState::kDeployed ? setState(ClimberState::kStowed) : setState(ClimberState::kDeployed);
}

void Climber::updateClimber(double dt) {
  if (_contGroup.Get(ControlMap::climberActuate, wml::controllers::XboxController::ONRISE)) {
    _toggleClimber();
  }

  _update(dt);
}

void Climber::setState(ClimberState state) {
  _state = state;
}

void Climber::onDisable(double dt) {
  setState(ClimberState::kStowed);
}