#include "ControlMap.h"

using namespace wml;
using namespace wml::controllers;

void ControlMap::InitsmartControllerGroup(SmartControllerGroup &contGroup) {
		//Remap here (map POV buttons to names, ect.)
}

// -------------------- Values --------------------

//Controller Ports
const int ControlMap::Xbox1Port = 0;
const int ControlMap::Xbox2Port = 1;

//Deadzones
const double ControlMap::XboxDeadzone = 0.1;
const double ControlMap::TriggerDeadzone = 0.15;

//PCMs
const int ControlMap::PCModule = 9;
const int ControlMap::PressureSensorPort = 0;
const int ControlMap::CompressorPort = 0;

//Left Drive
const int ControlMap::Lport = 1;
const int ControlMap::Rport = 2;

//Drivetrain speed
const double ControlMap::MaxDrivetrainSpeed = 0.5; //never trust the drivers.

//Robot Values 
const double ControlMap::TrackWidth = 0.56;
const double ControlMap::TrackDepth = 0.60;
const double ControlMap::WheelRadius = 0.0762; //in meters 
const double ControlMap::Mass = 50; //KG's 

//Intake
const int ControlMap::IntakePort = 99; //set unknown ports to 99
const int ControlMap::IntakeSolenoidPort1 = 99;
const int ControlMap::IntakeSolenoidPort2 = 99;
bool ControlMap::IntakeToggle = false;


// -------------------- Values --------------------
const tAxis ControlMap::DrivetrainLeft{ Driver, XboxController::kLeftYAxis };
const tAxis ControlMap::DrivetrainRight{ Driver, XboxController::kRightYAxis };

//Intake 
const tButton ControlMap::IntakeUp{ CoDriver, XboxController::kY };
const tAxis ControlMap::Intake{ CoDriver, XboxController::kLeftThrottle };
const tAxis ControlMap::Outake{ CoDriver, XboxController::kRightThrottle };
