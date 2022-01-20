// #include "Drivebase.h"

// using namespace wml;
// using namespace wml::controllers;

// DrivebaseManual::DrivebaseManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
//   Requires(&drivetrain);
//   SetCanBeInterrupted(true);
//   SetCanBeReused(true);
// };

// void DrivebaseManual::OnUpdate(double dt) {
//   if(fabs(_contGroup.Get(ControlMap::drivebaseL) >= ControlMap::XboxDeadzone)) {
//     _leftPower = _contGroup.Get(ControlMap::drivebaseL);
//   }

//   if(fabs(_contGroup.Get(ControlMap::drivebaseR)) >= ControlMap::XboxDeadzone) {
//     _rightPower = _contGroup.Get(ControlMap::drivebaseR);
//   }

//   _drivetrain.Set(_leftPower, _rightPower);
// }