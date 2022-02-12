#include <iostream>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "ControlMap.h"


#ifndef M_PI
#define M_PI 3.1415926535897932386264338327
#endif

double gearboxRatio = 6.10;
double wheelSize = 0.1016;

#include "Trajectory.h"


// PID pidAngle({0.3, 0, 0});
// Trajectory trajectory{{{0,4}, {1,4}, {2,4}, {3,4}}};
// RobotControl robotControl{trajectory, {distance, gyro}, {{0.3, 0, 0}}};

DrivetrainTrajectoryStrategy::DrivetrainTrajectoryStrategy(std::string name, Drivetrain &drivetrain, ::Trajectory &trajectory) : wml::Strategy(name), _drivetrain(drivetrain), _trajectory(trajectory) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  // SetTimeout(2.5);  // stops after time
}

/**
 * Periodic Update
 */
void DrivetrainTrajectoryStrategy::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double leftRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/gearboxRatio;
  double rightRotations = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()/gearboxRatio;
  double averageRotations = (leftRotations+rightRotations)/2;
  double gyro = _drivetrain.GetConfig().gyro->GetAngle();
  
  double wheelCirc = M_PI*wheelSize;

  // Gearbox ratio 6.10:1
  // Wheel size is 4 inches -> 0.1016
  // Distance = motor rotations -> wheel rotations -> circumference
  double distance = wheelCirc*averageRotations;

  std::cout << "\ngyro: " << gyro << "\ndistance: " << distance << std::endl;

  RobotControl robotControl{_trajectory, {distance, gyro}, {{0.3, 0, 0}}};

  std::pair<double, double> output = robotControl.followSpline(dt);
  leftPower = output.first;
  rightPower = output.second;



  _drivetrain.Set(-leftPower, -rightPower);

}