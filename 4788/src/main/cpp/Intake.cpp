#include "Intake.h"
#include <iostream>
#include "ControlMap.h"
#include "frc/RobotController.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) {}

void Intake::updateIntake(double dt) {
  auto magInst = nt::NetworkTableInstance::GetDefault();
  auto magSystem = magInst.GetTable("magSystem");

  switch(_magState) {
    case MagStates::kEmpty: //robot is empty, no balls
  //     if (_frontSensor() && _backSensor()) { //if yes for both
  //       std::cout << "both sensors have been activated in the empty stage, something is wrong" << std::endl;
  //       _magState = MagStates::kTwo;
  //     } else if (_frontSensor() && !_backSensor()) {
  //       std::cout << "you have a ball in the front without the back sensor being activated first, there is an issue" << std::endl;
  //       _magState = MagStates::kOne;
  //     } else if (!_frontSensor() && _backSensor()) {
  //       _magState = MagStates::kTransfer;
  //     } else if (!_frontSensor() && !_backSensor()) {
  //       //the robot continues to be empty 
  //     } else {
  //       std::cout << "Mag state empty error" << std::endl;
  //     }
      std::cout << "empty robot" << std::endl;

      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(false);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(false);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(true);
      
    break;

    case MagStates::kTransfer: //if a ball is sensed in the intake sensor, move it to the front 
  //     if (_backSensor() && !_frontSensor()) {
  //       _indexSetVoltage = 0.5;
  //     } else {
  //       _magState = MagStates::kOne;
  //     }
    break;

    case MagStates::kOne:
  //     nt::NetworkTableInstance::GetDefault().GetTable("intake states")->GetEntry("Mag One").SetBoolean(true);
  //     nt::NetworkTableInstance::GetDefault().GetTable("intake states")->GetEntry("Mag Two").SetBoolean(false);
    break;

    case MagStates::kTwo:
  //     nt::NetworkTableInstance::GetDefault().GetTable("intake states")->GetEntry("Mag One").SetBoolean(true);
  //     nt::NetworkTableInstance::GetDefault().GetTable("intake states")->GetEntry("Mag Two").SetBoolean(true);
    break;

    case MagStates::kEject:
    //   if (_frontSensor() || (_frontSensor() && _backSensor())) {
    //     _indexSetVoltage = 0.3;
    //   } else {
    //     _indexSetVoltage = 0;
    //   }
    break;

    case MagStates::kOverride:
      //a controller to spin mag till it gets to the front sensor 
      // !_frontSensor ? setIndexWheel(ControlMap::indexWheelTransferSpeed) : setIndexWheel(0); 
      _indexSetVoltage = _indexVoltage;

      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(false);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(true);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(false);
    break;

    case MagStates::kManual:
      //controller to spin mag
      //_intakeVoltage gets set straight to index wheel if 
      if (_frontSensor()) {
        _indexSetVoltage = 0;
      } else {
        _indexSetVoltage = _indexVoltage;
      }

      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(true);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(false);
      nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(false);

    break;

    default:
      std::cout << "in mag default state, something is wrong, being reset to empty" << std::endl;
      
      _magState = MagStates::kEmpty;
    break;
  }

  _intakeSystem.indexWheel.Set(_indexSetVoltage);
}

void Intake::setIndex(double voltage, MagStates magState) {
  _indexVoltage = voltage;
  _magState = magState;
}

void Intake::setIndex(MagStates magState) {
  _magState = magState;
}

void Intake::Update(double dt) {
  updateIntake(dt);
}

bool Intake::_frontSensor() {
  return _intakeSystem.shooterBallSensor.Get();
}

bool Intake::_backSensor() {
  return _intakeSystem.intakeBallSensor.Get();
}

// void Intake::_update(double dt) {
//   switch(_intakeState) {
//     case IntakeStates::DEPLOYED:
//       _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
//       break;
//     case IntakeStates::STOWED:
//       _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
//       break;
//   }
 
//   _intakeSystem.intakeSolenoid.Update(dt);
//   _intakeSystem.intake.Set(_power);
// }

// void Intake::_toggleIntake() {
//   _intakeState == IntakeStates::DEPLOYED ? setState(IntakeStates::STOWED) : setState(IntakeStates::DEPLOYED);
// }

// void Intake::setState(IntakeStates state) {
//   _intakeState = state;
//    if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
//      _intakeState == IntakeStates::DEPLOYED ? setState(IntakeStates::STOWED) : setState(IntakeStates::DEPLOYED);
//    }
// }

// void Intake::teleopOnUpdate (double dt){
//   _power = fabs(_contGroup.Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::intake) : 0;

//   if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
//     _toggleIntake(); // Call Toggle
//   }

//   _update(dt);
// }

// bool Intake::hasBall() {
//   return _intakeSystem.ballSensor.Get();
// }