#pragma once 

#include <vector>
#include "controllers/Controllers.h"

struct ControlMap {
	static void InitsmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup);

	// -------------------- Values --------------------

	//Controllers 
	static const int Xbox1Port, Xbox2Port;

	//USB port numbers 
	static const int Driver = 1;
	static const int CoDriver = 2;

	//Deadzones 
	static const double XboxDeadzone;
	static const double TriggerDeadzone;

	//PCM1 
	static const int PCModule;
	static const int PressureSensorPort, CompressorPort;

	//Driver System 
	static const int Lport, Rport;
	static const double MaxDrivetrainSpeed;
	static const double TrackWidth, TrackDepth, WheelRadius, Mass;

	//Intake 
	static const int IntakePort;
	static const int IntakeSolenoidPort1, IntakeSolenoidPort2;
	static bool IntakeToggle;


	// -------------------- Controls --------------------

	//Drivetrain
	static const wml::controllers::tAxis DrivetrainLeft, DrivetrainRight;

	//Intake 
	static const wml::controllers::tButton IntakeUp;
	static const wml::controllers::tAxis Intake, Outake;
};