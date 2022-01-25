#pragma once

#include "RobotMap.h";
#include "controllers/Controllers.h";

//Brings the nightmarish controller class into the scope 
using Controllers = wml::controllers::SmartControllerGroup;


//Different states for the arm (stowed or deployed)
enum class IntakeStates{
  STOWED = 0,
  DEPLOYED
};

//A class to group the gamestage variables and structs from Robotmap.h
class Intake {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);
  void teleopOnUpdate (double dt);
  void autoOnUpdate (double dt);
  void testOnUpdate (double dt);

  void setState(IntakeStates state);
 
 private:
  void _update(double dt);
  void _toggleIntake();

  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;

//variable for power
  double _power;
//sets the default to stowed
  IntakeStates _intakeState{IntakeStates::STOWED};
};