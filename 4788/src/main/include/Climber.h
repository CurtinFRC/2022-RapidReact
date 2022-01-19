#pragma once

#include <iostream>
#include "controllers/Controller.h"
#include "RobotMap.h"

enum class TeleopClimber {kStationary = 0, kZeroing, kManual, kMoving};

class Climber {
	public:
		Climber(wml::actuators::DoubleSolenoid &climberSolenoid, wml::controllers::SmartControllerGroup &contGroup);

	
	void teleopOnUpdate(double dt);
	void autoOnUpdate(double dt);
	void testOnUpdate(double dt);

	private:
		bool ClimberToggle = false;
		wml::actuators::DoubleSolenoid &_climberSolenoid;
		wml::controllers::SmartControllerGroup &_contGroup;


};