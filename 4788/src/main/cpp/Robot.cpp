#include "Robot.h"

using namespace frc;
using namespace wml;

double currentTimeStamp;
double lastTimeStamp;
double dt;

void Robot::RobotInit() {
	ControlMap::InitsmartControllerGroup(robotMap.contGroup);

	intake = new Intake(robotMap.intakeSystem.intakeMotor, robotMap.intakeSystem.intakeDown);
	robotMap.intakeSystem.intakeMotor.SetInverted(false);

	drivetrain = new Drivetrain(robotMap.driveSystem.drivetrainConfig, robotMap.driveSystem.gainsVelocity);

	robotMap.driveSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
	robotMap.driveSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();

	drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
	drivetrain->StartLoop(100);

	drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);
	drivetrain->GetConfig().leftDrive.transmission->SetInverted(false);

	StrategyController::Register(drivetrain);
	NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {
	currentTimeStamp = frc::Timer::GetFPGATimestamp();
	dt = currentTimeStamp - lastTimeStamp;

	StrategyController::Update(dt);
	NTProvider::Update();

	lastTimeStamp = currentTimeStamp;
}


void Robot::DisabledInit() {
	InterruptAll(true);
}
void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {
	Schedule(drivetrain->GetDefaultStrategy(), true);
}
void Robot::TeleopPeriodic() {
	intake->TeleopOnUpdate(dt);
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}