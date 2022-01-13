#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

class ExampleElevator {
 public:
  ExampleElevator(wml::TalonSrx &elevatorMotor, wml::actuators::DoubleSolenoid &elevatorSolenoid, bool &elevatorToggle);

  void TeleopOnUpdate(double dt);
  void AutoOnUpdate(double dt);
  void TestOnUpdate(double dt);

 private:
  wml::TalonSrx &_elevatorMotor;
  wml::actuators::DoubleSolenoid &_elevatorSolenoid;
  
  bool &_elevatorToggle;
};