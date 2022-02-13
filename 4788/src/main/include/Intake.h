#pragma once

#include "RobotMap.h"
#include "controllers/Controllers.h"

//Brings the nightmarish controller class into the scope 
using Controllers = wml::controllers::SmartControllerGroup;


  //Different states for the arm (stowed or deployed)
enum class IntakeStates{
  kStowed = 0,
  kDeployed
};

  //A class to group the gamestage variables and structs from Robotmap.h
class Intake : public wml::StrategySystem, public wml::loops::LoopSystem {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);

  void _toggleIntake();
  void updateIntake(double dt);
  void setIntake(double voltage);
 
 private:
  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;
  IntakeStates _intakeState{IntakeStates::kStowed};

  double _intakeSpeed = 0;
};