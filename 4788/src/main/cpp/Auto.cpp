#include "Auto.h"
#include <iostream>


double rotsPerMeter = (32/16); // 0.5 rotations per meter

double motors = 0;

Spline spline {{
  {0,0},{1,0},{2,2},{3,0},{4,0}
}};

int output = 0;
SplinePoint locationOnPath = {0,0};
double leftEncVal = 0;
double rightEncVal = 0;
double avgEncVal = 0;
double totalLength = 0;

/**
 * Initializer (Updates once)
 */
void Sim::Init() {
  output = Generator::buildPath(spline);
  std::cout << "Total Length: " << spline.totalLength << std::endl;
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
  double leftPower = 0, rightPower = 0;

  leftEncVal = leftEnc.getRotations();
  rightEncVal = rightEnc.getRotations();
  avgEncVal = (leftEncVal + rightEncVal) / 2;

  double distance = avgEncVal/2;

  std::cout << "Average Encoder: " << avgEncVal << std::endl;
  std::cout << "Average Meter: " << distance << std::endl;
  std::cout << "Total Lenght: " << spline.totalLength << std::endl;

  totalLength = spline.totalLength;

  // Main follower
  if (distance < spline.totalLength) {
    float t = RobotStuff::dist2t(distance, spline);
    // std::cout << "t value: " << t << std::endl;

    leftPower = 0.1;
    rightPower = 0.1;

    double goalAngle = Splines::getSplineAngleDeg(t, spline);
    double robotAngle = World::getGyro(0);

    double angleError = (goalAngle - robotAngle) / 180;

    leftPower += angleError;
    rightPower -= angleError;
  }

  m1.set(leftPower);
  m3.set(rightPower);
  // std::cout << "Encoder Rotations: " << leftEnc.getRotations() << std::endl;
}