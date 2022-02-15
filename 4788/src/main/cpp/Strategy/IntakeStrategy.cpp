#include "Strategy/IntakeStrategy.h"
#include <iostream>

IntakeStrategy::IntakeStrategy(std::string name, Intake &intake, Shooter &shooter, Controllers &contGroup) : Strategy(name), _intake(intake), _shooter(shooter), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&intake);
}

void IntakeStrategy::OnUpdate(double dt) {
  // double indexVoltage = fabs(_contGroup.Get(ControlMap::indexSpin)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::indexSpin) : 0;
  // _intake.setIndex(indexVoltage);
  // if (_intake._magState == MagStates::kManual) {
  //   _intake.setIndex(indexVoltage);
  // }

  // if (_contGroup.Get(ControlMap::indexManualToggleButton, wml::controllers::XboxController::ONRISE)) {
  //   if (indexManualToggle) {
  //     indexManualToggle = false;
  //   } else { 
  //     indexManualToggle = true;
  //   }
  // }

  // if (_contGroup.Get(ControlMap::indexOverrideToggleButton, wml::controllers::XboxController::ONRISE)) {
  //   if (indexOverrideToggle) {
  //     indexOverrideToggle = false;
  //   } else {
  //     indexOverrideToggle = true;
  //   }
  // }

  // auto magIns = nt::NetworkTableInstance::GetDefault();
  // auto magSyste = magIns.GetTable("magSystem");
  // nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Manual").SetBoolean(indexManualToggle);
  // nt::NetworkTableInstance::GetDefault().GetTable("magSystem")->GetEntry("Override").SetBoolean(indexOverrideToggle);


  // if (indexManualToggle) {
  //   _intake.setIndex(indexVoltage, MagStates::kManual); //will continue once it reaches the front sensor
  //   if (indexOverrideToggle) {
  //     _intake.setIndex(MagStates::kOverride);
  //   }
  // } else {
  //   if (indexManualToggle && _contGroup.Get(ControlMap::indexManualToggleButton, wml::controllers::XboxController::ONRISE)) {
  //     _intake.setIndex(MagStates::kEmpty);
  //   }
  // }

  // if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
  //   if (_intakeToggle) {
  //     _intakeToggle = false;
  //   } else {
  //     _intakeToggle = true;
  //   }
  // }

  // if (_intakeToggle) {
  //   _intake.setIntakeState(IntakeStates::kDeployed);
  // } else {
  //   _intake.setIntakeState(IntakeStates::kStowed);
  // }

  // double intakeVoltage = fabs(_contGroup.Get(ControlMap::intake)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::intake) : 0;
  // _intake.setIntake(intakeVoltage);

}