#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

class Drivebase {
  public:
    Drivebase(RobotMap::DrivebaseSystem &drivebaseSystem, SmartControllerGroup &contGroup);

    /*
     * Teleop Function
     */
    void teleopOnUpdate(double dt);
    
    /*
     * Auto Function
     */
    void autoOnUpdate(double dt);

    /*
     * Test Function
     */
    void testOnUpdate(double dt);

  private:
    RobotMap::DrivebaseSystem &_drivebaseSystem;
    wml::controllers::SmartControllerGroup &_contGroup;
};