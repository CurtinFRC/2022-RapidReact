#include "Robot.h"

using namespace frc;
using namespace wml;

using hand = frc::XboxController::JoystickHand;

double currentTimeStamp;
double lastTimeStamp;
double dt;

double rightPower = 0;
double leftPower = 0;

double motorSpeed = 0;
double speedIntake = 0;

double constexpr deadzone = 0.05;
//srx
void Robot::RobotInit() {
	driver = new frc::XboxController(0);
	coDriver = new frc::XboxController(1);

	// //drivebase 
	_leftMotor1 = new wml::VictorSpx(3);
	_leftMotor2 = new wml::VictorSpx(4);
	_leftMotor3 = new wml::VictorSpx(5);

	_rightMotor1 = new wml::VictorSpx(6);
	_rightMotor2 = new wml::VictorSpx(7);
	_rightMotor3 = new wml::VictorSpx(8);

	// //intake 
	_victorIntake = new wml::VictorSpx(1);
	// //hammer time 
	_hammerMotor = new wml::TalonSrx(2);

	_victorIntake->SetInverted(true);
	_hammerMotor->SetInverted(false);

	_leftMotor1->SetInverted(true);
	_leftMotor2->SetInverted(true);
	_leftMotor3->SetInverted(true);

	_rightMotor1->SetInverted(false);
	_rightMotor2->SetInverted(false);
	_rightMotor3->SetInverted(false);
}

void Robot::RobotPeriodic() {}


void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
	currentTimeStamp = Timer::GetFPGATimestamp();
	dt = currentTimeStamp - lastTimeStamp;

	//its hammer time 
	//go forwards with the left trigger 
	motorSpeed = coDriver->GetTriggerAxis(hand::kLeftHand);
	if (motorSpeed >= deadzone) {
		_hammerMotor->Set(0.8);
	} else {
		_hammerMotor->Set(0);
	}

	//go backwards with the y button 
	if (coDriver->GetYButton()) {
		_hammerMotor->Set(-0.5);
	}

	//drive base, tank drive
	if (fabs(driver->GetY(hand::kRightHand)) >= deadzone) {
		leftPower = driver->GetY(hand::kRightHand);
	} else {
		leftPower = 0;
	}

	if (fabs(driver->GetY(hand::kLeftHand)) >= deadzone ) {
		rightPower = driver->GetY(hand::kLeftHand);
	} else {
		rightPower = 0;
	}

	//intake, right trigger
	speedIntake = coDriver->GetTriggerAxis(hand::kRightHand);
	if (speedIntake >= deadzone) {
		_victorIntake->Set(1);
	} else {
		_victorIntake->Set(0);
	}

	//drivebase 
	_leftMotor1->Set(leftPower);
	_leftMotor2->Set(leftPower);
	_leftMotor3->Set(leftPower);
	
	_rightMotor1->Set(rightPower);
	_rightMotor2->Set(rightPower);
	_rightMotor3->Set(rightPower);

	lastTimeStamp = currentTimeStamp;
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}