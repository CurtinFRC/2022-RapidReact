#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

enum class TeleopShooter {
  kAuto,
  kManual,
  kIdle,
  kTesting,
  kekekekek
};

class Shooter : public wml::StrategySystem {
 public: 
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);

  void setFlywheel(double power);
  void setIndex(double power);
  void setAuto(double goal, double dt);
  double speed(double goal, double dt);

  void updateShooter(double dt);
  void update(double dt);

 private:
  TeleopShooter _teleopShooter{ TeleopShooter::kAuto};
  wml::controllers::SmartControllerGroup &_contGroup;

  double shooterManualSpeed = 0;
  double shooterTestingSpeed = 0;
  RobotMap::ShooterSystem &_shooterSystem;
  double shooterSpeed;

  double flyWheelGoal = 0;
  double setFlyWheelPower = 0;
  double pidShooterSpeed = 0;
  double setIndexPower = 0;
};