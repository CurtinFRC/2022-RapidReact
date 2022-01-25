#include "Climber.h" 
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(RobotMap::ClimberSystem &climberSystem, wml::controllers::SmartControllerGroup &contGroup) : _climberSystem(climberSystem), _contGroup(contGroup) {
  _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse); // Default State
}

void Climber::_update(double dt) {
  switch(_climberState) {
    case ClimberStates::DEPLOYED:
      _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
      break;
    case ClimberStates::STOWED:
      _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
      break;
  }


}

void Climber::setState(ClimberStates state) {
  _climberState = state;
}

void Climber::teleopOnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::ClimberToggle, wml::controllers::XboxController::ONRISE));
  _climberToggle = !_climberToggle;
  
  if (_climberToggle) {
    _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  } 
}

  void Climber::Disabled(double dt) { 
    _climberSystem.leftClimberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  }


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






