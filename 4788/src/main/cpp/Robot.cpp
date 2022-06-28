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
  shooter->SetDefault(std::make_shared<ShooterManualStrategy>("Shooter strategy", *shooter, robotMap.contGroup));

  robotMap.shooterSystem.shooterGearbox.transmission->SetInverted(true);
  shooter->StartLoop(100);

  intake = new Intake(robotMap.intakeSystem, robotMap.contGroup);
  intake->SetDefault(std::make_shared<IntakeStrategy>("Intake strategy", *intake, *shooter,robotMap.contGroup));
  intake->StartLoop(100);
  robotMap.intakeSystem.intake.SetInverted(true);
  robotMap.intakeSystem.indexWheel.SetInverted(true);
  
  climber = new Climber(robotMap.climberSystem, robotMap.contGroup);
  climber->SetDefault(std::make_shared<ClimberStrategy>("climber manual strategy", *climber, robotMap.contGroup));
  StrategyController::Register(climber);
  climber->StartLoop(100);

  drivetrain = new Drivetrain(robotMap.drivebaseSystem.drivetrainConfig, robotMap.drivebaseSystem.gainsVelocity);

  // Zero the Encoders
  robotMap.drivebaseSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.drivebaseSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  robotMap.drivebaseSystem.leftMotor.SetUpdateRate(200);
  robotMap.drivebaseSystem.rightMotor.SetUpdateRate(200);
  
  // Set the default strategy for drivetrain to manual
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
  drivetrain->StartLoop(100);

  //Invert one side of our drivetrain so it'll drive straight
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // Register our systems to be called via strategy
  StrategyController::Register(drivetrain);
  StrategyController::Register(shooter);
  StrategyController::Register(intake);
  NTProvider::Register(drivetrain);

  trajectories.build();

  StartLoop(50);
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

  table->GetEntry("Gyro").SetDouble(drivetrain->GetConfig().gyro->GetAngle());

  auto visionTable = nt::NetworkTableInstance::GetDefault().GetTable("photonvision/visionCam");  // check this
  double xCords = visionTable->GetEntry("targetPixelsX").GetDouble(0); 
  double yCords = visionTable->GetEntry("targetPixelsY").GetDouble(0);
  double yawCords = visionTable->GetEntry("targetYaw").GetDouble(0);

  NTProvider::Update();
  lastTimeStamp = currentTimeStamp;
}

// Disabled Logic
void Robot::DisabledInit() {
  InterruptAll(true);
}
void Robot::DisabledPeriodic() {
  Schedule(std::make_shared<ClimberDisableStrategy>("climber disable strategy", *climber));
}


// Auto Robot Logic
void Robot::AutonomousInit() {
  drivetrain->GetConfig().gyro->Reset();
  // auto testStrat = std::make_shared<DrivetrainTrajectoryStrategy>("testStrat", *drivetrain, trajectories.test);
  // auto testStrat = std::make_shared<DriveToDistanceStrategy>("testStrat", *drivetrain, 1);
  // auto testStrat = std::make_shared<DrivetrainAngleStrategy>("testStrat", *drivetrain, 90.0);

  bool success = Schedule(_auto.Vision(*drivetrain));

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
  climber->updateClimber(dt);


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

}

// During Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {}