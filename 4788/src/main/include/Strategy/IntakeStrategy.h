#pragma once 

#include "Intake.h"
#include "Shooter.h"
#include "strategy/Strategy.h"

using Controllers = wml::controllers::SmartControllerGroup;

class IntakeStrategy : public wml::Strategy {
 public:
  IntakeStrategy(std::string name, Intake &intake, Shooter &shooter, Controllers &contGroup);

  void OnUpdate(double dt) override;
 private:
  Intake &_intake;
  Shooter &_shooter;
  Controllers &_contGroup;

  bool indexManualToggle = false;
  bool indexOverrideToggle = false;
  bool _intakeToggle = false;
  bool intakeManualToggle = false;
};

class IntakeAutoStrategy : public wml::Strategy {
 public:
  IntakeAutoStrategy(std::string name,  Intake &intake, bool twoBall, bool passive = false);

  void OnUpdate(double dt) override;
 private:

  Debounce humanPlayerWait{3.5};

  Intake &_intake;
  bool _twoBall = false;
  bool _passive = false; //TODO @Jaci add getter to wml
};