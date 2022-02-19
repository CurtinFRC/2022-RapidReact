#pragma once 

#include "Shooter.h"
#include "Intake.h"
#include "strategy/Strategy.h"

using Controllers = wml::controllers::SmartControllerGroup;

class ShooterManualStrategy : public wml::Strategy {
 public:
  ShooterManualStrategy(std::string name, Shooter &shooter, Controllers &contGroup);

  void OnUpdate(double dt) override;
 private:
  Shooter &_shooter;
  Controllers &_contGroup;
};

class ShooterSpinUpStrategy : public wml::Strategy {
 public:
  ShooterSpinUpStrategy(std::string name, Shooter &shooter, double angularVelocity);

  void OnUpdate(double dt) override;
 private:
  Shooter &_shooter;
  double _angularVelocity = 0.0;
};

class ShooterShootStrategy : public wml::Strategy {
 public:
  ShooterShootStrategy(std::string name, Shooter &shooter, Intake &intake, double angularVelocity);

  void OnUpdate(double dt) override;
 private:

  Debounce db{0.25};
  Debounce emptyDB{0.1};

  Shooter &_shooter;
  Intake &_intake;
  double _angularVelocity = 0.0;
  int autoShooterIterations = 0;
};
