#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {}

void Climber::Update(double dt) {
  updateClimber(dt);
}

void Climber::updateClimber(double dt) {
  // std::cout << _state << std::endl;

  switch (_state) {
  case ClimberState::kDeployed:
    _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    // std::cout << "Deploy climber" << std::endl;
    break;

  case ClimberState::kStowed:
    _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
    // std::cout << "climber stowed" << std::endl;
    break;

  default:
    std::cout << "In climber default state, something is wrong" << std::endl;
    break;
  }

  _climberSystem.climberSolenoid.Update(dt);
}

void Climber::disabledClimber() {
  _state = ClimberState::kStowed;
}


void Climber::setState(ClimberState _climberState) {
  _state = _climberState;
}