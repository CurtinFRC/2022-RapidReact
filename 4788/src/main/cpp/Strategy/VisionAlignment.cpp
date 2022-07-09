#include <iostream>
#include <networktables/NetworkTableInstance.h>
#include "Strategy/VisionAlignment.h"
#include "ControlMap.h"

VisionAlignment::VisionAlignment(std::string name, Drivetrain &drivetrain) : wml::Strategy(name), _drivetrain(drivetrain), _drivetrainAngleStrategy("VisionAngle", drivetrain, _lastYaw){
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
}

void VisionAlignment::OnStart() {
  _drivetrainAngleStrategy.OnStart();
}

void VisionAlignment::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double xCords = _visionTable->GetEntry("targetPixelsX").GetDouble(0); 
  double yCords = _visionTable->GetEntry("targetPixelsY").GetDouble(0);
  double yawCords = _visionTable->GetEntry("targetYaw").GetDouble(0);

  if (std::abs(yawCords - _lastYaw) > 0.005)
    _drivetrainAngleStrategy.SetGoal(yawCords);

  _drivetrainAngleStrategy.OnUpdate(dt);

  if (_drivetrainAngleStrategy.IsFinished())
    SetDone();

  _lastYaw = yawCords;
}