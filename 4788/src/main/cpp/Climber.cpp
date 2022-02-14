#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {}

void Climber::Update(double dt) {
  updateClimber(dt);
}

void Climber::updateClimber(double dt) {
  switch (_state) {
  case ClimberState::kDeployed:
    // _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    std::cout << "Deploy climber" << std::endl;
    break;

  case ClimberState::kStowed:
    // _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
    break;

  default:
    std::cout << "In climber default state, something is wrong" << std::endl;
    break;
  }
}

void Climber::disabledClimber() {
  _state = ClimberState::kStowed;
}


void Climber::setState(ClimberState _climberState) {
  _state = _climberState;
}