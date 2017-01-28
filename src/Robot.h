#pragma once

#include <iostream>
#include <memory>

#include "CORERobotLib.h"
#include "DriveSubsystem.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public:
    static shared_ptr<DriveSubsystem> driveSubsystem;
    Robot() {

    }
    void robotInit() {

    }

    void teleopInit() {

    }

    void teleop() {

    }
};


#ifdef __arm__
START_ROBOT_CLASS(Robot)
#else
START_SIMULATED_ROBOT_CLASS(offSeasonRobot)
#endif