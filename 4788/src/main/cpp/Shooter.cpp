// #include "Shooter.h"
// #include <iostream>
// #include "frc/RobotController.h"

// using namespace wml;
// using namespace wml::controllers;

// Shooter::Shooter(RobotMap::ShooterSystem &shooterSystem, SmartControllerGroup &contGroup) : _shooterSystem(shooterSystem), _contGroup(contGroup) {}

// void Shooter::setManual(double voltage) {
//   _flyWheelVoltage = voltage;
//   _state = ShooterState::kManual;
// }

// void Shooter::setIndex(double voltage) {
//   _setIndexVoltage = voltage;
// }

// void Shooter::setPID(double goal, double dt) {
//   _state = ShooterState::kPID;
//   _angularVelocityGoal = goal;
// }

// void Shooter::updateShooter(double dt) {


//   switch (_state) {
//   case ShooterState::kManual:
//     _shooterSystem.shooterGearbox.transmission->SetVoltage(_flyWheelVoltage * 12);

//     _shooterSystem.indexWheel.Set(_setIndexVoltage);

//     break;

//   case ShooterState::kIdle:

//     _shooterSystem.indexWheel.Set(_setIndexVoltage);
//     _shooterSystem.shooterGearbox.transmission->SetVoltage(0);

//     break;

//   case ShooterState::kPID:
//     _flyWheelVoltage = calculatePID(_angularVelocityGoal, dt);
//     _shooterSystem.indexWheel.Set(_setIndexVoltage);

//     _shooterSystem.shooterGearbox.transmission->SetVoltage(_flyWheelVoltage * 12);
//     std::cout << "shooter speed" << _shooterSystem.rightFlyWheelMotor.GetEncoderAngularVelocity() << std::endl; 
//     break;

//   default:
//     _state = ShooterState::kIdle;
//     std::cout << "in default case, somthing is wrong" << std::endl;
//     break;
//   }
// }

// void Shooter::update(double dt) {
//   updateShooter(dt);
// }


// double Shooter::calculatePID(double angularVelocity, double dt) {
//   double input = (_shooterSystem.leftFlyWheelMotor.GetEncoderAngularVelocity());
//   std::cout << "angular velocity" << input << std::endl;
//   double error = _angularVelocityGoal - input;
//   double derror = (error - _previousError) / dt;
//   _sum += error * dt;

//   double output = ControlMap::ShooterGains::kp * error + ControlMap::ShooterGains::ki * _sum + (ControlMap::ShooterGains::kd) * derror;
//   std::cout << "P Value: " << ControlMap::ShooterGains::kp << std::endl;

//   auto &motor = _shooterSystem.shooterGearbox.motor;
//   double Vmax = ControlMap::ShooterGains::IMax * motor.R() + motor.kw() * input;
//   double Vmin = -(ControlMap::ShooterGains::IMax) * motor.R() + motor.kw() * input;

//   output = std::min(std::max(output, Vmin), Vmax);

//   _previousError = error;

//   std::cout << "error: " << error << std::endl;
//   std::cout << "Output: " << output*12 << std::endl;
//   // std::cout << "DT: " << dt << std::endl;
//   return output;
// }
