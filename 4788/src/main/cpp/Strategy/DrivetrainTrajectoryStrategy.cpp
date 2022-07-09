#include <iostream>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "ControlMap.h"

#ifndef M_PI
#define M_PI 3.1415926535897932386264338327
#endif

DrivetrainTrajectoryStrategy::DrivetrainTrajectoryStrategy(std::string name, Drivetrain &drivetrain, ::Trajectory &trajectory) 
  : wml::Strategy(name), _drivetrain(drivetrain), _trajectory(trajectory), _control(trajectory, PID{ PID::Gains{0.02, 0, 0}, 0.2, 1 }, PID{ PID::Gains{1, 0, 0}, 3, 0.1 }) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();

  // SetTimeout(2.5);  // stops after time
}

/**
 * Periodic Update
 */
void DrivetrainTrajectoryStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double leftRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().leftDrive.reduction;
  double rightRotations = _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()/_drivetrain.GetConfig().rightDrive.reduction;
  double averageRotations = (leftRotations-rightRotations)/2;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();
  
  double wheelCirc = 2*M_PI*_drivetrain.GetConfig().wheelRadius;
  double distance = wheelCirc*averageRotations;

  std::cout << "\ngyro: " << gyro << "\ndistance: " << distance << std::endl;

  RobotControl::FollowInfo output = _control.followSpline(dt, distance, gyro);
  leftPower = output.left;
  rightPower = output.right;

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");

  table->GetEntry("Distance").SetDouble(distance);
  table->GetEntry("is_done").SetBoolean(output.is_done);
  table->GetEntry("goal_angle").SetDouble(output.goal_angle);
  table->GetEntry("right").SetDouble(output.right);
  table->GetEntry("left").SetDouble(output.left);
  table->GetEntry("gyro").SetDouble(gyro);

  _drivetrain.Set(-leftPower, -rightPower);
  if (output.is_done) {
    SetDone();
  } else {
    table->GetEntry("gyroError").SetDouble(output.goal_angle - gyro);
  }
}