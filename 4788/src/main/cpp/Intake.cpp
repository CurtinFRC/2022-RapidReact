#include "Intake.h"
#include <iostream>
#include "ControlMap.h"
#include "frc/RobotController.h"

Intake::Intake (RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup) : _intakeSystem(intakeSystem), _contGroup(contGroup) {}

void Intake::updateIntake(double dt) {
  // auto magInst = nt::NetworkTableInstance::GetDefault();
  // auto magSystem = magInst.GetTable("magSystem");

  // _magState == MagStates::kEmpty ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Empty State").SetBoolean(false);
  // _magState == MagStates::kManual ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual State").SetBoolean(false);
  // _magState == MagStates::kOverride ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override State").SetBoolean(false);
  // _magState == MagStates::kOne ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("One State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("One State").SetBoolean(false);
  // _magState == MagStates::kTwo ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Two State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Two State").SetBoolean(false);
  // _magState == MagStates::kEject ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Eject State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Eject State").SetBoolean(false);
  // _magState == MagStates::kTransfer ? nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Transfer State").SetBoolean(true) : nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Transfer State").SetBoolean(false);
  
  // nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Front Sensor").SetBoolean(_frontSensor());
  // nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Back Sensor").SetBoolean(_backSensor());

  // switch(_magState) {
  //   case MagStates::kEmpty: //robot is empty, no balls

  //   break;

  //   case MagStates::kTransfer: //if a ball is sensed in the intake sensor, move it to the front 
      
  //   break;

  //   case MagStates::kOne:

  //   break;

  //   case MagStates::kTwo:

  //   break;

  //   case MagStates::kEject:

  //   break;

  //   case MagStates::kOverride:

  //   break;

  //   case MagStates::kManual:
  //     _indexSetVoltage = _indexVoltage;
  //     _intakeSetVoltage = _intakeVoltage;

  //     if (db.Get(_frontSensor())) {
  //       std::cout << "AGHGHG" << std::endl;
  //     }
  //   break;

  //   default:
  //     std::cout << "in mag default state, something is wrong, being reset to empty" << std::endl;
  //   break;
  // }

  // switch(_intakeState) {
  //   case IntakeStates::kStowed:
  //     _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  //   break;
    
  //   case IntakeStates::kDeployed:
  //     _intakeSystem.intakeSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  //   break;

  //   default:
  //     std::cout << "In intake default state, something is wrong, being reset to Idle" << std::endl;
  //   break;
  // }

  // _intakeSystem.intake.Set(_intakeSetVoltage);
  // _intakeSystem.indexWheel.Set(_indexSetVoltage);

  // _intakeSystem.intakeSolenoid.Update(dt);
}

void Intake::setIndex(double voltage) {
  _indexVoltage = voltage;
}

void Intake::setIntake(double intakeVoltage) {
  _intakeVoltage = intakeVoltage;
}

void Intake::setIntakeState(IntakeStates intakeState) {
  _intakeState = intakeState;
}

bool Intake::_frontSensor() {
  return !_intakeSystem.shooterBallSensor.Get();
}

bool Intake::_backSensor() {
  return !_intakeSystem.intakeBallSensor.Get();
}

void Intake::Update(double dt) {
  updateIntake(dt);
}