#pragma once 

#include "Intake.h"
#include "Shooter.h"
#include "strategy/Strategy.h"

using Controlllers = wml::controllers::SmartControllerGroup;

class GetOutStrategy : public wml::Strategy {
 public:
  GetOutStrategy(std::string name, Intake &intake, Shooter &shooter, Controllers &contGroup);

  void OnUpdate(double dt) override;
 private:
  Intake &_intake;
  Shooter &_shooter;
  Controllers &_contGroup;

  frc::Timer GetOutTimer;
  double _power = 5;
};