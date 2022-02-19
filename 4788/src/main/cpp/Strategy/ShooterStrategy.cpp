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
    _shooter.setPID(ControlMap::Shooter::innerCircleShootValue, dt);
  } else if (_contGroup.Get(ControlMap::outerCircleShoot)) {
    _shooter.setPID(ControlMap::Shooter::outerCircleShootValue, dt);
  } else if (_contGroup.Get(ControlMap::shooterEject)) {
    _shooter.setManual(-ControlMap::Shooter::shooterEjectPower);
  } else if (_contGroup.Get(ControlMap::farShoot)) {
    _shooter.setPID(ControlMap::Shooter::farShootValue, dt);
  } else if (_contGroup.Get(ControlMap::noahShoot)) {
    _shooter.setPID(ControlMap::Shooter::noahShootValue, dt);
  } else if (_contGroup.Get(ControlMap::GetOutBoogalloo)) {
    _shooter.setManual(-1 * 12);
  } else {
    // auto &motor = _shooter._shooterSystem.shooterGearbox.motor;
    _shooter.setManual(manualFlyWheelPower * 12);
  }
}

ShooterSpinUpStrategy::ShooterSpinUpStrategy(std::string name, Shooter &shooter, double angularVelocity) : Strategy(name), _shooter(shooter), _angularVelocity(angularVelocity) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  SetPassive(true);
  Requires(&shooter);
}


void ShooterSpinUpStrategy::OnUpdate(double dt) {
  _shooter.setPID(_angularVelocity, dt);
}

ShooterShootStrategy::ShooterShootStrategy(std::string name, Shooter &shooter, Intake &intake, double angularVelocity) : Strategy(name), _shooter(shooter), _intake(intake), _angularVelocity(angularVelocity) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
  Requires(&shooter);
  // SetTimeout(4);
}

void ShooterShootStrategy::OnUpdate(double dt) {
  _shooter.setPID(_angularVelocity, dt);
  if (emptyDB.Get(_intake._magState == MagStates::kEmpty)) {
    SetDone();
  } else if (db.Get(_shooter.isDone() && _intake.isIdle())) {
    _intake.fireBall();
  }

  // if (_shooter.isDone()) {
  //   if (_twoBall) {
  //     if (autoShooterIterations < 2) {
  //       _intake.fireBall();
  //       autoShooterIterations ++;
  //     } else {
  //       SetDone();
  //     }
  //   } else {
  //     if (autoShooterIterations < 1) {
  //       _intake.fireBall();
  //     } else {
  //       SetDone();
  //     }
  //   }
  // }
}