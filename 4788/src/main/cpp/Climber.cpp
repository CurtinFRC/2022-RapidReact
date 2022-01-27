#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {}

void Climber::_update(double dt) {
  switch(_climberState) {
    case ClimberStates::DEPLOYED:
      _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
      break;
    case ClimberStates::STOWED:
      _climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
      break;
  }

  _climberSystem.climberSolenoid.Update(dt);
}

void Climber::_toggle() {
  _climberState == ClimberStates::DEPLOYED ? setState(ClimberStates::STOWED) : setState(ClimberStates::DEPLOYED);
}

void Climber::setState(ClimberStates state) {
  _climberState = state; 
}

void Climber::teleopOnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::climberToggle, wml::controllers::XboxController::ONRISE)) {
    _toggle();
  }

  _update(dt);
}

  // void Climber::Disabled(double dt) { 
  //   _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  // }


/* void Climber::testOnUpdate(double dt) {
  switch () {
    if (_climberToggle) {
      _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    }
    else if (!_climberToggle) {
      _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
        
      
    }

  }
}
*/






