#include <iostream>
#include "Strategy/DriveToDistanceStrategy.h"
#include "ControlMap.h"

static wml::control::PIDGains &getAngleGains() {
  static wml::control::PIDGains gains{"AngleStratGains", 0.015, 0.01, 0, 0.06};
  return gains;
};

static wml::control::PIDGains &getDistanceGains() {
  static wml::control::PIDGains gains{"DistanceStratGains", 1.2, 0.4, 0, 0.06};
  return gains;
};

static wml::control::PIDGains &getDistanceAngleGains() {
  static wml::control::PIDGains gains{"DistanceAngleStratGains", 0.01, 0, 0.005, 0};
  return gains;
};

DriveToDistanceStrategy::DriveToDistanceStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), 
  _distancePID(getDistanceGains(), _goal), _anglePID(getDistanceAngleGains()) {
  
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  _distancePID.SetIZone(0.25);
  _anglePID.SetWrap(360);
  _anglePID.SetIZone(10);
  _distancePID.SetIsDoneThreshold(0.05, 0.2);
}

void DriveToDistanceStrategy::OnStart() {
  _heading = _drivetrain.GetConfig().gyro->GetAngle();
  _anglePID.SetSetpoint(_heading);
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

  double distPID = _distancePID.Calculate(distance, dt, 1.0);
  // double distPID = _control.getDistancePID().calculate(distance, _goal, dt);
  distPID = std::max(-_accSpeed, std::min(_accSpeed, distPID));
  leftPower = distPID;
  rightPower = distPID;

  double output = _anglePID.Calculate(gyro, dt, 1.0);
  // double output = _control.getAnglePID().calculate(gyro, _heading, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");
  table->GetEntry("Distance").SetDouble(distance);


  leftPower += output * 1.1;  // replace with anglePID
  rightPower -= output;  // replace with anglePID

  _drivetrain.Set(-leftPower, -rightPower);

  if (_distancePID.IsDone()) {
    _drivetrain.Set(0, 0);
    SetDone();
  }
}


// ----------------- Angle Strats -----------------


DrivetrainAngleStrategy::DrivetrainAngleStrategy(std::string name, Drivetrain &drivetrain, double goal) 
  : wml::Strategy(name), _drivetrain(drivetrain), _goal(goal), 
  // _anglePID({ 0.012, 0.0005, -0.00000 }, 2, 0.5) {
  _anglePID(getAngleGains(), goal) {
  Requires(&drivetrain); //0.012, 0.012, -0
  SetCanBeInterrupted(true);

  _anglePID.SetIZone(15);
  _anglePID.SetWrap(360);
  _anglePID.SetIsDoneThreshold(1, 0.5);
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

  // double output = _anglePID.calculate(gyro, _goal, dt);
  double output = _anglePID.Calculate(gyro, dt, 1.0);
  // Poor man's feedforward
  // if (output > 0)
  //   output += 0.1;
  // else
  //   output -= 0.1;
  // double output = _control.getAnglePID().calculate(gyro, _heading, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");
  table->GetEntry("Angles").SetDouble(output);
  table->GetEntry("gyro").SetDouble(gyro);

  output = std::max(-_accSpeed, std::min(_accSpeed, output));

  leftPower += output * 1.1;  // replace with anglePID
  rightPower -= output;  // replace with anglePID

  table->GetEntry("leftPre").SetDouble(leftPower);
  table->GetEntry("rightPre").SetDouble(rightPower);

  _drivetrain.Set(-leftPower, -rightPower);

  if (_anglePID.IsDone()) {
    _drivetrain.Set(0, 0);
    SetDone();
  }
}

DriveToAngleRoughStrategy::DriveToAngleRoughStrategy(std::string name, Drivetrain &drivetrain, double goal) : Strategy(name), _drivetrain(drivetrain), _goal(goal) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&drivetrain);
}

void DriveToAngleRoughStrategy::OnUpdate(double dt) {
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();

  double error = gyro - _goal;
  if (std::abs(error) > 5) {
    double ratio = std::signbit(error) ? -1 : 1;
    _drivetrain.Set(0.5 * ratio, -0.5 * ratio);
  } else {
    SetDone();
}

// void DrivetrainAngleStrategy::SetGoal(double newGoal) {
//   _goal = newGoal;
// }