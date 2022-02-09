#include <iostream>
#include "Auto.h"
#include "ControlMap.h"

// double rotsPerMeter = (32/16); // 0.5 rotations per meter


// Splines::Spline spline {{
//   {0,0},{1,0},{2,2},{3,0},{4,0}
// }};

// int output = 0;
// Splines::SplinePoint locationOnPath = {0,0};
// double leftEncVal = 0;
// double rightEncVal = 0;
// double avgEncVal = 0;
// double totalLength = 0;

#include "Trajectory.h"

double distance, gyro;

Trajectory trajectory({distance, gyro});


/**
 * Initializer (Updates once)
 */
void Auto::Init() {
  trajectory.build();


  // output = Splines::Splines::buildPath(spline);
  // std::cout << "Total Length: " << spline.totalLength << std::endl;
}

/**
 * Periodic Update
 */
void Auto::Periodic() {
  // double leftPower = 0, rightPower = 0;

  // leftEncVal = _drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations();
  // rightEncVal = _drivebaseSystem.drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations();
  // avgEncVal = (leftEncVal + rightEncVal) / 2;

  // double distance = avgEncVal/2;

  // std::cout << "Average Encoder: " << avgEncVal << std::endl;
  // std::cout << "Average Meter: " << distance << std::endl;
  // std::cout << "Total Lenght: " << spline.totalLength << std::endl;

  // totalLength = spline.totalLength;

  // // Main follower
  // if (distance < spline.totalLength) {
  //   float t = RobotControl::dist2t(distance, spline);
  //   // std::cout << "t value: " << t << std::endl;

  //   leftPower = 0.1;
  //   rightPower = 0.1;

  //   double goalAngle = Splines::getSplineAngleDeg(t, spline);
  //   double robotAngle = _drivebaseSystem.drivetrain.GetConfig().gyro->GetAngle(); 

  //   double angleError = (goalAngle - robotAngle) / 180;

  //   leftPower += angleError;
  //   rightPower -= angleError;
  // }

  // _drivebaseSystem.drivetrain.Set(leftPower, rightPower);

}