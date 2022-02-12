// #pragma once 

// #include "controllers/Controllers.h"
// #include "RobotMap.h"

// enum class ShooterState {
//   kPID,
//   kManual,
//   kIdle
// };

// class Shooter : public wml::StrategySystem {
//  public: 
//   Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);

//   void setManual(double voltage);
//   void setPID(double angularVelocity, double dt);
//   void setIndex(double voltage);

//   //PID for the shooter
//   double calculatePID(double angularVelocity, double dt);

//   void updateShooter(double dt);
//   void update(double dt);

//  private:
//   ShooterState _state{ ShooterState::kPID};
//   wml::controllers::SmartControllerGroup &_contGroup;
//   RobotMap::ShooterSystem &_shooterSystem;

//   double _flyWheelVoltage = 0;
//   double _setIndexVoltage = 0;
//   double _angularVelocityGoal = 0;
//   double _sum = 0;
//   double _previousError = 0;
// };