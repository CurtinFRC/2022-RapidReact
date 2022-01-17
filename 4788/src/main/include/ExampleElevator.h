#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

enum class TeleopElevator { kStationary = 0, kZeroing, kManual, kMoving};

class ExampleElevator {
 public:
  ExampleElevator(RobotMap::ExampleElevatorSystem &exampleElevatorSystem);

  void teleopOnUpdate(double dt);
  void autoOnUpdate(double dt);
  void testOnUpdate(double dt);

 private:
  RobotMap::ExampleElevatorSystem &_exampleElevatorSystem;
};