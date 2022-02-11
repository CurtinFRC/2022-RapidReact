#pragma once

#include <vector>
#include "controllers/Controllers.h"

#define __CONTROLMAP_USING_JOYSTICK__ false

using namespace wml;
using namespace wml::controllers;

struct ControlMap { 
  // USB port numbers
  static constexpr int driver = 0;
  static constexpr int coDriver = 1;

  static void InitSmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup) {
    contGroup.GetController(ControlMap::shoot.cont).Map(ControlMap::shoot, {
      { Controller::POVPos::kLeft, ControlMap::farShoot },
      { Controller::POVPos::kRight, ControlMap::noahShoot },
      { Controller::POVPos::kBottom, ControlMap::shooterEject }
    });
  }

  // ------------------ Values ------------------


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

  static constexpr int leftMotorPort = 99;
  static constexpr int rightMotorPort = 99;

  static constexpr double maxDrivetrainPower = 0.5; //never trust drivers


  // Intake
  static constexpr int  intakeMotorPort = 9;

  // Shooter
  static constexpr int leftFlyWheelPort = 99;
  static constexpr int rightFlyWheelPort = 99;
  static constexpr int centerFlyWheelPort = 99;
  static constexpr int indexMotorPort = 8;
  inline static bool shooterPID = false;

  inline static double shooterEjectPower = 0.2;
  inline static double innerCircleShootValue = 200;
  inline static double outerCircleShootValue = 400;
  inline static double farShootValue = 500;
  inline static double noahShootValue = 600;

  //shooter PID stuff 
  inline static double kp = 0.46;
  inline static double ki = 0;  
  inline static double kd = -0.00001;
  inline static double IMax = 40;

  // Climber
  static constexpr int climberPort = 99;
  static constexpr int climberPort1 = 99;
  static constexpr int climberPort2 = 99;

  // ------------------ Controls ------------------

  // Shooter
  inline static const wml::controllers::tAxis manualFlyWheel{ coDriver, XboxController::kLeftThrottle }; //used for manual control or testing the shooter
  inline static const wml::controllers::tButton innerCircleShoot{ coDriver, XboxController::kBumperLeft };
  inline static const wml::controllers::tButton outerCircleShoot{ coDriver, XboxController::kBumperRight };

  // inline static const wml::controllers::tButton pidON{ coDriver, XboxController::kBumperRight }; //used only for PID testing
  inline static const wml::controllers::tAxis indexSpin{ coDriver, XboxController::kRightYAxis };
  inline static const wml::controllers::tButton shooterEject{ coDriver, __LINE__ + 30 }; //switch to a POV button later

  inline static const wml::controllers::tPOV shoot{ coDriver, 0};
  inline static const wml::controllers::tButton farShoot{ coDriver, __LINE__ + 30 };
  inline static const wml::controllers::tButton noahShoot{ coDriver, __LINE__ + 30 }; //haha get it, like noahtunes launch pad

  // Drivetrain
  inline static const wml::controllers::tAxis leftDrive{driver, XboxController::kLeftYAxis};
  inline static const wml::controllers::tAxis rightDrive{driver, XboxController::kRightYAxis};

  // Climber
  inline static const wml::controllers::tButton climberToggle{ coDriver, XboxController::kA };

  // Intake
  inline static const wml::controllers::tAxis intake{ coDriver, wml::controllers::XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton intakeActuation{ coDriver, wml::controllers::XboxController::kB };
};