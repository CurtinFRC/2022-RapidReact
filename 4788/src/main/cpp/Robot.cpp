#include "Robot.h"

using namespace frc;
// using namespace wml;

const int deadzone = 0.15;
bool pressed = false;


// Intake Wheel Motors
wml::TalonSrx wheelMotorL{99};
wml::TalonSrx wheelMotorR{99};

// Solenoids
wml::actuators::DoubleSolenoid pistonL{0, 1, 0.2};
wml::actuators::DoubleSolenoid pistonR{99, 99, 0.2};

// Compressor
wml::actuators::Compressor compressor{99};

// Xbox Controller
wml::controllers::XboxController xbox{1};

void Robot::RobotInit() {}

void Robot::RobotPeriodic() {
	compressor.SetTarget(wml::actuators::kForward);
}

void Robot::DisabledInit() {
	InterruptAll(true);
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {
	wheelMotorL.SetInverted(true);
	wheelMotorR.SetInverted(false);
}

void Robot::TeleopPeriodic() {
	double wheelSpeed = 0;

	if(xbox.GetButton(xbox.kX)) {
		pressed = true;
	}

	// Intake Wheels
	if(xbox.GetAxis(xbox.kLeftThrottle) >= deadzone) {
		wheelSpeed += xbox.GetAxis(xbox.kRightThrottle);
	}

	// Outake Wheels
	if(xbox.GetAxis(xbox.kRightThrottle) >= deadzone) {
		wheelSpeed += -xbox.GetAxis(xbox.kRightThrottle);
	}

	// Intake Pistons
	if(pressed == true) {
		pistonL.SetTarget(wml::actuators::kForward);
		pistonR.SetTarget(wml::actuators::kForward);
	} 
	
	if(pressed == false) {
		pistonL.SetTarget(wml::actuators::kReverse);
		pistonR.SetTarget(wml::actuators::kReverse);
	}

	wheelMotorL.Set(wheelSpeed);
	wheelMotorR.Set(wheelSpeed);

}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}