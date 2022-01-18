#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

enum class TeleopElevator { kStationary = 0, kZeroing, kManual, kMoving};

/**
 * @ports all the ports of the elevator, 1 2 3.
 * @brief Small description. basbdkajsbdkasjbdkajbs
 */
class ExampleElevator {
 public:
  ExampleElevator(RobotMap::ExampleElevatorSystem &exampleElevatorSystem);

  /**
   * Teleop function
   */
  void teleopOnUpdate(double dt);

  /**
   * Auto function
   */
  void autoOnUpdate(double dt);

  /**
   * Test function
   */
  void testOnUpdate(double dt);

 private:
  RobotMap::ExampleElevatorSystem &_exampleElevatorSystem;
};