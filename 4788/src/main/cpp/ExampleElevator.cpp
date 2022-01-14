#include "ExampleElevator.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ExampleElevator::ExampleElevator(wml::TalonSrx &elevatorMotor, wml::actuators::DoubleSolenoid &elevatorSolenoid, bool &elevatorToggle) : _elevatorMotor(elevatorMotor), _elevatorSolenoid(elevatorSolenoid), _elevatorToggle(elevatorToggle) {
  _elevatorSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse); // Default State
}

void ExampleElevator::TeleopOnUpdate(double dt) {

}