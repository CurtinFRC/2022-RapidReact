#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

class DrivetrainTrajectoryStrategy : public wml::Strategy {
 public:
  DrivetrainTrajectoryStrategy(std::string name, Drivetrain &drivetrain, ::Trajectory &trajectory);
  
  void OnUpdate(double dt) override; 

 private:
  Drivetrain &_drivetrain;
  ::Trajectory &_trajectory;
};
