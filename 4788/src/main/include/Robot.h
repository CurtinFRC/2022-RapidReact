#pragma once
#include <iostream>

#include <cameraserver/CameraServer.h>
#include <frc/DriverStation.h>
#include "Toggle.h"

/**
 * Local Files 
 */
#include "ControlMap.h"
#include "RobotMap.h"
#include "Subsystems/Intake.h"
#include "Subsystems/DriveSystem.h"

class Robot : public frc::TimedRobot, protected wml::StrategyController, protected wml::NTProvider {
 public:
	void RobotInit() override;
	void RobotPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;

	void AutonomousInit() override;
	void AutonomousPeriodic() override;

	void TeleopInit() override;
	void TeleopPeriodic() override;

	void TestInit() override;
	void TestPeriodic() override;

 private:
	RobotMap robotMap;
	wml::Drivetrain *drivetrain;
	Intake *intake;
};
