#include "ExampleElevator.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ExampleElevator::ExampleElevator(RobotMap::ExampleElevatorSystem &exampleElevatorSystem) : _exampleElevatorSystem(exampleElevatorSystem) {
  exampleElevatorSystem.elevatorSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
}

void ExampleElevator::teleopOnUpdate(double dt) {
  
}