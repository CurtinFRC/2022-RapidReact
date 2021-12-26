#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Intake {
 public:
	Intake(wml::TalonSrx &intakeMotor, wml::actuators::DoubleSolenoid &IntakeSolenoid);

	void TeleopOnUpdate(double dt);
	void AutoOnUpdate(double dt);
	void TestOnUpdate(double dt);

 private:
	wml::TalonSrx &_intakeMotor;
	wml::actuators::DoubleSolenoid &_intakeSolenoid;
};