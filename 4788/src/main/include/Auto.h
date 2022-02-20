#pragma once

#include "strategy/Strategy.h"
#include "Drivetrain.h"
#include "Intake.h"
#include "Shooter.h"

class Auto {
 public:
  std::shared_ptr<wml::Strategy> FiveBallTerminal(wml::Drivetrain &drivetrain, Intake &intake, Shooter &shooter);
};

