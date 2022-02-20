#include "Auto.h"
#include <strategy/StrategyBuilder.h>
#include <strategy/StrategyController.h>
#include "Strategy/DrivetrainTrajectoryStrategy.h"
#include "Strategy/DriveToDistanceStrategy.h"
#include "Strategy/IntakeStrategy.h"
#include "Strategy/ShooterStrategy.h"

std::shared_ptr<wml::Strategy> Auto::FiveBallTerminal(wml::Drivetrain &drivetrain, Intake &intake, Shooter &shooter) {
  auto autoStrat = wml::StrategyBuilder{}.Start() //TODO set timeout to last intake in case of shoddy HP
    ->Add(std::make_shared<IntakeAutoStrategy>("Intake to ball 1", intake, true))
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 1", drivetrain, 1.6))
    // ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    ->Add(std::make_shared<DriveToAngleRoughStrategy>("Rough turn to hub", drivetrain, 30))
    // ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 11)) 
    // ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    // ->Add(std::make_shared<ShooterShootStrategy>("shoot first 2 balls", shooter, intake, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 3", drivetrain, 121.5))
    // ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("intake ball 3", intake, false))
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 2", drivetrain, 2.9744))
    // ->Add(std::make_shared<ShooterSpinUpStrategy>("spin up shooter for ball 3", shooter, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 53.5))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 265))
    ->Then()
    ->Add(std::make_shared<ShooterShootStrategy>("Shoot ball 3", shooter, intake, 265))
    ->Then()
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to ball 3", drivetrain, 84.5))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 328))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("passively turn on the intake to get 4 + 5", intake, false))
    // ->Add(std::make_shared<IntakeAutoStrategy>("intake ball 4+5", intake, true))     //this needs to have a timer override for if the HP misses or the ball doesnt get fed in correctly
    ->Add(std::make_shared<DriveToDistanceStrategy>("Move to ball 4+5", drivetrain, 3.55))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("Spin up shooter for ball 4 and 5", shooter, 328))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("passively turn on the intake to get 4 + 5", intake, false))
    ->Add(std::make_shared<DrivetrainAngleStrategy>("Turn to hub", drivetrain, 68))
    ->Add(std::make_shared<ShooterSpinUpStrategy>("shooter spin up initial", shooter, 330))
    ->Then()
    ->Add(std::make_shared<IntakeAutoStrategy>("passively turn on the intake to get 4 + 5", intake, true, true))
    ->Add(std::make_shared<ShooterShootStrategy>("shoot balls 4 and 5", shooter, intake, 328, true))
    // std::cout << "SHOOT 4 + 5 BALLS" std::endl;

    // ->Add(std::make_shared<DriveToDistanceStrategy>("drive to something", drivetrain, 8))
    // ->Add(std::make_shared<DriveToAngleRoughStrategy>("turn to rough angle", drivetrain, 30))
    // ->Then()
    // ->Add(std::make_shared<DrivetrainAngleStrategy>("shallow angle", drivetrain, 10))

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

