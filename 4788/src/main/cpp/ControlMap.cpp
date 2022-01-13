#include "ControlMap.h"

using namespace wml;
using namespace wml::controllers;

void ControlMap::InitSmartControllerGroup(SmartControllerGroup &contGroup) {
  // Remap Here (map POV buttons to names ect)
}


// ------------------ Values ------------------

// Controller Ports
const int ControlMap::Xbox1Port = 0;
const int ControlMap::Xbox2Port = 0;

// Deadzone
const double ControlMap::xboxDeadzone = 0.1;
const double ControlMap::TriggerDeadzone = 0.15;

// PCMs
const int ControlMap::PCModule = 9;
// const int ControlMap::PressureSensorPort = 0;
// const int ControlMap::CompressorPort = 0;

// Robot Values

// Drivetrain Speed

// Intake

// Shooter

// Climber

// Example Elevator
const int ControlMap::ElevatorMotorPort = 99;
const int ControlMap::ElevatorSolenoidPort = 99;
bool ControlMap::ElevatorToggle = false, ControlMap::ReverseElevatorToggle = false;


// ------------------ Values ------------------

// Drivetrain Speed

// Intake

// Shooter

// Climber

// Example Elevator
const tButton ControlMap::ElevatorActuation{ CoDriver, XboxController::kY };
const tAxis ControlMap::ExampleElevator{ CoDriver, XboxController::kLeftThrottle };
const tButton ControlMap::ElevatorToggleButton{CoDriver, XboxController::kBumperLeft };