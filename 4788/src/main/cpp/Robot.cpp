#include "Robot.h"

using namespace frc;
using namespace wml;

// General Robot Logic
void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}


void Robot::DisabledInit() {
	InterruptAll(true);
}
void Robot::DisabledPeriodic() {}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

// During Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {}