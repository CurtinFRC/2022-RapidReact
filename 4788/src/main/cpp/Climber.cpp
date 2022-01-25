#include "Climber.h" 
#include <iostream>


using namespace wml;
using namespace wml::controllers;

Climber::Climber(wml::actuators::DoubleSolenoid &climberSolenoid, wml::controllers::SmartControllerGroup &contGroup) : _climberSolenoid(climberSolenoid), _contGroup(contGroup) {
  _climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse); // Default State
}

void Climber::teleopOnUpdate(double dt) {
  
  if (_contGroup.Get(ControlMap::climberToggle, wml::controllers::XboxController::ONRISE)) {
    ClimberToggle = !ClimberToggle;
  }

  if (ClimberToggle) {
    _climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  }

}

