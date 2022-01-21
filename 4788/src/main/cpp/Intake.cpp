#include "Intake.h"
#include <iostream>
#include "ControlMap.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) { 
  _intakeSystem.intakeSolenoid_left.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  _intakeSystem.intakeSolenoid_right.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
}
  

void Intake::teleopOnUpdate (double dt){
  double intakeCont = fabs(_contGroup.Get(ControlMap::Intake)) > ControlMap::TriggerDeadzone ? _contGroup.Get(ControlMap::Intake) : 0;
  _intakeSystem.intake.Set(intakeCont);

  //switch to a toggle

  if (_contGroup.Get(ControlMap::IntakeActuation, wml::controllers::XboxController::ONRISE)) {
    switch(_intakeState) {
      case IntakeStates::DEPLOYED:
        _intakeSystem.intakeSolenoid_left.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
        _intakeSystem.intakeSolenoid_right.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
        _intakeState = IntakeStates::STOWED;
        break;
      case IntakeStates::STOWED:
        _intakeSystem.intakeSolenoid_left.SetTarget(wml::actuators::BinaryActuatorState::kForward);
        _intakeSystem.intakeSolenoid_right.SetTarget(wml::actuators::BinaryActuatorState::kForward);
        _intakeState = IntakeStates::DEPLOYED;
        break;
    }
  }
}