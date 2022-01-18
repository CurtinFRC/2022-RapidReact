#pragma once

#include <vector>
#include "controllers/Controllers.h"

#define __CONTROLMAP_USING_JOYSTICK__ false

using namespace wml;
using namespace wml::controllers;

struct ControlMap {
  static void InitSmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup) {
  //remap Here (map POV buttons to names ect)
  }

  // ------------------ Values ------------------

  // Controllers
  static constexpr int Xbox1Port = 0;
  static constexpr int Xbox2Port = 1;

  // USB port numbers
  static constexpr int Driver = 1;
  static constexpr int CoDriver = 2;

  // Deadzone
  static constexpr double XboxDeadzone = 0.15;
  static constexpr double TriggerDeadzone = 0.05;

  // PCM1
  static constexpr int PCModule = 9;
  static constexpr int PressureSensorPort = 0;
  static constexpr int CompressorPort = 0;

  // Drivetrain
  static constexpr double TrackWidth = 0.56;
  static constexpr double TrackDepth = 0.60;
  static constexpr double WheelRadius = 0.0762; 
  static constexpr double Mass = 50;

  static constexpr int dbLeftPort1 = 99;
  static constexpr int dbLeftPort2 = 99;

  static constexpr int dbRightPort1 = 99;
  static constexpr int dbRightPort2 = 99;

  // Intake

  // Shooter

  // Climber

  // Example Elevator
  static constexpr int ElevatorMotorPort = 99;
  static constexpr int ElevatorSolenoidPort = 99;
  static constexpr bool ElevatorToggle = false;
  static constexpr bool ReverseElevatorToggle = false;

  // ------------------ Controls ------------------

  // Drivetrain
  inline static const wml::controllers::tAxis drivebaseL{Driver, XboxController::kLeftYAxis};
  inline static const wml::controllers::tAxis drivebaseR{Driver, XboxController::kRightYAxis};
  
  // Intake

  // Shoter

  // Climber

  // Example Elevator
  inline static const wml::controllers::tAxis Belevator{ CoDriver, XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton BelevatorActuation{ CoDriver, XboxController::kY };
  inline static const wml::controllers::tButton BelevatorToggle{ CoDriver, XboxController::kX };
};