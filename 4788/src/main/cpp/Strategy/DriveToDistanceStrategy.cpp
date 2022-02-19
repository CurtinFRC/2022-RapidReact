#include <iostream>
#include "Strategy/DriveToDistanceStrategy.h"
#include "ControlMap.h"

DriveToDistanceStrategy::DriveToDistanceStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), 
  _distancePID({ 0.8, 0.1, 0 }, 0.1, 0.2), _anglePID({ 0.0025, 0.001, 0 }, 3, 1) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  _distancePID.setIZone(0.25);
}

void DriveToDistanceStrategy::OnStart() {
  _heading = _drivetrain.GetConfig().gyro->GetAngle();
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
}

void DriveToDistanceStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double leftRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().leftDrive.reduction;
  double rightRotations = _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().rightDrive.reduction;
  double averageRotations = (leftRotations-rightRotations)/2;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();
  
  double wheelCirc = 2*M_PI*_drivetrain.GetConfig().wheelRadius;
  double distance = wheelCirc*averageRotations;

  _accSpeed += 0.7*dt;

  double distPID = _distancePID.calculate(distance, _goal, dt);
  // double distPID = _control.getDistancePID().calculate(distance, _goal, dt);
  distPID = std::max(-_accSpeed, std::min(_accSpeed, distPID));
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

  if (_distancePID.isDone()) {
    _drivetrain.Set(0, 0);
    SetDone();
  }
}


// ----------------- Angle Strats -----------------

DrivetrainAngleStrategy::DrivetrainAngleStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), _anglePID({ 0.012, 0.0005, -0.00000 }, 2, 0.5) {
  Requires(&drivetrain); //0.012, 0.012, -0
  SetCanBeInterrupted(true);

  _anglePID.setIZone(10);
  _anglePID.setWrap(360);
  _goal = goal;
}

void DrivetrainAngleStrategy::OnStart() {
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
}

void DrivetrainAngleStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();

  _accSpeed += 0.5*dt;
  _accSpeed = std::min(_accSpeed, 0.35);

  double output = _anglePID.calculate(gyro, _goal, dt);
  // Poor man's feedforward
  if (output > 0)
    output += 0.1;
  else
    output -= 0.1;
  // double output = _control.getAnglePID().calculate(gyro, _heading, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");
  table->GetEntry("Angles").SetDouble(output);
  table->GetEntry("gyro").SetDouble(gyro);

  output = std::max(-_accSpeed, std::min(_accSpeed, output));

  leftPower += output;  // replace with anglePID
  rightPower -= output;  // replace with anglePID

  table->GetEntry("leftPre").SetDouble(leftPower);
  table->GetEntry("rightPre").SetDouble(rightPower);

  _drivetrain.Set(-leftPower, -rightPower);

  if (_anglePID.isDone()) {
    _drivetrain.Set(0, 0);
    SetDone();
  }
}