#include "Intake.h"
#include <iostream>
#include "ControlMap.h"
#include "frc/RobotController.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) {}

void Intake::updateIntake(double dt) {
  auto magInst = nt::NetworkTableInstance::GetDefault();
  auto magSystem = magInst.GetTable("magSystem");

  _magState == MagStates::kEmpty ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(false);
  _magState == MagStates::kManual ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(false);
  _magState == MagStates::kOverride ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(false);
  _magState == MagStates::kOne ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("One State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("One State").SetBoolean(false);
  _magState == MagStates::kTwo ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Two State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Two State").SetBoolean(false);
  _magState == MagStates::kEject ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Eject State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Eject State").SetBoolean(false);
  _magState == MagStates::kTransfer ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Transfer State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Transfer State").SetBoolean(false);
  
  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Front Sensor").SetBoolean(_frontSensor());
  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Back Sensor").SetBoolean(_backSensor());

  switch(_magState) {
    case MagStates::kEmpty: //robot is empty, no balls
      if (_frontSensor() && _backSensor()) { //if yes for both
        std::cout << "both sensors" << std::endl;
        _magState = MagStates::kTwo;
      } else if (!_frontSensor() && _backSensor()) {
        _magState = MagStates::kOne;
      } else if (_frontSensor() && !_backSensor()){
        _magState = MagStates::kTransfer;
      }
      
      // else if (_frontSensor() && !_backSensor()) {
      //   std::cout << "you have a ball in the front without the back sensor being activated first, there is an issue" << std::endl;
      //   _magState = MagStates::kOne;
      // } else if (!_frontSensor() && _backSensor()) {
      //   _magState = MagStates::kTransfer;
      // } else if (!_frontSensor() && !_backSensor()) {
      //   //the robot continues to be empty 
      // } else {
      //   std::cout << "Mag state empty error" << std::endl;
      // }
      // // std::cout << "empty robot" << std::endl;

    break;

    case MagStates::kTransfer: //if a ball is sensed in the intake sensor, move it to the front 
      if (!_backSensor() && _frontSensor()) {
        _indexSetVoltage = -0.5;
      } else {
        _magState = MagStates::kOne;
      }
    break;

    case MagStates::kOne:
      std::cout << "One ball in mag" << std::endl;
      if (_frontSensor() && _backSensor()) {
        _magState = MagStates::kTwo;
      } else if (!_frontSensor() && _backSensor()) {
        _magState = MagStates::kTransfer;
      } else if (!_frontSensor() && !_backSensor()) {
        _magState = MagStates::kEmpty;
      }
    break;

    case MagStates::kTwo:
      std::cout << "Two balls in mag" << std::endl;
      if (_frontSensor() && !_backSensor()) {
        _magState = MagStates::kOne;
      } else if (!_frontSensor() && _backSensor()) {
        _magState = MagStates::kTransfer;
      } else if (!_frontSensor() && !_backSensor()) {
        _magState = MagStates::kEmpty;
      }
    break;

    case MagStates::kEject:
      std::cout << "EJECT!!" << std::endl;
      if (_frontSensor() || (_frontSensor() && _backSensor())) {
        _indexSetVoltage = 0.3;
      } else {
        _indexSetVoltage = 0;
        _magState = MagStates::kEmpty;
      }
    break;

    case MagStates::kOverride:
      _indexSetVoltage = _indexVoltage;
    break;

    case MagStates::kManual:
      //controller to spin mag
      //_intakeVoltage gets set straight to index wheel if 
      
      if (_frontSensor()) {
        _indexSetVoltage = 0;
      } else {
        _indexSetVoltage = _indexVoltage;
      }

    break;

    default:
      std::cout << "in mag default state, something is wrong, being reset to empty" << std::endl;
      
      // _magState = MagStates::kEmpty;
    break;
  }

  _intakeState == IntakeStates::kIntake ? nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("intake state").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("intake state").SetBoolean(false);
  _intakeState == IntakeStates::kOutake ? nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("outake state").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("outake state").SetBoolean(false);
  _intakeState == IntakeStates::kIdle ? nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("idle state").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("idle state").SetBoolean(false);
  _intakeState == IntakeStates::kManual ? nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("manual state").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("manual state").SetBoolean(false);
  _intakeState == IntakeStates::kStowed ? nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("stowed state").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("intakeSystem")->GetEntry("stowed state").SetBoolean(false);


  switch(_intakeState) {
    case IntakeStates::kIdle:
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
      _intakeState = IntakeStates::kIntake;
      intakeSetPower = 0;
    break;
    case IntakeStates::kIntake:
      if (_magState == MagStates::kOne || _magState == MagStates::kTwo) {
        intakeSetPower = fabs(_intakeSetVoltage);
      }
    break;
    case IntakeStates::kOutake:
      intakeSetPower = -fabs(_intakeSetVoltage);
    break;

    case IntakeStates::kManual:

    break;

    case IntakeStates::kStowed:
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
    break;

    default:
      std::cout << "In intake default state, something is wrong, being reset to Idle" << std::endl;
    break;
  }

  if (_indexSetVoltage == 0) {
    _intakeSystem.indexWheel.Set(_testingManualIndex);
  } else {
    _intakeSystem.indexWheel.Set(_indexSetVoltage);
  }

  // if (intakeSetPower == 0) {
  //   _intakeSystem.intake.Set(_testingManualIntake);
  // } else {
  // }

  _intakeSystem.intake.Set(intakeSetPower);
  _intakeSystem.intakeSolenoid.Update(dt);
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
  return !_intakeSystem.shooterBallSensor.Get();
}

bool Intake::_backSensor() {
  return !_intakeSystem.intakeBallSensor.Get();
}

void Intake::setIntakeState(IntakeStates intakeState) {
  _intakeState = intakeState;
}

void Intake::setIntake(double intakeVoltage) {
  _intakeSetVoltage = intakeVoltage;

  if (_intakeState == IntakeStates::kIdle) {
    if (_intakeSetVoltage > 0) {
      _intakeState = IntakeStates::kIntake;
    } else if (_intakeSetVoltage < 0) {
      _intakeState = IntakeStates::kOutake;
    }
  }
}

void Intake::ejectBall(bool readyFire) {
  //check that we have 1/2 balls, then check that the shooter is up to speed
  if (_magState == MagStates::kOne || _magState == MagStates::kTwo) {
    if (readyFire) {
      _magState = MagStates::kEject;
    }
  }
}

void Intake::manualSetIntake(double power) {
  _testingManualIntake = power;
}

void Intake::manualSetIndex(double power) {
  _testingManualIndex = power;
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