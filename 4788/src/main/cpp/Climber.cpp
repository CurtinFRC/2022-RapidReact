#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {}

void Climber::teleopOnUpdate(double dt) {

  if (_contGroup.Get(ControlMap::climberToggle, wml::controllers::XboxController::ONRISE)) {
    if (ClimberToggle) {
      ClimberToggle = false;
    } else {
      ClimberToggle = true;
    }
  }

  if (ClimberToggle) {
    _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  } else {
    _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  }

}

void Climber::onDisable(double dt) {
  _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
}