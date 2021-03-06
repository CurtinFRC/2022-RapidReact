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
  static constexpr int tester = 2;

  static void InitSmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup) {
    contGroup.GetController(ControlMap::shoot.cont).Map(ControlMap::shoot, {
      { Controller::POVPos::kLeft, ControlMap::farShoot },
      { Controller::POVPos::kRight, ControlMap::noahShoot },
      { Controller::POVPos::kBottom, ControlMap::shooterEject },
      { Controller::POVPos::kBottom, ControlMap::indexManualToggleButton},
      { Controller::POVPos::kTop, ControlMap::indexManualStop },
    });
  }

  // ------------------ Values ------------------
  //structmap 2 electric boogaloo

  // Controllers  
  static constexpr int xbox1Port = driver;
  static constexpr int xbox2Port = coDriver;
  static constexpr int xbox3Port = tester;

  // Deadzone
  static constexpr double xboxDeadzone = 0.15;
  static constexpr double triggerDeadzone = 0.05;

  // PCM1
  static constexpr int pcModule = 1;
  static constexpr int pressureSensorPort = 1;
  static constexpr int compressorPort = 1;

  

  // Drivetrain
  struct Drivetrain {
    static constexpr double trackWidth = 0.56;
    static constexpr double trackDepth = 0.60;
    static constexpr double wheelRadius = 0.0508; 
    static constexpr double mass = 50;

    static constexpr int leftMotorPort = 6;
    static constexpr int rightMotorPort = 7;

    static constexpr double maxDrivetrainPower = 0.5; //never trust drivers
  };

  struct Intake {
    static constexpr int  intakeMotorPort = 5;
    static constexpr bool intakeSolenoid = false;
    static constexpr int  intakeSolenoidPort = 10; //11   9
    static constexpr int intakeSolenoidPort2 = 8; //15   11

    // static constexpr double 
  };

  struct Shooter {
    static constexpr int leftFlyWheelPort = 11;
    static constexpr int rightFlyWheelPort = 12;
    static constexpr int centerFlyWheelPort = 13;
    static constexpr int indexMotorPort = 4;
    inline static bool shooterPID = false;

    inline static double shooterEjectPower = 0.8;
    inline static double innerCircleShootValue = 200;
    inline static double outerCircleShootValue = 300;
    inline static double farShootValue = 400;
    inline static double noahShootValue = 500;
  };
  

  struct ShooterGains {
    inline static double kp = 0.002; //0.002
    inline static double ki = 0.0005; //0.0005
    inline static double kd = -0.001; //-0.001
    inline static double IMax = 100;
  };

  struct Climber {
    static constexpr int climberPort = 99;
    static constexpr int climberPort1 = 11; //14 up   8
    static constexpr int climberPort2 = 9; //12 down   10
  };

  // ------------------ Controls ------------------

  // Shooter
  inline static const wml::controllers::tAxis manualFlyWheel{ coDriver, XboxController::kLeftThrottle }; //used for manual control or testing the shooter
  inline static const wml::controllers::tButton innerCircleShoot{ coDriver, XboxController::kBumperLeft };
  inline static const wml::controllers::tButton outerCircleShoot{ coDriver, XboxController::kBumperRight };

  // inline static const wml::controllers::tButton pidON{ coDriver, XboxController::kBumperRight }; //used only for PID testing
  inline static const wml::controllers::tAxis indexSpin{ coDriver, XboxController::kRightYAxis };
  inline static const wml::controllers::tButton shooterEject{ driver, __LINE__ + 30 }; //switch to a POV button later

  inline static const wml::controllers::tPOV shoot{ coDriver, 0};
  inline static const wml::controllers::tButton farShoot{ coDriver, __LINE__ + 30 };
  inline static const wml::controllers::tButton noahShoot{ coDriver, __LINE__ + 30 }; //haha get it, like noahtunes launch pad

  // Drivetrain
  inline static const wml::controllers::tAxis leftDrive{driver, XboxController::kLeftYAxis};
  inline static const wml::controllers::tAxis rightDrive{driver, XboxController::kRightYAxis};

  // Climber
  inline static const wml::controllers::tButton climberActuate{ coDriver, wml::controllers::XboxController::kY };

  // Intake
  inline static const wml::controllers::tAxis intake{ coDriver, wml::controllers::XboxController::kLeftYAxis };
  inline static const wml::controllers::tButton intakeActuation{ coDriver, wml::controllers::XboxController::kB };

  inline static const wml::controllers::tButton indexManualToggleButton{ driver, wml::controllers::XboxController::kX };
  inline static const wml::controllers::tButton indexManualStop{ driver, wml::controllers::XboxController::kB };

  inline static const wml::controllers::tButton intakeManualToggle{ coDriver, wml::controllers::XboxController::kA };

  inline static const wml::controllers::tButton fire{ coDriver, wml::controllers::XboxController::kX };

  inline static const wml::controllers::tAxis testingIndex{ coDriver, wml::controllers::XboxController::kRightYAxis };
  inline static const wml::controllers::tAxis testingIntake{ tester, wml::controllers::XboxController::kRightYAxis };

  inline static const wml::controllers::tButton GetOut{ driver, wml::controllers::XboxController::kY };
  inline static const wml::controllers::tButton GetOutBoogalloo{ driver, wml::controllers::XboxController::kA };
};