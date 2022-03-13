#pragma once

#include "strategy/Strategy.h"
#include "Drivetrain.h"

class Auto {
 public:
  std::shared_ptr<wml::Strategy> FiveBallTerminal(wml::Drivetrain &drivetrain);
  std::shared_ptr<wml::Strategy> ThreeBallTerminal(wml::Drivetrain &drivetrain);
  std::shared_ptr<wml::Strategy> ThreeBallHanger(wml::Drivetrain &drivetrain);
  std::shared_ptr<wml::Strategy> OneTwoBallAuto(wml::Drivetrain &drivetrain);
};

