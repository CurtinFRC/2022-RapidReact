#include "Shooter.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {

}

void Shooter::teleopOnUpdate(double dt) {
  // TODO @Anna decide which case to switch to

  switch (_teleopShooter) {
    case TeleopShooter::kAuto:
      //left bumper for close shot, right bumper for far shot, POV button 
      // if (_contGroup.Get(ControlMap::shortShoot)) {
      //   speed(8, dt);
      // }
      break;
    case TeleopShooter::kStill:

      break;
    case TeleopShooter::kManual:

      manualControl(dt);

      break;
    case TeleopShooter::kTesting:
      testing(dt);
      break;
    default:
      break;
  }
}

//TODO @Anna figure out PID algorithm stuff
/**
  * Needs to be a closed loop PID system 
  * 
  */
double Shooter::speed(double metersPerSecond, double dt) {

  // take the encoder read out of the 3 NEOs and average them
  double leftFlyWheelEncoder = _shooterSystem.leftFlyWheelMotor.GetEncoderRotations();
  double rightFlyWheelEncoder = _shooterSystem.rightFlyWheelMotor.GetEncoderRotations();
  double centerFlyWheelEncoder = _shooterSystem.centerFlyWheelMotor.GetEncoderRotations();

  double input = (leftFlyWheelEncoder + rightFlyWheelEncoder + centerFlyWheelEncoder) / 3;

  ControlMap::error = ControlMap::goal - input;
  ControlMap::derror = (ControlMap::error - ControlMap::previousError) / dt;
  ControlMap::sum = ControlMap::sum + ControlMap::error * dt;

  ControlMap::output = ControlMap::kp * ControlMap::error + ControlMap::ki * ControlMap::sum + ControlMap::kd * ControlMap::derror;
  ControlMap::previousError = ControlMap::error;

  return ControlMap::output;
}


/**
  * Left trigger controls the shooter manually
  */
void Shooter::manualControl(double dt) {
  shooterManualSpeed = fabs(_contGroup.Get(ControlMap::ShooterManualSpin)) > ControlMap::TriggerDeadzone ? _contGroup.Get(ControlMap::ShooterManualSpin) : 0;

  _shooterSystem.cimShooterGearbox.transmission->SetVoltage(shooterManualSpeed);
}

/**
  * for testing the shooter
  */
void Shooter::testing(double dt) {

  shooterTestingSpeed = fabs(_contGroup.Get(ControlMap::ShooterManualSpin)) > ControlMap::TriggerDeadzone ? _contGroup.Get(ControlMap::ShooterManualSpin) : 0;

  // _shooterSystem.cimShooterGearbox.transmission->SetVoltage(shooterTestingSpeed);

  _shooterSystem.leftFlyWheelMotor.Set(shooterTestingSpeed);
  _shooterSystem.rightFlyWheelMotor.Set(shooterTestingSpeed);


  // std::cout << shooterManualSpeed << std::endl;
  // std::cout << _leftFlyWheelMotor.GetEncoder()->GetEncoderAngularVelocity() << std::endl;
  // std::cout << _rightFlyWheelMotor.encoder->GetEncoderAngularVelocity() << std::endl;

  nt::NetworkTableInstance::GetDefault().GetTable("RobotValue")->GetSubTable("Shooter")->GetEntry("Angular velocity").SetDouble(0.6);
}