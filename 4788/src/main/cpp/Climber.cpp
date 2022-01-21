#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {
  _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse); // Default State
}

void Climber::teleopOnUpdate(double dt) {

  if (_contGroup.Get(ControlMap::ClimberToggle, wml::controllers::XboxController::ONRISE)) {
    ClimberToggle = !ClimberToggle;
  }

  if (ClimberToggle) {
    _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  }

}

