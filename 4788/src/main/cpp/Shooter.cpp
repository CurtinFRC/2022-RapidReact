#include "Shooter.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {}

void Shooter::teleopOnUpdate(double dt) {
  // TODO @Anna decide which case to switch to

  switch (_teleopShooter) {
    case TeleopShooter::kAuto:
      //left bumper for close shot, right bumper for far shot, POV button 
      // if (_contGroup.Get(ControlMap::shortShoot)) {
      //   speed(8, dt);
      // }
      break;
    case TeleopShooter::kIdle:

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

  // double input = _shooterSystem._flyWheel.encoder->GetAngularVelocity();

  // ControlMap::error = ControlMap::goal - input;
  // ControlMap::derror = (ControlMap::error - ControlMap::previousError) / dt;
  // ControlMap::sum = ControlMap::sum + ControlMap::error * dt;

  // ControlMap::ouput = ControlMap::kp * ControlMap::error + ControlMap::ki * ControlMap::sum + ControlMap::kd * ControlMap::derror;
  // ControlMap::previousError = ControlMap::error;

  // return ControlMap::output;
}


/**
  * Left trigger controls the shooter manually
  */
void Shooter::manualControl(double dt) {
  shooterManualSpeed = fabs(_contGroup.Get(ControlMap::shooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::shooterManualSpin) : 0;

  _shooterSystem.shooterGearbox.transmission->SetVoltage(shooterManualSpeed);
}

/**
  * for testing the shooter
  */
void Shooter::testing(double dt) {

  shooterManualSpeed = fabs(_contGroup.Get(ControlMap::shooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::shooterManualSpin) : 0;

  // _shooterSystem.shooterGearbox.transmission->SetVoltage(shooterTestingSpeed);

  _shooterSystem.leftFlyWheelMotor.Set(shooterTestingSpeed);
  _shooterSystem.rightFlyWheelMotor.Set(shooterTestingSpeed);
  _shooterSystem.centerFlyWheelMotor.Set(shooterTestingSpeed);

  // std::cout << shooterManualSpeed << std::endl;
  // std::cout << _leftFlyWheelMotor.GetEncoder()->GetEncoderAngularVelocity() << std::endl;
  // std::cout << _rightFlyWheelMotor.encoder->GetEncoderAngularVelocity() << std::endl;

  nt::NetworkTableInstance::GetDefault().GetTable("RobotValue")->GetSubTable("Shooter")->GetEntry("Angular velocity").SetDouble(0.6);
}