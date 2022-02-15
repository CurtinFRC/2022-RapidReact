#pragma once

#include "RobotMap.h"
#include "controllers/Controllers.h"

//Brings the nightmarish controller class into the scope 
using Controllers = wml::controllers::SmartControllerGroup;


enum class MagStates{
  kEmpty, //robot has no balls 
  kTransfer, //ball going from back to front of robot 
  kOne, //ball at front
  kTwo, //ball at front and back 
  kEject, //send ball to the shooter
  kManual, //sometime code bad
  kOverride
};

  //Different states for the arm (stowed or deployed)
enum class IntakeStates{
  kStowed,
  kIdle,
  kIntake,
  kOutake,
  kManual
};

  //A class to group the gamestage variables and structs from Robotmap.h
class Intake : public wml::StrategySystem, public wml::loops::LoopSystem {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);

  void updateIntake(double dt);

  void Update(double dt);
  void setIndex(double voltage, MagStates magState);
  void setIndex(MagStates magState);

  void setIntake(double intakeVoltage);
  void setIntakeState(IntakeStates intakeState);

  bool _frontSensor();
  bool _backSensor();

  void ejectBall(bool readyFire); //runs checks then sets to eject state

  void manualSetIntake(double power);
  void manualSetIndex(double power);

 private:

  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;

  IntakeStates _intakeState{ IntakeStates::kStowed };
  MagStates _magState{ MagStates::kEmpty };

  //variable for power
  double _power;
  double _indexVoltage = 0;
  double _indexSetVoltage = 0;
  double _intakeSetVoltage = 0;

  double _testingManualIndex = 0;
  double _testingManualIntake = 0;
  double intakeSetPower = 0;
};