#include "Robot.h"
#include "Intake.h"

using namespace frc;
using namespace wml;

double currentTimeStamp;
double lastTimeStamp;
double dt;

// General Robot Logic
void Robot::RobotInit() {
  //Init the controllers
  ControlMap::InitSmartControllerGroup(robotMap.contGroup);

  // shooter = new Shooter(robotMap.shooterSystem.leftFlyWheelMotor, robotMap.shooterSystem.rightFlyWheelMotor, robotMap.contGroup);
  shooter = new Shooter(robotMap.shooterSystem, robotMap.contGroup);
  robotMap.shooterSystem.leftFlyWheelMotor.SetInverted(true);
  robotMap.shooterSystem.rightFlyWheelMotor.SetInverted(true);
  robotMap.shooterSystem.centerFlyWheelMotor.SetInverted(true);

  intake = new Intake(robotMap.intakeSystem, robotMap.contGroup);
  robotMap.intakeSystem.intake.SetInverted(false);

  climber = new Climber(robotMap.climberSystem, robotMap.contGroup);

  drivetrain = new Drivetrain(robotMap.drivebaseSystem.drivetrainConfig, robotMap.drivebaseSystem.gainsVelocity);

  // Zero the Encoders
  robotMap.drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.drivebaseSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  
  // Set the default strategy for drivetrain to manual
  drivetrain->SetDefault(std::make_shared<DrivebaseManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
  drivetrain->StartLoop(100);

  //Invert one side of our drivetrain so it'll drive straight
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // Register our systems to be called via strategy
  StrategyController::Register(drivetrain);
  NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {
  currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
  dt = currentTimeStamp - lastTimeStamp;

  StrategyController::Update(dt);
  robotMap.controlSystem.compressor.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  robotMap.controlSystem.compressor.Update(dt);
  NTProvider::Update();

  lastTimeStamp = currentTimeStamp;
}

// Disabled Logic
void Robot::DisabledInit() {
  InterruptAll(true);
}
void Robot::DisabledPeriodic() {
  climber->disabled(dt);
}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {
  Schedule(drivetrain->GetDefaultStrategy(), true);
}
void Robot::TeleopPeriodic() {
  shooter->teleopOnUpdate(dt);
  intake->teleopOnUpdate(dt);
  climber->teleopOnUpdate(dt);
}

// During Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {} 