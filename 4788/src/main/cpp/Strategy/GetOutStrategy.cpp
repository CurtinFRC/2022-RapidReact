#include "Strategy/GetOutStrategy.h"
#include <iostream>

GetOutStrategy::GetOutStrategy(std::string name, Intake &intake, Shooter &shooter, Controllers &contGroup) : Strategy(name), _intake(intake), _shooter(shooter), _contGroup(contGroup) {
  SetCanBeInterrupted(false);
  SetCanBeReused(true);
  Requires(&intake);
}

void GetOutStrategy::OnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::GetOut)) {
    std::cout << "stop getout" << std::endl;
    SetDone();
  } else {
    std::cout << "getout" << std::endl;
    _intake.GetOut();
  }
}