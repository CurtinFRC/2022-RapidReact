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
  ShooterShootStrategy(std::string name, Shooter &shooter, Intake &intake, double angularVelocity, bool twoBall);

  void OnUpdate(double dt) override;
 private:
  Shooter &_shooter;
  Intake &_intake;
  double _angularVelocity = 0.0;
  bool _twoBall = false;
  int autoShooterIterations = 0;
};
