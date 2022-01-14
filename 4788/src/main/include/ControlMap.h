#pragma once

#include <vector>
#include "controllers/Controllers.h"
#define __CONTROLMAP_USING_JOYSTICK__ false


struct ControlMap {
  static void InitSmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup);


  // ------------------ Values ------------------

  // Controllers
  static const int Xbox1Port, Xbox2Port;

  // USB port numbers
  static const int Driver = 1;
  static const int CoDriver = 2;

  // Deadzone
  static const double XboxDeadzone;
  static const double TriggerDeadzone;

  // PCM1
  static const int PCModule;
  static const int PressureSensorPort, CompressorPort;

  // Drivetrain

  // Intake

  // Shooter

  // Climber

  // Example Elevator
  static const int ElevatorMotorPort;
  static const int ElevatorSolenoidPort;
  static bool ElevatorToggle, ReverseElevatorToggle;


  // ------------------ Controls ------------------

  // Drivetrain

  // Intake

  // Shoter

  // Climber

  // Example Elevator
  static const wml::controllers::tAxis ExampleElevator;
  static const wml::controllers::tButton ElevatorActuation;
  static const wml::controllers::tButton ElevatorToggleButton;
};