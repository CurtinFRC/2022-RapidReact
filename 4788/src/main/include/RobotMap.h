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

#include "MP_Trajedy.h"

// WML Rev
#include <WMLRev.h>

// Local Files
#include "ControlMap.h"

static wml::physics::DcMotor mNEO { 12.0, wml::physics::DcMotor::rpm2rads(5880), 1.3, 166, 3.36 };

struct RobotMap {
  /**
   * Controllers
   */
  wml::controllers::XboxController xbox1{ ControlMap::xbox1Port };
  wml::controllers::XboxController xbox2{ ControlMap::xbox2Port };
  wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2};

  /**
   * Robot Control System
   * Includes Pressure sensor and compressor
   */
  struct ControlSystem {

  }; ControlSystem controlSystem;

  /**
   * Shooter subsystem 
   * 3 spark maxs into a gearbox 
   */
  struct ShooterSystem {
    wml::SparkMax leftFlyWheelMotor{ ControlMap::leftFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};
    wml::SparkMax rightFlyWheelMotor{ ControlMap::rightFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};
    wml::SparkMax centerFlyWheelMotor{ ControlMap::centerFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};

    wml::TalonSrx indexWheel{ ControlMap::indexMotorPort, 2048};

    wml::actuators::MotorVoltageController shooterMotorGroup = wml::actuators::MotorVoltageController::Group(leftFlyWheelMotor, rightFlyWheelMotor, centerFlyWheelMotor);
    wml::Gearbox shooterGearbox{
      &shooterMotorGroup,
      &leftFlyWheelMotor,
      1.0, 
      mNEO * 3
    };
  }; ShooterSystem shooterSystem;

  struct DrivebaseSystem {
    // Drivetrain Left Motors
    wml::TalonSrx dbLeftMotor1{ControlMap::dbLeftPort1, 2048};
    wml::TalonSrx dbLeftMotor2{ControlMap::dbLeftPort2, 2048};

    // Drivetrain Right Motors
    wml::TalonSrx dbRightMotor1{ControlMap::dbRightPort1, 2048};
    wml::TalonSrx dbRightMotor2{ControlMap::dbRightPort2, 2048};
    
    // Motor Grouping
    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(dbLeftMotor1, dbLeftMotor2);
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(dbRightMotor1, dbRightMotor2);

    // Gearboxes
    wml::Gearbox LGearbox{&leftMotors, &dbLeftMotor1};
    wml::Gearbox RGearbox{&rightMotors, &dbRightMotor1};

    wml::sensors::NavX navX{};
    wml::sensors::NavXGyro gyro{navX.Angular(wml::sensors::AngularAxis::YAW)};

    wml::DrivetrainConfig drivetrainConfig{LGearbox, RGearbox, &gyro, ControlMap::trackWidth, ControlMap::trackDepth, ControlMap::wheelRadius, ControlMap::mass};
    wml::control::PIDGains gainsVelocity{"Drivetrain Velocity", 1};
    wml::Drivetrain drivetrain{drivetrainConfig, gainsVelocity};

  }; DrivebaseSystem drivebaseSystem;

  struct IntakeSystem {
    wml::TalonSrx intake{ControlMap::intakeMotorPort, 2048};
  }; IntakeSystem intakeSystem;

};