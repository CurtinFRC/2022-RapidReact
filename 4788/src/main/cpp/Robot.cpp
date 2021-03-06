#include "Robot.h"
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "Strategy/DriveToDistanceStrategy.h"

using namespace frc;
using namespace wml;

double currentTimeStamp;
double lastTimeStamp;
double dt;

template<typename Terminator>
void t2000(Terminator terminate) {
  std::cout << terminate << " Target Acquired" << std::endl;
}

// General Robot Logic
void Robot::RobotInit() {
  //Init the controllers
  ControlMap::InitSmartControllerGroup(robotMap.contGroup);

  auto camera = CameraServer::GetInstance()->StartAutomaticCapture(0);
  camera.SetFPS(30);
  camera.SetResolution(160, 120);

  shooter = new Shooter(robotMap.shooterSystem, robotMap.contGroup);
  shooter->SetDefault(std::make_shared<ShooterManualStrategy>("Shooter teleop strategy", *shooter, robotMap.contGroup));

  robotMap.shooterSystem.shooterGearbox.transmission->SetInverted(true);
  shooter->StartLoop(100);

  intake = new Intake(robotMap.intakeSystem, robotMap.contGroup);
  intake->SetDefault(std::make_shared<IntakeStrategy>("Intake teleop strategy", *intake, *shooter,robotMap.contGroup));
  intake->StartLoop(100);
  robotMap.intakeSystem.intake.SetInverted(true);
  robotMap.intakeSystem.indexWheel.SetInverted(true);
  
  climber = new Climber(robotMap.climberSystem, robotMap.contGroup);
  climber->SetDefault(std::make_shared<ClimberStrategy>("climber manual strategy", *climber, robotMap.contGroup));
  climber->StartLoop(100);

  drivetrain = new Drivetrain(robotMap.drivebaseSystem.drivetrainConfig, robotMap.drivebaseSystem.gainsVelocity);

  // Zero the Encoders
  robotMap.drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.drivebaseSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  robotMap.drivebaseSystem.leftMotor.SetUpdateRate(200);
  robotMap.drivebaseSystem.rightMotor.SetUpdateRate(200);
  // robotMap.drivebaseSystem.gyro
  
  // Set the default strategy for drivetrain to manual
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
  drivetrain->StartLoop(100);

  //Invert one side of our drivetrain so it'll drive straight
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // Register our systems to be called via strategy
  StrategyController::Register(climber);
  StrategyController::Register(drivetrain);
  StrategyController::Register(shooter);
  StrategyController::Register(intake);
  NTProvider::Register(drivetrain);

  trajectories.build();

  StartLoop(100);
}

void Robot::Update(double dt) {
  StrategyController::Update(dt);
}

void Robot::RobotPeriodic() {
  currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
  dt = currentTimeStamp - lastTimeStamp;

  // t2000("<Anna>");

  // StrategyController::Update(dt);
  // shooter->update(dt);
  // robotMap.controlSystem.compressor.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  // robotMap.controlSystem.compressor.Update(dt);
  auto table = nt::NetworkTableInstance::GetDefault().GetTable("Robot Data");
  auto dt_strat = drivetrain->GetActiveStrategy();
  if (dt_strat)
    table->GetEntry("Drivetrain Strategy").SetString(dt_strat->GetStrategyName());
  else
    table->GetEntry("Drivetrain Strategy").SetString("<none>");

  auto in_strat = intake->GetActiveStrategy();
  if (in_strat)
    table->GetEntry("Intake Strategy").SetString(in_strat->GetStrategyName());
  else
    table->GetEntry("Intake Strategy").SetString("<none>");

  auto sh_strat = shooter->GetActiveStrategy();
  if (sh_strat)
    table->GetEntry("Shooter Strategy").SetString(sh_strat->GetStrategyName());
  else
    table->GetEntry("Shooter Strategy").SetString("<none>");

  NTProvider::Update();

  

  table->GetEntry("Gyro").SetDouble(drivetrain->GetConfig().gyro->GetAngle());

  lastTimeStamp = currentTimeStamp;
}

// Disabled Logic
void Robot::DisabledInit() {
  InterruptAll(true);
}
void Robot::DisabledPeriodic() {
  // Schedule(std::make_shared<ClimberDisableStrategy>("climber disable strategy", *climber));
}


// Auto Robot Logic
void Robot::AutonomousInit() {
  drivetrain->GetConfig().gyro->Reset();
  // auto testStrat = std::make_shared<DrivetrainTrajectoryStrategy>("testStrat", *drivetrain, trajectories.test);
  // auto testStrat = std::make_shared<DriveToDistanceStrategy>("testStrat", *drivetrain, 1);
  // auto testStrat = std::make_shared<DrivetrainAngleStrategy>("testStrat", *drivetrain, 90.0);

  bool success = Schedule(_auto.FiveBallTerminal(*drivetrain, *intake, *shooter));

  std::cout << "TEST " << success << std::endl;
}
void Robot::AutonomousPeriodic() {
}

// Manual Robot Logic
void Robot::TeleopInit() {
  outToggle = false;
  Schedule(drivetrain->GetDefaultStrategy(), true);
  Schedule(shooter->GetDefaultStrategy(), true);
  Schedule(intake->GetDefaultStrategy(), true);
  Schedule(climber->GetDefaultStrategy(), true);
}
void Robot::TeleopPeriodic() {
  // climber->updateClimber(dt);

  // if (robotMap.contGroup.Get(ControlMap::climberActuate)) {
  //   climberToggle = false;
  // } else {
  //   climberToggle = true;
  // }

  // if (climberToggle) {
  //   robotMap.climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);

  // } else {
  //   robotMap.climberSystem.climberSolenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  // }


  if (robotMap.contGroup.Get(ControlMap::GetOut, wml::controllers::XboxController::ONRISE)) {
    if (outToggle) {
      outToggle = false;
    } else {
      outToggle = true;
    }
  }

  if (outToggle) {
    Schedule(std::make_shared<GetOutStrategy>("EJECT ALL FROM INTAKE, MAG, SHOOT",  *intake, *shooter, robotMap.contGroup));
  }


  // if (frc::DriverStation::GetMatchTime() < 1) {
  //   Schedule(std::make_shared<ClimberDisableStrategy>("Climber Disabled (Auto Stow)", *climber));
  // }
}

// During Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {}