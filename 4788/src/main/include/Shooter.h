#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"
#include "control/PIDController.h"

enum class ShooterState {
  kPID,
  kManual,
  kIdle,
  kRaw
};

inline std::string shooter_state_to_string(ShooterState &state) {
  switch (state) {
    case ShooterState::kIdle:
      return "Idle";
    case ShooterState::kManual:
      return "Manual";
    case ShooterState::kPID:
      return "PID";
    case ShooterState::kRaw:
      return "Raw";
  }
}

class Shooter : public wml::StrategySystem, public wml::loops::LoopSystem {
 public: 
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);

  void setManual(double voltage);
  void setPID(double angularVelocity, double dt);

  //PID for the shooter
  double calculatePID(double angularVelocity, double dt);

  void updateShooter(double dt);
  void Update(double dt) override;

  void GetOut(double dt, double power);

  void SetIsDoneThreshold(double threshAvgPos, double threshAvgVel);
  bool isDone();

  ShooterState getShooterState();

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

  double _threshAvgPos = 25;
  double _threshAvgVel = 5;
  int _iterations = 0;
  double _avgVel = 0;
  double _avgPos = 0;

  double manualOutput = 0;

  double _rawPower = 0;

  //called in the intake class
};