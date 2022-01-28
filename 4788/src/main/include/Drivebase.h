#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

class DrivetrainManual : public wml::Strategy {
 public:
  DrivetrainManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup);

  void OnUpdate(double dt) override;

 private:
  Drivetrain &_drivetrain;
  wml::controllers::SmartControllerGroup &_contGroup;
};