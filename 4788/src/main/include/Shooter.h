#pragma once 

#include "controllers/Controllers.h"
#include "RobotMap.h"

/**
 * State machine for the shooter in teleop
 * kAuto -> fot auto firing 
 * kManual -> driver controlled firing with a trigger
 * kStill -> Shooter is stationary. 
 * kTesting -> for testing :)
 */
enum class TeleopShooter {
  kAuto,
  kManual,
  kStill, //like stationary but easier to spell (kIdle)
  kTesting
  // kStill, 
  // kSpinUp,
  // kInner,
  // kOuter,
  // kManual,
  // kTesting,
  // kEject
};

//i could put a state machine inside the state machine so that 
// manual and teleop modes can have a couple of states. 

class Shooter {
 public: 
  // Shooter(rev::CANSparkMax &leftFlyWheelMotor, rev::CANSparkMax &rightFlyWheelMotor, wml::controllers::SmartControllerGroup &contGroup);
  Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup);
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
  TeleopShooter _teleopShooter{ TeleopShooter::kTesting};
  wml::controllers::SmartControllerGroup &_contGroup;

  double shooterManualSpeed = 0;
  double shooterTestingSpeed = 0;
  RobotMap::ShooterSystem &_shooterSystem;
};