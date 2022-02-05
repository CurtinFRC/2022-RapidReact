#include "Shooter.h"
#include <iostream>
#include "frc/RobotController.h"

using namespace wml;
using namespace wml::controllers;

Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {
  ControlMap::shooterPID = false;
}

void Shooter::teleopOnUpdate(double dt) {
  // TODO @Anna decide which case to switch to

  double power = 0;

  switch (_teleopShooter) {
    case TeleopShooter::kAuto:
      //left bumper for close shot, right bumper for far shot, POV button 
      
      // std::cout << "Power: " << power << std::endl;
      // if ((_contGroup.GetController(1).Get(ControlMap::ShortShoot))) {
      //   _shooterSystem.rightFlyWheelMotor.Set(power);
      //   _shooterSystem.centerFlyWheelMotor.Set(power);
      //   // set power to 0.1 till button press then PID loop
      // }
      // shooterTestingSpeed = (_contGroup.GetController(1).Get(ControlMap::ShooterManualSpin)) > ControlMap::TriggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::ShooterManualSpin) : 0;
      // _shooterSystem.leftFlyWheelMotor.Set(shooterTestingSpeed);
      // _shooterSystem.rightFlyWheelMotor.Set(shooterTestingSpeed);
      // _shooterSystem.centerFlyWheelMotor.Set(shooterTestingSpeed);

      

      if (_contGroup.GetController(1).Get(ControlMap::PIDON)) {
        ControlMap::shooterPID = true;
      }

      // std::cout << "shooterPID" << ControlMap::shooterPID << std::endl;

      if (ControlMap::shooterPID) {
        power = speed(200, dt);
        // power = 0.5;
      } else {
        // power = 0.1;
      }

      // _shooterSystem.leftFlyWheelMotor.Set(power/frc::RobotController::GetBatteryVoltage().value());
      // _shooterSystem.rightFlyWheelMotor.Set(power/frc::RobotController::GetBatteryVoltage().value());
      // _shooterSystem.centerFlyWheelMotor.Set(power/frc::RobotController::GetBatteryVoltage().value());

      _shooterSystem.shooterGearbox.transmission->SetVoltage(power);
      // _shooterSystem.shooterGearbox.transmission->SetVoltage(10);


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

  // std::cout << "Power outer scope: " << power << std::endl;
  _shooterSystem.leftFlyWheelMotor.Set(power);
}

//TODO @Anna figure out PID algorithm stuff
/**
  * Needs to be a closed loop PID system 
  * 
  */
double goal = 2;
double sum = 0;
double previousError = 0;
double previousOutput = 0;
double Shooter::speed(double metersPerSecond, double dt) {
  //radians per second 
  double input = (_shooterSystem.leftFlyWheelMotor.GetEncoderAngularVelocity());
  // std::cout << "angular velocity" << input << std::endl;
  // std::cout << "radians per second" << input << std::endl;
  double error = metersPerSecond - input;
  double derror = (error - previousError) / dt;
  sum += error * dt;

  double output = ControlMap::kp * error + ControlMap::ki * sum + ControlMap::kd * derror;

  // double deriv = (output - previousOutput) / dt;
  // if (std::fabs(deriv) > ControlMap::output_deriv_max) {
  //   output = previousOutput + ((deriv > 0) ? 1 : -1) * ControlMap::output_deriv_max * dt;
  //   std::cout << "Limit" << std::endl;
  // }

  auto &motor = _shooterSystem.shooterGearbox.motor;
  double Vmax = ControlMap::IMax * motor.R() + motor.kw() * input;
  double Vmin = -(ControlMap::IMax) * motor.R() + motor.kw() * input;

  output = std::min(std::max(output, Vmin), Vmax);
  // output = std::min(output, Vfwd);

  previousError = error;
  previousOutput = output;

  // ControlMap::output = (-(ControlMap::output)) / 10;
  // std::cout << "error: " << error << std::endl;
  // std::cout << "Output: " << output << std::endl;
  // std::cout << "DT: " << dt << std::endl;
  return output;
}


/**
  * Left trigger controls the shooter manually
  */
void Shooter::manualControl(double dt) {
  // shooterManualSpeed = fabs(_contGroup.Get(ControlMap::ShooterManualSpin)) > ControlMap::TriggerDeadzone ? _contGroup.Get(ControlMap::ShooterManualSpin) : 0;

  // _shooterSystem.shooterGearbox.transmission->SetVoltage(shooterManualSpeed);
}

/**
  * for testing the shooter
  */
void Shooter::testing(double dt) {

  // shooterTestingSpeed = (_contGroup.Get(ControlMap::ShooterManualSpin)) > ControlMap::TriggerDeadzone ? _contGroup.Get(ControlMap::ShooterManualSpin) : 0;
  // if (_contGroup.Get(ControlMap::ShooterManualSpin) > ControlMap::TriggerDeadzone) {
  //   shooterSpeed = _contGroup.Get(ControlMap::ShooterManualSpin);/
  // } else {
  //   shooterSpeed = 0;
  // }

  shooterTestingSpeed = (_contGroup.GetController(1).Get(ControlMap::ShooterManualSpin)) > ControlMap::triggerDeadzone ? _contGroup.GetController(1).Get(ControlMap::ShooterManualSpin) : 0;

  // _shooterSystem.shooterGearbox.transmission->SetVoltage(shooterTestingSpeed);

  // shooterTestingSpeed *= 0.8;

  // std::cout << shooterTestingSpeed << std::endl;

  _shooterSystem.leftFlyWheelMotor.Set(shooterTestingSpeed);
  _shooterSystem.rightFlyWheelMotor.Set(shooterTestingSpeed);
  _shooterSystem.centerFlyWheelMotor.Set(shooterTestingSpeed);

  //get the average angular velocity of all 3 motors
  double encoderValue = _shooterSystem.leftFlyWheelMotor.GetEncoderTicksPerRotation();
  double encoder = _shooterSystem.leftFlyWheelMotor.GetEncoderAngularVelocity();

  // double encoderValue = _shooterSystem.leftFlyWheelMotor.GetSensorVelocity();
  // double encoderValue = _shooterSystem.leftFlyWheelMotor.GetEncoderTicks();
  //  + _shooterSystem.rightFlyWheelMotor.GetSensorVelocity() + _shooterSystem.centerFlyWheelMotor.GetSensorVelocity()) / 3;
  //  + _shooterSystem.rightFlyWheelMotor.GetAngularVelocity() + _shooterSystem.centerFlyWheelMotor.GetAngularVelocity()) / 3;

  // std::cout << "ticks per rotation: " << encoderValue << std::endl;
  // std::cout << "encoder velocity??: " << encoder/42 << std::endl;

  // std::cout << shooterManualSpeed << std::endl;
  // std::cout << _leftFlyWheelMotor.GetEncoder()->GetEncoderAngularVelocity() << std::endl;
  // std::cout << _rightFlyWheelMotor.encoder->GetEncoderAngularVelocity() << std::endl;

  // nt::NetworkTableInstance::GetDefault().GetTable("RobotValue")->GetSubTable("Shooter")->GetEntry("Angular velocity").SetDouble(0.6);
}