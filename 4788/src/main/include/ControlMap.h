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
  static constexpr int  intakeMotorPort = 99;
  static constexpr int  intakeMotorPort_2 = 99;
  static constexpr bool intakeSolenoid = false;
  static constexpr int  intakeSolenoidPort = 99;

  // Shooter
  static constexpr int leftFlyWheelPort = 10;
  static constexpr int rightFlyWheelPort = 13;
  static constexpr double flyWheelMass = 3;

  //shooter PID stuff 
  static constexpr double kp = 0.01;
  static constexpr double ki = 0.0001;
  static constexpr double kd = 0.00001;

  static constexpr double goal = 0;
  static constexpr double sum = 0;
  static constexpr double derror = 0;
  static constexpr double previousError = 0;

  // Climber
  static constexpr int ClimberPort = 99;
  static constexpr int leftClimberPort1 = 99;
  static constexpr int leftClimberPort2 = 99;
  static constexpr int rightClimberPort1 = 99;
  static constexpr int rightClimberPort2 = 99;

  // ------------------ Controls ------------------

  // Shooter
  inline static const wml::controllers::tAxis ShooterManualSpin{ CoDriver, XboxController::kLeftThrottle }; //used for manual control or testing the shooter

  // Drivetrain
  inline static const wml::controllers::tAxis drivebaseL{Driver, XboxController::kLeftYAxis};
  inline static const wml::controllers::tAxis drivebaseR{Driver, XboxController::kRightYAxis};
  
  // Climber
 inline static const wml::controllers::tButton ClimberToggle{ CoDriver, XboxController::kA };
   


  // Intake
  inline static const wml::controllers::tAxis Intake{ CoDriver, wml::controllers::XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton IntakeActuation{ CoDriver, wml::controllers::XboxController::kB };
};