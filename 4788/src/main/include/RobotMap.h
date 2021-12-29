#pragma once 

#include <string>
#include <stdint.h>

// #include <rev/CANSparkMax.h>
// #include <rev/CANEncoder.h>
// #include <WMLRev.h>
//for after kickoff when things have updated. 

#include "WMLCtre.h"

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/PWMSparkMax.h>
#include <frc/Servo.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogInput.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <networktables/NetworkTableInstance.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>

#include "controllers/Controllers.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "NTProvider.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "Drivetrain.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "sensors/PressureSensor.h"
#include "control/PIDController.h"
#include "MotionProfiling.h"
#include "Toggle.h"

#include "devices/StateDevice.h"
#include "strategy/StrategyController.h"
#include "strategy/MPStrategy.h"
#include "control/MotorFilters.h"
#include "Gearbox.h"
#include "strategy/Strategy.h"
#include "sensors/BinarySensor.h"

#include "ControlMap.h"

struct RobotMap {
	//Controllers
	wml::controllers::XboxController xbox1 { ControlMap::Xbox1Port };
	wml::controllers::XboxController xbox2 { ControlMap::Xbox2Port };
	wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2 };

	struct DriveSystem {

		//Drive motors {port, encoderTicks}
		wml::TalonFX RD{ControlMap::Lport, 2048}, LD{ControlMap::Rport, 2048}; //right and left drive

		//Motor Grouping 
		wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(LD);
		wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(RD);

		wml::Gearbox LGearbox{&leftMotors, &LD};
		wml::Gearbox RGearbox{&rightMotors, &RD};

		wml::sensors::NavX navx{};
		wml::sensors::NavXGyro gyro{navx.Angular(wml::sensors::AngularAxis::YAW)};

		wml::DrivetrainConfig drivetrainConfig{LGearbox, RGearbox, &gyro, ControlMap::TrackWidth, ControlMap::TrackDepth, ControlMap::WheelRadius, ControlMap::Mass};
		wml::control::PIDGains gainsVelocity{"Drivetrain Velocity", 1};
		wml::Drivetrain drivetrain{drivetrainConfig, gainsVelocity};
	}; DriveSystem driveSystem;

	struct ControlSystem {
		wml::sensors::PressureSensor pressureSensor{ ControlMap::PressureSensorPort };
		wml::actuators::Compressor compressor{ ControlMap::CompressorPort };
	}; ControlSystem controlSystem;

	struct IntakeSystem {
		wml::TalonSrx intakeMotor{ ControlMap::IntakePort, 2048 };
		wml::actuators::DoubleSolenoid intakeDown{ ControlMap::PCModule, ControlMap::IntakeSolenoidPort1, ControlMap::IntakeSolenoidPort2, 0.1 };
	}; IntakeSystem intakeSystem;
};