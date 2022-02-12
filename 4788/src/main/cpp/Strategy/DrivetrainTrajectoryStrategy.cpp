#include <iostream>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "ControlMap.h"


#ifndef M_PI
#define M_PI 3.1415926535897932386264338327
#endif

double gearboxRatio = 6.10;
double wheelSize = 0.1016;

#include "Trajectory.h"

double distance, gyro;


// PID pidAngle({0.3, 0, 0});
// Trajectory trajectory{{{0,4}, {1,4}, {2,4}, {3,4}}};
// RobotControl robotControl{trajectory, {distance, gyro}, {{0.3, 0, 0}}};

DrivetrainTrajectoryStrategy::DrivetrainTrajectoryStrategy(std::string name, Drivetrain &drivetrain, ::Trajectory &trajectory) : wml::Strategy(name), _drivetrain(drivetrain), _trajectory(trajectory) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
}

/**
 * Periodic Update
 */
void DrivetrainTrajectoryStrategy::OnUpdate(double dt) {
  double leftPower = 0.15, rightPower = 0.15;

  std::cout << "Test" << std::endl;

  // double leftRotations = _drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/gearboxRatio;
  // double rightRotations = _drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/gearboxRatio;
  // double averageRotations = (leftRotations+rightRotations)/2;
  // gyro = _drivebaseSystem.drivetrain.GetConfig().gyro->GetAngle();
  
  // double wheelCirc = M_PI*wheelSize;

  // // Gearbox ratio 6.10:1
  // // Wheel size is 4 inches -> 0.1016
  // // Distance = motor rotations -> wheel rotations -> circumference
  // distance = wheelCirc*averageRotations;

  // std::pair<double, double> output = robotControl.followSpline(dt);
  // leftPower = output.first;
  // rightPower = output.second;

  _drivetrain.Set(leftPower, rightPower);

}