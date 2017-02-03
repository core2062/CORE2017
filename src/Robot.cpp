#include "Robot.h"

shared_ptr<DriveSubsystem> Robot::driveSubsystem = make_shared<DriveSubsystem>();
shared_ptr<HopperSubsystem> Robot::hopperSubsystem = make_shared<HopperSubsystem>();
shared_ptr<ClimberSubsystem> Robot::climberSubsystem = make_shared<ClimberSubsystem>();
shared_ptr<GearSubsystem> Robot::gearSubsystem = make_shared<GearSubsystem>();
shared_ptr<COREJoystick> Robot::driverJoystick = make_shared<COREJoystick>(0);
shared_ptr<COREJoystick> Robot::operatorJoystick = make_shared<COREJoystick>(1);


#ifdef __arm__
START_ROBOT_CLASS(Robot)
#else
START_SIMULATED_ROBOT_CLASS(offSeasonRobot)
#endif
