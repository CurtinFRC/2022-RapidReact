#include <iostream>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "ControlMap.h"


#ifndef M_PI
#define M_PI 3.1415926535897932386264338327
#endif

double gearboxRatio = 6.10;
double wheelSize = 0.1016;



DrivetrainTrajectoryStrategy::DrivetrainTrajectoryStrategy(std::string name, Drivetrain &drivetrain, ::Trajectory &trajectory) : wml::Strategy(name), _drivetrain(drivetrain), _trajectory(trajectory) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().gyro->Reset();

  // SetTimeout(2.5);  // stops after time
}

/**
 * Periodic Update
 */
void DrivetrainTrajectoryStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double leftRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/gearboxRatio;
  double rightRotations = _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()/gearboxRatio;
  double averageRotations = (leftRotations-rightRotations)/2;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();
  
  double wheelCirc = M_PI*wheelSize;

  // Gearbox ratio 6.10:1
  // Wheel size is 4 inches -> 0.1016
  // Distance = motor rotations -> wheel rotations -> circumference
  double distance = wheelCirc*averageRotations;

  std::cout << "\ngyro: " << gyro << "\ndistance: " << distance << std::endl;

  RobotControl robotControl{_trajectory, {distance, gyro}, {{0.005, 0, 0}}};

  RobotControl::FollowInfo output = robotControl.followSpline(dt);
  leftPower = output.left;
  rightPower = output.right;


  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Auto stuff");

  table->GetEntry("Distance").SetDouble(distance);
  table->GetEntry("is_done").SetBoolean(output.is_done);
  table->GetEntry("goal_angle").SetDouble(output.goal_angle);
  table->GetEntry("right").SetDouble(output.right);
  table->GetEntry("left").SetDouble(output.left);


  _drivetrain.Set(-leftPower, -rightPower);
  if (output.is_done) {
    SetDone();
  }
}