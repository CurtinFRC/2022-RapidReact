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

  // USB port numbers
  static constexpr int driver = 0;
  static constexpr int coDriver = 1;

  // Controllers
  static constexpr int xbox1Port = driver;
  static constexpr int xbox2Port = coDriver;

  // Deadzone
  static constexpr double xboxDeadzone = 0.15;
  static constexpr double triggerDeadzone = 0.05;

  // PCM1
  static constexpr int pcModule = 9;
  static constexpr int pressureSensorPort = 0;
  static constexpr int compressorPort = 0;

  // Drivetrain
  static constexpr double trackWidth = 0.56;
  static constexpr double trackDepth = 0.60;
  static constexpr double wheelRadius = 0.0762; 
  static constexpr double mass = 50;

  static constexpr int dbLeftPort1 = 2;
  static constexpr int dbLeftPort2 = 3;

  static constexpr int dbRightPort1 = 5;
  static constexpr int dbRightPort2 = 4;

  static constexpr double maxDrivetrainPower = 0.9;


  // Intake
  static constexpr int  intakeMotorPort = 9;

  // Shooter
  static constexpr double flyWheelMass = 3;
  static constexpr int leftFlyWheelPort = 6;
  static constexpr int rightFlyWheelPort = 11;
  static constexpr int centerFlyWheelPort = 7;
  static constexpr int indexMotorPort = 8;
  inline static double shooterMaxSpeed = 0.5;
  inline static bool shooterPID = false;

  inline static double shooterEjectPower = 0.2;

  //shooter PID stuff 
  inline static double kp = 0.01;
  inline static double ki = 0.0000;  
  inline static double kd = 0.0000;
  // inline static double output_deriv_max = 2;
  inline static double IMax = 40;

  inline static double goal = 0;
  inline static double sum = 0;
  inline static double derror = 0;
  inline static double previousError = 0;
  inline static double error = 0;
  inline static double output = 0;

  // ------------------ Controls ------------------

  // Shooter
  inline static const wml::controllers::tAxis manualFlyWheel{ coDriver, XboxController::kLeftThrottle }; //used for manual control or testing the shooter

  inline static const wml::controllers::tButton innerCircleShoot{ coDriver, XboxController::kBumperLeft };
  inline static const wml::controllers::tButton outerCircleShoot{ coDriver, XboxController::kBumperRight };

  // inline static const wml::controllers::tButton pidON{ coDriver, XboxController::kBumperRight }; //used only for PID testing
  inline static const wml::controllers::tAxis indexSpin{ coDriver, XboxController::kRightYAxis };

  // inline static const wml::controllers::tButton ShooterSlow{ coDriver, XboxController::kX};
  // inline static const wml::controllers::tButton ShooterMid{ coDriver, XboxController::kY};
  // inline static const wml::controllers::tButton ShooterSpeedChange{ coDriver, XboxController::kB};
  // inline static const wml::controllers::tButton ShooterHighSpeed{ coDriver, XboxController::kA};
  inline static const wml::controllers::tButton shooterEject{ coDriver, XboxController::kA }; //switch to a POV button later


  // Drivetrain
  inline static const wml::controllers::tAxis drivebaseL{driver, XboxController::kLeftYAxis};
  inline static const wml::controllers::tAxis drivebaseR{driver, XboxController::kRightYAxis};

  // Intake
  inline static const wml::controllers::tAxis intake{ coDriver, wml::controllers::XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton intakeActuation{ coDriver, wml::controllers::XboxController::kB };
};