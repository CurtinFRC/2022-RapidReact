#pragma once 

#include "Intake.h"
#include "strategy/Strategy.h"

using Controllers = wml::controllers::SmartControllerGroup;

class IntakeStrategy : public wml::Strategy {
 public:
  IntakeStrategy(std::string name, Intake &intake, Controllers &contGroup);

  void OnUpdate(double dt) override;
 private:
  Intake &_intake;
  Controllers &_contGroup;

  bool indexManualToggle = false;
  bool indexOverrideToggle = false;
};