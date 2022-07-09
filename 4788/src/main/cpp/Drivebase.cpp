#include "Drivebase.h"
#include "frc/RobotController.h"

using namespace wml;
using namespace wml::controllers;

DrivetrainManual::DrivetrainManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void DrivetrainManual::OnUpdate(double dt) {
  double leftPower = fabs(_contGroup.Get(ControlMap::leftDrive)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::leftDrive) : 0;
  double rightPower = fabs(_contGroup.Get(ControlMap::rightDrive)) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::rightDrive) : 0;

  leftPower *= ControlMap::Drivetrain::maxDrivetrainPower;
  rightPower *= ControlMap::Drivetrain::maxDrivetrainPower;

  auto table = nt::NetworkTableInstance::GetDefault().GetTable("drivetrain");
  table->GetEntry("left drivetrain").SetDouble(leftPower * frc::RobotController::GetBatteryVoltage().value());
  table->GetEntry("right drivetrain").SetDouble(rightPower * frc::RobotController::GetBatteryVoltage().value());

  _drivetrain.Set(leftPower, rightPower);
}