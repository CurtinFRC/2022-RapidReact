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
  static const int Driver = 1;
  static const int CoDriver = 2;

  // Deadzone
  static constexpr double XboxDeadzone = 0.15;
  static constexpr double TriggerDeadzone = 0.05;

  // PCM1
  static constexpr int PCModule = 9;
  static constexpr int PressureSensorPort = 0;
  static constexpr int CompressorPort = 0;

  // Drivetrain

  // Intake

  // Shooter

  // Climber
  inline static const wml::controllers::tButton ClimberToggle{ CoDriver, XboxController::kA };

  // Example Elevator
  static constexpr int ElevatorMotorPort = 99;
  static constexpr int ElevatorSolenoidPort = 99;
  static constexpr bool ElevatorToggle = false;
  static constexpr bool ReverseElevatorToggle = false;

  // ------------------ Controls ------------------

  // Drivetrain

  // Intake

  // Shoter

  // Climber
   static constexpr int ClimberPort = 0;
   static constexpr int ClimberSolenoidPort1 = 0;
   static constexpr int ClimberSolenoidPort2 = 0;


  // Example Elevator
  inline static const wml::controllers::tAxis Belevator{ CoDriver, XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton BelevatorActuation{ CoDriver, XboxController::kY };
  inline static const wml::controllers::tButton BelevatorToggle{ CoDriver, XboxController::kX };
};