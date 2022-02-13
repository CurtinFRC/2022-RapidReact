#include "Strategy/IntakeStrategy.h"
#include <iostream>

IntakeStrategy::IntakeStrategy(std::string name, Intake &intake, Controllers &contGroup) : Strategy(name), _intake(intake), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&intake);
}

void IntakeStrategy::OnUpdate(double dt) {
  // double indexVoltage = (_contGroup.Get(ControlMap::indexSpin));

  // if (_contGroup.Get(ControlMap::indexManualToggleButton)) {
  //   if (indexManualToggle) {
  //     indexManualToggle = false;
  //   } else { 
  //     indexManualToggle = true;
  //   }
  // }

  // if (_contGroup.Get(ControlMap::indexOverrideToggleButton)) {
  //   if (indexOverrideToggle) {
  //     indexOverrideToggle = false;
  //   } else {
  //     indexOverrideToggle = true;
  //   }
  // }

  // if (indexManualToggle) {
  //   //set everything manually 
  //   if (fabs(_contGroup.Get(ControlMap::indexSpin) > 0.4)) {
  //     if (indexOverrideToggle) {
  //       _intake.setIndex(indexVoltage, MagStates::kOverride); //will continue once it reaches the front sensor
  //     } else {
  //       _intake.setIndex(indexVoltage, MagStates::kManual); // will stop when it gets to the front sensor
  //     }\
  //   }
  // } else {
  //   //autoooooo
  //   _intake.setIndex(MagStates::kEmpty);
  // }
}