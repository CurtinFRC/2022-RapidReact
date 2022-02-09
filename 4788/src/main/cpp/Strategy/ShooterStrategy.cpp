#include "Strategy/ShooterStrategy.h"
#include <iostream>

ShooterManualStrategy::ShooterManualStrategy(std::string name, Shooter &shooter, Controllers &contGroup) : Strategy(name), _shooter(shooter), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&shooter);

}

void ShooterManualStrategy::OnUpdate(double dt) {
  double manualFlyWheelPower = fabs(_contGroup.Get(ControlMap::manualFlyWheel)) > fabs(ControlMap::xboxDeadzone) ? _contGroup.Get(ControlMap::manualFlyWheel) : 0;

  if (_contGroup.Get(ControlMap::innerCircleShoot)) {
    _shooter.setAuto(200, dt);
  } else if (_contGroup.Get(ControlMap::outerCircleShoot)) {
    _shooter.setAuto(400, dt);
  } else if (_contGroup.Get(ControlMap::shooterEject)) {
    _shooter.setFlywheel(-ControlMap::shooterEjectPower);
  } else {
    _shooter.setFlywheel(manualFlyWheelPower);
  }

  double indexSpeed = fabs(_contGroup.Get(ControlMap::indexSpin)) > fabs(0.2) ? _contGroup.Get(ControlMap::indexSpin) : 0;
  _shooter.setIndex(indexSpeed);
}