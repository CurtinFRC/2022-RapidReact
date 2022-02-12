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


// PID pidAngle({0.3, 0, 0});
Trajectory trajectory{{{0,4}, {1,4}, {2,4}, {3,4}}};
RobotControl robotControl{trajectory, {distance, gyro}, {{0.3, 0, 0}}};


/**
 * Initializer (Updates once)
 */
void Auto::init() {
  trajectory.build();

  // output = Splines::Splines::buildPath(spline);
  // std::cout << "Total Length: " << spline.totalLength << std::endl;
}

/**
 * Periodic Update
 */
void Auto::periodic(double dt) {
  double leftPower = 0, rightPower = 0;

  std::pair<double, double> output = robotControl.followSpline(dt);
  leftPower = output.first;
  rightPower = output.second;

  _drivebaseSystem.drivetrain.Set(leftPower, rightPower);

}