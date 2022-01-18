#include "Robot.h"

using namespace frc;
using namespace wml;

double currentTimeStamp;
double lastTimeStamp;
double dt;

// General Robot Logic
void Robot::RobotInit() {

	//Init the controllers
	ControlMap::InitSmartControllerGroup(robotMap.contGroup);

	// belevator = new Belevator(robotMap.belevatorSystem.belevatorMotor, robotMap.belevatorSystem.belevatorSolenoid);

	shooter = new Shooter(robotMap.shooterSystem.leftFlyWheelMotor, robotMap.shooterSystem.rightFlyWheelMotor, robotMap.contGroup);
	robotMap.shooterSystem.leftFlyWheelMotor.SetInverted(true);
	robotMap.shooterSystem.rightFlyWheelMotor.SetInverted(true);

}
void Robot::RobotPeriodic() {
	currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
	dt = currentTimeStamp - lastTimeStamp;

	// StrategyController::Update(dt);

	// robotMap.controlSystem.compressor.SetTarget(wml::actuators::BinaryActuatorState::kForward);
	// robotMap.controlSystem.compressor.Update(dt);

	// NTProvider::Update();

	lastTimeStamp = currentTimeStamp;
}

// Disabled Logic
void Robot::DisabledInit() {
	InterruptAll(true);
}
void Robot::DisabledPeriodic() {}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
	// belevator->teleopOnUpdate(dt);
	shooter->teleopOnUpdate(dt);
}

// During Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {}