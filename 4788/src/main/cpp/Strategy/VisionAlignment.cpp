#include <iostream>
#include <networktables/NetworkTableInstance.h>
#include "Strategy/VisionAlignment.h"
#include "ControlMap.h"

VisionAlignment::VisionAlignment(std::string name, Drivetrain &drivetrain) : wml::Strategy(name), _drivetrain(drivetrain), _targetPID({ 0, 0, 0 }, 0){
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
}

void VisionAlignment::OnStart() {

}

void VisionAlignment::OnUpdate(double dt) {
  double leftPower = 0, rightPower = 0;

  double xCords = _visionTable->GetEntry("targetPixelsX").GetDouble(0); 
  double yCords = _visionTable->GetEntry("targetPixelsY").GetDouble(0);
  double yawCords = _visionTable->GetEntry("targetYaw").GetDouble(0);

  double output = _targetPID.calculate(yawCords, 0, dt);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Vision Stuff");
  table->GetEntry("Yaw").SetDouble(yawCords);
  table->GetEntry("Distance from Goal").SetDouble(output);

  output = std::max(-_accSpeed, std::min(_accSpeed, output));

  leftPower += output;
  rightPower -= output;

  table->GetEntry("leftPre").SetDouble(leftPower);
  table->GetEntry("rightPre").SetDouble(rightPower);

  _drivetrain.Set(-leftPower, -rightPower);

  if (_targetPID.isDone())
    SetDone();

}