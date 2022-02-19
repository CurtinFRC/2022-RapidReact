#pragma once

#include "strategy/Strategy.h"
#include "Drivetrain.h"
#include "Intake.h"
#include "Shooter.h"

// class Auto : public wml::Strategy, protected wml::StrategyController {
//  public:
//   // Auto(Drivetrain *drivetrain) : _drivetrain(drivetrain) {}
//   void FiveBallTerminal(Drivetrain *drivetrain);

//  private:
//   // Drivetrain &_drivetrain;
// };

class Auto {
 public:
  std::shared_ptr<wml::Strategy> FiveBallTerminal(wml::Drivetrain &drivetrain, Intake &intake, Shooter &shooter);
};

