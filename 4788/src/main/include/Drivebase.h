#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

class DrivebaseManual : public wml::Strategy {
 public:
  DrivebaseManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup);

  void OnUpdate(double dt) override;

 private:
  Drivetrain &_drivetrain;
  controllers::SmartControllerGroup &_contGroup;
  double _leftPower, _rightPower;
};