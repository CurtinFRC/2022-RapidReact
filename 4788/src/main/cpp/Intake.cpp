#include "Intake.h"
#include <iostream>

Intake::Intake (RobotMap::IntakeSystem &intakeSystem,
  Controllers &contGroup) : _intakeSystem(intakeSystem),
  _contGroup(contGroup) {
  _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
}
  
void Intake::TeleopOnUpdate (double dt){
  double intakeCont = _contGroup.Get(ControlMap::Intake);
  if(fabs(intakeCont) > ControlMap::XboxDeadzone) {
    _intakeSystem.intake.Set(intakeCont);
  }
  
  if (_contGroup.Get(ControlMap::IntakeActuation)) {
    switch(_intakeState) {
      case IntakeStates::DEPLOYED:
        _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
        _intakeState = IntakeStates::STOWED;
        break;
      case IntakeStates::STOWED:
        _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
        _intakeState = IntakeStates::DEPLOYED;
        break;
    }
  }
};

 