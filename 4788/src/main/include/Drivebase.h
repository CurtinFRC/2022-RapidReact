#include "Drivebase.h"

using namespace wml;
using namespace wml::controllers;

Drivetrain::Drivetrain(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
	Requires(&drivetrain);
	SetCanBeInterrupted(true);
	SetCanBeReused(true);
}

void Drivetrain::teleopOnUpdate(double dt) {
	_leftPower = abs(_contGroup.Get(ControlMap::DrivetrainLeft)) > ControlMap::XboxDeadzone ? _contGroup.Get(ControlMap::DrivetrainLeft) : 0;
	_rightPower = abs(_contGroup.Get(ControlMap::DrivetrainRight)) > ControlMap::XboxDeadzone ? _contGroup.Get(ControlMap::DrivetrainRight) : 0;

	_leftPower *= ControlMap::MaxDrivetrainSpeed;
	_rightPower *= ControlMap::MaxDrivetrainSpeed;

	_drivetrain.Set(_leftPower, _rightPower);
}