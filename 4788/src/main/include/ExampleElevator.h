#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

enum class TeleopElevator { kStationary = 0, kZeroing, kManual, kMoving};

class ExampleElevator {
 public:
  ExampleElevator(wml::TalonSrx &elevatorMotor, wml::actuators::DoubleSolenoid &elevatorSolenoid);

  void teleopOnUpdate(double dt);
  void autoOnUpdate(double dt);
  void testOnUpdate(double dt);

 private:
  wml::TalonSrx &_elevatorMotor;
  wml::actuators::DoubleSolenoid &_elevatorSolenoid;
};