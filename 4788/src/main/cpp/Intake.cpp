#include "Intake.h"
#include <iostream>
#include "ControlMap.h"
#include "frc/RobotController.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) {}

void Intake::updateIntake(double dt) {
  auto magInst = nt::NetworkTableInstance::GetDefault();
  auto magSystem = magInst.GetTable("magSystem");

  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("State").SetString(mag_state_to_string(_magState));
  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Front Sensor").SetBoolean(_frontSensor());
  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Back Sensor").SetBoolean(_backSensor());

  switch(_magState) {
    case MagStates::kEmpty: //robot is empty, no balls
      _indexSetVoltage = 0;
      if (!_frontSensor() && _backSensor()) {
        _magState = MagStates::kOne;
      } else if (_frontSensor() && !_backSensor()) {
        _magState = MagStates::kTransfer;
      } else if (_frontSensor() && _backSensor()) {
        _magState = MagStates::kTwo;
      }
    break;

    case MagStates::kTransfer: //if a ball is sensed in the intake sensor, move it to the front 
      if (_frontSensor()) {
        _intakeSetVoltage = 1;
        _indexSetVoltage = -0.35;
        _magState = MagStates::kTransfering;
      }
    break;

    case MagStates::kTransfering:
      if (transferSensorDebounce.Get(_backSensor()) && !_frontSensor()) {
        _intakeSetVoltage = 0;
        _indexSetVoltage = 0;
        _magState = MagStates::kOne;
      } else if (transferDebounce.Get(true)) {
        // Prevent the system getting stuck in 'transferring'
        // by imposing a time limit set by transferDebounce
        transferDebounce.Get(false);
        _magState = MagStates::kEmpty;
      }
      break;

    case MagStates::kOne:
      _indexSetVoltage = 0;
      if (_frontSensor() && !_backSensor()) {
        _magState = MagStates::kTransfer;
      } else if (_frontSensor() && _backSensor()) {
        _magState = MagStates::kTwo;
      } else if (!_frontSensor() && !_backSensor()) {
        _magState = MagStates::kEmpty;
      }

    break;

    case MagStates::kTwo:
      if (!_frontSensor() && _backSensor()) {
        _magState = MagStates::kOne;
      } else if (_frontSensor() && _backSensor()) {
        _magState = MagStates::kTwo;
      } else if (!_frontSensor() && !_backSensor()) {
        _magState = MagStates::kEmpty;
      } else if (_frontSensor() && !_backSensor()) {
        _magState = MagStates::kTransfer;
      }
      _intakeSetVoltage = 0;
      _indexSetVoltage = 0;
      _intakeState = IntakeStates::kDeployed;
    break;

    case MagStates::kEject:
      if (!ejectDebounce.Get(true)) {
        _indexSetVoltage = -0.7;
        // _intakeSetVoltage = 0.5;
      } else {
        ejectDebounce.Get(false);
        if (_frontSensor()) {
          _magState = MagStates::kTransfer;
        } else {
          _magState = MagStates::kEmpty;
        }
        std::cout << "EJECT" << std::endl;
      }
    break;

    case MagStates::kOverride:

    break;

    case MagStates::kManual:
      std::cout << _indexSetVoltage << std::endl;
      _indexSetVoltage = _indexVoltage;
    break;

    default:
  //     std::cout << "in mag default state, something is wrong, being reset to empty" << std::endl;
    break;
  }

  switch(_intakeState) {
    case IntakeStates::kStowed:
      _intakeSetVoltage = 0;
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
      // std::cout << "Intake stowed" << std::endl;
    break;

    case IntakeStates::kDeployed:
      _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
      // std::cout << "Intake deployed" << std::endl;
    break;

    default:
      std::cout << "In intake default state, something is wrong, being reset to Idle" << std::endl;
    break;
  }

  _intakeSystem.intake.Set(_intakeSetVoltage);
  _intakeSystem.indexWheel.Set(_indexSetVoltage);
  nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Index").SetDouble(_indexSetVoltage);

  _intakeSystem.intakeSolenoid.Update(dt);
}

void Intake::setIndex(double voltage) {
  _indexVoltage = voltage;
}

void Intake::setIntakeState(IntakeStates intakeState) {
  // if (_magState == MagStates::kTwo) {
  //   _intakeState = IntakeStates::kDeployed;
  // } else {
    _intakeState = intakeState;

  // }
}

void Intake::setMagState(MagStates magState) {
  _magState = magState;
}

void Intake::setIntake(double voltage) {
  if (_magState != MagStates::kTransfer && _magState != MagStates::kTransfering && _magState != MagStates::kTwo)
    _intakeSetVoltage = voltage;
}

bool Intake::_frontSensor() {
  return !_intakeSystem.shooterBallSensor.Get();
}

bool Intake::_backSensor() {
  return !_intakeSystem.intakeBallSensor.Get();
}

void Intake::fireBall() {
  if (_backSensor()) {
    _magState = MagStates::kEject;
  }
}

void Intake::Update(double dt) {
  updateIntake(dt);
}

bool Intake::isIdle() {
  return _magState == MagStates::kOne || _magState == MagStates::kTwo;
}

void Intake::GetOut() {
  _intakeSystem.intake.Set(-0.6);
  _intakeSystem.indexWheel.Set(0.6);
}