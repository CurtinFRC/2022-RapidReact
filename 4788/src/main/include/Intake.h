#pragma once

#include "RobotMap.h"
#include "controllers/Controllers.h"
#include "Util.h"


//Brings the nightmarish controller class into the scope 
using Controllers = wml::controllers::SmartControllerGroup;


enum class MagStates{
  kEmpty, //robot has no balls 
  kTransfer, //ball going from back to front of robot
  kTransfering, 
  kOne, //ball at front
  kTwo, //ball at front and back 
  kEject, //send ball to the shooter
  kManual, //sometime code bad
  kOverride
};

inline std::string mag_state_to_string(MagStates &state) {
  switch (state) {
    case MagStates::kEmpty:
      return "Empty";
    case MagStates::kManual:
      return "Manual";
    case MagStates::kOverride:
      return "Override";
    case MagStates::kOne:
      return "One";
    case MagStates::kTwo:
      return "Two";
    case MagStates::kEject:
      return "Eject";
    case MagStates::kTransfer:
      return "Transfer";
    case MagStates::kTransfering:
      return "Transferring";
  }
}


  //Different states for the arm (stowed or deployed)
enum class IntakeStates{
  kStowed,
  kDeployed
};

  //A class to group the gamestage variables and structs from Robotmap.h
class Intake : public wml::StrategySystem, public wml::loops::LoopSystem {
 public:
  Intake(RobotMap::IntakeSystem &intakeSystem, Controllers &contGroup);

  void updateIntake(double dt);

  void Update(double dt);
  void setIndex(double voltage);

  void setIntakeState(IntakeStates intakeState);
  void setIntake(double intakeVoltage);

  void setMagState(MagStates magState);

  bool _frontSensor();
  bool _backSensor();

  void fireBall();

  void ejectBall(bool readyFire); //runs checks then sets to eject state

  void manualSetIntake(double power);
  void manualSetIndex(double power);

  bool isIdle();

  void GetOut();

  IntakeStates _intakeState{ IntakeStates::kStowed };
  MagStates _magState{ MagStates::kEmpty };
 private:
  RobotMap::IntakeSystem &_intakeSystem;
  Controllers &_contGroup;

  Debounce ejectDebounce{0.1};
  Debounce transferSensorDebounce{0.03};
  Debounce transferDebounce{2};

  //variable for power
  double _power;
  double _indexVoltage = 0;
  double _intakeVoltage = 0;


  double _indexSetVoltage = 0;
  double _intakeSetVoltage = 0;
  double _intakeSetVoltageSet = 0;

  double _testingManualIndex = 0;
  double _testingManualIntake = 0;
  double intakeSetPower = 0;
};