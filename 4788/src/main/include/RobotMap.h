#pragma once 

// General
#include <string>
#include <stdint.h>


// FRC/WPI
#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

#include <cameraserver/CameraServer.h>
#include <frc/DriverStation.h>

#include <frc/SpeedControllerGroup.h>
#include <frc/PowerDistribution.h>
#include <frc/Servo.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogInput.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <networktables/NetworkTableInstance.h>
#include <wpi/SmallString.h>

// WML
#include <WMLCtre.h>
#include <controllers/Controllers.h>
#include <actuators/BinaryServo.h>
#include <actuators/Compressor.h>
#include <NTProvider.h>
#include <actuators/DoubleSolenoid.h>
#include <actuators/VoltageController.h>
#include <Drivetrain.h>
#include <sensors/Encoder.h>
#include <sensors/LimitSwitch.h>
#include <sensors/NavX.h>
#include <sensors/PressureSensor.h>
#include <control/PIDController.h>
#include <MotionProfiling.h>
#include <Toggle.h>

#include <devices/StateDevice.h>
#include <strategy/StrategyController.h>
#include <strategy/MPStrategy.h>
#include <control/MotorFilters.h>
#include <Gearbox.h>
#include <strategy/Strategy.h>
#include <sensors/BinarySensor.h>
#include <rev/CANSparkMax.h>

// WML Rev
#include <WMLRev.h>

// Local Files
#include "ControlMap.h"

struct RobotMap {
  /**
   * Controllers
   */
  wml::controllers::XboxController xbox1{ ControlMap::Xbox1Port };
  wml::controllers::XboxController xbox2{ ControlMap::Xbox2Port };
  wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2};

  /**
   * Robot Control System
   * Includes Pressure sensor and compressor
  //  */
  // struct ControlSystem {
  //   wml::sensors::PressureSensor pressureSensor{ ControlMap::PressureSensorPort };
  //   wml::actuators::Compressor compressor{ ControlMap::CompressorPort, wml::actuators::PneumaticsModuleType::kCTRE, "Cj" };
  // }; ControlSystem controlSystem;

  /**
   * Example elevator system 
   * includes a TalonSrx motor controlling the upwards linear motion
   * includes a solenoid to move the elevator up and down
   */
  // struct BelevatorSystem {
  //   wml::TalonSrx belevatorMotor{ControlMap::BelevatorMotorPort, 2048};
  //   wml::actuators::DoubleSolenoid belevatorSolenoid{ ControlMap::PCModule, ControlMap::BelevatorSolenoidPort, 0.1};
  // }; BelevatorSystem belevatorSystem;

  /**
   * Shooter subsystem 
   * 2 spark maxs into a gearbox 
  //  */
  struct ShooterSystem {
    // wml::SparkMax leftFlyWheelMotor{ 10, wml::SparkMax::MotorType::kNEO , 42 };
    // wml::SparkMax rightFlyWheelMotor{ ControlMap::rightFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42 };
    rev::CANSparkMax leftFlyWheelMotor{6, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax rightFlyWheelMotor{7, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    // wml::actuators::MotorVoltageController shooterMotorGroup = wml::actuators::MotorVoltageController::Group(leftFlyWheelMotor, rightFlyWheelMotor);
    // wml::Gearbox ShooterGearbox{&shooterMotorGroup, &leftFlyWheelMotor};
  }; ShooterSystem shooterSystem;

  struct IntakeSystem {
    wml::TalonSrx intakeMotor{ 99, 2048 };
  }; IntakeSystem intakeSystem;

  struct DriveSystem {
    wml::TalonSrx FrontLeft{ ControlMap::frontLeftPort, 2048}, BackLeft{ ControlMap::backLeftPort, 2048};
    wml::TalonSrx FrontRight{ ControlMap::frontRightPort, 2048}, BackRight{ ControlMap::backRightPort, 2048};

    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(FrontLeft, BackLeft);
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(FrontRight, BackRight);

    wml::Gearbox LGearbox{&leftMotors, &FrontLeft };
    wml::Gearbox RGearbox{&rightMotors, &FrontRight };

    wml::sensors::NavX navx{};
    wml::sensors::NavXGyro gyro{navx.Angular(wml::sensors::AngularAxis::YAW)};

    wml::DrivetrainConfig drivetrainConfig{LGearbox, RGearbox, &gyro, ControlMap::TrackWidth, ControlMap::TrackDepth, ControlMap::WheelRadius, ControlMap::Mass };
    wml::control::PIDGains gainsVelocity{"Drivetrain velocity", 1};
    wml::Drivetrain drivetrain{drivetrainConfig, gainsVelocity };
  }; DriveSystem driveSystem;
};