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
// #include <actuators/Compressor.h>
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

// #include "MP_Trajedy.h"

// WML Rev
#include <WMLRev.h>

// Local Files
#include "ControlMap.h"

static wml::physics::DcMotor mNEO { 12.0, wml::physics::DcMotor::rpm2rads(5880), 1.3, 166, 3.36 };
static wml::physics::DcMotor mFalcon500 { 12.0, wml::physics::DcMotor::rpm2rads(6380), 1.5, 257, 4.69 };

struct RobotMap {
  /**
   * Controllers
   */
  wml::controllers::XboxController xbox1{ ControlMap::xbox1Port };
  wml::controllers::XboxController xbox2{ ControlMap::xbox2Port };
  wml::controllers::XboxController xbox3{ ControlMap::xbox3Port };
  wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2, xbox3};

  /**
   * Robot Control System
   * Includes Pressure sensor and compressor
   */
  struct ControlSystem {
    wml::sensors::PressureSensor pressureSensor{ ControlMap::pressureSensorPort };
    // wml::actuators::Compressor compressor{ ControlMap::compressorPort, wml::actuators::PneumaticsModuleType::kCTRE, "Cj" };
  }; ControlSystem controlSystem;

  /**
   * Shooter subsystem 
   * 3 spark maxs into a gearbox 
   */
  struct ShooterSystem {
    wml::SparkMax leftFlyWheelMotor{ ControlMap::Shooter::leftFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};
    wml::SparkMax rightFlyWheelMotor{ ControlMap::Shooter::rightFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};
    wml::SparkMax centerFlyWheelMotor{ ControlMap::Shooter::centerFlyWheelPort, wml::SparkMax::MotorType::kNEO, 42};


    wml::actuators::MotorVoltageController shooterMotorGroup = wml::actuators::MotorVoltageController::Group(
      leftFlyWheelMotor,
      rightFlyWheelMotor,
      centerFlyWheelMotor
    );
    wml::Gearbox shooterGearbox{
      &shooterMotorGroup,
      &rightFlyWheelMotor,
      1.0, 
      mNEO * 3
    };

  }; ShooterSystem shooterSystem;

  struct DrivebaseSystem {
    wml::TalonFX leftMotor{ ControlMap::Drivetrain::leftMotorPort, 2048 };
    wml::TalonFX rightMotor{ ControlMap::Drivetrain::rightMotorPort, 2048 };

    // Motor Grouping
    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(leftMotor);
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(rightMotor);

    // Gearboxes
    wml::Gearbox LGearbox{&leftMotors, &leftMotor, 6.1, mFalcon500};
    wml::Gearbox RGearbox{&rightMotors, &rightMotor, 6.1, mFalcon500};

    wml::sensors::NavX navX{frc::SPI::Port::kMXP, 200};
    wml::sensors::NavXGyro gyro{navX.Angular(wml::sensors::AngularAxis::YAW)};

    wml::DrivetrainConfig drivetrainConfig{LGearbox, RGearbox, &gyro, ControlMap::Drivetrain::trackWidth, ControlMap::Drivetrain::trackDepth, ControlMap::Drivetrain::wheelRadius, ControlMap::Drivetrain::mass};
    wml::control::PIDGains gainsVelocity{"Drivetrain Velocity", 1};
    wml::Drivetrain drivetrain{drivetrainConfig, gainsVelocity};

  }; DrivebaseSystem drivebaseSystem;

  struct IntakeSystem {
    wml::TalonSrx intake{ControlMap::Intake::intakeMotorPort, 2048};
    wml::actuators::DoubleSolenoid intakeSolenoid{ ControlMap::pcModule, wml::actuators::PneumaticsModuleType::kREV, ControlMap::Intake::intakeSolenoidPort, ControlMap::Intake::intakeSolenoidPort2, 0.1, "CJ"};
    wml::TalonSrx indexWheel{ ControlMap::Shooter::indexMotorPort, 2048};
    wml::sensors::LimitSwitch intakeBallSensor{0, false, "kee-an"}; //ball sensor
    wml::sensors::LimitSwitch shooterBallSensor{9, false, "Sam"};
  }; IntakeSystem intakeSystem;

  struct ClimberSystem {
    wml::actuators::DoubleSolenoid climberSolenoid{ ControlMap::pcModule, wml::actuators::PneumaticsModuleType::kREV, ControlMap::Climber::climberPort1, ControlMap::Climber::climberPort2, 0.1, "Nicole"};
  }; ClimberSystem climberSystem;
};