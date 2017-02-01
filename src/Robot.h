#pragma once

#include <iostream>
#include <memory>

#include "CORERobotLib.h"
#include "DriveSubsystem.h"

#define CLIMB_LIMIT_SWITCH_PORT 0
#define PUNCH_SOLENOID_OPEN_PORT 1
#define PUNCH_SOLENOID_CLOSE_PORT 2
#define DRIVE_SHIFTER_A_OPEN_PORT 3
#define DRIVE_SHIFTER_A_CLOSE_PORT 4
#define DRIVE_SHIFTER_B_OPEN_PORT 5
#define DRIVE_SHIFTER_B_CLOSE_PORT 6
#define DUMP_FLAP_SOLENOID_OPEN_PORT 7
#define DUMP_FLAP_SOLENOID_CLOSE_PORT 8
#define GEAR_FLAP_SOLENOID_OPEN_PORT 7
#define GEAR_FLAP_SOLENOID_CLOSE_PORT 8
#define FR_DRIVE_MOTOR_PORT 10
#define BR_DRIVE_MOTOR_PORT 11
#define BL_DRIVE_MOTOR_PORT 12
#define FL_DRIVE_MOTOR_PORT 13
#define LIFT_MOTOR_PORT 14
#define LEFT_CLIMB_MOTOR_PORT 15
#define RIGHT_CLIMB_MOTOR_PORT 16
#define DUMP_FLAP_MOTOR_PORT 17
#define GEAR_FLAP_MOTOR_PORT 18
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
