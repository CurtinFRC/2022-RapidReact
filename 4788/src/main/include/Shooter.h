#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

/**
 * State machine for the shooter in teleop
 * kSpinUp -> spinning up the shooter ready to fire 
 * kInner -> shooting from the circle created by the tarmac 
 * kOuter -> shooting from the circle created by the cargo rings 
 * kManual -> shooter with trigger at a percentage speed
 */
enum class TeleopShooter {
	kStill, //like stationary but easier to spell
	kSpinUp,
	kInner,
	kOuter,
	kManual,
	kTesting,
	kEject
};

//i could put a state machine inside the state machine so that 
// manual and teleop modes can have a couple of states. 

class Shooter {
 public: 
	Shooter(rev::CANSparkMax &leftFlyWheelMotor, rev::CANSparkMax &rightFlyWheelMotor, wml::controllers::SmartControllerGroup &contGroup);

	/**
	 * 
	 */
	void teleopOnUpdate(double dt);

	/**
	 * Sets the flywheel to a specific speed,
	 * later can be called in teleopOnUpdate for different distances.
	 */
	double speed(double metersPerSecond);

	/**
	 * manual control of the shooter. 
	 */
	void manualControl(double dt);

	void testing(double dt);

 private:
	// wml::Gearbox &_flyWheel;
	TeleopShooter _teleopShooter{ TeleopShooter::kTesting};
  wml::controllers::SmartControllerGroup &_contGroup;

	rev::CANSparkMax &_leftFlyWheelMotor;
	rev::CANSparkMax &_rightFlyWheelMotor;

	double shooterManualSpeed = 0;
};