#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"
#include "Trajectory.h"
#include "RobotControl.h"
#include "control/MotorFilters.h"


class DriveToDistanceStrategy : public wml::Strategy {
 public:
  DriveToDistanceStrategy(std::string name, Drivetrain &drivetrain, double goal);

  void OnStart() override;
  void OnUpdate(double dt) override;

 private:
  Drivetrain &_drivetrain;
  double _heading;
  double _goal;
  PID _anglePID;
  PID _distancePID;
  double _accSpeed = 0.2;
};

class DrivetrainAngleStrategy : public wml::Strategy {
 public:
  DrivetrainAngleStrategy(std::string name, Drivetrain &drivetrain, double goal);

  void SetGoal(double newGoal);
  void OnUpdate(double dt) override;
  void OnStart() override;

 private:
  Drivetrain &_drivetrain;
  double _goal;
  PID _anglePID;
  double _accSpeed = 0.2;
};