#pragma once

#include <iostream>
#include <memory>

#include "CORERobotLib.h"
#include "DriveSubsystem.h"
#include "HopperSubsystem.h"
#include "ClimberSubsystem.h"
#include "GearSubsystem.h"

using namespace CORE;
using namespace std;

/****************************************************MOTORS************************************************************/
#define FR_DRIVE_MOTOR_PORT 10
#define BR_DRIVE_MOTOR_PORT 11
#define BL_DRIVE_MOTOR_PORT 12
#define FL_DRIVE_MOTOR_PORT 13
#define HOPPER_FLAP_MOTOR_PORT 14
#define GEAR_FLAP_MOTOR_PORT 15
#define LIFT_MOTOR_PORT 16

/****************************************************SOLENOIDS*********************************************************/
#define FL_DRIVE_MOTOR_PORT 10
#define FL_DRIVE_MOTOR_PORT 10
#define FL_DRIVE_MOTOR_PORT 10
#define FL_DRIVE_MOTOR_PORT 10
#define FL_DRIVE_MOTOR_PORT 10

class Robot : public CORERobot {
public:
    static shared_ptr<DriveSubsystem> driveSubsystem;
    static shared_ptr<HopperSubsystem> hopperSubsystem;
    static shared_ptr<ClimberSubsystem> climberSubsystem;
    static shared_ptr<GearSubsystem> gearSubsystem;
    static shared_ptr<COREJoystick> driverJoystick;
    static shared_ptr<COREJoystick> operatorJoystick;

    Robot() {

    }
    void robotInit() {

    }

    void teleopInit() {

    }

    void teleop() {

    }
};
