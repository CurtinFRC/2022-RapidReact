#pragma once

/**
 * Local Files 
 */
#include "RobotMap.h"
#include "Shooter.h"
#include "Drivebase.h"
#include "Intake.h"
#include "Trajectories.h"
#include "Climber.h"

#include "Strategy/ShooterStrategy.h"


class Robot : public frc::TimedRobot, protected wml::StrategyController, protected wml::NTProvider, protected wml::loops::LoopSystem {
public:

  /**
   * Robot boot initilization.
   * Then robot continuous periodic (regardless of mode [teleop/auto/test etc..])
   */
  void RobotInit() override;
  void RobotPeriodic() override;

  /**
   * In it's dissabled mode, simillar to robot init/periodic. However only executes once
   * robot has been disabled at least once.
   */
  void DisabledInit() override;
  void DisabledPeriodic() override;

  /**
   * When the drivestation starts init auto mode,
   * these functions will execute, once for init. And then continuously for periodic
   */
  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  /**
   * Teleop version of auto, used for manual control
   */
  void TeleopInit() override;
  void TeleopPeriodic() override;

  /**
   * Test mode. Runs only in test mode
   */
  void TestInit() override;
  void TestPeriodic() override;

  void Update(double dt) override;

private:
  RobotMap robotMap;
  Trajectories trajectories;
  wml::Drivetrain *drivetrain;
  Shooter *shooter;
  Intake *intake;
  Climber *climber;
};
