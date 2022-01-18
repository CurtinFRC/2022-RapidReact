#pragma once

#include <iostream>
#include "controllers/Controllers.h"
#include "RobotMap.h"

class Drivebase {
  public:
    Drivebase();

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
    
};