#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

class Auto {
public:
  Auto(RobotMap::DrivebaseSystem &drivebaseSystem) : _drivebaseSystem(drivebaseSystem) {}
  void Init();
  void Periodic();

private:
  RobotMap::DrivebaseSystem &_drivebaseSystem;
};