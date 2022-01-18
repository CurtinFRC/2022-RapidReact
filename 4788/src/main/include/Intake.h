#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Intake {
 public:
	Intake(wml::TalonSrx &intakeMotor, wml::controllers::SmartControllerGroup &contGroup);


	void teleopOnUpdate(double dt);

 private:
	wml::controllers::SmartControllerGroup &_contGroup;

	wml::TalonSrx &_intakeMotor;
};