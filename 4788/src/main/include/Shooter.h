#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

enum class ShooterState {
  kPID,
  kManual,
  kIdle
};

class Shooter : public wml::StrategySystem {
 public: 
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);

  void setManual(double voltage);
  void setPID(double angularVelocity, double dt);
  void setIndex(double power);

  //PID for the shooter
  double calculatePID(double angularVelocity, double dt);

  void updateShooter(double dt);
  void update(double dt);

 private:
  ShooterState _state{ ShooterState::kPID};
  wml::controllers::SmartControllerGroup &_contGroup;
  RobotMap::ShooterSystem &_shooterSystem;

  double flyWheelGoal = 0;
  double setFlyWheelVoltage = 0;
  double pidShooterSpeed = 0;
  double setIndexVoltage = 0;
  double angularVelocityGoal = 0;
};