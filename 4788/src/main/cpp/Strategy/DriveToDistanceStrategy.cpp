#include <iostream>
#include "Strategy/DriveToDistanceStrategy.h"
#include "ControlMap.h"

DriveToDistanceStrategy::DriveToDistanceStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), 
  _distancePID({ 0.8, 0.03, 0 }), _anglePID({ 0.0025, 0.001, 0 }) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);

  _heading = _drivetrain.GetConfig().gyro->GetAngle();
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  _goal = goal;
}

void DriveToDistanceStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double leftRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().leftDrive.reduction;
  double rightRotations = _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().rightDrive.reduction;
  double averageRotations = (leftRotations-rightRotations)/2;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();
  
  double wheelCirc = 2*M_PI*_drivetrain.GetConfig().wheelRadius;
  double distance = wheelCirc*averageRotations;

  double distPID = _distancePID.calculate(distance, _goal, dt);
  // double distPID = _control.getDistancePID().calculate(distance, _goal, dt);
  leftPower = distPID;
  rightPower = distPID;

  double output = _anglePID.calculate(gyro, _heading, dt);
  // double output = _control.getAnglePID().calculate(gyro, _heading, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");
  table->GetEntry("Distance").SetDouble(distance);

  leftPower += output;  // replace with anglePID
  rightPower -= output;  // replace with anglePID

  _drivetrain.Set(-leftPower, -rightPower);
}


// ----------------- Angle Strats -----------------

DrivetrainAngleStrategy::DrivetrainAngleStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), _anglePID({ 0.022, 0.0001, -0.00025 }) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);

  _goal = goal;
}

void DrivetrainAngleStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();

  double output = _anglePID.calculate(gyro, _goal, dt);
  // double output = _control.getAnglePID().calculate(gyro, _heading, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");
  table->GetEntry("Angles").SetDouble(output);
  table->GetEntry("gyro").SetDouble(gyro);


  leftPower += output;  // replace with anglePID
  rightPower -= output;  // replace with anglePID

  table->GetEntry("leftPre").SetDouble(leftPower);
  table->GetEntry("rightPre").SetDouble(rightPower);

  _drivetrain.Set(-leftPower, -rightPower);
}