#include "Auto.h"
#include <strategy/StrategyBuilder.h>
#include <strategy/StrategyController.h>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "Strategy/DriveToDistanceStrategy.h"

std::shared_ptr<wml::Strategy> Auto::FiveBallTerminal(wml::Drivetrain &drivetrain) {
  auto autoStrat = wml::StrategyBuilder{}.Start()
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 1", drivetrain, 1.6))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 10.750))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 2", drivetrain, 120.25))
    ->Then()
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 2", drivetrain, 2.9744))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 125.250))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 3", drivetrain, 80.595))
    ->Then()
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 3", drivetrain, 3.3606))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 67.347))
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

