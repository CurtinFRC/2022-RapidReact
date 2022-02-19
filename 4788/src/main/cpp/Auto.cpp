#include "Auto.h"
#include <strategy/StrategyBuilder.h>
#include <strategy/StrategyController.h>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "Strategy/DriveToDistanceStrategy.h"
#include "Strategy/IntakeStrategy.h"
#include "Strategy/ShooterStrategy.h"

std::shared_ptr<wml::Strategy> Auto::FiveBallTerminal(wml::Drivetrain &drivetrain, Intake &intake, Shooter &shooter) {
  auto autoStrat = wml::StrategyBuilder{}.Start() //set timeout to last intake in case of shoddy HP
    ->Add(std::make_shared<IntakeAutoStrategy>("Intake to ball 1", intake, true))
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 1", drivetrain, 1.6))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 260))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 7.5))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 260))
    ->Then()
    ->Add(std::make_shared<ShooterShootStrategy>("shoot first 2 balls", shooter, intake, 260))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 3", drivetrain, 124))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 260))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("intake ball 3", intake, false))
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 2", drivetrain, 2.9744))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("spin up shooter for ball 3", shooter, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 52))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    ->Add(std::make_shared<ShooterShootStrategy>("Shoot ball 3", shooter, intake, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 3", drivetrain, 80.595))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 300))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("intake ball 4+5", intake, true))
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 4+5", drivetrain, 3.5))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("Spin up shooter for ball 4 and 5", shooter, 300))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 69))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 300))
    ->Then()
    ->Add(std::make_shared<ShooterShootStrategy>("shoot balls 4 and 5", shooter, intake, 300))
    ->Build();
  return autoStrat;
};




// void someFunction() {
//   auto autoStrat = StrategyBuilder{}.Start()
//     ->Add<DriveToDistanceStrategy>("Move to Ball 1", *drivetrain, trajectory)
//     ->Add<DrivetrainAngleStrategy>("Shoot", *shooter)
//     ->Then()
//     ->Add<VisionStrat>("Align", *drivetrain, *vision)
//     ->Then()
//     ->Add<DriveTrainStrat>("Move", *drivetrain, trajectory)
//     ->Build();
  
//   Schedule(autoStart);
// }

