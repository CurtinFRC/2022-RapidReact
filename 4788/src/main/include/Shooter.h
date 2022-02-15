#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"
#include "control/PIDController.h"

enum class ShooterState {
  kPID,
  kManual,
  kIdle
};

class Shooter : public wml::StrategySystem, public wml::loops::LoopSystem {
 public: 
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);

  void setManual(double voltage);
  void setPID(double angularVelocity, double dt);

  //PID for the shooter
  double calculatePID(double angularVelocity, double dt);

  void updateShooter(double dt);
  void Update(double dt) override;

  void SetIsDoneThreshold(double threshAvgPos, double threshAvgVel);
  bool isDone();

  bool readyToFire = false;

 private:
  ShooterState _state{ ShooterState::kPID};
  wml::controllers::SmartControllerGroup &_contGroup;
  RobotMap::ShooterSystem &_shooterSystem;

  wml::control::LinearFilter _filterPos, _filterVel;

  double _flyWheelVoltage = 0;
  double _setIndexVoltage = 0;
  double _angularVelocityGoal = 0;
  double _sum = 0;
  double _previousError = 0;

  double _threshAvgPos = 20;
  double _threshAvgVel = 8;
  int _iterations = 0;
  double _avgVel = 0;
  double _avgPos = 0;


  //called in the intake class
};