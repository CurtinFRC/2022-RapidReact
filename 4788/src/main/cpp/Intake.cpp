// #include "Intake.h"
// #include <iostream>
// #include "ControlMap.h"

// Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) { 
//   _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
// }

// void Intake::setState(IntakeStates state) {
//   switch(state) {
//     case IntakeStates::DEPLOYED:
//       // _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
//       break;
//     case IntakeStates::STOWED:
//       // _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
//       break;
//   }
// }

// void Intake::teleopOnUpdate (double dt){
//   double intakeCont = fabs(_contGroup.GetController(1).Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::intake) : 0;
//   _intakeSystem.intake.Set(intakeCont);

//   //Call StateMachine

//    if (_contGroup.GetController(1).Get(ControlMap::intake)) {
//      _intakeState == IntakeStates::DEPLOYED ? setState(IntakeStates::STOWED) : setState(IntakeStates::DEPLOYED);
//    }
// }

