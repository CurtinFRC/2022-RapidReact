#include "Strategy/IntakeStrategy"
#include <iostream>

IntakeStrategy::IntakeStrategy(std::string name, Intake &intake, Controllers &contGroup) : Strategy(name), _intake(intake), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&intake);
}

void IntakeStrategy::OnUpdate(double dt) {
  // manualIntakePower = fabs(_contGroup.Get(ControlMap::intake)) > fabs(ControlMap::xboxDeadzone) ? _contGroup.Get(ControlMap::intake) : 0;
  // setIntake(manualIntakePower);

  // if (_contGroup.Get(ControlMap::intakeActuation, wml::controllers::XboxController::ONRISE)) {
  //   _toggleIntake();
  // }
}