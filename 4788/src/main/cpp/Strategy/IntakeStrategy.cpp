#include "Strategy/IntakeStrategy.h"
#include <iostream>

IntakeStrategy::IntakeStrategy(std::string name, Intake &intake, Shooter &shooter, Controllers &contGroup) : Strategy(name), _intake(intake), _shooter(shooter), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&intake);
}

void IntakeStrategy::OnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::indexManualToggleButton, wml::controllers::XboxController::ONRISE)) {
    if (indexManualToggle) {
      indexManualToggle = false;
    } else {
      indexManualToggle = true;
    }
  }

  if (_contGroup.Get(ControlMap::indexManualStop, wml::controllers::XboxController::ONRISE)) {
    if (indexOverrideToggle) {
      indexOverrideToggle = false;
    } else {
      indexOverrideToggle = true;
    }
  }

  if (indexOverrideToggle) {
    _intake.setMagState(MagStates::kEmpty);
  }

  if (indexManualToggle) {
    _intake.setMagState(MagStates::kManual);
  }

  if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
    if (_intakeToggle) {
      _intakeToggle = false;
    } else {
      _intakeToggle = true;
    }
  }

  if (_intakeToggle) {
    _intake.setIntakeState(IntakeStates::kDeployed);
  } else {
    _intake.setIntakeState(IntakeStates::kStowed);
  }

  double intakeVoltage = fabs(_contGroup.Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::intake) : 0;
  _intake.setIntake(intakeVoltage);

  double indexVoltage = fabs(_contGroup.Get(ControlMap::testingIndex)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::testingIndex) : 0;
  _intake.setIndex(indexVoltage);

  if (_contGroup.Get(ControlMap::fire)) {
    if (_shooter.isDone()) {
      _intake.fireBall();
    }
  } 
}