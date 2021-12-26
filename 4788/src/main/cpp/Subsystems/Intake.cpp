#include "Subsystems/Intake.h"

using namespace wml;
using namespace wml::controllers;

Intake::Intake(wml::TalonSrx &intakeMotor, wml::actuators::DoubleSolenoid &intakeSolenoid) : _intakeMotor(intakeMotor), _intakeSolenoid(intakeSolenoid) {}

void Intake::TeleopOnUpdate(double dt) {

}

void Intake::AutoOnUpdate(double dt) {

}

void Intake::TestOnUpdate(double dt) {

}