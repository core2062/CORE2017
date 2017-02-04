#pragma once

#include <iostream>
#include <memory>

#include "CORERobotLib.h"
#include "DriveSubsystem.h"
#include "HopperSubsystem.h"
#include "GearSubsystem.h"
#include "ClimberSubsystem.h"

/****************************************************MOTORS************************************************************/
#define FR_DRIVE_MOTOR_PORT 10
#define BR_DRIVE_MOTOR_PORT 11
#define BL_DRIVE_MOTOR_PORT 12
#define FL_DRIVE_MOTOR_PORT 13
#define HOPPER_FLAP_MOTOR_PORT 14
#define LEFT_CLIMB_MOTOR_PORT 15
#define RIGHT_CLIMB_MOTOR_PORT 16
#define DUMP_FLAP_MOTOR_PORT 17
#define GEAR_FLAP_MOTOR_PORT 18
#define LIFT_MOTOR_PORT 19

/****************************************************SOLENOIDS*********************************************************/
#define PUNCH_SOLENOID_OPEN_PORT 1
#define PUNCH_SOLENOID_CLOSE_PORT 2
#define RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT 3
#define RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT 4
#define LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT 5
#define LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT 6

/****************************************************SENSORS**********************************************************/
#define CLIMB_LIMIT_SWITCH_PORT 0

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public:
    static shared_ptr<DriveSubsystem> driveSubsystem;
    static shared_ptr<HopperSubsystem> hopperSubsystem;
    static shared_ptr<ClimberSubsystem> climberSubsystem;
    static shared_ptr<GearSubsystem> gearSubsystem;
    static shared_ptr<COREJoystick> driverJoystick;
    static shared_ptr<COREJoystick> operatorJoystick;

    Robot();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
};
