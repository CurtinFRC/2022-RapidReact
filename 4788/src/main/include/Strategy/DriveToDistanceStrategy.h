#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"
#include "Trajectory.h"
#include "RobotControl.h"


class DriveToDistanceStrategy : public wml::Strategy {
 public:
  DriveToDistanceStrategy(std::string name, Drivetrain &drivetrain, double goal);

  void OnUpdate(double dt) override;

 private:
  Drivetrain &_drivetrain;
  double _heading;
  double _goal;
  // double _accSpeed = 0;
  PID _anglePID;
  PID _distancePID;
};