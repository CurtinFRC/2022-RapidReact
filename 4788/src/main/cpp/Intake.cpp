#include "Intake.h"
#include <iostream>
#include "ControlMap.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) { 
  _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
}

void Intake::_update(double dt) {
  switch(_intakeState) {
    case IntakeStates::DEPLOYED:
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
      break;
    case IntakeStates::STOWED:
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
      break;
  }
 
  _intakeSystem.intakeSolenoid.Update(dt);
  _intakeSystem.intake.Set(_power);
}

void Intake::_toggleIntake() {
  _intakeState == IntakeStates::DEPLOYED ? setState(IntakeStates::STOWED) : setState(IntakeStates::DEPLOYED);
}

void Intake::setState(IntakeStates state) {
  _intakeState = state;
   if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
     _intakeState == IntakeStates::DEPLOYED ? setState(IntakeStates::STOWED) : setState(IntakeStates::DEPLOYED);
   }
}

void Intake::teleopOnUpdate (double dt){
  _power = fabs(_contGroup.Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::intake) : 0;

  if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
    _toggleIntake(); // Call Toggle
  }

  _update(dt);
}
